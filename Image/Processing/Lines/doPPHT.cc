// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Lines/doPPHT.cc"

#include "Ravl/Image/Image.hh"
#include "Ravl/Option.hh"
#include "Ravl/Image/PPHT.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/EdgeDetector.hh"
#include "Ravl/DP/Method2Proc.hh"
#include "Ravl/DP/Compose.hh"
#include "Ravl/LinePP2d.hh"

#include <time.h>
#include <stdlib.h>

extern void InitFileFormatBinStream();
extern void InitLineIO();
extern void InitEdgeIO();

using namespace RavlImageN;
using namespace RavlN;

#ifdef __sgi__
#include <stdlib.h>
static DPOPortBodyC<PCPixMappingC<Curve2dLineSegmentC> > fix_sgi_bug1;
static DPOPortC<PCPixMappingC<Curve2dLineSegmentC> > fix_sgi_bug2;
static DPIPortBodyC<DListC<EdgelC > > fix_sgi_bug3;
static DPIPortBodyC<SArray1dC<EdgelC > > fix_sgi_bug4;
#endif

DListC<LinePP2dC> LineMap2LinePP(const PCPixMappingC<Curve2dLineSegmentC> &lines) {
  DListC<LinePP2dC> ret;
  for(DLIterC<PCPixMapC<Curve2dLineSegmentC> >  it(lines);it;it++)
    ret.InsLast(LinePP2dC(it->Curve().StartPnt(),it->Curve().EndPnt()));
  return ret;
}


int doPPHT(int argc,char **argv) 
{
  // Parse options.
  
  OptionC option(argc,argv,true);
  StringC   inType = option.String("it","","Input file type. ");
  StringC   outType = option.String("ot","","Output file type. ");
  Point2dC res(option.Real("prx",0.01,"Angle resolution. "),
	       option.Real("pry",1,"Position resolution. "));
  RealT fp = option.Real("pfp",0.9999999,"False Postive threshold. ");
  RealT angRange = option.Real("pw",90,"Angle range. ");  
  RealT ptl = option.Real("ptl",-1,"Processing time limit, -ve is none.");
  
  bool useSobel = option.Boolean("sb",false,"Use sobel sampling. ");
  bool setMagSort = option.Boolean("ms",false,"Use magnitude sort. ");
  
  RealT sFract = option.Real("sf",1.4,"Search size for Sobel search");
  srand(option.Int("s",(int) time(0),"Seed random number generator.  "));  
  bool verb = option.Boolean("v",false,"Verbose. ");
  bool seq = option.Boolean("seq",false,"Process sequence. ");
  bool fullDir = option.Boolean("fd",false,"Full direction. ");
  bool doSHT = option.Boolean("sht",false,"Do SHT instread.");
  bool setupOnly = option.Boolean("so",false,"Do setup only.");
  
  RealT hystLower = option.Real("hl",10,"Edge detector, Lower hysterisis threshold. ");
  RealT hystUpper = option.Real("hu",17,"Edge detector, Upper hysterisis threshold. ");
  
  RealT cWidth = option.Real("cw",2.5,"Line corridor width in pixels ");
  IntT maxGap = option.Int("mg",5,"Maxium size of gap inline in pixels ");
  IntT minLen = option.Int("ml",3,"Minimum line length to that can be detected ");
  
  StringC inFile = option.String("","in.ppm","Input filename. ");
  StringC outFile = option.String("","lines.abs","Output filename. ");
  option.Check();
  
  PPHoughTransformC pphtProc(res,fp,angRange,ptl,useSobel,sFract,fullDir);
  
  pphtProc.SetCorridor(cWidth);
  pphtProc.SetMaxGap(maxGap);
  pphtProc.SetMinLineLength(minLen);
  pphtProc.SetMagSort(setMagSort);
  pphtProc.SetDoSHT(doSHT);
  
  // Setup edge detector.
  EdgeDetectorC edgeDet(true,hystLower,hystUpper);
  
  if(setupOnly)
    exit(0);
  
  if(seq) { // Process sequence.
    // Setup IO.

    DPIPortC<ImageC<RealT> > imgIn;
    if(!OpenISequence(imgIn,inFile,inType,verb)) {
      cerr << "Failed to open input '" << inFile << "' \n";
      return 1;
    }
    
    DPIPortC<DListC<EdgelC > > in = imgIn >> Process(edgeDet,&EdgeDetectorC::LApply);
    DPOPortC<DListC<LinePP2dC> > linesOut;
    
    if(!OpenOSequence(linesOut,outFile,outType,verb)) {
      cerr << "Failed to open output '" << outFile << "' \n";
      return 0;
    }
    
    // Do some processsing.
    
    DListC<EdgelC> inList;
    while(in.Get(inList)) {
      linesOut.Put(LineMap2LinePP(pphtProc.Apply(inList)));
    }    
  } else { // Process single frame.
    
    ImageC<RealT> img;
    if(!Load(inFile,img,inType,verb)) {
      cerr << "Failed to open input '" << inFile << "' \n";
      return 1;
    }
    if(verb)
      cerr << "Detecting edges. \n";
    
    DListC<EdgelC> input = edgeDet.LApply(img);
    
    if(verb)
      cerr << "Processing... \n";
    
    PCPixMappingC<Curve2dLineSegmentC> output = pphtProc.Apply(input);
    
    if(verb)
      cerr << "Writing data. \n";
    
    DListC<LinePP2dC> linesOut = LineMap2LinePP(output);
    if(!Save(outFile,linesOut,outType,verb)) {
      cerr << "Failed to open output '" << outFile << "' \n";
      return 1;
    }
    
  }
  
  return 0;
}

RAVL_ENTRY_POINT(doPPHT);

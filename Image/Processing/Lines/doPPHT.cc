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
//#include "Ravl/DP/ComposeSE.hh"
#include "Ravl/Image/ImageConv.hh"
//#include "Ravl/Image/GradEst.hh"
//#include "Ravl/DP/WriteGF.hh"
//#include "Ravl/Image/ImgIO.hh"
//#include "Ravl/Image/VidIO.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/IO.hh"


#include <time.h>

extern void InitFileFormatBinStream();
extern void InitLineIO();
extern void InitEdgeIO();

using namespace RavlImageN;
using namespace RavlN;

#ifndef __sgi__
static DPOPortBodyC<PCPixMappingC<Curve2dLineSegmentC> > out3;
#endif

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
  
  RealT cWidth = option.Real("cw",2.5,"Line corridor width in pixels ");
  IntT maxGap = option.Int("mg",5,"Maxium size of gap inline in pixels ");
  IntT minLen = option.Int("ml",3,"Minimum line length to that can be detected ");
  
  StringC inFile = option.String("","edges.abs","Input filename. ");
  StringC outFile = option.String("","lines.abs","Output filename. ");
  option.Check();
  
  PPHoughTransformC pphtProc(res,fp,angRange,ptl,useSobel,sFract,fullDir);
  
  pphtProc.SetCorridor(cWidth);
  pphtProc.SetMaxGap(maxGap);
  pphtProc.SetMinLineLength(minLen);
  pphtProc.SetMagSort(setMagSort);
  pphtProc.SetDoSHT(doSHT);
  
  if(setupOnly)
    exit(0);
  
  if(seq) { // Process sequence.
    // Setup IO.
    
    DPIPortC<DListC<EdgelC > > in;
    if(!OpenISequence(in,inFile,inType,verb)) {
      cerr << "Failed to open input '" << inFile << "' \n";
      return 0;
    }

    DPOPortC<PCPixMappingC<Curve2dLineSegmentC> > out;
    if(!OpenOSequence(out,outFile,outType,verb)) {
      cerr << "Failed to open output '" << outFile << "' \n";
      return 0;
    }
    
    // Do some processsing.
    
    DListC<EdgelC> inList;
    while(in.Get(inList)) {
      out.Put(pphtProc.Apply(inList));
    }    
  } else { // Process single frame.

    DListC<EdgelC> input;
    
    if(!Load(inFile,input,inType,verb)) {
      cerr << "Failed to open input '" << inFile << "' \n";
      return 1;      
    }
    if(verb)
      cerr << "Processing... \n";
    
    PCPixMappingC<Curve2dLineSegmentC> output = pphtProc.Apply(input);
    
    if(verb)
      cerr << "Writing data. \n";
    
    if(!Save(outFile,output,outType,verb)) {
      cerr << "Failed to open output '" << outFile << "' \n";
      return 1;
    }
    
  }
  
  return 0;
}

RAVL_ENTRY_POINT(doPPHT);

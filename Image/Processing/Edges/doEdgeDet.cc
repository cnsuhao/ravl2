// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc

#include "Ravl/Image/Image.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DP/Compose.hh"
#include "Ravl/DP/ThreadPipe.hh"
#include "Ravl/DP/Method2Proc.hh"
#include "Ravl/DP/Multiplex.hh"
#include "Ravl/DP/MTIOConnect.hh"

#include "Ravl/IO.hh"
#include "Ravl/Option.hh"
#include "Ravl/Image/EdgeDeriche.hh"
#include "Ravl/Image/SqrComposition.hh"
#include "Ravl/Image/Edgel.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/EdgeDetector.hh"
#include "Ravl/OS/Date.hh"

using namespace RavlN;
using namespace RavlImageN;

ImageC<RealT> SquareComp(const Tuple2C<ImageC<RealT>,ImageC<RealT> > &dat) {
  static SqrCompositionC sc;
  ImageC<RealT> out;
  sc.Apply(dat.Data1(),dat.Data2(),out);
  return out;
}

ImageC<RealT> SquareComp(const ImageC<TFVectorC<RealT,2> > &dat) {
  static SqrCompositionC sc;
  ImageC<RealT> out;
  sc.Apply(dat,out);
  return out;
}



int main(int argc,char **argv) {
    
  // Parse options.
  
  OptionC option(argc,argv,true);
  StringC   inType = option.String("it","","Input file type. ");
  StringC   outType = option.String("ot","","Output file type. ");
  bool seq = option.Boolean("seq",false,"Assume input is a sequence. ");
  bool verb = option.Boolean("v",false,"Verbose. ");
  //bool eightCon = option.Boolean("u",false,"Use eight contectivity. ");
  bool rawEdgeImg = option.Boolean("rei",false,"Show raw edge image.");
  RealT hystLower = option.Real("hl",10,"Lower hysterisis threshold. ");
  RealT hystUpper = option.Real("hu",17,"Upper hysterisis threshold. ");
  IntT threads = option.Int("th",2,"Number of threads to use in processing. ");
  StringC inFile = option.String("","in.pgm","Input filename");
  StringC outFile = option.String("","edges.abs","Output filename");
  
  option.Check();
  
  // Setup edge detector.
  EdgeDetectorC edgeDet(true,hystLower,hystUpper);
  
  EdgeDericheC edgeDeriche;
  if(!seq) { // 
    ImageC<RealT> input;
    if(!Load(inFile,input,inType,verb)) {
      cerr << "Failed to open input '" << inFile << "' \n";
      return 1;      
    }
    if(verb)
      cerr << "Processing... \n";
    
    if(rawEdgeImg) {
      ImageC<RealT> mag;
      ImageC<TFVectorC<RealT,2> > inImg;
      edgeDeriche.Apply(input,inImg);
      mag = SquareComp(inImg);
      if(!Save(outFile,mag,outType,verb)) {
	cerr << "Failed to open output '" << outFile << "' \n";
	return 1;
      }
      exit(0); // Done.
    }
    
    SArray1dC<EdgelC> output;
    edgeDet.Apply(input,output);
    
    if(verb)
      cerr << "Writing data. \n";
    
    if(!Save(outFile,output,outType,verb)) {
      cerr << "Failed to open output '" << outFile << "' \n";
      return 1;
    }
  } else {
    // Setup IO.
    
    DPIPortC<ImageC<ByteT> > in;
    if(!OpenISequence(in,inFile,inType,verb)) {
      cerr << "Failed to open input '" << inFile << "' \n";
      return 1;
    }
    //IPBWSubSampleC subSampleProc(subSampl,subSampl);
    
    if(rawEdgeImg) {
      DPOPortC<ImageC<RealT> > out;
      if(!OpenOSequence(out,outFile,outType,verb)) {
	cerr << "Failed to open output '" << outFile << "' \n";
	return 1;
      }
      
      DPEventC done = in >>= DPMultiplex(threads,DPThread(RavlImageN::ByteImageCT2DoubleImageCT >> Process(edgeDeriche,&EdgeDericheC::EdgeMagnitude))) >>= out;
      if(verb)
	cerr << "Running... \n";
      done.Wait();
      exit(0);
    }
    DPOPortC<SArray1dC<EdgelC > > out;
    if(!OpenOSequence(out,outFile,outType,verb)) {
      cerr << "Failed to open output '" << outFile << "' \n";
      return 1;
    }
    
    // Do some processing.
    
    if(verb)
      cerr << "Processing... \n";
    //subSampleProc >> 
    DPEventC done = in >>= DPMultiplex(threads,DPThread(RavlImageN::ByteImageCT2DoubleImageCT >> Process(edgeDet,&EdgeDetectorC::PApply))) >>= out;
    done.Wait();
  }
  
  if(verb)
    cerr << "Done. \n";
  return 0;
}

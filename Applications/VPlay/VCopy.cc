//////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Option.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/DP/FrameInfo.hh"

#include "Ravl/Image/SubSamp2Intl.hh"

#include "Ravl/DP/Compose.hh"
#include "Ravl/DP/MTIOConnect.hh"
#include "Ravl/DP/EventSet.hh"

#include "Ravl/DP/SequenceIO.hh"

#include "Ravl/DP/Buffer.hh"

#include "Ravl/Image/ByteYUVValue.hh"

using namespace StdDP;
using namespace DPComposeMT; // Using multi-threaded namespace.

int main(int nargs,char *args[]) 
{
  OptionC option(nargs,args,true);
  //IntT N(option.Int("nf",-1, "Max no. of frames read"));
  bool verb = option.Boolean("v",false,"Verbose mode. ");
  StringC formatIn = option.String("if","","Input format. ");
  StringC formatOut = option.String("of","","Output format. ");
  FilenameC infile = option.String("","","Input filename");
  FilenameC outfile = option.String("","","Output filename");
  bool yuvMode = option.Boolean("yuv",false,"Use yuv type. \n");
#ifndef __linux__
  pthread_setconcurrency(option.Int("cc",4,"pthread concurrentcy."));
#endif
  
  option.Check();
  
  DPEventSetC es;
  
  if(!yuvMode) {
    DPISPortC<FrameC<ImageC<ByteRGBValueC> > > vidIn;
    DPOSPortC<FrameC<ImageC<ByteRGBValueC> > > vidOut;
    
    if(!OpenISequence(vidIn,infile,formatIn,verb)) {
      cerr << "ERROR: Failed to open input '" << infile << "'\n";
      exit(1);
    }
    
    if(!OpenOSequence(vidOut,outfile,formatOut,verb)) {
      cerr << "ERROR: Failed to open output '" << infile << "'\n";
      exit(1);
    }
    
    es += vidIn >>= DPBufferC<FrameC<ImageC<ByteRGBValueC > > >(true) 
		>>= vidOut;
  
  } else {
    DPISPortC<FrameC<ImageC<ByteYUVValueC> > > vidIn;
    DPOSPortC<FrameC<ImageC<ByteYUVValueC> > > vidOut;
    
    if(!OpenISequence(vidIn,infile,formatIn,verb)) {
      cerr << "ERROR: Failed to open input '" << infile << "'\n";
      exit(1);
    }
    
    if(!OpenOSequence(vidOut,outfile,formatOut,verb)) {
      cerr << "ERROR: Failed to open output '" << infile << "'\n";
      exit(1);
    }
    
    es += vidIn >>= DPBufferC<FrameC<ImageC<ByteYUVValueC > > >(true) 
		>>= vidOut;
  }
  es.Wait();
  
  return 0;
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlVPlay
//! author="Charles Galambos"
//! userlevel=Normal
//! docentry="Ravl.Applications.Video"

//: Copy a Video sequence.
//
// This program uses the RAVL sequence handling to copy a 
// video sequence.

#include "Ravl/Option.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/DP/Compose.hh"
#include "Ravl/DP/MTIOConnect.hh"
#include "Ravl/DP/EventSet.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DP/FixedBuffer.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/OS/NetPortManager.hh"
#include "Ravl/OS/NetIPortServer.hh"
#include "Ravl/OS/NetPortFormat.hh"
#include "Ravl/OS/Date.hh"

using namespace RavlImageN;

NetPortFormatC<ImageC<ByteRGBValueC> > formatNetRGBImage;
NetPortFormatC<ImageC<ByteYUVValueC> > formatNetYUVImage;

int main(int nargs,char *args[]) 
{
  OptionC option(nargs,args,true);
  //IntT N(option.Int("nf",-1, "Max no. of frames read"));
  bool verb = option.Boolean("v",false,"Verbose mode. ");
  StringC formatIn = option.String("if","","Input format. ");
  StringC formatOut = option.String("of","","Output format. ");
  bool netExport = option.Boolean("e",false,"Export to network. ");
  IntT bufferSize = option.Int("b",10,"Buffer size.");
  StringC serverAddress = option.String("a","localhost:4046","Video server address. ");
  bool yuvMode = option.Boolean("yuv",false,"Use yuv type. ");
#ifndef __linux__
  pthread_setconcurrency(option.Int("cc",4,"pthread concurrentcy."));
#endif
  
  FilenameC infile = option.String("","","Input filename");
  FilenameC outfile = option.String("","","Output filename");
  option.Check();
  
  DPEventSetC es;
  if(netExport) {
    if(!NetPortOpen(serverAddress)) {
      if(verb)
	cout << "STATUS: Open network failed. \n" << flush;
      cerr << "Failed to open NetPortManager." << serverAddress << " \n";
      return __LINE__;
    }
  }
  
  if(!yuvMode) {
    DPISPortC<ImageC<ByteRGBValueC> > vidIn;
    DPOSPortC<ImageC<ByteRGBValueC> > vidOut;
    
    if(!OpenISequence(vidIn,infile,formatIn,verb)) {
      if(verb)
	cout << "STATUS: Open failed. \n" << flush;
      cerr << "ERROR: Failed to open input '" << infile << "'\n";
      exit(1);
    }
    
    if (!vidIn.IsGetReady()) {
      if (verb) 
	cout << "STATUS: Open failed. \n" << flush;
      exit(1);
    }

    if(netExport) {
      if(!NetExport(outfile,vidIn)) {
	cerr << "ERROR: Failed to export '" << outfile << "' \n";
	return __LINE__;
      }
      if(verb)
	cout << "STATUS: Stream ready.\n" << flush;
      while(1)
	Sleep(1000);
      return 0;
    }
    
    if(!OpenOSequence(vidOut,outfile,formatOut,verb)) {
      cerr << "ERROR: Failed to open output '" << infile << "'\n";
      exit(1);
    }
    
    if (!vidOut.IsPutReady()) {
      if (verb) 
	cout << "STATUS: Open failed. \n" << flush;
      exit(1);
    }

    if (verb)
      cout << "STATUS: Stream ready.\n" << flush;
    
    es += vidIn >>= DPFixedBufferC<ImageC<ByteRGBValueC > >(bufferSize)
		>>= vidOut;
    
  } else {
    DPISPortC<ImageC<ByteYUVValueC> > vidIn;
    DPOSPortC<ImageC<ByteYUVValueC> > vidOut;
    
    if(!OpenISequence(vidIn,infile,formatIn,verb)) {
      if(verb)
	cout << "STATUS: Open failed. \n" << flush;
      cerr << "ERROR: Failed to open input '" << infile << "'\n";
      exit(1);
    }
    
    if (!vidIn.IsGetReady()) {
      if (verb) 
	cout << "STATUS: Open failed. \n" << flush;
      exit(1);
    }

    if(netExport) {
      if(!NetExport(outfile,vidIn)) {
	cerr << "ERROR:  Failed to export '" << outfile << "' \n";
	return __LINE__;
      }
      if(verb)
	cout << "STATUS: Stream ready.\n" << flush;
      while(1)
	Sleep(1000);
      return 0;
    }
    
    if(!OpenOSequence(vidOut,outfile,formatOut,verb)) {
      cerr << "ERROR: Failed to open output '" << infile << "'\n";
      exit(1);
    }

    if (!vidOut.IsPutReady()) {
      if (verb) 
	cout << "STATUS: Open failed. \n" << flush;
      exit(1);
    }

    if(verb)
      cout << "STATUS: Stream ready.\n" << flush;
    
    es += vidIn >>= DPFixedBufferC<ImageC<ByteYUVValueC > >(bufferSize) 
		>>= vidOut;
  }
  es.Wait();
  if(verb)
    cout << "STATUS: Done.\n" << flush;
  
  return 0;
}

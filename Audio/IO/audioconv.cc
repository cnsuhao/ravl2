// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAudioIO
//! author="Charles Galambos"
//! docentry="Ravl.Audio"

#include "Ravl/IO.hh"
#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Audio/Types.hh"

using namespace RavlN;
using namespace RavlAudioN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  IntT bufSize = opt.Int("bs",512,"Buffer size. ");
  StringC idev = opt.String("","@DEVAUDIO:/dev/audio","Input  device.");
  StringC odev = opt.String("","@DEVAUDIO:/dev/audio","Output device.");
  StringC ifmt = opt.String("if","","Input format.");
  StringC ofmt = opt.String("of","","Output format.");
  bool verbose = opt.Boolean("v",false,"Verbose. ");
  RealT len    = opt.Real("l",-1,"Length of track to copy. -1=Unlimited ");
  bool stereo = opt.Boolean("s",false,"Enable stereo. ");
  opt.Check();

  if(!stereo) {
    SArray1dC<Int16T> buff(bufSize);
    
    DPIPortC<Int16T> in;
    if(!OpenISequence(in,idev,ifmt,verbose)) {
      cerr << "Failed to open input : " << idev << "\n";
      return 1;
    }
    
    DPOPortC<Int16T> out;
    if(!OpenOSequence(out,odev,ofmt,verbose)) {
      cerr << "Failed to open output : " << odev << "\n";
      return 1;
    }
    RealT sampleRate = 8000;
    if(!in.GetAttr("samplerate",sampleRate))
      cerr << "WARNING: Failed to find input sample rate. \n";
    out.SetAttr("samplerate",sampleRate);
    cerr << "Sample rate = " << sampleRate << "\n";
    RealT samples = sampleRate;
    for(;;) {
      if(in.GetArray(buff) == 0) {
	break;
      }
      if(!out.PutArray(buff)) {
	cerr << "Failed to write array of data. \n";
	break;
      }
    }
  } else {
    SArray1dC<SampleElemC<2,Int16T> > buff(bufSize);
    
    DPIPortC<SampleElemC<2,Int16T> > in;
    if(!OpenISequence(in,idev,ifmt,verbose)) {
      cerr << "Failed to open input : " << idev << "\n";
      return 1;
    }
    
    DPOPortC<SampleElemC<2,Int16T> > out;
    if(!OpenOSequence(out,odev,ofmt,verbose)) {
      cerr << "Failed to open output : " << odev << "\n";
      return 1;
    }
    RealT sampleRate = 8000;
    if(!in.GetAttr("samplerate",sampleRate))
      cerr << "WARNING: Failed to find input sample rate. \n";
    out.SetAttr("samplerate",sampleRate);
    cerr << "Sample rate = " << sampleRate << "\n";
    RealT samples = sampleRate;
    for(;;) {
      if(in.GetArray(buff) == 0) {
	break;
      }
      if(!out.PutArray(buff)) {
	cerr << "Failed to write array of data. \n";
	break;
      }
    }
  }
  
  return 0;
}

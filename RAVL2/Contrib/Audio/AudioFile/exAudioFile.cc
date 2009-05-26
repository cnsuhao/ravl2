// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAudioFile
//! author="Lee Gregory"
//! docentry="Ravl.API.Audio.IO"
//! file="Ravl/Contrib/Audio/AudioFile/exAudioFile.cc"

#include "Ravl/IO.hh"
#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Audio/Types.hh"
#include "Ravl/DP/AttributeType.hh"
using namespace RavlN;
using namespace RavlAudioN ; 

// This example reads from a wav file and outputs to a sound device.
// This example needs to be linked against RavlDevAudio as well as RavlAudioFile.


int main(int nargs,char **argv) {
  
  // get some options
  OptionC opt(nargs,argv);
  StringC idev = opt.String("i","test.wav","Input  device.");
  StringC odev = opt.String("o","@DEVAUDIO:/dev/dsp","Output device.");
  opt.Check();

  
  // open the input port 
  DPIPortC<SampleElemC<1,Int16T> > in;
  if(!OpenISequence(in,idev)) {
    cerr << "Failed to open input : " << idev << "\n";
    return 1;
  }
  
  
  // now lets setup an output port 
  DPOPortC<SampleElemC<1,Int16T> > out;
  if(!OpenOSequence(out,odev)) {
    cerr << "Failed to open output : " << odev << "\n";
    return 1;
  }
 
  
  // lets look at the attributes available 
  DListC<AttributeTypeC> attrList ; 
  in.GetAttrTypes(attrList) ; 
  cout << "\nAvailable Attributes are :\n" << attrList ; 
  
  // lets get some attributes 
  RealT sampleRate ; 
  IntT  sampleBits ; 
  in.GetAttr("samplerate", sampleRate) ; 
  in.GetAttr("samplebits", sampleBits) ; 
  cout << "\nSample rate is " << sampleRate << " and sample bits is " << sampleBits << "\n\n" ; 
    
  // now lets read data from file and play to device
  out.SetAttr("samplerate",sampleRate) ; 
  while ( true ) 
    {
      SampleElemC<1,Int16T>  sample = in.Get() ; 
      out.Put(sample) ; // play sample
    }


    
  return 0;
}

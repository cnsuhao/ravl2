// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAudioUtil

#include "Ravl/Audio/AudioFrame.hh"

namespace RavlAudioN {

  //: Construct from components.
  
  AudioFrameC::AudioFrameC(const SArray1dC<ByteT> &data,
			   IntT nchannels,
			   RealT nfreq,
			   IntT nbits)
    : audio(data),
      channels(nchannels),
      freq(nfreq),
      bits(nbits)
  {}
  
  AudioFrameC::AudioFrameC(const SArray1dC<SampleElemC<2,Int16T> > &data,RealT nfreq) 
    : stereoData(data),
      channels(2),
      freq(nfreq),
      bits(16)
  {}
  
  
}

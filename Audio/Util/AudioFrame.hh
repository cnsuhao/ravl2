// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_AUDIOFRAME_HEADER
#define RAVLAUDIO_AUDIOFRAME_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAudioUtil
//! author="Charles Galambos"
//! docentry="Ravl.Audio.Audio IO"
//! userlevel=Normal
//! date="13/07/2003"

#include "Ravl/Audio/Types.hh"
#include "Ravl/SArray1d.hh"

namespace RavlAudioN {
  
  //! userlevel=Normal
  //: Frame of audio data.
  
  class AudioFrameC {
  public:
    AudioFrameC()
      : channels(0),
	freq(0),
	bits(0)
    {}
    //: Default constructor.
    
    AudioFrameC(const SArray1dC<ByteT> &data,
		IntT nchannels,
		RealT nfreq,
		IntT nbits);
    //: Construct from components.
    
    AudioFrameC(const SArray1dC<SampleElemC<2,Int16T> > &data,RealT nfreq);
    //: Construct from components.
    
    RealT AudioFrequency() const
    { return freq; }
    //: Access frequency.
    
    IntT AudioBits() const
    { return bits; }
    //: Bits per sample.
    
    const SArray1dC<ByteT> &AudioData() const
    { return audio; }
    //: Access audio data.
    
    const SArray1dC<SampleElemC<2,Int16T> > &Stereo() const
    { return stereoData; }
    //: Get as stereo data. 
    
  protected:
    SArray1dC<ByteT> audio; // Raw audio data.
    SArray1dC<SampleElemC<2,Int16T> > stereoData; // Data in 16-bit stereo.
    IntT channels;
    RealT freq;
    IntT bits;
  };

}
#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_AVFRAME_HEADER
#define RAVLIMAGE_AVFRAME_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAV
//! author="Charles Galambos"
//! userlevel=Normal
//! docentry="Ravl.Images.Video"
//! file="Ravl/Image/AV/AVFrame.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Audio/AudioFrame.hh"
#include "Ravl/Image/ByteRGBValue.hh"

namespace RavlImageN {
  using namespace RavlAudioN;
  
  //! userlevel=Normal
  //: Audio-Video frame.
  
  class AVFrameC
  {
  public:
    AVFrameC()
    {}
    //: Default constructor.
    
    AVFrameC(const AudioFrameC &audioData,ImageC<ByteRGBValueC> &img);
    //: Constructor.

    AudioFrameC &Audio()
    { return audio; }
    //: Access audio data.
    
    const AudioFrameC &Audio() const
    { return audio; }
    //: Access audio data.
    
    ImageC<ByteRGBValueC> &Image()
    { return image; }
    //: Image. 

    const ImageC<ByteRGBValueC> &Image() const
    { return image; }
    //: Image. 
    
  protected:
    AudioFrameC audio;
    ImageC<ByteRGBValueC> image;
  };
}

#endif

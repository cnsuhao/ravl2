// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAV

#include "Ravl/AVFrame.hh"

namespace RavlImageN {

  //: Constructor.
  
  AVFrameC::AVFrameC(const AudioFrameC &audioData,ImageC<ByteRGBValueC> &img)
    : audio(audioData),
      image(img)
  {}

}

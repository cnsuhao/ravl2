// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_BLUESCREEN_HEADER
#define RAVLIMAGE_BLUESCREEN_HEADER 1
////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Images.Segmentation"
//! author="Charles Galambos"
//! lib=RavlImage

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

namespace RavlImageN {
  
  //! userlevel=Normal.
  //: Simple and fast blue screen mask generation.
  // Calculates "(2*Blue - (Red+Green)) < thresh" for each pixel
  
  class BlueScreenC {
  public:
    BlueScreenC(int nthresh = 40)
      : thresh(nthresh)
    {}
    //: Constructor.
  
    void SetThreshold(int value)
    { thresh=value; }
    //: Set the threshold used bluescreening.
    // Values should be between 0 and 512
    
    ImageC<bool> Apply(const ImageC<ByteRGBValueC> &img);
    //: Produce a background/forground mask.
    // true is assigned to forground pixels.
    
  protected:
    int thresh;
  };
  
}


#endif

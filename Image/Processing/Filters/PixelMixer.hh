// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_PIXELMIXER_HEADER 
#define RAVLIMAGE_PIXELMIXER_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Images.Warping"
//! author="Charles Galambos"
//! lib=RavlImageProc
//! date="20/07/2002"

#include "Ravl/Types.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Pixel mixer, assignement.
  
  template<class InT,class OutT>
  class PixelMixerAssignC {
  public:
    PixelMixerAssignC()
    {}
    //: Default constructor.
    
    void operator()(OutT &pixel,const InT &mixin)
    { pixel = mixin; }
    //: Mix operator
  };
  
  //! userlevel=Normal
  //: Pixel mixer, mean.
  // This updates the pixel with the mean of the two values.
  
  template<class InT,class OutT>
  class PixelMixerAverageC {
  public:
    PixelMixerAverageC()
    {}
    //: Default constructor.
    
    void operator()(OutT &pixel,const InT &mixin)
    { pixel = (mixin + pixel)/2; }
    //: Mix operator
  };
  
}



#endif 

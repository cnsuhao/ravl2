// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLUINT16RGBVALUE_HEADER
#define RAVLUINT16RGBVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/UInt16RGBValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/RGBValue.hh"

namespace RavlN {
  
  //: UInt16 RGB value class.
  
  class UInt16RGBValueC
    : public RGBValueC<UInt16T>
  {
  public:
    UInt16RGBValueC()
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.

    UInt16RGBValueC(UInt16T r,UInt16T g, UInt16T b)
      : RGBValueC<UInt16T>(r,g,b)
      {}
    //: Construct from components.

    UInt16RGBValueC(const RGBValueC<UInt16T> &oth)
      : RGBValueC<UInt16T>(oth)
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.
    
    UInt16T Y() const
      { return (UInt16T)( ((int) data[0] + (int)data[1] + (int)data[2])/3); }
    //: Calculate intensity of the pixel.
    // This returns the average of the red, green
    // and blue components.

  };
}

#endif

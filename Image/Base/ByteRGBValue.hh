// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBYTERGBVALUE_HEADER
#define RAVLBYTERGBVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ByteRGBValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/RGBValue.hh"

namespace RavlImageN {
  
  //: Byte RGB value class.
  
  class ByteRGBValueC
    : public RGBValueC<ByteT>
  {
  public:
    ByteRGBValueC()
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.
    
    ByteRGBValueC(ByteT r,ByteT g, ByteT b)
      : RGBValueC<ByteT>(r,g,b)
      {}
    //: Construct from components.
    
    ByteRGBValueC(const RGBValueC<ByteT> &oth)
      : RGBValueC<ByteT>(oth)
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.
    
    ByteT Y() const
      { return (ByteT)( ((int) data[0] + (int)data[1] + (int)data[2])/3); }
    //: Calculate intensity of the pixel.
    // This returns the average of the red, green
    // and blue components.

  };
  
}

#endif

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
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/RGBValue.hh"

namespace RavlN {
  
  //: Byte RGB value class.
  
  class ByteRGBValueC
    : public RGBValueC<ByteT>
  {
  public:
    ByteRGBValueC()
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.

    ByteRGBValueC(const RGBValueC<ByteT> &oth)
      : RGBValueC<ByteT>(oth)
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.
    
  };
  
}

#endif

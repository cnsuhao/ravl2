// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBYTERGBAVALUE_HEADER
#define RAVLBYTERGBAVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ByteRGBAValue.hh"
//! lib=RavlImage
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/RGBAValue.hh"

namespace RavlN {
  
  //: Byte RGBA value class.
  
  class ByteRGBAValueC
    : public RGBAValueC<ByteT>
  {
  public:
    ByteRGBAValueC()
      {}
    //: Default constructor.
    // creates an undefined RGBA pixel.

    ByteRGBAValueC(const RGBAValueC<ByteT> &oth)
      : RGBAValueC<ByteT>(oth)
      {}
    //: Default constructor.
    // creates an undefined RGBA pixel.
    
  };
  
}

#endif

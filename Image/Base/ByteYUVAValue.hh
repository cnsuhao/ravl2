// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBYTEYUVAVALUE_HEADER
#define RAVLBYTEYUVAVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ByteYUVAValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/YUVAValue.hh"

namespace RavlImageN {
  
  //: Byte YUVA value class.
  
  class ByteYUVAValueC
    : public YUVAValueC<ByteT>
  {
  public:
    ByteYUVAValueC()
      {}
    //: Default constructor.
    // creates an undefined YUVA pixel.
    
    ByteYUVAValueC(ByteT y,ByteT u, ByteT v,ByteT a)
      : YUVAValueC<ByteT>(y,u,v,a)
      {}
    //: Construct from components.

    ByteYUVAValueC(const YUVAValueC<ByteT> &oth)
      : YUVAValueC<ByteT>(oth)
      {}
    //: Copy constructor.
    // creates an undefined YUVA pixel.
    
  };
}

#endif

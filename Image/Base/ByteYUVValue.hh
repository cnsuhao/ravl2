// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBYTEYUVVALUE_HEADER
#define RAVLBYTEYUVVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ByteYUVValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/YUVValue.hh"

namespace RavlN {
  
  //: Byte YUV value class.
  
  class ByteYUVValueC
    : public YUVValueC<ByteT>
  {
  public:
    ByteYUVValueC()
      {}
    //: Default constructor.
    // creates an undefined YUV pixel.
    
    ByteYUVValueC(ByteT y,ByteT u, ByteT v)
      : YUVValueC<ByteT>(y,u,v)
      {}
    //: Construct from components.

    ByteYUVValueC(const YUVValueC<ByteT> &oth)
      : YUVValueC<ByteT>(oth)
      {}
    //: Copy constructor.
    // creates an undefined YUV pixel.
    
  };
  
  inline
  istream &operator>>(istream &strm,ByteYUVValueC &val) 
    { return strm >> ((TFVectorC<ByteT,3> &)(val)); }
  //: Stream input.
  
  inline
  ostream &operator<<(ostream &strm,const ByteYUVValueC &val) 
    { return strm << ((const TFVectorC<ByteT,3> &)(val)); }
  //: Stream output.

  inline  
  BinIStreamC &operator>>(BinIStreamC &strm,ByteYUVValueC &val) 
    { return strm >> ((TFVectorC<ByteT,3> &)(val)); }
  //: Binary stream input.
  
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const ByteYUVValueC &val) 
    { return strm << ((const TFVectorC<ByteT,3> &)(val)); }
  //: Binary stream output
}

#endif

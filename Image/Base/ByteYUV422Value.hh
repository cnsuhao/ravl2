// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BYTEYUV422VALUE_HEADER
#define RAVL_BYTEYUV422VALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ByteYUV422Value.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/YUV422Value.hh"
#include "Ravl/Stream.hh"

namespace RavlImageN {
  
  //: Byte YUV value class.
  
  class ByteYUV422ValueC
    : public YUV422ValueC<ByteT>
  {
  public:
    ByteYUV422ValueC()
      {}
    //: Default constructor.
    // The value is left undefined.
    
    ByteYUV422ValueC(ByteT xuv,ByteT xy)
      : YUV422ValueC<ByteT>(xuv,xy)
    {}
    //: Construct from components.
    
    template<class OCompT>
    ByteYUV422ValueC(YUV422ValueC<OCompT> &oth) {
      y = oth.Y();
      uv = oth.UV();
    }
    //: Construct from another component type.
  };
  
  inline
  istream &operator>>(istream &strm,ByteYUV422ValueC &val) { 
    int uv,y;
    // Mess about so it works on SGI.
    strm >> uv >> y;
    val.UV() = uv;
    val.Y() = y;
    return strm;
  }
  //: Stream input.
  
  inline
  ostream &operator<<(ostream &strm,const ByteYUV422ValueC &val) 
  { return strm << ((int) val.UV()) << ' ' << ((int) val.Y()); }
  //: Stream output.
  
}

#endif

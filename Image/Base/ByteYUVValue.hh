// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BYTEYUVVALUE_HEADER
#define RAVL_BYTEYUVVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ByteYUVValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/YUVValue.hh"

namespace RavlImageN {
  
  //: Byte YUV value class.
  
  class ByteYUVValueC
  {
  public:
    ByteYUVValueC()
      {}
    //: Default constructor.
    // creates an undefined YUV pixel.
    
    ByteYUVValueC(ByteT xy,SByteT xu, SByteT xv)
      : y(xy),
	u(xu),
	v(xv)
      {}
    //: Construct from components.
    
    template<class OCompT>
    ByteYUVValueC(YUVValueC<OCompT> &oth) {
      y = oth.Y();
      u = oth.U();
      v = oth.V();
    }
    //: Construct from another component type.
    
    inline const ByteT & Y() const
      { return y; }
    //: Returns the level of the Y component.
    
    inline const SByteT & U() const
      { return u; }
    //: Returns the level of the U component.
    
    inline const SByteT & V() const
      { return v; }
    //: Returns the level of the V component.
    
    inline ByteT & Y() 
      { return y; }
    //: Returns the level of the Y component.
    
    inline SByteT & U()
      { return u; }
    //: Returns the level of the U component.
    
    inline SByteT & V()
      { return v; }
    //: Returns the level of the V component.

    operator YUVValueC<RealT> () const
    { return YUVValueC<RealT>((RealT)y,(RealT)u,(RealT)v); }
    //: Convert to real values.
  protected:
    ByteT  y;
    SByteT u;
    SByteT v;

  };

  inline
  istream &operator>>(istream &strm,ByteYUVValueC &val) 
  { return strm >> val.Y() >> val.U() >> val.V(); }
  //: Stream input.
  
  inline
  ostream &operator<<(ostream &strm,const ByteYUVValueC &val) 
  { return strm << val.Y() << ' ' << val.U() << ' '  << val.V(); }
  //: Stream output.
  
#if 0
  inline
  BinIStreamC &operator>>(BinIStreamC &strm,ByteYUVValueC &val) 
  { return strm >> val.Y() >> val.U() >> val.V(); }
  //: Binary stream input.
  
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const ByteYUVValueC &val) 
  { return strm << val.Y() << val.U() << val.V(); }
  //: Binary stream output
#endif

}

#endif

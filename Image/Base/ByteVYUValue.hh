// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BYTEVYUVALUE_HEADER
#define RAVL_BYTEVYUVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ByteVYUValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/VYUValue.hh"
#include "Ravl/Stream.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Byte VYU value class.
  
  class ByteVYUValueC
  {
  public:
    ByteVYUValueC()
    {}
    //: Default constructor.
    // creates an undefined VYU pixel.
    
    ByteVYUValueC(SByteT xv,ByteT xy,SByteT xu)
      : v(xv),
	y(xy),
	u(xu)
    {}
    //: Construct from components.
    
    template<class OCompT>
    ByteVYUValueC(VYUValueC<OCompT> &oth) {
      v = oth.V();
      y = oth.Y();
      u = oth.U();
    }
    //: Construct from another component type.

    void Set(const SByteT &nv,const ByteT &ny,const SByteT &nu) {
      v =nv;
      y =ny;
      u =nu;
    }
    //: Set the values.
    
    inline const SByteT & V() const
    { return v; }
    //: Returns the level of the V component.
    
    inline const ByteT & Y() const
    { return y; }
    //: Returns the level of the Y component.
    
    inline const SByteT & U() const
    { return u; }
    //: Returns the level of the U component.
    
    
    inline SByteT & V()
    { return v; }
    //: Returns the level of the V component.
    
    inline ByteT & Y() 
    { return y; }
    //: Returns the level of the Y component.
    
    inline SByteT & U()
    { return u; }
    //: Returns the level of the U component.
    

    operator VYUValueC<RealT> () const
    { return VYUValueC<RealT>((RealT)v,(RealT)y,(RealT)u); }
    //: Convert to real values.
  protected:
    SByteT v;
    ByteT  y;
    SByteT u;
  };

  inline
  istream &operator>>(istream &strm,ByteVYUValueC &val) { 
    int u,v,y;
    strm >> v >> y >> u;
    val.V() = v; 
    val.Y() = y;
    val.U() = u;
    return strm;
  }
  //: Stream input.
  
  inline
  ostream &operator<<(ostream &strm,const ByteVYUValueC &val) 
  { return strm << ((int) val.V()) << ' ' << ((int) val.Y()) << ' ' << ((int) val.U()); }
  //: Stream output.
  
}

#endif

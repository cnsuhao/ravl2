// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BYTERGBVALUE_HEADER
#define RAVL_BYTERGBVALUE_HEADER 1
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
  using namespace RavlN;
  
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
    
    ByteRGBValueC(const RGBValueC<RealT> &vals)
      : RGBValueC<ByteT>((ByteT)vals[0],(ByteT)vals[1],(ByteT)vals[2])
    {}
    //: Convert from RealT's.
    
    ByteRGBValueC(const RGBValueC<ByteT> &oth)
      : RGBValueC<ByteT>(oth)
    {}
    //: Base class constructor.
    
    ByteRGBValueC(const TFVectorC<ByteT,3> &v)
      : RGBValueC<ByteT>(v)
    {}
    //: Base class constructor.
    
    ByteT Y() const
    { return (ByteT)( ((int) data[0] + (int)data[1] + (int)data[2])/3); }
    //: Calculate intensity of the pixel.
    // This returns the average of the red, green
    // and blue components.
    
    RGBValueC<RealT> operator*(RealT val) const {
      RGBValueC<RealT> ret;
      ret[0] = ((RealT)(*this)[0] * val);
      ret[1] = ((RealT)(*this)[1] * val);
      ret[2] = ((RealT)(*this)[2] * val);
      return ret;
    }
    //: Multiply by a real.
  };
  
  
}

#endif

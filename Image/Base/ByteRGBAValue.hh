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
    
    ByteT Y() const
      { return (ByteT)( ((int) data[0] + (int)data[1] + (int)data[2])/3); }
    //: Calculate intensity of the pixel.
    // This returns the average of the red, green
    // and blue components.
  };

  inline
  istream &operator>>(istream &strm,ByteRGBAValueC &val) 
    { return strm >> ((TFVectorC<ByteT,4> &)(val)); }
  //: Stream input.
  
  inline
  ostream &operator<<(ostream &strm,const ByteRGBAValueC &val) 
    { return strm << ((const TFVectorC<ByteT,4> &)(val)); }
  //: Stream output.

  inline  
  BinIStreamC &operator>>(BinIStreamC &strm,ByteRGBAValueC &val) 
    { return strm >> ((TFVectorC<ByteT,4> &)(val)); }
  //: Binary stream input.
  
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const ByteRGBAValueC &val) 
    { return strm << ((const TFVectorC<ByteT,4> &)(val)); }
  //: Binary stream output
  
}

#endif

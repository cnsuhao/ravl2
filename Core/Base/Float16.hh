#ifndef RAVL_FLOAT16_HEADER
#define RAVL_FLOAT16_HEADER 1
// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! docentry="Ravl.API.Core.Misc"
//! userlevel=Normal
//! file="Ravl/Core/Base/Float16.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="18/09/2008"

#include "Ravl/Types.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  //: 16 bit floating point number.
  // This has 5 exponent bits and 10 mantissa bits.
  // This is primarily intended to provide compact storage for
  // large number's of floating point values that need realtively little
  // precision.
  
  // Notes:
  // float 16, 1 sign bit,5 exponent bits,10 mantissa bits
  //                  FEDCBA9876543210
  //                  seeeeemmmmmmmmmm
  //
  // float 32, 1 sign bit,8 exponent bits,23 mantissa bits
  //  FEDCBA9876543210FEDCBA9876543210
  //  seeeeeeeemmmmmmmmmmmmmmmmmmmmmmm
  
  class Float16C {
  public:    
    Float16C()
    {}
    //: Default constructor.
    // Value is undefined
    
    Float16C(bool sign,int exp,int fraction);
    //: Build a value from its component parts.
    
    Float16C(Int16T val,bool build) 
      : m_data(val)
    {}
    //: Build a value from a short in.
    
    Float16C(signed char value);
    //: Construct from a byte
    
    Float16C(unsigned char value);
    //: Construct from a byte
    
    Float16C(unsigned int value);
    //: Construct from an unsigned int
    
    Float16C(int value);
    //: Construct from an int
    
    Float16C(float value);
    //: Construct from a float
    
    bool IsPositive() const
    { return (m_data & 0x8000) == 0; }
    //: Test if the value is positive
    
    bool IsNegative() const
    { return (m_data & 0x8000) != 0; }
    //: Test if the value is positive
    
    bool IsDenormal() const
    { return (m_data & 0x7C00) == 0x0000; }
    //: Test if number is denormal.
    
    float Float() const;
    //: convert to a 32 bit float.
    
    operator float() const
    { return Float(); }
    // Convert to a floating point number.
    
    const Int16T &V() const
    { return m_data; }
    //: Access raw data.
    
    Int16T &V()
    { return m_data; }
    //: Access raw data.

  protected:
    Int16T m_data;
  };
  
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const Float16C &value) { 
    strm << value.V(); 
    return strm;
  }
  
  inline
  BinIStreamC &operator>>(BinIStreamC &strm,Float16C &value) { 
    strm >> value.V(); 
    return strm;
  }
  
}


#endif

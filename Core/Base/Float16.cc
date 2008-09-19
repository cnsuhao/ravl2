// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/Float16.hh"
#include "Ravl/Math.hh"
#include <iostream>

namespace RavlN {
  
  //: Build a value from its component parts.
  
  Float16C::Float16C(bool sign,int exp,int fraction) 
    : m_data((sign ? 0x8000 : 0) | (((exp + 15) & 0x1f) << 10) | (exp & 0x3ff))
  {}
  
  //: Construct from a byte
  
  Float16C::Float16C(unsigned char value)
    : m_data(0)
  {
    if(value == 0)
      return;
    int hb = ILog2(value);
    //std::cerr << "Val=" << ((int) value) << " Bit=" << hb << "\n";
    m_data = (value << (10 - hb)) & 0x03ff;
    m_data |= (((hb + 15) & 0x1f) << 10);
  }

  Float16C::Float16C(signed char value)
    : m_data(0)
  {
    if(value == 0)
      return;
    if(value < 0) {
      m_data |= 0x8000;
      value *= -1;
    }
    int hb = ILog2(value);
    //std::cerr << "Val=" << ((int) value) << " Bit=" << hb << "\n";
    m_data |= (value << (10 - hb)) & 0x03ff;
    m_data |= (((hb + 15) & 0x1f) << 10);
  }
  
  //: Construct from an unsigned int
  
  Float16C::Float16C(unsigned int value)
    : m_data(0)
  {
    if(value == 0)
      return;
    int hb = ILog2(value);
    //std::cerr << "Val=" << ((int) value) << " Bit=" << hb << "\n";
    m_data = (value << (10 - hb)) & 0x03ff;
    m_data |= (((hb + 15) & 0x1f) << 10);
  }
  
  //: Construct from an int
  
  Float16C::Float16C(int value)
    : m_data(0)
  {
    if(value == 0)
      return;
    if(value < 0) {
      value *= -1;
      m_data |= 0x8000;
    }
    int hb = ILog2(value);
    //std::cerr << "Val=" << ((int) value) << " Bit=" << hb << "\n";
    int shift = 10 - hb;
    if(shift >= 0)
      m_data |= (value << shift) & 0x03ff;
    else
      m_data |= (value >> (-shift)) & 0x03ff;
    m_data |= (((hb + 15) & 0x1f) << 10);
  }

  //: Construct from a float
  
  Float16C::Float16C(float value)
  {
    union{ float _f; Int32T _u; } val;
    val._f = value;
    // Copy the sign bit.
    m_data = (val._u >> 16) & 0x8000;
    
    // Sort out exponent
    int exp = ((val._u >> 23)&0xff) - 127;
    if(exp < -14) {
      if(exp > -24) {
	int shift = (13+14-exp);
	int frac = ((val._u & 0x007fffff) | (0x0080000)) >> shift  ;
	//std::cerr << "Exp= " << exp << " Shift=" << shift << " frac=" << (frac & 0x03ff) << "\n";
	m_data |= frac & 0x03ff;
      }
      
      // FIXME:-
      // Leave as zero denormal.
      return ;
    }
    if(exp > 15) {
      // Number to big, set to infinity.
      m_data |= 0x7c00;
      return ;
    }
    m_data |= ((exp+15) & 0x3f) << 10;
    
    // Copy fraction.
    m_data |= ((val._u) >> 13) & 0x03ff;
  }

  float Float16C::Float() const {
    union{ float _f; Int32T _u; } val;
    // Put in sign bit.
    val._u = (m_data & 0x8000) << 16;
    if(IsDenormal()) {
      int frac = (m_data & 0x03ff);
      if(frac == 0) 
	return val._f;
      int hb = ILog2(frac);
      int shift = 13 + hb;
      val._u |= (frac & 0x7c00) << shift;
      val._u |= ((127-37) + shift) << 23;
      
    } else {
      val._u |= (Int32T)(m_data & 0x03ff) << 13;
      val._u |= ((Int32T)((m_data & 0x7C00)>>10) + (127-15)) << 23;
    }
    return val._f;
  }
  //: convert to a 32 bit float.

}

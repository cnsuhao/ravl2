// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLANGLE_HEADER
#define RAVLANGLE_HEADER 1
////////////////////////////////////////////////////////
//! file="Ravl/Core/Math/Angle.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.Core.Math"
//! rcsid="$Id$"
//! date="09/02/98"

#include "Ravl/StdConst.hh"
#include "Ravl/StdMath.hh"

class ostream;

namespace RavlN {

  
  //: This class is designed to deal with angles in radians.
  // It keeps the values normalised and provides arithmetic operations. <p>
  // A SMALL OBJECT
  
  class AngleC {
  public:
    inline AngleC(RealT anglerad = 0,RealT maxval = RavlConstN::pi * 2);
    //: Construct from value in radians.
    // maxval is angle to wrap around at. 
    //  for directed lines this should be 2*pi.
    //  for undirected lines is should be pi.
    
    void Restrict(RealT newMax);
    //: Restrict angle to values between 0 and newMax.
    
    inline void Normalise();
    //: Normalise the angle.
    
    inline AngleC operator- (const AngleC &val) const;
    //: Subtract angles.
    
    inline AngleC operator+ (const AngleC &val) const;
    //: Add angles.
    
    inline const AngleC &operator-= (const AngleC &val) ;
    //: Subtract angles.
    
    inline const AngleC &operator+= (const AngleC &val) ;
    //: Add angles.
    
    inline RealT Diff(const AngleC &val) const;
    //: Find the difference between two angles.
    // it returns values in the rangle +/- max/2.
    
    inline RealT MaxAngle() const { return max; };
    //: Get maximum angle.
    
    inline RealT Value() const { return angle; }
    //: Get value of angle.
    
    inline RealT Sin() const { return RavlN::Sin(angle); }
    //: Get sin of angle.
    
    inline RealT Cos() const { return RavlN::Cos(angle); }
    //: Get cos of angle.
    
    void Dump(ostream &out);
    //: Dump to stream.
  protected:
    RealT angle;
    RealT max;
  };
  
  /////////////////////////////////////////////
  
  inline 
  void AngleC::Normalise() {
    angle -= Floor(angle/max) * max;
  }
  
  inline 
  AngleC::AngleC(RealT anglerad,RealT maxval) 
    : angle(anglerad),
      max(maxval)
  { Normalise(); }
  
  inline
  void AngleC::Restrict(RealT newMax) {
    max = newMax;
    Normalise();
  }
  
  inline 
  AngleC AngleC::operator- (const AngleC &val) const {
    return AngleC(angle - val.angle,max);
  }
  
  inline 
  AngleC AngleC::operator+ (const AngleC &val) const {
    return AngleC(angle + val.angle,max);
  }
  
  inline 
  RealT AngleC::Diff(const AngleC &val) const {
    RealT ret = angle - val.angle;
    RealT maxb2 = max / 2;
    if(ret > maxb2)
      ret -= max;
    else {
      if(ret < -maxb2)
	ret += max;
    }
    return ret;
  }
  
  inline 
  const AngleC &AngleC::operator-= (const AngleC &val) {
    angle -= val.angle;
    Normalise();
    return *this;
  }
  
  inline
  const AngleC &AngleC::operator+= (const AngleC &val) {
    angle += val.angle;
    Normalise();
    return *this;
  }
}


#endif

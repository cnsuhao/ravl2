// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_VECTOR2D_HEADER
#define RAVL_VECTOR2D_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/FixedSize/Vector2d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! docentry="Ravl.Math.Geometry.2D"
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/FVector.hh"

namespace RavlN {
  
  //: 2D Vector
  
  class Vector2dC
    : public FVectorC<2>
  {
  public:
    Vector2dC()
      {}
    //: Default constructor.
    
    Vector2dC(const TFVectorC<RealT,2> &base)
      : FVectorC<2>(base)
      {}
    //: Base onstructor.
    
    Vector2dC(RealT v1,RealT v2) { 
      data[0] = v1;
      data[1] = v2;
    }
    //: Constructor.
    
    RealT &X()
      { return data[0]; }
    //: First component of vector.

    RealT X() const
      { return data[0]; }
    //: First component of vector.

    RealT &Y()
      { return data[1]; }
    //: Second component of vector.

    RealT Y() const
      { return data[1]; }
    //: Second component of vector.
    
    Vector2dC Perpendicular() const
    { return Vector2dC(-Y(),X()); }
    //: Get a vector perpendicular to this one.

    RealT Dot(const Vector2dC & vector) const
    { return X() * vector.X() + Y() * vector.Y(); }
    //: Return the dot product
    
    RealT Cross(const Vector2dC & vector) const
    { return X() * vector.Y() - Y() * vector.X(); }
    //: Returns the third coordinate of the cross product of this vector
    //: and the vector 'v'.

    RealT SqrNorm() const
    { return Dot(*this); }
    //: Returns the square of the norm.
  
    RealT Norm() const
    { return Sqrt(SqrNorm()); }
    //: Returns the Euclidian size of the vector.

    RealT Modulus() const
    { return Norm(); }  
    //: Returns the Euclidian size of the vector.


    RealT Angle() const
    { return atan2(Y(), X()); }
    //: Returns the oriented angle (rad) from the axes x in
    //: the  range -PI to PI.
  };
  
  inline RealT TFVectorC<RealT,2>::Dot(const TFVectorC<RealT,2> &oth) const 
  { return data[0] * oth.data[0] + data[1] * oth.data[1]; }
  //: Calculate the dot product of this and 'oth' vector.

  inline 
  void Mul(const TFVectorC<RealT,2> &vec,RealT val,TFVectorC<RealT,2> &result) {
    result[0] = vec[0] * val;
    result[1] = vec[1] * val;
  }
  //: Multiply a vector my a constant.
  
  inline
  Vector2dC Angle2Vector2d(RealT angle) 
  { return Vector2dC(Sin(angle),Cos(angle)); }
  //: Convert an angle to a unit vector in that direction.
  
}

#endif

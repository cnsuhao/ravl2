// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLVECTOR2D_HEADER
#define RAVLVECTOR2D_HEADER 1
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
    
    RealT Cross(const Vector2dC & vector) const
    { return X() * vector.Y() - Y() * vector.X(); }
    //: Returns the third coordinate of the cross product of this vector
    //: and the vector 'v'.
  };
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLVECTOR3D_HEADER
#define RAVLVECTOR3D_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/FixedSize/Vector3d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Geometry.3D"

#include "Ravl/FVector.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: 3D Vector
  
  class Vector3dC
    : public FVectorC<3>
  {
  public:
    Vector3dC()
      {}
    //: Default constructor.
    
    Vector3dC(const FVectorC<3> &base)
      : FVectorC<3>(base)
      {}
    //: Constructor.
    
    Vector3dC(RealT v1,RealT v2,RealT v3) { 
      data[0] = v1;
      data[1] = v2;
      data[2] = v3;
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
    
    RealT &Z()
      { return data[2]; }
    //: Third component of vector.
    
    RealT Z() const
      { return data[2]; }
    //: Third component of vector.
    
    inline Vector3dC Cross(const Vector3dC & v) const {
      return Vector3dC(  Y() * v.Z() - Z() * v.Y() ,
			 -(X() * v.Z() - Z() * v.X()),
			 X() * v.Y() - Y() * v.X()
			 );
    }
    // Returns the cross product of this vector and the 'vector'.
    
  };
}

#endif

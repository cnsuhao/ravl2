// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_3D_AXIS_ANGLE_HH
#define RAVL_3D_AXIS_ANGLE_HH
//! rcsid="$Id$"
//! lib=RavlMath
//! date="7/12/2002"
//! author="Joel Mitchelson"
//! docentry="Ravl.Math.Geometry.3D"


#include "Ravl/Vector3d.hh"
#include "Ravl/Matrix3d.hh"

namespace RavlN
{

  //! userlevel=Develop
  
  // C-style axis-angle conversions
  void AxisAngleToMatrix(const RealT* a, RealT* R);
  void MatrixToAxisAngle(const RealT* R, RealT* a);

  //! userlevel=Normal

  //: Axis-angle -> matrix conversion.
  inline void AxisAngleToMatrix(const Vector3dC& a, Matrix3dC& R)
  { AxisAngleToMatrix(&a[0], &R[0][0]); }

  //: Matrix -> axis-angle conversion.
  inline void MatrixToAxisAngle(const Matrix3dC& R, Vector3dC& a)
  { MatrixToAxisAngle(&R[0][0], &a[0]); }

  //: Axis-angle class
  class AxisAngleC : public Vector3dC
  {
  public:
    AxisAngleC()
    {
    }
    //: Default constructor (constructs un-initialised axis-angle)

    AxisAngleC(RealT a, RealT b, RealT c) :
      Vector3dC(a,b,c)
    {
    }
    //: Construct from axis-angle parameters.

    AxisAngleC(const Vector3dC& a) :
      Vector3dC(a)
    {
    }
    //: Construct from 3d axis-angle vector.

    AxisAngleC(const Matrix3dC& R)
    { MatrixToAxisAngle(R, *static_cast<Vector3dC*>(this)); }
    //: Construct from rotation matrix.
    
  public:
    void Matrix(Matrix3dC& R) const
    { AxisAngleToMatrix(*static_cast<const Vector3dC*>(this), R); }
    //: Convert to rotation matrix.

    Matrix3dC Matrix() const
    {
      Matrix3dC R;
      Matrix(R);
      return R;
    }
    //: Convert to rotation matrix (as return value).
  };

}

#endif


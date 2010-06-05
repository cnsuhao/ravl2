// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: PinholeCamera0.hh 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlCameraCal
//! author="Joel Mitchelson"
//! docentry="Ravl.API.3D.Camera Calibration"
#ifndef _CAMERA_CAL_PINHOLE_CAMERA_0_HH_
#define _CAMERA_CAL_PINHOLE_CAMERA_0_HH_
//! file="Ravl/3D/CameraCal/PinholeCamera0.hh"

#include "Ravl/Vector2d.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/Stream.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/SArray1d.hh"

namespace Ravl3DN
{
  using namespace RavlN;

  //! userlevel=Normal

  //: Simple pinhole camera model
  // Describes the transform of 3D world points to 2D image points.
  // This class is simplest camera model with no lens distortion.

  class PinholeCamera0C
  {
  public:
    
    RealT& cx() { return _cx; };
    //: centre of projection, x co-ordinate
    
    RealT& cy() { return _cy; };
    //: centre of projection, y co-ordinate

    RealT& fx() { return _fx; };
    //: focal length in camera y direction (pixels)

    RealT& fy() { return _fy; };
    //: focal length in camera z direction (pixels)

    Matrix3dC& R() { return _R; };
    //: rotation world -> camera

    Vector3dC& t() { return _t; };
    //: translation world -> camera (in camera co-ordinates)

    const RealT& cx() const { return _cx; };
    const RealT& cy() const { return _cy; };
    const RealT& fx() const { return _fx; };
    const RealT& fy() const { return _fy; };
    const Matrix3dC& R() const { return _R; };
    const Vector3dC& t() const { return _t; };

    void Project(Vector2dC& z, const Vector3dC& x) const
    {
      Vector3dC Rx = (_R * x) + _t;
      z[0] = _cx + _fx * Rx[0] / Rx[2];
      z[1] = _cy + _fy * Rx[1] / Rx[2];
    }
    //: Project 3D point in space to 2D image point
    //  Projects according to:<br>
    //    z[0] = cx + fx*( (R*x + t)[0] / (R*x + t)[2] )<br>
    //    z[1] = cy + fy*( (R*x + t)[1] / (R*x + t)[2] )<br>
    //  Can result in a divide-by-zero for degenerate points.
    //  See ProjectCheck if this is to be avoided.

    bool ProjectCheck(Vector2dC& z, const Vector3dC& x) const
    {
      Vector3dC Rx = (_R * x) + _t;
      if (Rx[2] > -1E-3 && Rx[2] < 1E-3)
	return false;
      z[0] = _cx + _fx * Rx[0] / Rx[2];
      z[1] = _cy + _fy * Rx[1] / Rx[2];
      return true;
    }
    //: Project 3D point in space to 2D image point
    // The same as Project(...) but checks that the point
    // is not degenerate.

    void ProjectJacobian(FMatrixC<2,3>& Jz, const Vector3dC& x) const
    {
      Vector3dC Rx = (_R * x) + _t;
      RealT r_Rx2_2 = 1.0 / (Rx[2]*Rx[2]);
      Jz[0][0] = _fx * (_R[0][0]*Rx[2] - _R[2][0]*Rx[0]) * r_Rx2_2;
      Jz[0][1] = _fx * (_R[0][1]*Rx[2] - _R[2][1]*Rx[0]) * r_Rx2_2;
      Jz[0][2] = _fx * (_R[0][2]*Rx[2] - _R[2][2]*Rx[0]) * r_Rx2_2;
      Jz[1][0] = _fy * (_R[1][0]*Rx[2] - _R[2][0]*Rx[1]) * r_Rx2_2;
      Jz[1][1] = _fy * (_R[1][1]*Rx[2] - _R[2][1]*Rx[1]) * r_Rx2_2;
      Jz[1][2] = _fy * (_R[1][2]*Rx[2] - _R[2][2]*Rx[1]) * r_Rx2_2;
    }
    //:The Jacobian matrix of the projection funtion

    void ProjectInverseDirection(Vector3dC& x, const Vector2dC& z) const {
      Vector3dC Rx;
      Rx[0] = (z[0] - _cx) / _fx;
      Rx[1] = (z[1] - _cy) / _fy;
      Rx[2] = 1.0;
      TMul(_R,Rx,x);
    }
    //:Inverse projection up to a scale factor
    // Origin + lambda*ProjectInverseDirection is the camera ray
    // corresponding to image point z.
    
    void Origin(Vector3dC& org) const {
      TMul(_R,_t,org);
      org *= -1.0;      
    }
    //: Origin of the camera in world co-ordinates
    //  Computed as -R.T() * t.

  protected:
    RealT _cx;
    RealT _cy;
    RealT _fx;
    RealT _fy;
    Matrix3dC _R;
    Vector3dC _t;
  };

  istream& operator>>(istream& s, PinholeCamera0C& camera);
  //:Read camera parameters from a text stream.

  ostream& operator<<(ostream& s, const PinholeCamera0C& camera);
  //:Write camera parameters to a text stream.

  BinIStreamC& operator>>(BinIStreamC& s, PinholeCamera0C& camera);
  //:Read camera parameters from a binary stream.

  BinOStreamC& operator<<(BinOStreamC& s, const PinholeCamera0C& camera);
  //:Write camera parameters to a binary stream.
};

#endif

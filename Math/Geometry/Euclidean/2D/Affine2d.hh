// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_AFFINE2D_HEADER
#define RAVL_AFFINE2D_HEADER 1
//////////////////////////////////////////////////////
//! file="amma/Geometry/AnGeo2/Affine2d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="17/3/1997"
//! docentry="Ravl.Math.Geometry.2D"
//! rcsid="$Id$"

#include "Ravl/Matrix2d.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/FAffine.hh"

namespace RavlN {

  //! userlevel=Normal
  //: 2-D affine transformation
  
  // This class is used to apply a (6-parameter) 2-D affine transformation.  Note
  // that it transforms the point w.r.t. the coordinate system; it does
  // <b>not</b> transform the coordinate system itself.
  
  class Affine2dC 
    : public FAffineC<2> 
  {
  public:
    inline Affine2dC();
    //: Construct identity transformation.
    
    inline Affine2dC(const FAffineC<2> &Oth);
    //: Construct from base template.
    
    inline Affine2dC(const Affine2dC &Oth);
    //: Copy constructor.
    
    inline Affine2dC(const Matrix2dC &SR, const Vector2dC &T);
    //: Constructor from scaling/rotation matrix and translation vector.
    
    inline Affine2dC(const Vector2dC &Scale, RealT Angle, const Vector2dC &Trans);
    //: Constructor for arbitrary anisotropic scaling, rotation and translation.
    // The scaling axes are aligned with the coordinate axes.
    
    inline Affine2dC(const Vector2dC &Scale, RealT ScaleAngle, RealT Angle, const Vector2dC &Trans);
    //: Constructor for arbitrary anisotropic scaling, rotation and
    //: translation.
    // The scaling axes are aligned at an angle <code>ScaleAngle</code> w.r.t. the coordinate axes.
    
    void Rotate(RealT Angle);
    //: Add rotation <code>Angle</code> to transformation
    
  };
  
  /////////////////////////////////
  
  inline 
  Affine2dC::Affine2dC() 
    : FAffineC<2>()
  {}
  
  inline 
  Affine2dC::Affine2dC(const Affine2dC &Oth) 
    : FAffineC<2>(Oth)
  {}

  inline 
  Affine2dC::Affine2dC(const FAffineC<2> &Oth)
    : FAffineC<2>(Oth)
  {}
  
  inline 
  Affine2dC::Affine2dC(const Matrix2dC &SR, const Vector2dC &T) 
    : FAffineC<2>(SR,T)
  {}
  
  inline 
  Affine2dC::Affine2dC(const Vector2dC &Sc, RealT Angle, const Vector2dC &Trans) 
    : FAffineC<2>(Matrix2dC(1,0,0,1),Trans)
  {
    Scale(Sc);
    Rotate(Angle);
  }
  
  inline 
  Affine2dC::Affine2dC(const Vector2dC &Sc, RealT ScaleAngle, RealT Angle, const Vector2dC &Trans) 
    : FAffineC<2>(Matrix2dC(1,0,0,1),Trans)
  {
    Rotate(-ScaleAngle);
    Scale(Sc);
    Rotate(ScaleAngle+Angle);
  }
  
}
#endif

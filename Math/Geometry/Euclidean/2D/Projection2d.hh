// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_PROJECTION2D_HEADER
#define RAVL_PROJECTION2D_HEADER 1
/////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlMath
//! date="17/10/2002"
//! docentry="Ravl.Math.Geometry.2D"

#include "Ravl/Matrix3d.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/Point2d.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Projective transform.
  
  class Projection2dC {
  public:
    Projection2dC()
      : trans(Matrix3dC::I()),
	iz(1),
	oz(1)
    {}
    //: Default constructor.
    // Creates an identity transform.

    Projection2dC(const Matrix3dC &transform,RealT niz = 1,RealT noz = 1)
      : trans(transform),
	iz(niz),
	oz(noz)
    {}
    //: Construct a projective transform.
    
    inline
    Point2dC Project(const Point2dC &pnt) const {
      Vector3dC vo = trans * Vector3dC(pnt[0],pnt[1],oz);
      return Point2dC(iz*vo[0]/vo[2],iz*vo[1]/vo[2]);          
    }
    //: Project a point through the transform.
    
    Point2dC operator*(const Point2dC &pnt) const
    { return Project(pnt); }
    //: Project a point through the transform.
    
    Projection2dC Inverse() const
    { return Projection2dC(trans.Inverse(),oz,iz); }
    //: Invert transform.
    
    Matrix3dC &Matrix()
    { return trans; }
    //: Access transformation matrix.

    const Matrix3dC &Matrix() const
    { return trans; }
    //: Access transformation matrix.
    
    RealT Iz() const
    { return iz; }
    //: Accesss iz.

    RealT Oz() const
    { return oz; }
    //: Accesss iz.

    RealT &Iz()
    { return iz; }
    //: Accesss iz.

    RealT &Oz()
    { return oz; }
    //: Accesss iz.
    
  protected:
    Matrix3dC trans;
    RealT iz, oz;
  };
  
  istream &operator>>(istream &s,Projection2dC &proj);  
  //: Read from a stream.
  
  ostream &operator<<(ostream &s,const Projection2dC &proj);  
  //: Write to a stream.
  
  BinIStreamC &operator>>(BinIStreamC &s,Projection2dC &proj);  
  //: Read from a binary stream.
  
  BinOStreamC &operator<<(BinOStreamC &s,const Projection2dC &proj);  
  //: Write to a binary stream.
  
    
}



#endif

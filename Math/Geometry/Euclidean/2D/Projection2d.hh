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
//! file="Ravl/Math/Geometry/Euclidean/2D/Projection2d.hh"

#include "Ravl/Matrix3d.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/Matrix2d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/FAffine.hh"

namespace RavlN {
  template<class DataT> class DListC;
  class PointSet2dC;
  class Polygon2dC;
  
  //! userlevel=Normal
  //: 2D Projective transform.
  // <p>Represents a perspective projection in 2D space. </p>
  // <p>The difference between this class and <a href="RavlN.PProjection2dC.html">PProjection2dC</a> is:</p><ul>
  // <li> This class (Projection2dC) includes the relevant projective scaling parameters within the projection object.  Use this class when dealing with Point2dC Euclidean 2D points.</li>
  // <li> PProjection2dC does not include the projective scaling parameters: it is for use with projective 2D points PPoint2dC which themselves already contain the scaling parameters.</li></ul>

  class Projection2dC {
  public:
    Projection2dC()
      : trans(Matrix3dC(0,0,0,
			0,0,0,
			0,0,0)),
	iz(1),
	oz(1)
    {}
    //: Default constructor.
    // Creates an invalid (zero) transform.

    Projection2dC(const Matrix3dC &transform,RealT niz = 1,RealT noz = 1)
      : trans(transform),
	iz(niz),
	oz(noz)
    {}
    //: Construct a projective transform.
    //!param: transform - the 2D projective transformation
    //!param: niz, noz - the normalisation values for the input and output vectors
    // The normalisation values are the values the last term in the vectors must have for correct normalisation.  This is ususally set = 1, but for some operations is better set to a value representative of typical components of the vector.

    Projection2dC(const FAffineC<2> &affineTransform, RealT niz = 1, RealT noz = 1) 
      : iz(niz),
        oz(noz)
    {
      trans[0][0] = affineTransform.SRMatrix()[0][0];
      trans[1][0] = affineTransform.SRMatrix()[1][0];
      trans[0][1] = affineTransform.SRMatrix()[0][1];
      trans[1][1] = affineTransform.SRMatrix()[1][1];
      trans[0][2] = affineTransform.Translation()[0];
      trans[1][2] = affineTransform.Translation()[1];
      trans[2][2] = 1;
      trans[2][0] = trans[2][1] = 0;
    }
    //: Construct a projective transform from an affine one
    //!param: affineTransform - the 2D affine transform
    //!param: niz, noz - the normalisation values for the input and output vectors
    // The ambiguous parameters that are not specified by the affine transform are set to 0.
    
    inline
    Point2dC Project(const Point2dC &pnt) const {
      Vector3dC vo = trans * Vector3dC(pnt[0],pnt[1],oz);
      return Point2dC(iz*vo[0]/vo[2],iz*vo[1]/vo[2]);          
    }
    //: Project a point through the transform.
    
    Projection2dC operator*(const Projection2dC &oth) const {
      Matrix3dC diag(Matrix3dC::I());
      diag[2][2] = oth.oz/iz;
      Matrix3dC transform = trans * diag * oth.trans;
      return Projection2dC(transform, oth.iz, oz);
    }
    //: Combine two transforms
    //!param: oth - the other transform to be combined with this one
    //!return: the result of cascading this transform with the other one
    // Note that the average iz and oz value of the two transforms are used
    // for the resultant one.

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
    
    Matrix3dC Homography() const;
    //: Get homography normalised for iz and oz

    FAffineC<2> AffineApproximation() const {
      RealT t1 = trans[0][2] / trans[2][2];
      RealT t2 = trans[1][2] / trans[2][2];
      RealT h1 = trans[0][0] - t1 * trans[2][0];
      RealT h2 = trans[0][1] - t1 * trans[2][1];
      RealT h3 = trans[1][0] - t2 * trans[2][0];
      RealT h4 = trans[1][1] - t2 * trans[2][1];
      return FAffineC<2>(Matrix2dC(h1,h2,h3,h4), Vector2dC(t1,t2));
    }
    //: Get an affine approximation of this projective transform
    //!return: the affine approximation
    
    inline bool IsValid() const
    { return ((trans != Matrix3dC(0,0,0,0,0,0,0,0,0)) && trans.IsReal()); }
    // True if not the zero projection and Matrix3dC is "real"
    
  protected:
    Matrix3dC trans;
    RealT iz, oz;
  };
  
  Projection2dC FitProjection(const DListC<Point2dC> &org,const DListC<Point2dC> &newPos,RealT &residual);
  //: Fit a projective transform given to the mapping between original and newPos.

  Projection2dC FitProjection(const DListC<Point2dC> &org,const DListC<Point2dC> &newPos);
  //: Fit a projective transform given to the mapping between original and newPos.
  
  bool FitProjection(const SArray1dC<Point2dC> &from,const SArray1dC<Point2dC> &to,Matrix3dC &proj);
  //: Fit a projective matrix.
  
  PointSet2dC operator*(const Projection2dC &trans,const PointSet2dC &points);
  //: Apply a projective transform to a point set
  
  Polygon2dC operator*(const Projection2dC &trans,const Polygon2dC &points);
  //: Apply a projective transform to a polygon
  
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

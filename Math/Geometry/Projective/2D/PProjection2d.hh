// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_PPROJECTION2D_HH
#define RAVL_PPROJECTION2D_HH 1
////////////////////////////////////////////////////////////////////////
//! file="Ravl/Math/Geometry/Projective/2D/PProjection2d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Radek Marik"
//! docentry="Ravl.Math.Projective Geometry.2D"
//! date="26.06.1995"
//! rcsid="$Id$"

#include "Ravl/Matrix3d.hh"
#include "Ravl/PPoint2d.hh"
#include "Ravl/PLine2d.hh"

namespace RavlN {
  template<class DataT> class SArray1dC;
  
  class Projection2dC;
  
  //! userlevel=Normal
  //: Projective transformation in 2D space
  // The class PProjection2dC represents a  projective transformation
  // of objects in projective plane. The projection is
  // represented by a 3 x 3 matrix. The indexes start from 0.

  class PProjection2dC
    : public Matrix3dC
  {
  public:
    
    //:----------------------------------------
    // Constructors, assigment, and destructor.
    
    inline PProjection2dC()
      : Matrix3dC(0,0,0,
		  0,0,0,
		  0,0,0)
    {}
    // Creates the zero projection. All points are projected into
    // not-valid projective object.

    inline PProjection2dC(const Matrix3dC & m)
      : Matrix3dC(m)
    {}
    // Creates a projectivity transformation defined by the matrix 'm'..
    
    inline PProjection2dC(RealT b00, RealT b01, RealT b02,
			  RealT b10, RealT b11, RealT b12,
			  RealT b20, RealT b21, RealT b22)
      : Matrix3dC(b00, b01, b02,
		  b10, b11, b12,
		  b20, b21, b22)
    {}
    // Creates a new projection and assign the values b[ij].
    
    PProjection2dC(const PPoint2dC & ix0, const PPoint2dC & ix1,
		   const PPoint2dC & iy0, const PPoint2dC & iy1,
		   const PPoint2dC & o0,  const PPoint2dC & o1,
		   const PPoint2dC & u0,  const PPoint2dC & u1);
    // Creates a projection transformation taking plane p0 to the plane p1.
    // The plane p0, resp. p1 contains the ideal points ix0, iy0, resp. ix1,
    // iy1, the origin point o0, resp. o1, and the unit point u0, resp. u1.
    // No three points x0, resp. x1, can be collinear.
    
    PProjection2dC(istream & inS);
    // Creates a projection from the input stream.
    
    PProjection2dC(const Projection2dC &proj);
    //: Construct from a euclidean projection. 
    
    //:--------------------------------------------
    // Access to the elements of the projection.
    
    inline const PProjection2dC & PProjection2d() const
    { return *this; }
    // Access to the constant object.
    
    inline PProjection2dC & PProjection2d()
    { return *this; }
    // Access to the object.
    
    PLine2dC Plane(IndexC i) const;
    // Returns the row 'i'.
    
    //:---------------------------
    // Setting of matrix elements.
    
    PProjection2dC & SetLine(IndexC i, const PLine2dC & p);
    // Sets the elements of the row 'i' according to the elements of 
    // the line 'p'.
  
    //:----------------------
    // Projective operations.
    
    inline PProjection2dC Inverse() const
    { return Matrix3dC::Inverse(); }
    // Returns the inverse projective transformation.
    
    inline PPoint2dC operator*(const PPoint2dC & p) const
    { return Matrix3dC::operator*(p); }
    // Projects the point 'p' into the image point. The function
    // is equivalent to the operator()(const PPoint2dC & p).
    
    inline PPoint2dC operator()(const PPoint2dC & p) const
    { return Matrix3dC::operator*(p); }
    // Projects the point 'p' into the image point. The function
    // is equivalent to the operator*(const PPoint2dC & p).
    
    inline PProjection2dC operator*(const PProjection2dC & p) const
    { return Matrix3dC::operator*(p); }
    // Returns the composition of two projections. The result
    // projects projective objects in the same way as they would be
    // projected by projection 'p' at first and then by this projection.
    
    SizeBufferAccessC<RealT> operator[](UIntT ind) 
    { return ((Matrix3dC &) (*this))[ind]; }
    //: Access.
    
    const SizeBufferAccessC<RealT> operator[](UIntT ind) const 
    { return ((const Matrix3dC &) (*this))[ind]; }
    //: Access.
    
  protected:    
    inline PProjection2dC(const RavlN::FMatrixC<3,3> & m)
      : Matrix3dC(m)
    {}
    // Creates a projectivity transformation defined by the matrix 'm'..
    
    inline PProjection2dC(const RavlN::TFMatrixC<RealT,3,3> & m)
      : Matrix3dC(m)
    {}
    // Creates a projectivity transformation defined by the matrix 'm'..
  };    
  
  bool FitPProjection(const SArray1dC<PPoint2dC> &from,const SArray1dC<PPoint2dC> &to,PProjection2dC &proj);
  //: Fit projection to a set of points.  4 or more point correspondances are required
  //!param: from - 1st point set.
  //!param: to - 2nd point set.
  //!param: proj - Projection to store result in.
  //!return: Returns true if fit was successfull.
  
  ostream & operator<<(ostream & outS, const PProjection2dC & p);
  // Saves the projection 'p' into the output stream 'outS'.

  istream & operator>>(istream & inS, PProjection2dC & p);
  // Sets the projective transformation elements according to the values
  // read from input stream 'inS'.
  
}
#endif

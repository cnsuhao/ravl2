// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_POLYGON2D_HEADER
#define RAVL_POLYGON2D_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/Geometry/Euclidean/2D/Polygon2d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Radek Marik"
//! date="26/9/2002"
//! docentry="Ravl.Math.Geometry.2D"

#include "Ravl/PointSet2d.hh"
#include "Ravl/LinePP2d.hh"
#include "Ravl/DLIter.hh"

namespace RavlN {

   //: A polygon in 2d space
   // The Polygon2dC class is a representation of a polygon in 2 dimensional
   // space. A polygon is the region of a plane bounded by a finite collection
   // of line segments forming a simple closed curve. <p>
   // Ref.: -  O'Rourke,J.: Computatinal geometry in C;
   //          Cambridge University Press, 1994, p. 1 <p>
   
   class Polygon2dC: public PointSet2dC
   {
   public:

      Polygon2dC() {}
      // Empty list of points.
      
      Polygon2dC(const DListC<Point2dC>& points)
         : PointSet2dC(points)
      {}
      // Construct from list of points  

      RealT Area2() const;
      // Returns twice the signed area of this polygon.
      // Ref.: -  O'Rourke,J.: Computatinal geometry in C;
      //          Cambridge University Press, 1994, pp. 20-26
  
      bool IsDiagonal(const DLIterC<Point2dC> & a, const DLIterC<Point2dC> & b, bool allowExternal = false) const;
      // Returns TRUE if (a, b) is a proper internal or external (if allowExternal is true)
      // diagonal of this polygon. The edges incident to 'a' and 'b'
      // are ignored.
      // Ref.: -  O'Rourke,J.: Computatinal geometry in C;
      //          Cambridge University Press, 1994, pp. 35-36
  
      bool IsInCone(const DLIterC<Point2dC> & a, const DLIterC<Point2dC> & b) const;
      // Returns TRUE iff the diagonal (a,b) is strictly internal
      // to this polygon in the neighborhood of the 'a' endpoint.
      // Ref.: -  O'Rourke,J.: Computatinal geometry in C;
      //          Cambridge University Press, 1994, pp. 37-38
  
      bool Contains(const Point2dC & p) const;
      // Returns TRUE iff the point 'p' is an internal point of this polygon.
  
      DListC<LinePP2dC> Triangulate();
      // Returns the set of diagonals of this polygon. The polygon vertexes are
      // supposed to be in the counter-clockwise order and they can
      // be collinear.
      // Ref.: -  O'Rourke,J.: Computatinal geometry in C;
      //          Cambridge University Press, 1994, pp. 35-42
  
   };

}

#endif

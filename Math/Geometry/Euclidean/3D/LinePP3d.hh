// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_LINE3DPP_HEADER
#define RAVL_LINE3DPP_HEADER
///////////////////////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Radek Marik"
//! docentry="Ravl.Math.Geometry.3D"
//! date="26/10/1992"
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Types.hh"
#include "Ravl/Point3d.hh"
#include "Ravl/Vector3d.hh"

namespace RavlN {

  class Line3dPVC;
  class Vector3dC;
  
  //: Line determined by two points in 3D space 
  // The class LinePP3dC represents an oriented line segment in 3 dimensional
  // Euclidian space. Furthermore, it has the same features as any line
  // in Euclidian space. A line is represented by 2 points.
  
  class LinePP3dC
  {
  public:
    LinePP3dC()
      : pointA(0,0,0), pointB(0,0,0)
    {}
    //: Creates the non-existing line ([0,0,0]; [0,0,0]);
    
    LinePP3dC(const Point3dC & first, const Point3dC & second)
      : pointA(first), pointB(second)
    {}
    //: Creates the line segment connecting the point 'first' with the
    //: point 'second'.
    
    LinePP3dC(const Point3dC & a, const Vector3dC & v) 
      : pointA(a), pointB(a+v)
    {}
    //: Creates the line segment connecting the point 'a' and the point
    //: a+v.
    
    //:---------------------------------------
    //: Access to elements of the line segment.
    
    const Point3dC & FirstPoint() const
    { return pointA; }
    //: Returns the start point of the line segment.
    
    const Point3dC & SecondPoint() const
    { return pointB; }
    //: Returns the end point of the line segment.

    Point3dC & FirstPoint()
    { return pointA; }
    //: Returns the start point of the line segment.
    
    Point3dC & SecondPoint()
    { return pointB; }
    //: Returns the end point of the line segment.
    
    const Point3dC & P1() const
    { return pointA; }
    //: Returns the start point of the line segment. 
    // It is equivalent to the function FirstPoint().
    
    const Point3dC & P2() const
    { return pointB; }
    // Returns the start point of the line segment. 
    //: It is equivalent to the function SecondPoint().
    
    Point3dC & P1()
    { return pointA; }
    //: Returns the start point of the line segment. 
    // It is equivalent to the function FirstPoint().
    
    Point3dC & P2()
    { return pointB; }
    //: Returns the start point of the line segment. 
    // It is equivalent to the function SecondPoint().
    
    const Point3dC & operator[](const IndexC i) const {
      RavlAssertMsg(i != 0 && i != 1,"Index out of range 0..1"); 
      return (i==0) ? P1() : P2();
    }
    //: Returns the ith point.

    Point3dC & operator[](const IndexC i) {
      RavlAssertMsg(i != 0 && i != 1,"Index out of range 0..1"); 
      return (i==0) ? P1() : P2();
    }
    //: Returns the ith point.
    
    Vector3dC Vector() const
    { return Vector3dC(pointB - pointA); } 
    //: Returns the line segment as a free vector.
    
    Line3dPVC LinePV() const;
    //: Returns the line represented by the start point and the vector.
    // The start point is equal to the start point of this line
    // segment. The vector of the returned line is determined by the
    // start point and the end point of this line segment.
    
    RealT Length() const
    { return pointA.EuclidDistance(pointB); }
    //: Returns the Euclidian distance of the start and end points.
    
    void Swap();
    //: Swaps the end points of this
    
    LinePP3dC Swapped() const
    { return LinePP3dC (P2(), P1()); }
    //: Returns a line with swapped endpoints
    
    // Geometrical computations.
    // -------------------------
    
    LinePP3dC operator+(const Vector3dC & v) const
    { return LinePP3dC(Point3dC(P1()+v),Point3dC(P2()+v)); }
    //: Returns the line segment translated into the new position.
    
    LinePP3dC & operator+=(const Vector3dC & v) {
      pointA += v;
      pointB += v;
      return *this;
    }
    //: Moves the line segment into the new position.
    // The operator is equivalent to the member function Translate().

    LinePP3dC & Translate(const Vector3dC & v)
    { return operator+=(v); }
    //: Moves the line segment into the new position.
    // The member function is equivalent to the operator+=.

    LinePP3dC & FixStart(const Point3dC & p);
    //: Translates the line segment to start in the point 'p'.

    LinePP3dC & FixEnd(const Point3dC & p);
    //: Translates the line segment to end in the point 'p'.

    RealT Distance(const LinePP3dC & line);
    //: Returns the distance of the lines represented by this line segment
    //: and the segment 'line'.
    
    RealT Distance(const Point3dC & p) const;
    //: Returns the distance between the point 'p' and the line represented
    //: by this line segment.
    
    inline LinePP3dC ShortestLine(const LinePP3dC & line);
    //: Returns the shortest line connecting this to 'line'.
    // The returned line has the first point on this
    // line and the second point on the 'line'.
    
    Point3dC Point(const RealT t) const
    { return FirstPoint() + Vector() * t; }
    //: Returns the point of the line: FirstPoint() + t * Vector().
    
    Vector3dC Perpendicular(const Point3dC & p) const
    { return Vector().Cross(p-P1()); }
    //: Returns the vector that is perpendicular to the plane containing
    //: the line segment and the point 'p'. 
    // The direction of the return vector is determined by the cross 
    // product (P2-P1) % (p-P1) which is equivalent to (P1-p) % (P2-p).
    
  private:

    // The representation of the object.
    // ---------------------------------

    Point3dC pointA;  // The start point of the line segment.
    Point3dC pointB;  // The end point of the line segment.

    friend RealT Distance(const Point3dC & point, const LinePP3dC & line);
    friend istream & operator>>(istream & inS, LinePP3dC & line);
  };
  
  inline RealT Distance(const Point3dC & point, const LinePP3dC & line) 
  { return line.Distance(point); }
  
  ostream & operator<<(ostream & outS, const LinePP3dC & line);
  istream & operator>>(istream & inS, LinePP3dC & line);
  
  ////////////////////////////////////////////////////////////
  
  inline void LinePP3dC::Swap() {
    Point3dC tmp(P1());
    P1() = P2();
    P2() = tmp;
  }
  
  inline LinePP3dC &LinePP3dC::FixStart(const Point3dC & p) {
    pointB += p-pointA;
    pointA  = p;
    return *this;
  }
  
  inline LinePP3dC & LinePP3dC::FixEnd(const Point3dC & p) {
    pointA += p-pointB;
    pointB  = p;
    return *this;
  }
  
  
}
#endif



// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_LINEPP2D_HEADER
#define RAVL_LINEPP2D_HEADER 1
//! rcsid="$Id: LinePP2d.hh 7472 2010-01-20 16:37:57Z ees1wc $"
//! lib=RavlMath
//! date="13/9/2002"
//! author="Charles Galambos"
//! docentry="Ravl.API.Math.Geometry.2D"
//! file="Ravl/Math/Geometry/Euclidean/2D/LinePP2d.hh"

#include "Ravl/Vector2d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/FLinePP.hh"
#include "Ravl/RealRange2d.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Line defined by 2 points in 2 dimensional space.
  
  class LinePP2dC 
    : public FLinePPC<2>
  {
  public:
    LinePP2dC()
    {}
    //: Default constructor.
    // The contents of the line are undefined.

    LinePP2dC(const FLinePPC<2> &base)
      : FLinePPC<2>(base)
    {}
    //: Constructor from base class
    
    LinePP2dC(const Point2dC &start,const Point2dC &end)
      : FLinePPC<2>(start,end)
    {}
    //: Construct a line from two points.

    LinePP2dC(const Point2dC &start,const Vector2dC &direction)
      : FLinePPC<2>(start,direction)
    {}
    //: Construct a line from a start point and a direction
    
    bool ClipBy(const RealRange2dC &rng);
    //: Clip line by given rectangle.
    // If no part of the line is in the rectangle:<ul>
    // <li>line is <i>not</i> clipped</li>
    // <li>method returns <code>false</code></li></ul>
    
    bool IsPointToRight(const Point2dC& pnt) const
    { return pnt.Area2(P1(),P2()) < 0; }
    //: Checks if this point is to the right of the line
    
    bool IsPointToRightOn(const Point2dC& pnt) const 
    { return pnt.Area2(P1(),P2()) <= 0; }
    //: Checks if this point is to the right of, or exactly on the line
    
    bool IsPointOn(const Point2dC& pnt) const
    { return pnt.Area2(P1(),P2()) == 0; }
    //: Checks if this point is exactly on the line

    bool IsPointIn(const Point2dC& pnt) const;
    //: Checks if this point is exactly on the closed segment
    
    RealT ParIntersection(const LinePP2dC & l) const;
    //: Returns the parameter of the intersection point of 'l' with this line.
    // If the parameter is equal to 0, the intersection is the starting
    // point of this line, if the parameter is 1, the intersection is the
    // end point. If the parameter is between 0 and 1 the intersection is
    // inside of this line segment.

    bool HasInnerIntersection(const LinePP2dC & l) const;
    // Returns true if the intersection of this line segment and the 
    // line 'l' is either inside of this line segment or one of the end points.
 
    Point2dC Intersection(const LinePP2dC & l) const;
    // Returns the intersection of 2 lines.

    bool Intersection(const LinePP2dC & l, Point2dC& here) const;
    //: Calculate the intersection point between this line and l
    //!param: l - another line
    //!param: here - the point of intersection
    //!return: true if the lines intersect or false if they are parallel
    
    bool IntersectRow(RealT row,RealT &col) const;
    //: Find the column position which itersects the given row.
    //!param: row - Row for which we want to find the interecting column
    //!param: col - Place to store the intersecting col.
    //!return: True if position exists, false if there is no intersection
    
    RealT Angle() const {
      Vector2dC dir = P2() - P1();
      return ATan2(dir[1],dir[0]);
    }
    //: Return the direction of the line.

    Vector2dC Normal() const
    { return Vector2dC(point[1][1]-point[0][1],point[1][0]-point[0][0]); }
    //: Returns the normal of the line.
    
    Vector2dC UnitNormal() const
    { 
      Vector2dC normal = Normal();
      return normal / normal.Magnitude();
    }
    //: Returns the normal of the line normalized to have unit size.
    
    RealT SignedDistance(const Point2dC pt) const
    { return Vector2dC(Vector()).Cross(Vector2dC(pt-P1()))/Length(); }
    //: Return signed distance of pt from this line
    
    RealT Distance(const Point2dC pt) const
    { return Abs(SignedDistance(pt)); }
    //: Return signed distance of pt from this line
    
    Point2dC Projection(const Point2dC & Pt) const
    { 
      return Point(ParClosest(Pt));
    }
  };
  
}

#endif

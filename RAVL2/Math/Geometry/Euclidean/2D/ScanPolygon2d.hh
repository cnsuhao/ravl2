// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SCANPOLYGON2D_HEADER
#define RAVL_SCANPOLYGON2D_HEADER 1
//! lib=RavlMath
//! date="16/8/2004"
//! author="Charles Galambos"
//! docentry="Ravl.API.Math.Geometry.2D"
//! file="Ravl/Math/Geometry/Euclidean/2D/ScanPolygon2d.hh"

#include "Ravl/Polygon2d.hh"
#include "Ravl/RealRange1d.hh"
#include "Ravl/SArray1dIter.hh"

namespace RavlN {
  
  
  //! userlevel=Develop
  //: Convert a polygon to a set of scan lines.
  // This assumes the boundary does not cross itself and is
  // oriented clockwise (in the Ravl coordinate system). <br>
  // Note: This class is still in development, use with care.
  
  class ScanPolygon2dC {
  public:
    ScanPolygon2dC()
    {}
    //: Default constructor.
    
    ScanPolygon2dC(const Polygon2dC &poly,RealT rowStep = 1.0)
    { First(poly,rowStep); }
    //: Default constructor.
    
    bool First(const Polygon2dC &poly,RealT rowStep = 1.0);
    //: Goto first polygon in scan.
    
    bool Next();
    //: Goto next scan element.
    
    const RealRangeC &Data() 
    { return span; }
    //: Current range 
    
    bool operator++(int)
    { return Next(); }
    //: Goto next scan element.
    
    bool IsElm() const
    { return spans.IsElm(); }
    //: Are we on a valid element ?
    
    operator bool() const
    { return IsElm(); }
    //: Are we on a valid element ?
    
    RealT Row() const
    { return row; }
    //: Access current row.
    
    class LineSegmentC {
    public:
      LineSegmentC(const Point2dC *_p1,const Point2dC *_p2);
      //: Constructor.
      
      LineSegmentC()
      {}
      //: Default constructor.
      
      const Point2dC *P1() const
      { return p1; }
      
      const Point2dC *P2() const
      { return p2; }
      
      bool IntersectRow(RealT row,RealT &col) const;
      //: Get column of intersection with row.
      
      RealT IntersectRow(RealT row) const;
      //: Get row intersection with no checking.
    protected:
      const Point2dC *p1;
      const Point2dC *p2;
    };
    
  protected:
    const Point2dC *NextPnt(const Point2dC *pnt);
    //: Get following point on polygon
    
    const Point2dC *PrevPnt(const Point2dC *pnt);
    //: Get previous point on polygon
    
    RealT RowQuant(RealT row);
    //: Quantise row position
    
    bool SetupSpan();
    //: Setup current 'span'
    
    bool CheckSpans();
    
    
    RealT row;
    RealT rowStep;
    RealT rowLast;
    RealRangeC span;
    DLIterC<PairC<LineSegmentC> > spans; // Current set of spans.
    const Point2dC *firstPnt,*lastPnt;
    SArray1dIterC<Point2dC *> pit;
    SArray1dC<Point2dC> points;
  };
  
}


#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_POINT2D_HEADER
#define RAVL_POINT2D_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/Geometry/Euclidean/Point2d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Geometry.2D"

#include "Ravl/FPoint.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: 2D Point
  
  class Point2dC
    : public FPointC<2>
  {
  public:
    Point2dC()
    {}
    //: Default constructor.
    
    Point2dC(const TFVectorC<RealT,2> &base)
      : FPointC<2>(base)
    {}
    //: Base class constructor.
    
    Point2dC(UIntT size)
    { RavlAssert(size == 2); }
    //: Construct with size.
    // This is used in some templates that are
    // designed to work with PointNdC as well as instances of FPointC.
    
    Point2dC(const FIndexC<2> &ind) 
      : FPointC<2>(ind)
    {}
    //: Construct from a 2d index.
    
    Point2dC(RealT v1,RealT v2) { 
      data[0] = v1;
      data[1] = v2;
    }
    //: Construct from two reals.
    
    RealT &X()
    { return data[0]; }
    //: First component of vector.
    
    RealT X() const
    { return data[0]; }
    //: First component of vector.

    RealT &Y()
    { return data[1]; }
    //: Second component of vector.

    RealT Y() const
    { return data[1]; }
    //: Second component of vector.

    RealT Area2(const Point2dC& second, const Point2dC& third) const;
    //: return twice the area contained by the three points

  };
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_LINEPP2D_HEADER
#define RAVL_LINEPP2D_HEADER 1
//! rcsid="$Id$"
//! lib=RavlMath
//! date="13/9/2002"
//! author="Charles Galambos"
//! docentry="Ravl.Math.Geometry.2D"

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
    // Returns false if no part of the line is in the rectangle.
    
  };
  
}

#endif

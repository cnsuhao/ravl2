// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/LinePP2d.hh"

namespace RavlN {

#if 0
  enum ContainCodeT { CC_NONE=0x0,TOP=0x1,BOTTOM=0x2,RIGHT=0x4,LEFT=0x8 };
  
  static inline ContainCodeT ContainsCode(const Point2dC &pnt,const RealRange2dC &rng) {
    ContainCodeT ret = NONE;
    if(pnt[0] > rng.BRow())
      ret |= BOTTOM;
    if(pnt[0] < rng.TRow())
      ret |= TOP;
    if(pnt[1] > rng.RCol())
      ret |= RIGHT;
    if(pnt[1] < rng.LCol())
      ret |= LEFT;
    return ret;
  }
#endif
  
  //: Clip line by given rectangle.
  // Returns false if no part of the line is in the rectangle.
  
  bool LinePP2dC::ClipBy(const RealRange2dC &rng) {
#if 0
    bool accept = false;
    bool done = false;
    ContainCodeT c0 = ContainsCode(P1(),rng);
#endif
    return true;
  }
  
}

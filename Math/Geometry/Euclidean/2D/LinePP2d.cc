// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/LinePP2d.hh"

#define CTOP    0x1
#define CBOTTOM 0x2
#define CRIGHT  0x4
#define CLEFT   0x8

namespace RavlN {
  
  static inline int ContainsCode(const Point2dC &pnt,const RealRange2dC &rng) {
    int ret = 0;
    if(pnt[0] > rng.BRow())
      ret |= CTOP;
    else if(pnt[0] < rng.TRow())
      ret |= CBOTTOM;
    if(pnt[1] > rng.RCol())
      ret |= CRIGHT;
    else if(pnt[1] < rng.LCol())
      ret |= CLEFT;
    return ret;
  }
  
  //: Clip line by given rectangle.
  // Returns false if no part of the line is in the rectangle.
  // Uses the Cohen and Sutherland line clipping algorithm.
  
  bool LinePP2dC::ClipBy(const RealRange2dC &rng) {
    bool accept = false;
    int oc0 = ContainsCode(P1(),rng);
    int oc1 = ContainsCode(P2(),rng);
#if 0
    const RealT vscale = rng.Rows();
    const RealT hscale = rng.Cols();
    RealT diff = ;
    //if(IsSmall(diff,hscale)) // Avoid division by zero. 
    //  np[0] = 0;
    //else
#endif
    
    do {
      if(!(oc0 | oc1)) {
	accept = true;
	break;
      } 
      if(oc0 & oc1)
	break;
      Point2dC np;
      int oc = oc0 ? oc0 : oc1;
      if(oc & CTOP) {
	np[0] = rng.TRow();
	np[1] = P1()[1] + (P2()[1] - P1()[1]) * (rng.RCol() - P1()[0]) / (P2()[0] - P1()[0]);
      } else if(oc & CBOTTOM) {
	np[0] = rng.BRow();
	np[1] = P1()[1] + (P2()[1] - P1()[1]) * (rng.LCol() - P1()[0]) / (P2()[0] - P1()[0]);
      } else if(oc & CRIGHT) {
	np[0] = P1()[0] + (P2()[0] - P1()[0]) * (rng.BRow() - P1()[1]) / (P2()[1] - P1()[1]);
	np[1] = rng.RCol();
      } else { // CLEFT
	np[0] = P1()[0] + (P2()[0] - P1()[0]) * (rng.TRow() - P1()[1]) / (P2()[1] - P1()[1]);
	np[1] = rng.LCol();
      }
      if(oc == oc0) {
	P1() = np;
	oc0 = ContainsCode(P1(),rng);
      } else {
	P2() = np;
	oc1 = ContainsCode(P2(),rng);
      }
    } while(1) ;
    return accept;
  }
  
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! date="26.10.1992"
//! author="Radek Marik"
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/Boundary/Edge.cc"

// elementary boundary edge based on crack code

#include "Ravl/Edge.hh"
#include "Ravl/Stream.hh"

namespace RavlN {
  
  EdgeC::EdgeC(const BVertexC & begin, const BVertexC & end)
    : BVertexC(begin)
  {
    if (begin.RightN() == end) crackCode = CR_RIGHT;
    else if (begin.LeftN() == end)  crackCode = CR_LEFT;
    else if (begin.UpN() == end)    crackCode = CR_UP;
    else if (begin.DownN() == end)  crackCode = CR_DOWN;
  }
  
  EdgeC::EdgeC(const Index2dC &pxl, const CrackCodeC & cc)
    : BVertexC(pxl), CrackCodeC(cc)
  {
    switch (cc.Code()) {
    case CR_DOWN :                 break;
    case CR_RIGHT: Down();         break;
    case CR_UP   : Down().Right(); break;
    case CR_LEFT : Right();        break;
    case CR_NODIR:                 break;
    }
  }

  //: Mid point along edge.
  
  Point2dC EdgeC::MidPoint() const {
    switch(crackCode) {
    case CR_DOWN : return Point2dC((RealT) Row() +0.5 ,(RealT) Col());

    case CR_RIGHT: return Point2dC((RealT) Row()    ,(RealT) Col() + 0.5);
    case CR_UP   : return Point2dC((RealT) Row() -0.5 ,(RealT) Col());
    case CR_LEFT : return Point2dC((RealT) Row()      ,(RealT) Col() - 0.5);
    case CR_NODIR: return Point2dC((RealT) Row()  +0.5    ,(RealT) Col() + 0.5);
    }
    RavlAssert(0);
    return Point2dC(0,0);
  }
  
  // return the pixel on the right side of the edge.
  
  Index2dC EdgeC::RPixel() const {
    Index2dC px(*this);
    switch (crackCode) {
    case CR_DOWN : px = CrackStep(px,CR_LEFT);  break;
    case CR_RIGHT:                              break;
    case CR_UP   : px = CrackStep(px,CR_UP);    break;
    case CR_LEFT : px = px.Step(NEIGH_UP_LEFT); break;
    case CR_NODIR:                              break;
    }
    return px; 
  }
  
  // return the pixel on the left side of the edge.
  
  Index2dC EdgeC::LPixel() const {
    Index2dC px(*this);
    switch (crackCode) {
    case CR_DOWN :                                break;
    case CR_RIGHT: px = CrackStep(px,CR_UP);      break;
    case CR_UP   : px = px.Step(NEIGH_UP_LEFT);   break;
    case CR_LEFT : px = CrackStep(px,CR_LEFT);    break;
    case CR_NODIR:                                break;
    }
    return px; 
  }
  

}


  

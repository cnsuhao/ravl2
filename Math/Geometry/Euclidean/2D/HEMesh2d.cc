// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/HEMesh2d.hh"
#include "Ravl/THEMeshVertexIter.hh"
#include "Ravl/THEMeshFaceIter.hh"
#include "Ravl/LinePP2d.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Default constructor.
  
  HEMesh2dC::HEMesh2dC()
  {}
  
  //: Constructor.
  // Creates an empty mesh.
  
  HEMesh2dC::HEMesh2dC(bool)
    : THEMeshC<Point2dC>(true)
  {}
  
  //: Compute the mean position of points in the mesh.
  
  Point2dC HEMesh2dC::Mean() const {
    Point2dC ret(0,0);
    UIntT count = 0;
    for(THEMeshVertexIterC<Point2dC> it(Vertices());it;it++) {
      ret += (*it).Data();
      count++;
    }
    return ret / (RealT) count;
  }
  
  //: Find face containing point 'pnt'.
  // Returns an invalid handle if none found.
  
  THEMeshFaceC<Point2dC> HEMesh2dC::FindFace(const Point2dC &pnt) {
    ONDEBUG(cerr << "HEMesh2dC::FindFace(), Point= " << pnt << "\n");
    for(THEMeshFaceIterC<Point2dC> it(Faces());it;it++) {
      RavlAssert((*it).IsValid());
      THEMeshFaceEdgeIterC<Point2dC> eit(*it);
      if(!eit) continue; // Faces has no edges!
      Point2dC last = eit->Vertex().Data();
      Point2dC first = last;
      bool found = true;
      for(eit++;eit;eit++) {
	Point2dC pnt = eit->Vertex().Data();
	if(LinePP2dC(last,pnt).IsPointToLeft(pnt)) {
	  found = false;
	  break;
	}
	last = pnt;
      }
      if(found && !LinePP2dC(last,first).IsPointToLeft(pnt))
	return *it; // Found it !
      // Keep trying....
    }
    return THEMeshFaceC<Point2dC>();
  }
  
  //: Compute the bounding rectangle for the points in the mesh.
  
  RealRange2dC HEMesh2dC::BoundingRectangle() const {
    RealRange2dC ret(0,0);
    THEMeshVertexIterC<Point2dC> it(Vertices());
    if(!it)
      return ret;
    ret = RealRange2dC((*it).Data(),0);
    for(;it;it++)
      ret.Involve((*it).Data());
    return ret;
  }
  
}

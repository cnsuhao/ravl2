// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3D

#include "Ravl/3D/HEMeshEdge.hh"
#include "Ravl/3D/HEMeshFace.hh"

namespace Ravl3DN {

  //: Collapse edge to zero length.
  // This deletes the edge from the mesh and merges the vertex's
  // at either end.
  
  HEMeshVertexC HEMeshEdgeBodyC::CollapseEdge() {
    // Check face isn't relying on this edge.
    if(face->Edge() == this) {
      HEMeshEdgeBodyC *oth = &Next();
      // Has face collapsed to zero size ?
      if(oth == this) {
      } else
	face->SetEdge(oth);
    }
    Unlink();
    RavlAssertMsg(0,"HEMeshEdgeBodyC::CollapseEdge(), Not implemented. ");
    return HEMeshVertexC();
  }
  
  //: Open an edge, merging the faces on either side.
  // This deletes the edge from the mesh and returns
  // a handle to the new face.
  
  HEMeshFaceC HEMeshEdgeBodyC::OpenEdge() {
    RavlAssertMsg(0,"HEMeshEdgeBodyC::OpenEdge(), Not implemented. ");
    return HEMeshFaceC();
  }
  
  //: Constructor.
  
  HEMeshEdgeC::HEMeshEdgeC(HEMeshVertexC vert,HEMeshFaceC face)
    : body(new HEMeshEdgeBodyC(vert.Body(),face.Body()))
  {}

}

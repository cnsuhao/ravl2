// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3D

#include "Ravl/3D/HEMeshVertex.hh"
#include "Ravl/3D/HEMeshEdge.hh"
#include "Ravl/3D/HEMeshFace.hh"

namespace Ravl3DN {
    
  //: Look for a connection from this vertex to oth.
  // Returns an invalid handle if ones is not found.
  
  HEMeshEdgeC HEMeshVertexBodyC::FindEdge(const HEMeshVertexC &oth) const {
    if(edge == 0) // None ?
      return HEMeshEdgeC();
    
#if 0
    HEMeshEdgeC at(edge);
    while(at) {
      if(at.Vertex() == oth)
	return at;
      if(!at.HasPair())
	break;
      at = at.Pair().Next();
    }
#else
    RavlAssert(0);
#endif
    
    return HEMeshEdgeC();
  }

  //: Link this vertex to othvert on given face
  
  HEMeshEdgeC HEMeshVertexBodyC::Link(HEMeshVertexC vert,HEMeshFaceC face) {
    HEMeshEdgeC ret;
    RavlAssert(face.HasVertex(vert));
    RavlAssert(face.HasVertex(*this));
    
    HEMeshEdgeC newEdge1(vert,face);
    HEMeshEdgeC newEdge2(*this,face);
    
    return ret;
  }

  
}

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
#endif
    
    return HEMeshEdgeC();
  }
  
}

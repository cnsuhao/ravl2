// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3D

#include "Ravl/3D/HEMesh.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/Hash.hh"

namespace Ravl3DN {
  
  //: Insert face defined by vertices.
  
  HEMeshFaceC HEMeshBodyC::InsertFace(const SArray1dC<HEMeshVertexC> &vertices) {
    RavlAssert(vertices.Size() > 2);
    
    HEMeshFaceC face(true);
    faces.InsLast(face.Body());
    
    SArray1dIterC<HEMeshVertexC> it(vertices);
    HEMeshVertexC lastVert = *it;
    it++;    
    HashC<Tuple2C<HEMeshVertexC,HEMeshVertexC> , HEMeshEdgeC> edgeTab;
    HEMeshEdgeC firstEdge;
    for(it++;it;it++) {
      RavlAssert(it->IsValid());
      HEMeshEdgeC newEdge(it->Body(),face.Body());
      if(!firstEdge.IsValid())
	firstEdge = newEdge;
      else
	firstEdge.LinkBefore(newEdge);
      Tuple2C<HEMeshVertexC,HEMeshVertexC> okey(*it,lastVert);
      HEMeshEdgeC opedge = edgeTab[okey];
      if(opedge.IsValid()) {
	RavlAssertMsg(!opedge.HasPair(),"Can't represent nonplanar meshes.");
	opedge.SetPair(newEdge);
      }
      edgeTab[Tuple2C<HEMeshVertexC,HEMeshVertexC>(lastVert,*it)] = newEdge;
      lastVert = *it;
    }
    face.SetEdge(firstEdge);
    return face;
  }
  
}

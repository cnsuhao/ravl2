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

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace Ravl3DN {
  
  //: Insert face defined by vertices.
  
  HEMeshFaceC HEMeshBodyC::InsertFace(const SArray1dC<HEMeshVertexC> &vertices,HashC<Tuple2C<HEMeshVertexC,HEMeshVertexC> , HEMeshEdgeC> &edgeTab) {
    RavlAssert(vertices.Size() > 2);
    HEMeshFaceC face(true);
    ONDEBUG(cerr << "Inserting face " << face.Hash() << "\n"); 
    faces.InsLast(face.Body());
    
    SArray1dIterC<HEMeshVertexC> it(vertices);
    HEMeshVertexC lastVert = *it;
    HEMeshVertexC firstVert = *it;
    it++;
    HEMeshEdgeC firstEdge;
    for(;it;it++) {
      RavlAssert(it->IsValid());
      HEMeshEdgeC newEdge(it->Body(),face.Body());
      if(!firstEdge.IsValid())
	firstEdge = newEdge;
      else
	firstEdge.LinkBefore(newEdge);
      HEMeshEdgeC opedge = edgeTab[Tuple2C<HEMeshVertexC,HEMeshVertexC>(*it,lastVert)];
      if(opedge.IsValid()) {
	RavlAssertMsg(!opedge.HasPair(),"Can't represent nonplanar meshes.");
	opedge.SetPair(newEdge);
	newEdge.SetPair(opedge);
      }
      HEMeshEdgeC &me = edgeTab[Tuple2C<HEMeshVertexC,HEMeshVertexC>(lastVert,*it)];
      RavlAssert(!me.IsValid());
      me = newEdge;
      ONDEBUG(cerr << "Linking " << lastVert.Hash() << " To " << it->Hash() << "\n");
      lastVert = *it;
    }
    HEMeshEdgeC newEdge(firstVert.Body(),face.Body());
    firstEdge.LinkBefore(newEdge);
    HEMeshEdgeC opedge = edgeTab[Tuple2C<HEMeshVertexC,HEMeshVertexC>(firstVert,lastVert)];
    if(opedge.IsValid()) {
      RavlAssertMsg(!opedge.HasPair(),"Can't represent nonplanar meshes.");
      opedge.SetPair(newEdge);
      newEdge.SetPair(opedge);
    }
    edgeTab[Tuple2C<HEMeshVertexC,HEMeshVertexC>(lastVert,firstVert)] = newEdge;
    ONDEBUG(cerr << "Linking " << lastVert.Hash() << " To " << firstVert.Hash() << "\n");
    
    face.SetEdge(firstEdge);
    return face;
  }
  
}

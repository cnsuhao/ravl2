// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3D

#include "Ravl/3D/HEMesh.hh"
#include "Ravl/3D/TriMesh.hh"
#include "Ravl/SArr1Iter2.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/Hash.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace Ravl3DN {
  
  //: Construct from a TriMesh
  
  HEMeshBodyC::HEMeshBodyC(const TriMeshC &mesh) {
    SArray1dC<HEMeshVertexC> verts(mesh.Vertices().Size());
    // Creat all the vertices
    for(SArray1dIter2C<HEMeshVertexC,VertexC> it(verts,mesh.Vertices());it;it++)
      it.Data1() = InsertVertex(it.Data2());
    // Creat the faces.
    HashC<Tuple2C<HEMeshVertexC,HEMeshVertexC> , HEMeshEdgeC> edgeTab;
    for(SArray1dIterC<TriC> it(mesh.Faces());it;it++) {
      SArray1dC<HEMeshVertexC> face(3);
      for(int i = 0;i < 3;i++)
	face[i] = verts[mesh.Index(*it,i)];
      InsertFace(face,edgeTab);
    }
    ONDEBUG(cerr << "EdgeTab Size=" << edgeTab.Size() << "\n");
  }

  //: Build a TriMesh from this mesh.
  
  TriMeshC HEMeshBodyC::TriMesh() const {
    TriMeshC tm;
    UIntT noFaces = NoFaces();
    UIntT noVertices = NoVertices();
    SArray1dC<VertexC> verts(noVertices);
    // Copy vertices.
    HashC<HEMeshVertexC,UIntT> vindex;
    SArray1dIterC<VertexC> vit(verts);
    for(IntrDLIterC<HEMeshVertexBodyC> it(vertices);it;it++,vit++) {
      vindex[HEMeshVertexC(*it)] = vit.Index().V();
      RavlAssert(vit);
      *vit = *it;
    }
    // Copy faces.
    SArray1dC<TriC> tri(noFaces);
    SArray1dIterC<TriC> fait(tri);
    for(IntrDLIterC<HEMeshFaceBodyC> fit(faces);fit;fit++,fait++) {
      ONDEBUG(cerr << "HEMeshBodyC::TriMesh(), Building face " << fait.Index() << "\n");
      RavlAssert(fait);
      HEMeshFaceC aface(*fit);
      HEMeshFaceEdgeIterC eit(aface);      
      RavlAssert(eit);
      VertexC &v1 = verts[vindex[eit->Vertex()]];
      eit++;
      RavlAssert(eit);
      VertexC &v2 = verts[vindex[eit->Vertex()]];
      eit++;
      RavlAssert(eit);
      VertexC &v3 = verts[vindex[eit->Vertex()]];
#if DODEBUG
      eit++;
      RavlAssert(!eit);
#endif
      *fait = TriC(v1,v2,v3);
    }
      
    return tm;
  }
  
  TriMeshC HEMeshC::TriMesh() const 
  { return Body().TriMesh(); }
  //: Build a TriMesh from this mesh.

}

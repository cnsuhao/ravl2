// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/HEMeshBase.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Hash.hh"
#include "Ravl/HSet.hh"
#include "Ravl/IntrDLIter.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Destructor.
  // Needed to ensure faces are removed before vertices.
  
  HEMeshBaseBodyC::~HEMeshBaseBodyC() {
    while(!faces.IsEmpty()) {
      HEMeshBaseFaceBodyC *face = &faces.First();
      face->DestroyFace();
      delete face;
    }
    vertices.Empty(); 
  }
  
  //: Insert face defined by vertices.
  
  HEMeshBaseFaceC HEMeshBaseBodyC::InsertFace(HEMeshBaseFaceC &face,
					      const SArray1dC<HEMeshBaseVertexC> &vertices,
					      HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab) {
    RavlAssert(vertices.Size() > 2);
    RavlAssert(face.IsValid());
    ONDEBUG(cerr << "Inserting face " << face.Hash() << "\n"); 
    faces.InsLast(face.Body());
    
    SArray1dIterC<HEMeshBaseVertexC> it(vertices);
    HEMeshBaseVertexC lastVert = *it;
    HEMeshBaseVertexC firstVert = *it;
    it++;
    HEMeshBaseEdgeC firstEdge;
    for(;it;it++) {
      RavlAssert(it->IsValid());
      HEMeshBaseEdgeC newEdge = NewEdge(*it,face);
      if(!firstEdge.IsValid())
	firstEdge = newEdge;
      else
	firstEdge.LinkBefore(newEdge);
      HEMeshBaseEdgeC opedge = edgeTab[Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC>(*it,lastVert)];
      if(opedge.IsValid()) {
	RavlAssertMsg(!opedge.HasPair(),"Can't represent nonplanar meshes.");
	opedge.SetPair(newEdge);
	newEdge.SetPair(opedge);
      }
      HEMeshBaseEdgeC &me = edgeTab[Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC>(lastVert,*it)];
      RavlAssert(!me.IsValid());
      me = newEdge;
      ONDEBUG(cerr << "Linking " << lastVert.Hash() << " to " << it->Hash() << "\n");
      it->SetEdge(me.Body()); // Make sure vertex has a valid edge.
      lastVert = *it;
    }
    HEMeshBaseEdgeC newEdge(firstVert.Body(),face.Body());
    firstEdge.LinkBefore(newEdge);
    HEMeshBaseEdgeC opedge = edgeTab[Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC>(firstVert,lastVert)];
    if(opedge.IsValid()) {
      RavlAssertMsg(!opedge.HasPair(),"Can't represent nonplanar meshes.");
      opedge.SetPair(newEdge);
      newEdge.SetPair(opedge);
    }
    edgeTab[Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC>(lastVert,firstVert)] = newEdge;
    firstVert.SetEdge(newEdge.Body()); // Make sure vertex has a valid edge.
    ONDEBUG(cerr << "Linking " << lastVert.Hash() << " To " << firstVert.Hash() << "\n");
    
    face.SetEdge(firstEdge);
    return face;
  }
  
  //: Insert a vertex on an edge.
  
  HEMeshBaseVertexC HEMeshBaseBodyC::InsertVertexOnEdge(HEMeshBaseEdgeC edge) {
    HEMeshBaseVertexC ret;
    //vertices.InsLast(nvert.Body());
    RavlAssertMsg(0,"HEMeshBaseBodyC::InsertVertexOnEdge(), Not Implemented.");
    return ret;
  }


  //: Insert a vertex into a face, link all vertexes already in the face to it.
  
  bool HEMeshBaseBodyC::InsertVertexInFace(HEMeshBaseVertexC &vert,HEMeshBaseFaceC &face) {
    ONDEBUG(cerr << "HEMeshBaseBodyC::InsertVertexInFace(), Called.  Vert=" << vert.Hash() << " Face=" << face.Hash() << "\n");
    // Put in first link to new vertex.
    
    HEMeshBaseEdgeC lastEdge,firstEdge;
    HEMeshBaseEdgeC nextEdge;
    HEMeshBaseEdgeC endEdge = face.Edge();
    HEMeshBaseEdgeC thisEdge = face.Edge();
    for(;thisEdge.IsValid();thisEdge = nextEdge) {
      nextEdge = thisEdge.Next();
      if(nextEdge == endEdge)
	nextEdge.Invalidate();
      //ONDEBUG(cerr << "Edge :" << thisEdge.Hash() << "\n");
      HEMeshBaseFaceC newFace;
      if(thisEdge == endEdge) {
	newFace = NewFace();
	faces.InsLast(newFace.Body());
      } else 
	newFace = face;
      newFace.SetEdge(thisEdge);
      HEMeshBaseVertexC lastVert = thisEdge.Prev().Vertex();
      thisEdge.SetSelfPointing();
      thisEdge.SetFace(newFace);
      HEMeshBaseEdgeC edge1 = NewEdge(vert,newFace);
      HEMeshBaseEdgeC edge2 = NewEdge(lastVert,newFace);
      if(lastEdge.IsValid()) {
	lastEdge.SetPair(edge1);
	edge1.SetPair(lastEdge);
      } else
	firstEdge = edge1;
      thisEdge.LinkAfter(edge1);
      thisEdge.LinkBefore(edge2); 
      lastEdge = edge2;
    }
    firstEdge.SetPair(lastEdge);
    lastEdge.SetPair(firstEdge);
    
    return true;
  }
  

  //: Check mesh structure is consistant.
  // Returns false if an inconsistancy is found.
  
  bool HEMeshBaseBodyC::CheckMesh(bool canBeOpen) const {
    bool ret = true;
    if(!canBeOpen) {
      // Can't do this check properly on an open mesh.
      ONDEBUG(cerr << "HEMeshBaseBodyC::CheckMesh(), Checking vertexes. \n");
      for(IntrDLIterC<HEMeshBaseVertexBodyC> vit(vertices);vit;vit++) {
	ONDEBUG(cerr << " Checking vertex " << HEMeshBaseVertexC(*vit).Hash() << "\n");
	for(HEMeshBaseVertexEdgeIterC it(*vit);it;it++) {
	  if(it->SourceVertex() != *vit) {
	    cerr << "HEMeshBaseBodyC::CheckMesh(), Incorrect vertex pointer. \n";
	    ret = false;
	    //return false;
	  }
	  if(it->Vertex() == *vit) {
	    cerr << "HEMeshBaseBodyC::CheckMesh(), Zero area face. \n";
	    ret = false;
	    //return false;
	  }
	}
      }
    }
    ONDEBUG(cerr << "HEMeshBaseBodyC::CheckMesh(), Checking faces. \n");
    HSetC<HEMeshBaseFaceC> faceDone;
    for(IntrDLIterC<HEMeshBaseFaceBodyC> fit(faces);fit;fit++) {
      HEMeshBaseFaceC curFace(*fit);
      ONDEBUG(cerr << " Checking face " << curFace.Hash() << "\n");
      if(faceDone.IsMember(curFace)) {
	cerr << "HEMeshBaseBodyC::CheckMesh(), Infinite loop in face links. \n";
	break;
      }
      faceDone += curFace;
      HSetC<HEMeshBaseEdgeC> edgeDone;
      for(HEMeshBaseFaceEdgeIterC efit(*fit);efit;efit++) {
	HEMeshBaseEdgeC curEdge(*efit);
	ONDEBUG(cerr << " Checking Edge " << curEdge.Hash() << "\n");
	if(edgeDone.IsMember(curEdge)) {
	  cerr << "HEMeshBaseBodyC::CheckMesh(), Infinite loop in edge links. \n";
	  break;
	}
	edgeDone += curEdge;
	if(efit->Face() != *fit) {
	  cerr << "HEMeshBaseBodyC::CheckMesh(), Bad face pointer found. \n";
	  ret = false;
	  //return false;
	}
	if(efit->HasPair()) {
	  if(!efit->Pair().HasPair()) {
	    cerr << "HEMeshBaseBodyC::CheckMesh(), Half paired edge found.  \n";
	    ret = false;
	    //return false;
	  }
	  if(*efit != efit->Pair().Pair()) {
	    if(*efit == efit->Pair())
	      cerr << "HEMeshBaseBodyC::CheckMesh(), Self paired edge found.  \n";
	    else
	      cerr << "HEMeshBaseBodyC::CheckMesh(), Mis-paired edge found.  \n";
	    ret = false;
	    //	    return false;
	  }
	} else {
	  if(!canBeOpen) {
	    cerr << "HEMeshBaseBodyC::CheckMesh(), Open face found. \n";
	    ret = false;
	    //return false;
	  }
	}
      }
    }
    return ret;
  }

  //: Insert a new vertex into the mesh.
  
  HEMeshBaseVertexC HEMeshBaseBodyC::InsertVertex() {
    HEMeshBaseVertexC ret = NewVertex();
    vertices.InsLast(ret.Body());
    return ret;
  }

  //: Create a new face.
  
  HEMeshBaseFaceC HEMeshBaseBodyC::NewFace() {
    return HEMeshBaseFaceC(true);
  }
  
  //: Create a new face.
  
  HEMeshBaseVertexC HEMeshBaseBodyC::NewVertex() {
    return HEMeshBaseVertexC(true);
  }
    
    //: Create a new face.
  
  HEMeshBaseEdgeC HEMeshBaseBodyC::NewEdge(HEMeshBaseVertexBodyC &vert,HEMeshBaseFaceBodyC &face) 
  { return HEMeshBaseEdgeC(vert,face); }
  
  
}

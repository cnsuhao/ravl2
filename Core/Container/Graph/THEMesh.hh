// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_THEMESH_HEADER
#define RAVL_THEMESH_HEADER 1
//! rcsid="$Id$"
//! lib=RavlCore
//! author="Charles Galambos"
//! docentry="Ravl.Core.Graphs.Half Edge Mesh"
//! date="24/4/2002"

#include "Ravl/THEMeshFace.hh"
#include "Ravl/THEMeshVertex.hh"
#include "Ravl/THEMeshEdge.hh"
#include "Ravl/THEMeshFaceIter.hh"
#include "Ravl/THEMeshVertexIter.hh"
#include "Ravl/HEMeshBase.hh"

namespace RavlN {
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshC;
  
  //! userlevel=Develop
  //: Half Edge Mesh Body
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshBodyC 
    : public HEMeshBaseBodyC
  {
  public:
    THEMeshBodyC()
    {}
    //: Default constructor.
    // Creates an empty mesh.
    
    THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> InsertVertex(const VertexDataT &data) {
      THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> vert(data);
      vertices.InsLast(vert.Body());
      return vert;
    }
    //: Insert a new vertex into the mesh.
    
#if 0    
    THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT> InsertFace(const SArray1dC<THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> > &vertices,
							     HashC<Tuple2C<THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT>,THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> >,
							     THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> > &edgeTab);
#endif
    //: Insert face defined by vertices.
    
  protected:
    friend class THEMeshC<VertexDataT,EdgeDataT,FaceDataT>;
  };
  

  //! userlevel=Normal
  //: Half Edge Mesh
  // Reference counted handle to mesh.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshC 
    : public HEMeshBaseC
  {
  public:
    THEMeshC()
    {}
    //: Default constructor.

    THEMeshC(bool)
      : HEMeshBaseC(*new THEMeshBodyC<VertexDataT,EdgeDataT,FaceDataT>())
    {}
    //: Constructor.
    
  protected:
    THEMeshBodyC<VertexDataT,EdgeDataT,FaceDataT> &Body()
    { return static_cast<THEMeshBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(HEMeshBaseC::Body()); }
    //: Access body.
    
    const THEMeshBodyC<VertexDataT,EdgeDataT,FaceDataT> &Body() const
    { return static_cast<const THEMeshBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(HEMeshBaseC::Body()); }
    //: Access body.
    
  public:
    
    THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> InsertVertex(const VertexDataT &data)
    { return Body().InsertVertex(data); }
    //: Insert a new vertex into the mesh.
    
    THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> InsertVertexOnEdge(THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> &edge)
    { return Body().InsertVertexOnEdge(edge); }
    //: Insert a vertex on an edge.
    
#if 0
    THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT> InsertFace(const SArray1dC<THEMeshVertexC> &vertices,
			    HashC<Tuple2C<THEMeshVertexC,THEMeshVertexC>, 
			    THEMeshEdgeC> &edgeTab)
    { return Body().InsertFace(vertices,edgeTab); }
    //: Insert face defined by vertices.
#endif
    
    THEMeshFaceIterC<VertexDataT,EdgeDataT,FaceDataT> Faces()
    { return THEMeshFaceIterC<VertexDataT,EdgeDataT,FaceDataT>(Body().faces); }
    //: List of faces in the mesh.
    // Use to create THEMeshFaceIterC.
    
    THEMeshVertexIterC<VertexDataT,EdgeDataT,FaceDataT> Vertices()
    { return THEMeshVertexIterC<VertexDataT,EdgeDataT,FaceDataT>(Body().vertices); }
    //: List of vertices.
    // Use to create THEMeshVertexIterC.

    THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT> FirstFace()
    { return THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT>(Body().faces.First()); }
    //: Get the first face in the mesh.
    // Note: The mesh must NOT be empty.
    
    THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> FirstVirtex()
    { return THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT>(Body().vertices.First()); }
    //: Get the first vertex in the mesh.
    // Note: The mesh must NOT be empty.

  };

}

#endif

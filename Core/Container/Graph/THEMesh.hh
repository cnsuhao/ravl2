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
//! file="Ravl/Core/Container/Graph/THEMesh.hh"

#include "Ravl/THEMeshFace.hh"
#include "Ravl/THEMeshVertex.hh"
#include "Ravl/THEMeshEdge.hh"
#include "Ravl/THEMeshFaceIter.hh"
#include "Ravl/THEMeshVertexIter.hh"
#include "Ravl/HEMeshBase.hh"
#include "Ravl/Empty.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Half Edge Mesh Body
  
  template<class VertexDataT,class FaceDataT = EmptyC,class EdgeDataT = EmptyC>
  class THEMeshBodyC 
    : public HEMeshBaseBodyC
  {
  public:
    THEMeshBodyC()
    {}
    //: Default constructor.
    // Creates an empty mesh.
    
    THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> InsertVertex(const VertexDataT &data) {
      THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> vert(data);
      vertices.InsLast(vert.Body());
      return vert;
    }
    //: Insert a new vertex into the mesh.
    
    THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> InsertFace(const FaceDataT &data,
							     const SArray1dC<HEMeshBaseVertexC> &vertices,
							     HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab) {
      THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> ret(data);
      HEMeshBaseBodyC::InsertFace(ret,vertices,edgeTab);
      return ret;
    }
    //: Insert face defined by vertices.
    
    THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> InsertFace(const SArray1dC<HEMeshBaseVertexC> &vertices,
							     HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab) {
#if 1
      static FaceDataT tmp;
      THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> ret(tmp);
      //THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> ret(*new THEMeshFaceBodyC<VertexDataT,FaceDataT,EdgeDataT>(tmp));
#else
      static FaceDataT tmp;
      //THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> ret = NewFace();
      THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> ret(*new THEMeshFaceBodyC<VertexDataT,FaceDataT,EdgeDataT>(tmp));
#endif
      HEMeshBaseBodyC::InsertFace(ret,vertices,edgeTab);
      return ret;
    }
    //: Insert face defined by vertices.
    
  protected:
    virtual HEMeshBaseFaceC NewFace()
    { return THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT>(*new THEMeshFaceBodyC<VertexDataT,FaceDataT,EdgeDataT>()); }
    //: Create a new face.
    
    virtual HEMeshBaseVertexC NewVertex()
    { return THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT>(*new THEMeshVertexBodyC<VertexDataT,FaceDataT,EdgeDataT>()); }
    //: Create a new face.
    
    virtual HEMeshBaseEdgeC NewEdge(HEMeshBaseVertexBodyC &vert,HEMeshBaseFaceBodyC &face)
    { return THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT>(*new THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT>(vert,face)); }
    //: Create a new face.
    
    friend class THEMeshC<VertexDataT,FaceDataT,EdgeDataT>;
  };
  

  //! userlevel=Normal
  //: Half Edge Mesh
  // Reference counted handle to mesh.
  
  template<class VertexDataT,class FaceDataT = EmptyC,class EdgeDataT = EmptyC>
  class THEMeshC 
    : public HEMeshBaseC
  {
  public:
    THEMeshC()
    {}
    //: Default constructor.

    explicit THEMeshC(bool)
      : HEMeshBaseC(*new THEMeshBodyC<VertexDataT,FaceDataT,EdgeDataT>())
    {}
    //: Constructor.
    
  protected:
    THEMeshBodyC<VertexDataT,FaceDataT,EdgeDataT> &Body()
    { return static_cast<THEMeshBodyC<VertexDataT,FaceDataT,EdgeDataT> &>(HEMeshBaseC::Body()); }
    //: Access body.
    
    const THEMeshBodyC<VertexDataT,FaceDataT,EdgeDataT> &Body() const
    { return static_cast<const THEMeshBodyC<VertexDataT,FaceDataT,EdgeDataT> &>(HEMeshBaseC::Body()); }
    //: Access body.
    
  public:
    
    THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> InsertVertex(const VertexDataT &data)
    { return Body().InsertVertex(data); }
    //: Insert a new vertex into the mesh.
    
    THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> InsertVertexOnEdge(THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> &edge)
    { return Body().InsertVertexOnEdge(edge); }
    //: Insert a vertex on an edge.
    
    THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> InsertFace(const FaceDataT &data,
							     const SArray1dC<HEMeshBaseVertexC> &vertices,
							     HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab)
    { return Body().InsertFace(data,vertices,edgeTab); }
    //: Insert face defined by vertices.

    THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> InsertFace(const SArray1dC<HEMeshBaseVertexC> &vertices,
							     HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab)
    { return Body().InsertFace(vertices,edgeTab); }
    //: Insert face defined by vertices.
    
    THEMeshFaceIterC<VertexDataT,FaceDataT,EdgeDataT> Faces()
    { return THEMeshFaceIterC<VertexDataT,FaceDataT,EdgeDataT>(Body().faces); }
    //: List of faces in the mesh.
    // Use to create THEMeshFaceIterC.
    
    THEMeshVertexIterC<VertexDataT,FaceDataT,EdgeDataT> Vertices()
    { return THEMeshVertexIterC<VertexDataT,FaceDataT,EdgeDataT>(Body().vertices); }
    //: List of vertices.
    // Use to create THEMeshVertexIterC.
    
    THEMeshFaceIterC<VertexDataT,FaceDataT,EdgeDataT> Faces() const
    { return THEMeshFaceIterC<VertexDataT,FaceDataT,EdgeDataT>(Body().faces); }
    //: List of faces in the mesh.
    // Use to create THEMeshFaceIterC.
    
    THEMeshVertexIterC<VertexDataT,FaceDataT,EdgeDataT> Vertices() const
    { return THEMeshVertexIterC<VertexDataT,FaceDataT,EdgeDataT>(Body().vertices); }
    //: List of vertices.
    // Use to create THEMeshVertexIterC.
    
    THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> FirstFace()
    { return THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT>(Body().faces.First()); }
    //: Get the first face in the mesh.
    // Note: The mesh must NOT be empty.
    
    THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> FirstVirtex()
    { return THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT>(Body().vertices.First()); }
    //: Get the first vertex in the mesh.
    // Note: The mesh must NOT be empty.

  };

}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_HEMESHBASE_HEADER
#define RAVL_HEMESHBASE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlCore
//! author="Charles Galambos"
//! docentry="Ravl.Core.Graphs.Half Edge Mesh"
//! date="24/4/2002"

#include "Ravl/HEMeshBaseFace.hh"
#include "Ravl/HEMeshBaseVertex.hh"
#include "Ravl/HEMeshBaseEdge.hh"
#include "Ravl/HEMeshBaseFaceIter.hh"
#include "Ravl/HEMeshBaseVertexIter.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/DList.hh"
#include "Ravl/IntrDList.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Hash.hh"
#include "Ravl/Tuple2.hh"

namespace RavlN {
  
  class HEMeshBaseC;
  
  //! userlevel=Develop
  //: Half Edge Mesh Body
  
  class HEMeshBaseBodyC 
    : public RCBodyVC
  {
  public:
    HEMeshBaseBodyC()
    {}
    //: Default constructor.
    // Creates an empty mesh.
    
    ~HEMeshBaseBodyC();
    //: Destructor.
    
    HEMeshBaseVertexC InsertVertexOnEdge(HEMeshBaseEdgeC edge);
    //: Insert a vertex on an edge.
    
    HEMeshBaseFaceC InsertFace(HEMeshBaseFaceC &face,
			       const SArray1dC<HEMeshBaseVertexC> &vertices,
			       HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab);
    //: Insert face defined by vertices.
    
    HEMeshBaseFaceC InsertFace(const SArray1dC<HEMeshBaseVertexC> &vertices,
			       HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab)  { 
      HEMeshBaseFaceC face = NewFace(); 
      return InsertFace(face,vertices,edgeTab); 
    }
    //: Insert face defined by vertices.
    
    bool InsertVertexInFace(HEMeshBaseVertexC &vert,HEMeshBaseFaceC &face);
    //: Insert a vertex into a face, link all vertexes already in the face to it.
    
    bool TwistEdge(HEMeshBaseEdgeC &edge,HEMeshBaseEdgeC &vertFrom,HEMeshBaseEdgeC &vertTo);
    //: Twist an edge that lies between two faces.
    // Both 'from' and 'to' must be one of the faces adjacent to 'edge'.
    
    UIntT NoFaces() const
    { return faces.Size(); }
    //: Get the number of faces.
    
    UIntT NoVertices() const
    { return vertices.Size(); }
    //: Get the number of vertices.
    
    bool CheckMesh(bool canBeOpen = false) const;
    //: Check mesh structure is consistant.
    // Returns false if an inconsistancy is found.
    
    HEMeshBaseVertexC InsertVertex();
    //: Insert a new vertex into the mesh.
    
    virtual HEMeshBaseFaceC NewFace();
    //: Create a new face.
    
    virtual HEMeshBaseVertexC NewVertex();
    //: Create a new face.
    
    virtual HEMeshBaseEdgeC NewEdge(HEMeshBaseVertexBodyC &vert,HEMeshBaseFaceBodyC &face);
    //: Create a new face.
    
    HEMeshBaseEdgeC NewEdge(const HEMeshBaseVertexC &vert,const HEMeshBaseFaceC &face)
    { return NewEdge(const_cast<HEMeshBaseVertexC &>(vert).Body(),const_cast<HEMeshBaseFaceC &>(face).Body()); }
    //: Create a new face.
    
  protected:
    IntrDListC<HEMeshBaseFaceBodyC> faces;  // List of faces in the mesh.
    IntrDListC<HEMeshBaseVertexBodyC> vertices; // List of vertices.
    
    friend class HEMeshBaseC;
  };
  

  //! userlevel=Normal
  //: Half Edge Mesh
  // Reference counted handle to mesh.
  
  class HEMeshBaseC 
    : public RCHandleC<HEMeshBaseBodyC>
  {
  public:
    HEMeshBaseC()
    {}
    //: Default constructor.

    HEMeshBaseC(bool)
      : RCHandleC<HEMeshBaseBodyC>(*new HEMeshBaseBodyC())
    {}
    //: Constructor.

  protected:
    HEMeshBaseC(HEMeshBaseBodyC &bod)
      : RCHandleC<HEMeshBaseBodyC>(bod)
    {}
    //: Body constructor.
    
    HEMeshBaseBodyC& Body()
    { return RCHandleC<HEMeshBaseBodyC>::Body(); }
    //: Access body.
    
    const HEMeshBaseBodyC& Body() const
    { return RCHandleC<HEMeshBaseBodyC>::Body(); }
    //: Access body.

    HEMeshBaseFaceC NewFace()
    { return Body().NewFace(); }
    //: Create a new face.
    
    HEMeshBaseVertexC NewVertex()
    { return Body().NewVertex(); }
    //: Create a new face.
    
    HEMeshBaseEdgeC NewEdge(HEMeshBaseVertexBodyC &vert,HEMeshBaseFaceBodyC &face)
    { return Body().NewEdge(vert,face); }
    //: Create a new face.
    
    HEMeshBaseEdgeC NewEdge(HEMeshBaseVertexC &vert,HEMeshBaseFaceC &face)
    { return Body().NewEdge(vert.Body(),face.Body()); }
    //: Create a new face.
    
  public:
    HEMeshBaseVertexC InsertVertex()
    { return Body().InsertVertex(); }
    //: Insert a new vertex into the mesh.
    
    HEMeshBaseVertexC InsertVertexOnEdge(HEMeshBaseEdgeC edge)
    { return Body().InsertVertexOnEdge(edge); }
    //: Insert a vertex on an edge.
    
    bool TwistEdge(HEMeshBaseEdgeC &edge,HEMeshBaseEdgeC &vertFrom,HEMeshBaseEdgeC &vertTo)
    { return Body().TwistEdge(edge,vertFrom,vertTo); }
    //: Twist an edge that lies between two faces.
    // Both 'from' and 'to' must be one of the faces adjacent to 'edge'
    
    HEMeshBaseFaceC InsertFace(HEMeshBaseFaceC &face,
			       const SArray1dC<HEMeshBaseVertexC> &vertices,
			       HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab)
    { return Body().InsertFace(face,vertices,edgeTab); }
    //: Insert face defined by vertices.
    
    HEMeshBaseFaceC InsertFace(const SArray1dC<HEMeshBaseVertexC> &vertices,
			       HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab)
    { return Body().InsertFace(vertices,edgeTab); }
    //: Insert face defined by vertices.
    
    bool InsertVertexInFace(HEMeshBaseVertexC &vert,HEMeshBaseFaceC &face)
    { return Body().InsertVertexInFace(vert,face); }
    //: Insert a vertex into a face, link all vertexes already in the face to it.
    // This method assumes 'vert' is not connected to a mesh.
    
    UIntT NoFaces() const
    { return Body().NoFaces(); }
    //: Get the number of faces.
    
    UIntT NoVertices() const
    { return Body().NoVertices(); }
    //: Get the number of vertices.
    
    bool CheckMesh(bool canBeOpen = false) const
    { return Body().CheckMesh(canBeOpen); }
    //: Check mesh structure is consistant.
    // Returns false if an inconsistancy is found.
    
    HEMeshBaseFaceIterC Faces()
    { return HEMeshBaseFaceIterC(Body().faces); }
    //: List of faces in the mesh.
    // Use to create HEMeshBaseFaceIterC.
    
    HEMeshBaseVertexIterC Vertices()
    { return HEMeshBaseVertexIterC(Body().vertices); }
    //: List of vertices.
    // Use to create HEMeshBaseVertexIterC.

    HEMeshBaseFaceC FirstFace()
    { return HEMeshBaseFaceC(Body().faces.First()); }
    //: Get the first face in the mesh.
    // Note: The mesh must NOT be empty.
    
    HEMeshBaseVertexC FirstVirtex()
    { return HEMeshBaseVertexC(Body().vertices.First()); }
    //: Get the first vertex in the mesh.
    // Note: The mesh must NOT be empty.

  };

}

#endif

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
    
    HEMeshBaseFaceC InsertFace(const SArray1dC<HEMeshBaseVertexC> &vertices,HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab);
    //: Insert face defined by vertices.
    
    UIntT NoFaces() const
    { return faces.Size(); }
    //: Get the number of faces.
    
    UIntT NoVertices() const
    { return vertices.Size(); }
    //: Get the number of vertices.
    
    bool CheckMesh(bool canBeOpen = false) const;
    //: Check mesh structure is consistant.
    // Returns false if an inconsistancy is found.
    
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
    
  public:
#if 0
    HEMeshBaseVertexC InsertVertex(const Vector3dC &position,const Vector3dC &norm)
    { return Body().InsertVertex(position,norm); }
    //: Insert a new vertex into the mesh.

    HEMeshBaseVertexC InsertVertex(const VertexC &vert)
    { return Body().InsertVertex(vert); }
    //: Insert a new vertex into the mesh.
#endif
    
    HEMeshBaseVertexC InsertVertexOnEdge(HEMeshBaseEdgeC edge)
    { return Body().InsertVertexOnEdge(edge); }
    //: Insert a vertex on an edge.
    
    HEMeshBaseFaceC InsertFace(const SArray1dC<HEMeshBaseVertexC> &vertices,HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> &edgeTab)
    { return Body().InsertFace(vertices,edgeTab); }
    //: Insert face defined by vertices.

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

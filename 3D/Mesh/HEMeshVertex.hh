// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_HEMESHVERTEX_HEADER 
#define RAVL3D_HEMESHVERTEX_HEADER 1
//! rcsid="$Id$"
//! lib=Ravl3D
//! docentry="Ravl.3D.Half Edge Mesh"
//! date="24/4/2002"
//! author="Charles Galambos"

#include "Ravl/DLink.hh"
#include "Ravl/3D/Vertex.hh"

namespace Ravl3DN {

  using namespace RavlN;
  
  class HEMeshVertexC;
  class HEMeshEdgeC;
  class HEMeshFaceC;
  class HEMeshC;
  class HEMeshFaceEdgeIterC;
  class HEMeshEdgeBodyC;
  class HEMeshBodyC;

  //! userlevel=Develop
  //: Vertex body.
  
  class HEMeshVertexBodyC
    : public DLinkC, // Link in list of all vertexes
      public VertexC
  {
  public:    
    HEMeshEdgeC FindEdge(const HEMeshVertexC &oth) const;
    //: Look for a connection from this vertex to oth.
    // Returns an invalid handle if ones is not found.
    
    HEMeshEdgeBodyC &FirstEdge()
    { return *edge; }
    //: Access edge.

    const HEMeshEdgeBodyC &FirstEdge() const
    { return *edge; }
    //: Access edge.
    
    HEMeshEdgeC Link(HEMeshVertexC newVert,HEMeshFaceC face);
    //: Link this vertex to newVert on indicated face
    // Both vertexes must share the face. This will effectively
    // split the face in two.
    
    UIntT Valence() const;
    //: Get the number of edges/faces linking to this vertexs.
    // This assumes this is a closed mesh.
    
  protected:
    HEMeshVertexBodyC(const Vector3dC &pos,const Vector3dC &norm)
      : VertexC(pos,norm),
	edge(0)
    {}
    //: Construct from a vertex position.

    HEMeshVertexBodyC(const VertexC &vert)
      : VertexC(vert),
	edge(0)
    {}
    //: Construct from a vertex position.
    
    HEMeshEdgeBodyC *edge; 
    // Ptr to one of the edges on the vertex.
    // This must always point to an edge going to
    // this vertex.
    
    friend class HEMeshVertexC;
    friend class HEMeshEdgeBodyC;
  };
  
  //! userlevel=Normal.
  //: Vertex.
  
  class HEMeshVertexC {
  public:
    HEMeshVertexC()
      : body(0)
    {}
    //: Default constructor.
    
    bool IsValid()
    { return body != 0; }
    //: Is this a valid Vertex ?
    
    HEMeshEdgeC FindEdge(const HEMeshVertexC &oth) const;
    //: Look for a connection from this vertex to oth.
    // Returns an invalid handle if ones is not found.
    
    HEMeshEdgeC FirstEdge() const;
    //: Access edge.
    
  protected:
    HEMeshVertexC(const Vector3dC &pos,const Vector3dC &norm)
      : body(new HEMeshVertexBodyC(pos,norm))
    {}
    //: Construct a new vetrex from position and normal
    
    HEMeshVertexC(const VertexC &vert)
      : body(new HEMeshVertexBodyC(vert))
    {}
    //: Construct a new vetrex from a vertex
    
    HEMeshVertexC(HEMeshVertexBodyC *nbody)
      : body(nbody)
    {}
    //: Construct from pointer.
    
    HEMeshVertexBodyC &Body()
    { return *body; }
    //: Access body.
    
    const HEMeshVertexBodyC &Body() const
    { return *body; }
    //: Access body.
    
  public:
    bool operator==(const HEMeshVertexBodyC &vert) const
    { return body == &vert; }
    //: Is this a handle to the vertex.
    
    bool operator!=(const HEMeshVertexBodyC &vert) const
    { return body != &vert; }
    //: Is this a handle to the vertex.
    
    VertexC &Vertex()
    { return Body(); }
    //: Access vertex information.
    
    const VertexC &Vertex() const
    { return Body(); }
    //: Access vertex information.
    
    Vector3dC &Position()
    { return Body().Position(); }
    //: Access position of vertex.

    const Vector3dC &Position() const
    { return Body().Position(); }
    //: Access position of vertex.
    
    Vector3dC &Normal()
    { return Body().Normal(); }
    //: Access normal at vertex.

    const Vector3dC &Normal() const
    { return Body().Normal(); }
    //: Access normal at vertex.

    UIntT Hash() const
    { return ((UIntT) body) >> 3; }
    //: Hash value for handle.
    
    bool operator==(const HEMeshVertexC &oth) const
    { return body == oth.body; }
    //: Is this a handle to the same object ?

    UIntT Valence() const
    { return Body().Valence(); }
    //: Get the number of edges/faces linking to this vertexs.
    // This assumes this is a closed mesh.
    
  private:
    HEMeshVertexBodyC *body;    
    friend class HEMeshBodyC;
    friend class HEMeshVertexBodyC;
    friend class HEMeshEdgeC;
    friend class HEMeshEdgeBodyC;
  };
  
  
}
#endif

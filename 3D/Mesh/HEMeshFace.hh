// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_HEMESHFACE_HEADER
#define RAVL3D_HEMESHFACE_HEADER 1
//! rcsid="$Id$"
//! lib=Ravl3D
//! docentry="Ravl.3D.Half Edge Mesh"
//! date="24/4/2002"
//! author="Charles Galambos"

#include "Ravl/DLink.hh"
#include "Ravl/3D/HEMeshEdge.hh"

namespace Ravl3DN {

  using namespace RavlN;
  
  class HEMeshVertexC;
  class HEMeshFaceC;
  class HEMeshFaceBodyC;
  class HEMeshC;
  class HEMeshFaceEdgeIterC;
  class HEMeshEdgeC;
  class HEMeshEdgeBodyC;
  class HEMeshBodyC;
  
  //! userlevel=Develop.
  //: Face in mesh.
  
  class HEMeshFaceBodyC 
    : public DLinkC // Link in list of all faces.
  {
  public:
    HEMeshFaceBodyC()
      : edge(0)
    {}
    //: Default constructor.
    
  protected:
    HEMeshEdgeBodyC *FirstEdge()
    { return edge; }
    //: Access first edge.
    
  public:
    void SetEdge(HEMeshEdgeBodyC *nedge)
    { edge = nedge; }
    //: Set first edge.
    
    UIntT NoEdges() const;
    //: Get number of edges on face.
    
    bool HasVertex(HEMeshVertexC vert) const;
    //: Check that the vertex is connected to this face.
    
    HEMeshEdgeC Edge() 
    { return HEMeshEdgeC(*edge); }
    //: Get an edge leading to the face.
    
  private:
    HEMeshEdgeBodyC *edge; // Ptr to one of the edges adjacent to the face.
    friend class HEMeshFaceEdgeIterC;
    friend class HEMeshFaceC;
  };

  //! userlevel=Normal.
  //: Face in mesh.
  
  class HEMeshFaceC 
  {
  public:
    HEMeshFaceC()
      : body(0)
    {}
    //: Default constructor
    
    bool IsValid() const
    { return body != 0; }
    //: Is this a valid handle ?

  protected:
    HEMeshFaceC(HEMeshFaceBodyC &bod)
      : body(&bod)
    {}
    //: Body constructor.
    
    HEMeshFaceC(bool)
      : body(new HEMeshFaceBodyC())
    {}
    //: Construct a new face.
    
    HEMeshFaceBodyC &Body()
    { return *body; }
    //: Access body.

    const HEMeshFaceBodyC &Body() const
    { return *body; }
    //: Access body.

    HEMeshEdgeBodyC *FirstEdge()
    { return Body().FirstEdge(); }
    //: Access first edge.
    
  public:
    void SetEdge(HEMeshEdgeC nedge)
    { Body().SetEdge(&nedge.Body()); }
    //: Set first edge.
    
    UIntT Hash() const
    { return ((UIntT) body) >> 3; }
    //: Hash value for handle.
    
    bool operator==(const HEMeshFaceC &oth) const
    { return body == oth.body; }
    //: Is this a handle to the same object ?
    
    UIntT NoEdges() const
    { return Body().NoEdges(); }
    //: Get number of edges on face.
    
    bool HasVertex(HEMeshVertexC vert) const
    { return Body().HasVertex(vert); }
    //: Check that the vertex is connected to this face.
    
    HEMeshEdgeC Edge() 
    { return Body().Edge(); }
    //: Get an edge leading to the face.
    
  private:
    HEMeshFaceBodyC *body;
    friend class HEMeshFaceEdgeIterC;
    friend class HEMeshBodyC;
    friend class HEMeshEdgeC;
  };
  
  //! userlevel=Normal
  //: Iterate through edges around a face.
  
  class HEMeshFaceEdgeIterC {
  public:
    HEMeshFaceEdgeIterC()
      : first(0),
	at(0)
    {}
    //: Default constructor.
    
    HEMeshFaceEdgeIterC(HEMeshFaceC &face)
      : first(face.FirstEdge()),
	at(face.FirstEdge())
    {}
    //: Construct from a face

    HEMeshFaceEdgeIterC(HEMeshFaceBodyC &face)
      : first(face.FirstEdge()),
	at(face.FirstEdge())
    {}
    //: Construct from a face
    
    bool First() { 
      at = first; 
      return at != 0;
    }
    //: Goto first element.
    // Returns true if the new element is valid.
    
    bool IsFirst()
    { return at != first && at != 0; }
    //: Is this the first element in list.
    
    bool Next() { 
      at = &(at->Next());
      if(at == first) {
	at = 0;
	return false;
      }
      return true;
    }
    //: Goto next edge around face.
    // Returns true if the new element is valid.
    
    bool operator++(int)
    { return Next(); }
    //: Goto next edge around face.
    // Returns true if the new element is valid.
    
    operator bool() const
    { return at != 0; }
    //: Test if we're at a valid element.
    // Returns true if we are.
    
    bool IsElm() const
    { return at != 0; }
    //: Test if we're at a valid element.
    // Returns true if we are.
    
    HEMeshEdgeC Data()
    { return HEMeshEdgeC(*at); }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const HEMeshEdgeC Data() const
    { return HEMeshEdgeC(*at); }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const HEMeshEdgeC operator *() const
    { return HEMeshEdgeC(*at); }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    HEMeshEdgeC operator *()
    { return HEMeshEdgeC(*at); }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const HEMeshEdgeBodyC *operator ->() const
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    HEMeshEdgeBodyC *operator->()
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
  protected:
    HEMeshEdgeBodyC *first;
    HEMeshEdgeBodyC *at;
  };
  
  //////////////////////////////////////////////////////
  
  inline
  HEMeshFaceC HEMeshEdgeC::OpenEdge()
  { return Body().OpenEdge(); }

}

#endif

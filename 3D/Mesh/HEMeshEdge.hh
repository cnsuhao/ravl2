// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_HEMESHEDGE_HEADER
#define RAVL3D_HEMESHEDGE_HEADER 1
//! rcsid="$Id$"
//! lib=Ravl3D
//! docentry="Ravl.3D.Half Edge Mesh"
//! date="24/4/2002"
//! author="Charles Galambos"

#include "Ravl/DLink.hh"
#include "Ravl/3D/HEMeshVertex.hh"

namespace Ravl3DN {

  using namespace RavlN;
  
  class HEMeshFaceC;
  class HEMeshFaceBodyC;
  class HEMeshC;
  class HEMeshFaceEdgeIterC;
  class HEMeshFaceBodyC;  
  class HEMeshEdgeBodyC;
  class HEMeshBodyC;
  
  //! userlevel=Develop
  //: Half edge in mesh.
  
  class HEMeshEdgeBodyC 
    : public DLinkC // Link in list of  vertex's around a face.
  {
  public:
    HEMeshEdgeBodyC &Next()
    { return static_cast<HEMeshEdgeBodyC &>(DLinkC::Next()); }
    //: Get next edge on face.
    
    HEMeshEdgeBodyC &Prev()
    { return static_cast<HEMeshEdgeBodyC &>(DLinkC::Prev()); }
    //: Get previous edge on face.
    
    HEMeshEdgeBodyC &Pair()
    { return *pair; }
    //: Edge pair.
    // HasPair() must have return
    // true before using this method.
    
    const HEMeshEdgeBodyC &Pair() const
    { return *pair; }
    //: Edge pair.
    // HasPair() must have return
    // true before using this method.
    
    bool HasPair() const
    { return pair != 0; }
    //: Does this edge have a pair.
    
    void SetPair(HEMeshEdgeBodyC &edge)
    { pair = &edge; }
    //: Set edge pair.
    
    void LinkAfter(HEMeshEdgeBodyC &edge) 
    { DLinkC::LinkAft(edge); }
    //: Link 'edge' after this one.
    // If the edge is already in a chain it MUST
    // be unlinked first with Unlink().
    
    void LinkBefore(HEMeshEdgeBodyC &edge) 
    { DLinkC::LinkBef(edge); }
    //: Link 'edge' before this one.
    // If the edge is already in a chain it MUST
    // be unlinked first with Unlink().

    HEMeshVertexC Vertex() const
    { return HEMeshVertexC(const_cast<HEMeshVertexBodyC &>(*vertex)); }
    //: Access vertex.
    
  protected:
    HEMeshEdgeBodyC()
      : pair(0)
    {}
    //: Default cosntructor.
    // the contents are left undefined.

    HEMeshEdgeBodyC(HEMeshVertexBodyC &vert,HEMeshFaceBodyC &nface)
      : vertex(&vert),
	face(&nface),
	pair(0)
    {}
    //: Cosntructor.
    // the contents are left undefined.
    
    HEMeshVertexBodyC *vertex;
    HEMeshFaceBodyC *face;    // Adjacent face.
    HEMeshEdgeBodyC *pair;     // Other edge in pair, is its zero this in an edge
    
    friend class HEMeshEdgeC;
  };
  
  //! userlevel=Normal
  //: Half edge in mesh.
  
  class HEMeshEdgeC {
  public:
    HEMeshEdgeC()
      : body(0)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    bool IsValid() const
    { return body != 0; }
    //: Is this a valid handle ?
    
  protected:
    HEMeshEdgeC(HEMeshVertexBodyC &vert,HEMeshFaceBodyC &face)
      : body(new HEMeshEdgeBodyC(vert,face))
    {}
    //: Constructor.
    
    HEMeshEdgeC(HEMeshEdgeBodyC &bod)
      : body(&bod)
    {}
    //: Body constructor.
    
    HEMeshEdgeBodyC &Body()
    { return *body; }
    //: Access body.
    
    const HEMeshEdgeBodyC &Body() const
    { return *body; }
    //: Access body.

  public:
    HEMeshEdgeC Next()
    { return HEMeshEdgeC(Body().Next()); }
    //: Get next edge on face.
    
    HEMeshEdgeC Prev()
    { return HEMeshEdgeC(Body().Prev()); }
    //: Get previous edge on face.
    
    void LinkAfter(HEMeshEdgeC &edge) 
    { Body().LinkAfter(edge.Body()); }
    //: Link 'edge' after this one.
    // If the edge is already in a chain it MUST
    // be unlinked first with Unlink().
    
    void LinkBefore(HEMeshEdgeC &edge) 
    { Body().LinkBefore(edge.Body()); }
    //: Link 'edge' before this one.
    // If the edge is already in a chain it MUST
    // be unlinked first with Unlink().
    
    void Unlink()
    { Body().Unlink(); }
    //: Unlink the edge from a faces edge list.
    
    void SetPair(HEMeshEdgeC edge)
    { Body().SetPair(edge.Body()); }
    //: Set edge pair.

    bool HasPair() const
    { return Body().HasPair(); }
    //: Does this edge have a pair.

    UIntT Hash() const
    { return ((UIntT) body) >> 3; }
    //: Hash value for handle.
    
    bool operator==(const HEMeshEdgeC &oth) const
    { return body == oth.body; }
    //: Is this a handle to the same object ?
    
  private:
    HEMeshEdgeBodyC *body;
    
    friend class HEMeshBodyC;
    friend class HEMeshVertexBodyC;
    friend class HEMeshVertexC;
    friend class HEMeshVertexEdgeIterC;
    friend class HEMeshFaceC;
    friend class HEMeshFaceEdgeIterC;
  };
  
  //////////////////////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Iterate through edges around a vertex.
  
  class HEMeshVertexEdgeIterC {
  public:
    HEMeshVertexEdgeIterC()
      : first(0),
	at(0)
    {}
    //: Default constructor.

    HEMeshVertexEdgeIterC(HEMeshVertexC &face)
      : first(&face.FirstEdge().Body()),
	at(&face.FirstEdge().Body())
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
      at = &at->Pair().Next();
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
    
    HEMeshEdgeBodyC &Data()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const HEMeshEdgeBodyC &Data() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const HEMeshEdgeBodyC &operator *() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    HEMeshEdgeBodyC &operator *()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.

    const HEMeshEdgeBodyC *operator ->() const
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    HEMeshEdgeBodyC *operator ->()
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
  protected:
    HEMeshEdgeBodyC *first;
    HEMeshEdgeBodyC *at;
  };

  /////////////////////////////////////////////////////////////////////////
  
  inline
  HEMeshEdgeC HEMeshVertexC::FindEdge(const HEMeshVertexC &oth) const
  { return Body().FindEdge(oth); }

  inline
  HEMeshEdgeC HEMeshVertexC::FirstEdge() const
  { return HEMeshEdgeC(const_cast<HEMeshEdgeBodyC &>(Body().FirstEdge())); }

}



#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_THEMESHEDGE_HEADER
#define RAVL_THEMESHEDGE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlCore
//! docentry="Ravl.Core.Graphs.Half Edge Mesh"
//! date="24/4/2002"
//! author="Charles Galambos"

#include "Ravl/HEMeshBaseEdge.hh"
#include "Ravl/THEMeshVertex.hh"

namespace RavlN {
  
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshC;
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshFaceC;
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshFaceBodyC;
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshFaceEdgeIterC;
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshFaceBodyC;  
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshBodyC;
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshFaceBodyC;
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshVertexEdgeIterC;
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshToVertexEdgeIterC;
  
  //! userlevel=Develop
  //: Half edge in mesh.
  
  template<class VertexDataT,class FaceDataT = EmptyC,class EdgeDataT = EmptyC>
  class THEMeshEdgeBodyC 
    : public HEMeshBaseEdgeBodyC
  {
  public:
    
  protected:
    
    THEMeshEdgeBodyC()
    {}
    //: Default cosntructor.
    // the contents are left undefined.

    THEMeshEdgeBodyC(THEMeshVertexBodyC<VertexDataT,FaceDataT,EdgeDataT> &vert,THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &nface)
    {}
    //: Cosntructor.
    // the contents are left undefined.
    
    friend class THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT>;
    friend class THEMeshFaceBodyC<VertexDataT,FaceDataT,EdgeDataT>;
    
    EdgeDataT data;
  };
  
  //! userlevel=Normal
  //: Half edge in mesh.
  
  template<class VertexDataT,class FaceDataT = EmptyC,class EdgeDataT = EmptyC>
  class THEMeshEdgeC 
    : public HEMeshBaseEdgeC
  {
  public:
    THEMeshEdgeC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    THEMeshEdgeC(THEMeshVertexBodyC<VertexDataT,FaceDataT,EdgeDataT> &vert,THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &face)
      : HEMeshBaseEdgeC(*new THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT>(vert,face))
    {}
    //: Constructor.
    
    THEMeshEdgeC(THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> vert,
		 THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> face);
    //: Constructor.
    
    THEMeshEdgeC(THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &bod)
      : HEMeshBaseEdgeC(bod)
    {}
    //: Body constructor.
    
    THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &Body()
    { return static_cast<THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &> (HEMeshBaseEdgeC::Body()); }
    //: Access body.
    
    const THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &Body() const
    { return static_cast<const THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &> (HEMeshBaseEdgeC::Body()); }
    //: Access body.
    
  public:
    THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> Next()
    { return THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT>(Body().Next()); }
    //: Get next edge on face.
    
    THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> Prev()
    { return THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT>(Body().Prev()); }
    //: Get previous edge on face.
    
    THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> Next() const
    { return THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT>(const_cast<THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(Body().Next())); }
    //: Get next edge on face.
    
    THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> Prev() const
    { return THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT>(const_cast<THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(Body().Prev())); }
    //: Get previous edge on face.
    
    void LinkAfter(THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> &edge) 
    { Body().LinkAfter(edge.Body()); }
    //: Link 'edge' after this one.
    // If the edge is already in a chain it MUST
    // be unlinked first with Unlink().
    
    void LinkBefore(THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> &edge) 
    { Body().LinkBefore(edge.Body()); }
    //: Link 'edge' before this one.
    // If the edge is already in a chain it MUST
    // be unlinked first with Unlink().

    void CutPaste(THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> firstCut, THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> firstNotCut) 
    { Body().CutPaste(firstCut.Body(),firstNotCut.Body()); }
    //: Splice edges between firstCut, and firstNotCut into this list.
    // Cuts the chain of edges starting at 'firstCut' and
    // ending at the edge before 'firstNotCut' from the chain.
    // The rest of the chain is linked together again. The cut part
    // is linked in after this edge.
    
    void SetPair(THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> edge)
    { Body().SetPair(edge.Body()); }
    //: Set edge pair.
    
    void SetFace(THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> face);
    //: Set the face associated with the edge.
    
    inline THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> Face();
    //: Access the face the edge lies on.
    
    THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> Pair()
    { return THEMeshEdgeC(Body().Pair()); }
    //: Access edge's apair.
    
    THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> Vertex() const
    { return Body().Vertex(); }
    //: Access vertex this edge goes to
    
    THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> SourceVertex() const 
    { return Prev().SourceVertex(); }
    //: Access vertex this edge comes from.
    
    THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> CollapseEdge() { 
      THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> ret = Body().CollapseEdge(); 
      delete body;
      body = 0;
      return ret;
    }
    //: Collapse edge to zero length.
    // This deletes the edge from the mesh and merges the vertex's
    // at either end.  The new vertex is returned. The edge is deleted,
    // and the handle becomes invalid after the call completes.
    
    THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> OpenEdge();
    //: Open an edge, merging the faces on either side.
    // This deletes the edge from the mesh and returns
    // a handle to the new face. <p>
    // NOT IMPLEMENTED
    
  private:
    
    friend class THEMeshBodyC<VertexDataT,FaceDataT,EdgeDataT>;
    friend class THEMeshVertexBodyC<VertexDataT,FaceDataT,EdgeDataT>;
    friend class THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT>;
    friend class THEMeshVertexEdgeIterC<VertexDataT,FaceDataT,EdgeDataT>;
    friend class THEMeshToVertexEdgeIterC<VertexDataT,FaceDataT,EdgeDataT>;
    friend class THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT>;
    friend class THEMeshFaceEdgeIterC<VertexDataT,FaceDataT,EdgeDataT>;
    friend class THEMeshFaceBodyC<VertexDataT,FaceDataT,EdgeDataT>;
  };
  
  //////////////////////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Iterate through edges around a vertex. 
  // This goes through all the half edges pointing away from the vertex.
  
  template<class VertexDataT,class FaceDataT = EmptyC,class EdgeDataT = EmptyC>
  class THEMeshVertexEdgeIterC 
    : public HEMeshBaseVertexEdgeIterC
  {
  public:
    THEMeshVertexEdgeIterC()
    {}
    //: Default constructor.

    THEMeshVertexEdgeIterC(THEMeshVertexBodyC<VertexDataT,FaceDataT,EdgeDataT> &vert) 
      : HEMeshBaseVertexEdgeIterC(vert)
    {}
    //: Construct from a face
    
    THEMeshVertexEdgeIterC(THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> &vert) 
      : HEMeshBaseVertexEdgeIterC(vert)
    {}
    //: Construct from a face
    
    THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &Data()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &Data() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &operator *() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &operator *()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.

    const THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> *operator ->() const
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> *operator ->()
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
  };

  /////////////////////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Iterate through edges around a vertex. 
  // This goes through all the half edges pointing to a vertex.
  
  template<class VertexDataT,class FaceDataT = EmptyC,class EdgeDataT = EmptyC>
  class THEMeshToVertexEdgeIterC 
    : public HEMeshBaseToVertexEdgeIterC
  {
  public:
    THEMeshToVertexEdgeIterC()
    {}
    //: Default constructor.
    
    THEMeshToVertexEdgeIterC(THEMeshVertexBodyC<VertexDataT,FaceDataT,EdgeDataT> &vert)
      : HEMeshBaseToVertexEdgeIterC(vert)
    {}
    //: Construct from a face
    
    THEMeshToVertexEdgeIterC(THEMeshVertexC<VertexDataT,FaceDataT,EdgeDataT> &vert) 
      : HEMeshBaseToVertexEdgeIterC(vert)
    {}
    //: Construct from a face
    
    THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &Data()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &Data() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &operator *() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> &operator *()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.

    const THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> *operator ->() const
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeBodyC<VertexDataT,FaceDataT,EdgeDataT> *operator ->()
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
  };
  
}



#endif

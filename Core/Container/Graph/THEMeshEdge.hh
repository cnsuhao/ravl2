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
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceBodyC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceEdgeIterC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceBodyC;  
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshEdgeBodyC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshBodyC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceBodyC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshVertexEdgeIterC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshToVertexEdgeIterC;
  
  //! userlevel=Develop
  //: Half edge in mesh.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshEdgeBodyC 
    : public HEMeshBaseEdgeBodyC
  {
  public:
    
  protected:
    
    THEMeshEdgeBodyC()
    {}
    //: Default cosntructor.
    // the contents are left undefined.

    THEMeshEdgeBodyC(THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT> &vert,THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &nface)
    {}
    //: Cosntructor.
    // the contents are left undefined.
    
    friend class THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT>;
    
    EdgeDataT data;
  };
  
  //! userlevel=Normal
  //: Half edge in mesh.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshEdgeC 
    : public HEMeshBaseEdgeC
  {
  public:
    THEMeshEdgeC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    THEMeshEdgeC(THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT> &vert,THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &face)
      : HEMeshBaseEdgeC(*new THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT>(vert,face))
    {}
    //: Constructor.
    
    THEMeshEdgeC(THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> vert,
		 THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT> face);
    //: Constructor.
    
    THEMeshEdgeC(THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &bod)
      : HEMeshBaseEdgeC(bod)
    {}
    //: Body constructor.
    
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &Body()
    { return static_cast<THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &> (HEMeshBaseEdgeC::Body()); }
    //: Access body.
    
    const THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &Body() const
    { return static_cast<const THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &> (HEMeshBaseEdgeC::Body()); }
    //: Access body.
    
  public:
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Next()
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(Body().Next()); }
    //: Get next edge on face.
    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Prev()
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(Body().Prev()); }
    //: Get previous edge on face.
    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Next() const
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(const_cast<THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(Body().Next())); }
    //: Get next edge on face.
    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Prev() const
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(const_cast<THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(Body().Prev())); }
    //: Get previous edge on face.
    
    void LinkAfter(THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> &edge) 
    { Body().LinkAfter(edge.Body()); }
    //: Link 'edge' after this one.
    // If the edge is already in a chain it MUST
    // be unlinked first with Unlink().
    
    void LinkBefore(THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> &edge) 
    { Body().LinkBefore(edge.Body()); }
    //: Link 'edge' before this one.
    // If the edge is already in a chain it MUST
    // be unlinked first with Unlink().

    void CutPaste(THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> firstCut, THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> firstNotCut) 
    { Body().CutPaste(firstCut.Body(),firstNotCut.Body()); }
    //: Splice edges between firstCut, and firstNotCut into this list.
    // Cuts the chain of edges starting at 'firstCut' and
    // ending at the edge before 'firstNotCut' from the chain.
    // The rest of the chain is linked together again. The cut part
    // is linked in after this edge.
    
    void SetPair(THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> edge)
    { Body().SetPair(edge.Body()); }
    //: Set edge pair.
    
    void SetFace(THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT> face);
    //: Set the face associated with the edge.
    
    inline THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT> Face();
    //: Access the face the edge lies on.
    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Pair()
    { return THEMeshEdgeC(Body().Pair()); }
    //: Access edge's apair.
    
    THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> Vertex() const
    { return Body().Vertex(); }
    //: Access vertex this edge goes to
    
    THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> SourceVertex() const 
    { return Prev().SourceVertex(); }
    //: Access vertex this edge comes from.
    
    THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> CollapseEdge() { 
      THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> ret = Body().CollapseEdge(); 
      delete body;
      body = 0;
      return ret;
    }
    //: Collapse edge to zero length.
    // This deletes the edge from the mesh and merges the vertex's
    // at either end.  The new vertex is returned. The edge is deleted,
    // and the handle becomes invalid after the call completes.
    
    THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT> OpenEdge();
    //: Open an edge, merging the faces on either side.
    // This deletes the edge from the mesh and returns
    // a handle to the new face. <p>
    // NOT IMPLEMENTED
    
  private:
    
    friend class THEMeshBodyC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshVertexEdgeIterC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshToVertexEdgeIterC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshFaceEdgeIterC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT>;
  };
  
  //////////////////////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Iterate through edges around a vertex. 
  // This goes through all the half edges pointing away from the vertex.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshVertexEdgeIterC 
    : public HEMeshBaseVertexEdgeIterC
  {
  public:
    THEMeshVertexEdgeIterC()
    {}
    //: Default constructor.

    THEMeshVertexEdgeIterC(THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT> &vert) 
      : HEMeshBaseVertexEdgeIterC(vert)
    {}
    //: Construct from a face
    
    THEMeshVertexEdgeIterC(THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> &vert) 
      : HEMeshBaseVertexEdgeIterC(vert)
    {}
    //: Construct from a face
    
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &Data()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &Data() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &operator *() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &operator *()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.

    const THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> *operator ->() const
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> *operator ->()
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
  };

  /////////////////////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Iterate through edges around a vertex. 
  // This goes through all the half edges pointing to a vertex.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshToVertexEdgeIterC 
    : public HEMeshBaseToVertexEdgeIterC
  {
  public:
    THEMeshToVertexEdgeIterC()
    {}
    //: Default constructor.
    
    THEMeshToVertexEdgeIterC(THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT> &vert)
      : HEMeshBaseToVertexEdgeIterC(vert)
    {}
    //: Construct from a face
    
    THEMeshToVertexEdgeIterC(THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> &vert) 
      : HEMeshBaseToVertexEdgeIterC(vert)
    {}
    //: Construct from a face
    
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &Data()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &Data() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &operator *() const
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &operator *()
    { return *at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.

    const THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> *operator ->() const
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> *operator ->()
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
  };
  
}



#endif

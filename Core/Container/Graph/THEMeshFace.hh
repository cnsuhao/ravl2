// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_THEMESHFACE_HEADER
#define RAVL_THEMESHFACE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlCore
//! docentry="Ravl.Core.Graphs.Half Edge Mesh"
//! date="24/4/2002"
//! author="Charles Galambos"

#include "Ravl/DLink.hh"
#include "Ravl/HEMeshBaseFace.hh"
#include "Ravl/THEMeshEdge.hh"

namespace RavlN {
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshVertexC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceBodyC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceEdgeIterC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshEdgeC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshEdgeBodyC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshBodyC;  
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceIterC;
  
  //! userlevel=Develop
  //: Face in mesh.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshFaceBodyC 
    : protected HEMeshBaseFaceBodyC
  {
  public:
    THEMeshFaceBodyC()
    {}
    //: Default constructor.

    THEMeshFaceBodyC(const FaceDataT &faceData)
      : data(faceData)
    {}
    //: Constructor.
    
    THEMeshFaceBodyC(THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> &nedge)
      : HEMeshBaseFaceBodyC(&nedge)
    {}
    //: Default constructor.
    
  protected:
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> *FirstEdge()
    { return static_cast<THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> *>(edge); }
    //: Access first edge.
    
  public:        
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Edge() 
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(*edge); }
    //: Get an edge leading to the face.
    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> FindEdge(THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> a);
    //: Find the edge linking to vertex a.
    // If edge is not found an invalid handle is returned.
    
    FaceDataT &Data()
    { return data; }
    //: Access data.
    
    const FaceDataT &Data() const
    { return data; }
    //: Access data.
    
  private:
    FaceDataT data;
    
    friend class THEMeshFaceEdgeIterC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshBodyC<VertexDataT,EdgeDataT,FaceDataT>;
  };
  
  //! userlevel=Normal
  //: Face in mesh.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshFaceC 
    : public HEMeshBaseFaceC
  {
  public:
    THEMeshFaceC()
    {}
    //: Default constructor
    
  protected:
    THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &Body()
    { return static_cast<THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(HEMeshBaseFaceC::Body()); }
    //: Body access.
    
    const THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &Body() const
    { return static_cast<const THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(HEMeshBaseFaceC::Body()); }
    //: Body access.
    
  public:
    FaceDataT &Data()
    { return Body().Data(); }
    //: Access data.
    
    const FaceDataT &Data() const
    { return Body().Data(); }
    //: Access data.

  protected:
    THEMeshFaceC(THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &bod)
      : HEMeshBaseFaceC(bod)
    {}
    //: Body constructor.
    
    THEMeshFaceC(const FaceDataT &faceData)
      : HEMeshBaseFaceC(new THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT>(faceData))
    {}
    //: Construct a new face.

    THEMeshFaceC(THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> edge)
      : HEMeshBaseFaceC(new THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT>(edge.Body()))
    {}
    //: Construct a new face.
    
    
#if 0
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> *FirstEdge()
    { return Body().FirstEdge(); }
    //: Access first edge.
#endif
  public:    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Edge() 
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(Body().Edge()); }
    //: Get an edge leading to the face.

#if 0    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> FindEdge(THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> a)
    { return Body().FindEdge(a); }
    //: Find the edge linking to vertex a.
    // If edge is not found an invalid handle is returned.
#endif    
    
  private:
    friend class THEMeshFaceEdgeIterC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshBodyC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshFaceIterC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshC<VertexDataT,EdgeDataT,FaceDataT>;
  };
  
  //! userlevel=Normal
  //: Iterate through edges around a face.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>
  class THEMeshFaceEdgeIterC 
    : public HEMeshBaseFaceEdgeIterC
  {
  public:
    THEMeshFaceEdgeIterC()
    {}
    //: Default constructor.
    
    THEMeshFaceEdgeIterC(THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT> &face)
      : HEMeshBaseFaceEdgeIterC(face)
    {}
    //: Construct from a face
    
    THEMeshFaceEdgeIterC(THEMeshFaceBodyC<VertexDataT,EdgeDataT,FaceDataT> &face)
      : HEMeshBaseFaceEdgeIterC(face)
    {}
    //: Construct from a face
    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Data()
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(*at); }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Data() const
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(*at); }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> operator *() const
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(*at); }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> operator *()
    { return THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>(*at); }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    const THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> *operator ->() const
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
    THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT> *operator->()
    { return at; }
    //: Access edge.
    // Iterator must be at a valid element
    // before calling this method.
    
  };
  
}

#endif

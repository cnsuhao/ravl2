// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_THEMESHVERTEX_HEADER 
#define RAVL_THEMESHVERTEX_HEADER 1
//! rcsid="$Id$"
//! lib=RavlCore
//! docentry="Ravl.Core.Graphs.Half Edge Mesh"
//! date="24/4/2002"
//! author="Charles Galambos"

#include "Ravl/HEMeshBaseVertex.hh"

namespace RavlN {
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshVertexC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshEdgeC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshFaceEdgeIterC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshEdgeBodyC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshBodyC;
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshVertexIterC;
  
  //! userlevel=Develop
  //: Vertex body.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>  
  class THEMeshVertexBodyC
    : public HEMeshBaseVertexBodyC // Link in list of all vertexes
  {
  public:    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> FindEdge(const THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> &oth) const;
    //: Look for a connection from this vertex to oth.
    // Returns an invalid handle if ones is not found.
    
#if 0
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> Link(THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> newVert,THEMeshFaceC<VertexDataT,EdgeDataT,FaceDataT> face)
    { return Link(newVert,face); }
    //: Link this vertex to newVert on indicated face
    // Both vertexes must share the face. This will effectively
    // split the face in two.
#endif    
    
    VertexDataT &Data()
    { return data; }
    //: Access data.
    
    const VertexDataT &Data() const
    { return data; }
    //: Access data.
    
  protected:
    THEMeshVertexBodyC()
    {}
    //: Default constructor.

    THEMeshVertexBodyC(const VertexDataT &ndata)
      : data(ndata)
    {}
    //: Construct from a vertex data.
    
    VertexDataT data;
    
    friend class THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT>;
  };
  
  //! userlevel=Normal
  //: Vertex.
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>  
  class THEMeshVertexC 
    : public HEMeshBaseVertexC // Link in list of all vertexes
  {
  public:
    THEMeshVertexC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT> FindEdge(const THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> &oth) const;
    //: Look for a connection from this vertex to oth.
    // Returns an invalid handle if ones is not found.
    
  protected:
    
    THEMeshVertexC(THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT> &nbody)
      : HEMeshBaseVertexC(&nbody)
    {}
    //: Body constructor.
    
    THEMeshVertexC(const VertexDataT &data)
      : HEMeshBaseVertexC(*new THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT>(data))
    {}
    //: Constructor.
    
    THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT> &Body()
    { return static_cast<THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(HEMeshBaseVertexC::Body()); }
    //: Access body.
    
    const THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT> &Body() const
    { return static_cast<const THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT> &>(HEMeshBaseVertexC::Body()); }
    //: Access body.
    
  public:
    
  private:
    friend class THEMeshBodyC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshVertexBodyC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshEdgeC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshEdgeBodyC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshVertexIterC<VertexDataT,EdgeDataT,FaceDataT>;
    friend class THEMeshC<VertexDataT,EdgeDataT,FaceDataT>;
  };
  
  
}
#endif

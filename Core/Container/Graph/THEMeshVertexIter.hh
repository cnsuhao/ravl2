// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_THEMESHVERTEXITER_HEADER
#define RAVL_THEMESHVERTEXITER_HEADER 1
//! rcsid="$Id$"
//! lib=RavlCore
//! author="Charles Galambos"
//! docentry="Ravl.Core.Graphs.Half Edge Mesh"
//! date="22/5/2002"

#include "Ravl/THEMeshVertex.hh"
#include "Ravl/HEMeshBaseVertexIter.hh"

namespace RavlN {
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT> class THEMeshC;
  
  //! userlevel=Normal
  //: Mesh vertex iterator.
  // Note: It is the users responsibility to ensure the current vertex of the interator is NOT
  // deleted until the iterator is moved to another element. 
  
  template<class VertexDataT,class EdgeDataT,class FaceDataT>  
  class THEMeshVertexIterC 
    : public HEMeshBaseVertexIterC  
  {
  public:
    THEMeshVertexIterC()
    {}
    //: Default constructor.

    THEMeshVertexIterC(IntrDListC<HEMeshBaseVertexBodyC> &iter)
      : HEMeshBaseVertexIterC(iter)
    {}
    //: Constructor from a IntrDListC.
    
    THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> Data()
    { return THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT>(HEMeshBaseVertexIterC::Data()); }
    //: Access Vertex.

    const THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> Data() const
    { return THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT>(HEMeshBaseVertexIterC::Data()); }
    //: Access Vertex.

    THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> operator*()
    { return THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT>(HEMeshBaseVertexIterC::Data()); }
    //: Access Vertex.
    
    const THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT> operator*() const
    { return THEMeshVertexC<VertexDataT,EdgeDataT,FaceDataT>(HEMeshBaseVertexIterC::Data()); }
    //: Access Vertex.
    
  protected:
    
    friend class THEMeshC<VertexDataT,EdgeDataT,FaceDataT>;
  };
  
}


#endif

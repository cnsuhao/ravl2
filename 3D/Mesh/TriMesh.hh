// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_TRIMESH_HEADER
#define RAVL3D_TRIMESH_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=Ravl3D
//! docentry="Ravl.3D.Mesh"
//! author="Charles Galambos"
//! file="Ravl/3D/Mesh/TriMesh.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/3D/Tri.hh"

namespace Ravl3DN {
  using namespace RavlN;
  
  class TriMeshBodyC;
  class TriMeshC;
  
  //! userlevel=Develop
  //: Tri set body.
  
  class TriMeshBodyC
    : public RCBodyVC
  {
  public:
    TriMeshBodyC()
    {}
    
    TriMeshBodyC(UIntT noVertices,UIntT noFaces)
      : vertices(noVertices),
	faces(noFaces)
    {}
    //: Construct a mesh with a number of vertices and faces.
    // The inital values in the mesh are undefined.
    
    TriMeshBodyC(const SArray1dC<Vector3dC> &v,const SArray1dC<UIntT> &faceInd);
    //: Construct from an array of vertexes and an array of indexes.
    // The length of faceInd should be a power of 3, success triples are taken
    // from it to form the faces in the mesh.
    
    TriMeshBodyC(const SArray1dC<VertexC> &v,const SArray1dC<TriC> &nfaces,bool haveTextureCoord=false)
      : vertices(v),
	faces(nfaces),
	haveTexture(haveTextureCoord)
    {}
    //: Construct from an array of vertexes and an array of tri's.
    // The TriC's must refer to elements in 'v'
    
    RCBodyVC& Copy() const;
    //: Make a copy of the mesh.
    
    SArray1dC<VertexC> &Vertices()
    { return vertices; }
    //: Access a list of all vertices in the mesh.

    const SArray1dC<VertexC> &Vertices() const
    { return vertices; }
    //: Access a list of all vertices in the mesh.
    
    SArray1dC<TriC> &Faces()
    { return faces; }
    //: Access array of triangles in the mesh.
    
    const SArray1dC<TriC> &Faces() const
    { return faces; }
    //: Access array of triangles in the mesh.
    
    void FlipTriangles(void);
    //: Flips the mesh surface
    
    Vector3dC Centroid() const;
    //: Centre of triset.
    // - average vertex position
    
    SArray1dC<UIntT> FaceIndexes() const;
    //: Create an array of faces indexes.
    // each successive triple of indexes represents a face in the mesh.
    
    UIntT Index(const TriC &tri,int no) const
    { return tri.VertexPtr(no) - &(vertices[0]); }
    //: Find the index of a TriC's vertex.
    // no should be 0 to 2.
    
    void Limits(Vector3dC &min,Vector3dC &max) const;
    //: Find largest and smallest for each compoent of all vertices.
    
    void UpdateVertexNormals();
    //: Recalculate vertex normals.
    
    void OffsetScale(const Vector3dC &off,RealT scale);
    //: Offset and Scale mesh by given values.
    
    bool HaveTextureCoord() const
    { return haveTexture; }
    //: Do we have texture coordinates?

    void SetTextureCoord(bool val)
    { haveTexture = val; }
    //: Set have texture coordinates flag.
    
  protected:
    SArray1dC<VertexC> vertices; // Array of vertex positions.
    SArray1dC<TriC> faces;     // Array of triangles.
    bool haveTexture;
  };
  
  
  //! userlevel=Normal
  //: Tri set.

  class TriMeshC
    : public RCHandleC<TriMeshBodyC>
  {
  public:
    TriMeshC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    TriMeshC(const SArray1dC<Vector3dC> &v,const SArray1dC<UIntT> &faceInd)
      : RCHandleC<TriMeshBodyC>(*new TriMeshBodyC(v,faceInd))
    {}
    //: Construct from an array of vertexes and an array of indexes.
    // The length of faceInd should be a power of 3, success triples are taken
    // from it to form the faces in the mesh.

    TriMeshC(const SArray1dC<VertexC> &v,const SArray1dC<TriC> &nfaces,bool haveTextureCoord=false)
      : RCHandleC<TriMeshBodyC>(*new TriMeshBodyC(v,nfaces,haveTextureCoord))
    {}
    //: Construct from an array of vertexes and an array of tri's.
    // The TriC's must refer to elements in 'v'
    
    TriMeshC(UIntT noVertices,UIntT noFaces)
      : RCHandleC<TriMeshBodyC>(*new TriMeshBodyC(noVertices,noFaces))
    {}
    
  protected:
    TriMeshC(TriMeshBodyC &bod)
      : RCHandleC<TriMeshBodyC>(bod)
    {}
    //: Body constructor.
    
    TriMeshBodyC &Body()
    { return RCHandleC<TriMeshBodyC>::Body(); }
    //: Access body.

    const TriMeshBodyC &Body() const
    { return RCHandleC<TriMeshBodyC>::Body(); }
    //: Access body.
    
  public:
    TriMeshC Copy() const
    { return TriMeshC(static_cast<TriMeshBodyC &>(Body().Copy())); }
    //: Make a copy of the mesh.

    SArray1dC<VertexC> &Vertices()
    { return Body().Vertices(); }
    //: Access a list of all vertices in the mesh.

    const SArray1dC<VertexC> &Vertices() const
    { return Body().Vertices(); }
    //: Access a list of all vertices in the mesh.
    
    SArray1dC<TriC> &Faces()
    { return Body().Faces(); }
    //: Access array of triangles in the mesh.
    
    const SArray1dC<TriC> &Faces() const
    { return Body().Faces(); }
    //: Access array of triangles in the mesh.
    
    void FlipTriangles(void)      
    { Body().FlipTriangles(); }
    //: Flips the mesh surface
    
    Vector3dC Centroid() const
    { return Body().Centroid(); }
    //: Centre of triset.
    // - average vertex position
    
    SArray1dC<UIntT> FaceIndexes() const
    { return Body().FaceIndexes(); }
    //: Create an array of faces indexes.
    // each successive triple of indexes represents a face in the mesh.
    
    void UpdateVertexNormals()
    {  Body().UpdateVertexNormals(); }
    //: Recalculate vertex normals.
    
    UIntT Index(const TriC &tri,int no) const
    { return Body().Index(tri,no); }
    //: Find the index of a TriC's vertex.
    // no should be 0 to 2.
    
    void Limits(Vector3dC &min,Vector3dC &max) const
    { Body().Limits(min,max); }
    //: Find largest and smallest for each compoent of all vertices.
    
    void OffsetScale(const Vector3dC &off,RealT scale)
    { Body().OffsetScale(off,scale); }
    //: Offset and Scale mesh by given values.
    
    bool HaveTextureCoord() const
    { return Body().HaveTextureCoord(); }
    //: Do we have texture co-ordinates?
    
    void SetTextureCoord(bool val)
    { Body().SetTextureCoord(val); }
    //: Set have texture coordinates flag.
    
  };

  ostream &operator<<(ostream &s,const TriMeshC &ts);
  istream &operator>>(istream &s,TriMeshC &ts);
  
  BinIStreamC &operator>>(BinIStreamC &s,TriMeshC &ts);
  BinOStreamC &operator<<(BinOStreamC &s,const TriMeshC &ts);
  
}

#endif

#ifndef RAVL_TRISET_HEADER
#define RAVL_TRISET_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/RefCounter.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/SArray1d.hh"

namespace Ravl3DN {
  using namespace RavlN;

  class TriSetBodyC;
  

  //! userlevel=Normal
  //: Vertex in a mesh.
  // This holds a position and a normal.
  
  class VertexC {
  public:
    VertexC()
    {}
    //: Default constructor.
    
    VertexC(const Vector3dC &pos,const Vector3dC &norm)
      : at(pos),
	normal(norm)
    {}
    //: Constructor.
    
    Vector3dC &Position()
    { return at; }
    //: Access position of vertex.

    const Vector3dC &Position() const
    { return at; }
    //: Access position of vertex.
    
    Vector3dC &Normal()
    { return normal; }
    //: Access normal at vertex.

    const Vector3dC &Normal() const
    { return normal; }
    //: Access normal at vertex.
    
  protected:
    Vector3dC at;
    Vector3dC normal;
  };
  
  inline ostream &operator<<(ostream &s,const VertexC &v) { 
    s << v.Position() << ' ' << v.Normal();
    return s;
  }

  inline istream &operator>>(istream &s,VertexC &v) { 
    s >> v.Position() >> v.Normal();
    return s;
  }
  
  BinOStreamC &operator<<(BinOStreamC &s,const VertexC &v);
  BinIStreamC &operator>>(BinIStreamC &s,VertexC &v);
  
  //! userlevel=Normal
  //: Triangle in TriSet.
  // Tri's must be associated with a tri set, in the parent
  // triset goes out of scope the behavour of a tri from
  // it is undefined.
  
  class TriC 
  {
  public:
    TriC()
    {}
    //: Default constructor.
    
    TriC(const TFVectorC<VertexC *,3> &v)
      : vertices(v)
    {}
    //: Construct from another vector.
    
    void Flip(void)
    {  Swap(vertices[0],vertices[2]); }
    //: Flips the triangle.
    // Reverse the order of the vertices in the triangle.
    
    VertexC &Vertex(UIntT ind) {
      RavlAssert(ind < 3);
      return *(vertices[ind]);
    }
    //: Access vertex.
    
    const VertexC &Vertex(UIntT ind) const 
    { return *(vertices[ind]); }
    //: Access vertex.
    
    const Vector3dC &operator[](UIntT ind) const
    { return vertices[ind]->Position(); }
    //: Access position of vertex.

    Vector3dC &operator[](UIntT ind)
    { return vertices[ind]->Position(); }
    //: Access position of vertex.
    
    const Vector3dC &FaceNormal() const 
    { return normal; }
    //: Unit normal orthogonal to triangle plane
        
    Vector3dC &Normal(UIntT n) 
    { return vertices[n]->Normal(); }
    //: Access normal for a vertex.
    
    const Vector3dC Normal(UIntT n) const
    { return vertices[n]->Normal(); }
    //: Access normal for a vertex.

    Vector3dC &Position(UIntT n) 
    { return vertices[n]->Position(); }
    //: Access normal for a vertex.
    
    const Vector3dC Position(UIntT n) const
    { return vertices[n]->Position(); }
    //: Access normal for a vertex.
    
    void UpdateFaceNormal()
    { normal = (Vector3dC(Position(1) - Position(0)).Cross(Position(2) - Position(0))).Unit(); }
    //: Update the face normal.
    
    VertexC *&VertexPtr(UIntT n)
    { return vertices[n]; }
    //: Access vertex pointer.
    // Advanced users only.
    
    VertexC *VertexPtr(UIntT n) const
    { return vertices[n]; }
    //: Access vertex pointer.
    // Advanced users only.
  protected:
    TFVectorC<VertexC *,3> vertices;
    Vector3dC normal;
  };
  
  
  //! userlevel=Develop
  //: Tri set body.
  
  class TriSetBodyC
    : public RCBodyVC
  {
  public:
    TriSetBodyC()
    {}
    
    TriSetBodyC(UIntT noVertices,UIntT noFaces)
      : vertices(noVertices),
	faces(noFaces)
    {}
    //: Construct a mesh with a number of vertices and faces.
    // The inital values in the mesh are undefined.
    
    TriSetBodyC(const SArray1dC<Vector3dC> &v,const SArray1dC<UIntT> &faceInd);
    //: Construct from an array of vertexes and an array of indexes.
    // The length of faceInd should be a power of 3, success triples are taken
    // from it to form the faces in the mesh.
    
    TriSetBodyC(const SArray1dC<VertexC> &v,const SArray1dC<TriC> &nfaces)
      : vertices(v),
	faces(nfaces)
    {}
    //: Construct from an array of vertexes and an array of tri's.
    // The TriC's must refer to elements in 'v'
    
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
    
    UIntT Index(const TriC &tri,int no)
    { return tri.VertexPtr(no) - &(vertices[0]); }
    //: Find the index of a TriC's vertex.
    // no should be 0 to 2.
    
    void UpdateVertexNormals();
    //: Recalculate vertex normals.
  protected:
    SArray1dC<VertexC> vertices; // Array of vertex positions.
    SArray1dC<TriC> faces;     // Array of triangles.
  };
  
  
  //! userlevel=Normal
  //: Tri set.

  class TriSetC
    : public RCHandleC<TriSetBodyC>
  {
  public:
    TriSetC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    TriSetC(const SArray1dC<Vector3dC> &v,const SArray1dC<UIntT> &faceInd)
      : RCHandleC<TriSetBodyC>(*new TriSetBodyC(v,faceInd))
    {}
    //: Construct from an array of vertexes and an array of indexes.
    // The length of faceInd should be a power of 3, success triples are taken
    // from it to form the faces in the mesh.

    TriSetC(const SArray1dC<VertexC> &v,const SArray1dC<TriC> &nfaces)
      : RCHandleC<TriSetBodyC>(*new TriSetBodyC(v,nfaces))
    {}
    //: Construct from an array of vertexes and an array of tri's.
    // The TriC's must refer to elements in 'v'
    
  protected:
    TriSetC(TriSetBodyC &bod)
      : RCHandleC<TriSetBodyC>(bod)
    {}
    //: Body constructor.
    
    TriSetBodyC &Body()
    { return RCHandleC<TriSetBodyC>::Body(); }
    //: Access body.

    const TriSetBodyC &Body() const
    { return RCHandleC<TriSetBodyC>::Body(); }
    //: Access body.
    
  public:
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
    { return Body().UpdateVertexNormals(); }
    //: Recalculate vertex normals.
    
    UIntT Index(const TriC &tri,int no)
    { return Body().Index(tri,no); }
    //: Find the index of a TriC's vertex.
    // no should be 0 to 2.
    
  };

  ostream &operator<<(ostream &s,const TriSetC &ts);
  istream &operator>>(istream &s,TriSetC &ts);
  
  BinIStreamC &operator>>(BinIStreamC &s,TriSetC &ts);
  BinOStreamC &operator<<(BinOStreamC &s,const TriSetC &ts);
  
}

#endif

#ifndef RAVL3D_TRI_HEADER
#define RAVL3D_TRI_HEADER 1
/////////////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
  
#include "Ravl/3D/Vertex.hh"

namespace Ravl3DN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Triangle in TriMesh.
  // Tri's must be associated with a tri set, in the parent
  // triset goes out of scope the behavour of a tri from
  // it is undefined.
  
  class TriC 
  {
  public:
    TriC() {
      colour[0] = 196;
      colour[1] = 196;
      colour[2] = 196;
    }
    //: Default constructor.
    
    TriC(const TFVectorC<VertexC *,3> &v)
      : vertices(v)
    {
      colour[0] = 196;
      colour[1] = 196;
      colour[2] = 196;
    }
    //: Construct from another vector.

    TriC(VertexC &v0,VertexC &v1,VertexC &v2) {
      vertices[0] = &v0;
      vertices[1] = &v1;
      vertices[2] = &v2;
      colour[0] = 196;
      colour[1] = 196;
      colour[2] = 196;
    }
    //: Construct from vertices.
    
    void Flip(void);
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
    
    Vector3dC &FaceNormal()
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
    
    void UpdateFaceNormal();
    //: Update the face normal.
    
    VertexC *&VertexPtr(UIntT n)
    { return vertices[n]; }
    //: Access vertex pointer.
    // Advanced users only.
    
    VertexC *VertexPtr(UIntT n) const
    { return vertices[n]; }
    //: Access vertex pointer.
    // Advanced users only.
    
    TFVectorC<Vector2dC,3> &TextureCoords() 
    { return texture; }
    //: Access texture co-ordinates.
    
    const TFVectorC<Vector2dC,3> &TextureCoords() const
    { return texture; }
    //: Access texture co-ordinates.
    
    TFVectorC<ByteT,3> &Colour()
    { return colour; }
    //: Colour of face.
    
    const TFVectorC<ByteT,3> &Colour() const
    { return colour; }
    //: Colour of face.
    
  protected:
    TFVectorC<VertexC *,3> vertices;
    TFVectorC<Vector2dC,3> texture;
    Vector3dC normal;
    TFVectorC<ByteT,3> colour;
  };

}

#endif

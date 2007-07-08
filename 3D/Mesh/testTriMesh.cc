
#include "Ravl/3D/TriMesh.hh"
#include "Ravl/3D/MeshShapes.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/DrawPolygon.hh"
#include "Ravl/IO.hh"

using namespace Ravl3DN;

int testTriMesh();
int testTexTriMesh();
int testMeshShapes();

int main() {
  int ln;
  if((ln = testTriMesh()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  if((ln = testTexTriMesh()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
#if 0
  if((ln = testMeshShapes()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
#endif
  cerr << "Test passed. \n";
  return 0;
}

// Display the texture coorinates of a mesh.

void DisplayTexCoords(const TriMeshC &mesh) {
  RavlImageN::ImageC<ByteT> img(512,512);
  img.Fill(0);
  
  for(SArray1dIterC<TriC> it(mesh.Faces());it;it++) {
    Polygon2dC poly;
    poly.InsLast(it->TextureCoord(0)*512);
    poly.InsLast(it->TextureCoord(1)*512);
    poly.InsLast(it->TextureCoord(2)*512);
    RavlImageN::DrawPolygon(img,(ByteT) 255,poly);
  }
  Save("@X",img);
}

int testTriMesh() {
#if 0
  SArray1dC<Vector3dC> verts(10);
  for(int i = 0;i < 10;i++)
    verts[i] = Vector3dC(i%3,(i+1)%3,(i+2)%3);
  SArray1dC<UIntT> faces(30);
  for(int i = 0;i < 30;i++)
    faces[i] = i % verts.Size();
  TriMeshC tm;
  tm = TriMeshC(verts,faces);
  if(tm.Faces().Size() != (faces.Size() /3)) return __LINE__;
#endif
  return 0;
}

int testTexTriMesh() {
  
  
  
  return 0;
}

int testMeshShapes() {
  //TriMeshC mesh = CreateTriMeshPlane(1.0);
  TriMeshC mesh = CreateTriMeshCube(1.0);
  
#if 0
  RealT ns = mesh.Vertices()[0].Normal()[2];
  mesh.UpdateVertexNormals();
  // Check the normals are consistant
  if(Sign(ns) != Sign(mesh.Vertices()[0].Normal()[2])) return __LINE__;
#endif
  
  DisplayTexCoords(mesh);
  
  return 0;
}

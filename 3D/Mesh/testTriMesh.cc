
#include "Ravl/3D/TriMesh.hh"

using namespace Ravl3DN;

int testTriMesh();
int testTexTriMesh();

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
  cerr << "Test passed. \n";
  return 0;
}

int testTriMesh() {
  SArray1dC<Vector3dC> verts(10);
  SArray1dC<UIntT> faces(30);
  for(int i = 0;i < 30;i++)
    faces[i] = i % verts.Size();
  TriMeshC tm;
  tm = TriMeshC(verts,faces);
  if(tm.Faces().Size() != (faces.Size() /3)) return __LINE__;
  return 0;
}

int testTexTriMesh() {
  
  
  
  return 0;
}

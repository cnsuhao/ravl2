
#include "Ravl/Option.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/3D/TriMesh.hh"

using namespace Ravl3DN;

int main() {
  
  TriMeshC ts;
  if(!Load(PROJECT_OUT "/share/RAVL/data/cube.tri",ts,"",true)) {
    cerr << "Failed to load file. \n";
    return 1;
  }
  
  if(!Save("testoutput.tri",ts,"",true)) {
    cerr<< "Failed to save. \n";
    return 1;
  }
  
  return 0;
}


#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Random.hh"
#include "Ravl/Option.hh"
#include "Ravl/SArr2Iter.hh"

using namespace RavlN;

int testSVD();

int main() {
  int ln;
  if((ln = testSVD()) != 0) {
    cerr << "testSVD failed. Line:" << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}


int testSVD() {
  VectorC D;
  MatrixC U, V;
  MatrixC Test(30,3);
  
  int i,j;
  double value=1.0;
  for (i=0; i<30; i++)
    for (j=0; j<3; j++) {
      Test[i][j]=value;
      value+=0.1;
    }
  
  D=SVD(Test,U,V);
  
  return 0;
}

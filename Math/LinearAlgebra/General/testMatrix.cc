
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Random.hh"
#include "Ravl/Option.hh"
#include "Ravl/SArr2Iter.hh"

using namespace RavlN;

int testSVD();
int testMisc();

int main() {
  int ln;
  if((ln = testSVD()) != 0) {
    cerr << "testSVD failed. Line:" << ln << "\n";
    return 1;
  }
  if((ln = testMisc()) != 0) {
    cerr << "testMisc failed. Line:" << ln << "\n";
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

int testMisc() {
  // Check slicing and SetRow/SetColumn work ok.
  RealT array2[]={11.5,12.8,3,4,100,1000};
  MatrixC mat(3,2,array2);
  MatrixC mat2 = mat.Copy();
  VectorC wer1(mat.SliceRow(2));
  if(wer1.Size() != 2) return __LINE__;
  mat.SetRow(2,wer1); //this causes the following error**
  VectorC wer2(mat.SliceColumn(1));
  if(wer2.Size() != 3) return __LINE__;
  mat.SetColumn(1,wer2); //this causes the following error**
  if((mat - mat2).SumSqr() > 0.0000000001) return __LINE__;
  return 0;
}


#include "Ravl/SMatrix.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Option.hh"

using namespace RavlN;

int testMatrix(int iters,int matSize);
int testSMatrix(int iters,int matSize);

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  bool usetestMatrix = opt.Boolean("tm",false,"Test MatrixC. ");
  bool usetestSMatrix = opt.Boolean("tsm",false,"Test SMatrixC. ");
  IntT iters = opt.Int("i",10000,"Test iterations. ");
  IntT matSize = opt.Int("m",4,"Matrix size. ");
  opt.Check();
  cerr <<"Iterations=" << iters << " Matrix Size=" << matSize << "\n";
  
  if(usetestMatrix)
    testMatrix(iters,matSize);

  if(usetestSMatrix)
    testSMatrix(iters,matSize);
  
  return 0;
}

int testMatrix(int iters,int matSize) {
  MatrixC mat(matSize,matSize);
  mat.Fill(0.1);
  MatrixC res(matSize,matSize);
  res.Fill(0);
  for(int i = 0;i < 10000;i++)
    res += mat * mat;
  return 0;
}

int testSMatrix(int iters,int matSize) {
  MatrixC mat(matSize,matSize);
  mat.Fill(0.1);
  MatrixC res(matSize,matSize);
  res.Fill(0);
  SMatrixC smat(mat);
  SMatrixC sres(res);
  for(int i = 0;i < 10000;i++)
    sres += smat * smat;
  return 0;
}

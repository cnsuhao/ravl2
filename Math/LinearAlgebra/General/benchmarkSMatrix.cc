
#include "Ravl/SMatrix.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Option.hh"
#include "Ravl/OS/Date.hh"

#include "Ravl/TSMatrixFull.hh"
#include "Ravl/TSMatrixPartial.hh"
#include "Ravl/TSMatrixDiagonal.hh"
#include "Ravl/TSMatrixRightUpper.hh"
#include "Ravl/TSMatrixLeftLower.hh"
#include "Ravl/TSMatrixSparse.hh"
#include "Ravl/TSMatrixPositiveDefinite.hh"
#include "Ravl/TSMatrixScaledIdentity.hh"
#include "Ravl/Random.hh"

using namespace RavlN;

int testMatrix(MatrixC mat1,MatrixC mat2,int iters);
int testSMatrix(SMatrixC mat1,SMatrixC mat2,int iters);

SMatrixC createMatrix(UIntT size,IntT type) {
  switch(type)
    {
    case 0:  return SMatrixC(RandomMatrix(size,size));
    case 1:  return SMatrixC(TSMatrixDiagonalC<RealT>(size));
    case 2:  return SMatrixC(TSMatrixRightUpperC<RealT>(size));
    case 3:  return SMatrixC(TSMatrixLeftLowerC<RealT>(size));
    case 4:  return SMatrixC(TSMatrixScaledIdentityC<RealT>(size,0.1));
    case 5:  {
      SMatrixC ret(TSMatrixSparseC<RealT>(size,size));
      int n = (size * size)/10;
      cerr << "Elements=" << n << "\n";
      for(int i = 0;i < n;i++)
	ret.Element(RandomInt()%size,RandomInt()%size,Random1());
      return ret;
    }
    }
  cerr << "Unknown matrix type=" << type << "\n";
  return SMatrixC();
}

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  IntT iters = opt.Int("i",100000,"Test iterations. ");
  IntT matSize = opt.Int("m",4,"Matrix size. ");
  IntT type1 = opt.Int("m1",0,"Matrix 1 type. 0=Full 1=Diagonal 2=RightUpper 3=LeftLower 4=ScaledIdentity 5=Sparse"); 
  IntT type2 = opt.Int("m2",0,"Matrix 2 type. "); 
  opt.Check();
  cerr <<"Iterations=" << iters << " Matrix Size=" << matSize << "\n";
  
  SMatrixC mat1 = createMatrix(matSize,type1);
  SMatrixC mat2 = createMatrix(matSize,type2);
  
  DateC start(true);
  testMatrix(mat1.TMatrix(),mat2.TMatrix(),iters);
  RealT time1 = (DateC(true) - start).Double();
  cerr << "Matrix=" << time1 << "\n";
  
  start = DateC(true);
  testSMatrix(mat1,mat2,iters);
  RealT time2 = (DateC(true) - start).Double();
  cerr << "SMatrix=" << time2 << "\n";
  cerr << "Ratio=" << time2/time1 << "\n";
  return 0;
}

int testMatrix(MatrixC mat1,MatrixC mat2,int iters) {
  MatrixC res(mat1.Rows(),mat2.Cols());
  res.Fill(0);
  for(int i = 0;i < iters;i++)
    res += mat1 * mat2;
  return 0;
}

int testSMatrix(SMatrixC smat1,SMatrixC smat2,int iters) {
  SMatrixC sres(smat1.Rows(),smat1.Cols());
  sres.Fill(0);
  for(int i = 0;i < iters;i++)
    sres += smat1 * smat2;
  return 0;
}


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
#include "Ravl/TSMatrixSymmetric.hh"
#include "Ravl/TSMatrixTranspose.hh"
#include "Ravl/TSMatrixScaledIdentity.hh"
#include "Ravl/Random.hh"

using namespace RavlN;

int testMatrix(MatrixC mat1,MatrixC mat2,int iters);
int testSMatrix(SMatrixC mat1,SMatrixC mat2,int iters);

const int noMatrixTypes = 6;

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
      int n = (size * size)/5;
      //cerr << "Elements=" << n << "\n";
      for(int i = 0;i < n;i++)
	ret.Element(RandomInt()%size,RandomInt()%size,Random1());
      return ret;
    }
    }
  cerr << "Unknown matrix type=" << type << "\n";
  return SMatrixC();
}


int testMatrix(MatrixC mat1,MatrixC mat2,int iters,int method) {
  MatrixC res(mat1.Rows(),mat2.Cols());
  res.Fill(0);
  switch(method) {
  case 0: // All
    for(int i = 0;i < iters;i++)
      res += mat1 * mat2;
    for(int i = 0;i < iters;i++)
      res += mat1.TMul(mat2);
    for(int i = 0;i < iters;i++)
      res += mat1.MulT(mat2);
    break;
  case 1: // Mul.
    for(int i = 0;i < iters;i++)
      res += mat1 * mat2;
    break;
  case 2:
    for(int i = 0;i < iters;i++)
      res += mat1.TMul(mat2);
    break;
  case 3:
    for(int i = 0;i < iters;i++)
      res += mat1.MulT(mat2);
    break;
  }
  return 0;
}

int testSMatrix(SMatrixC smat1,SMatrixC smat2,int iters,int method) {
  SMatrixC sres(smat1.Rows(),smat1.Cols());
  sres.Fill(0);
  switch(method) {
  case 0: // All
    for(int i = 0;i < iters;i++)
      sres += smat1 * smat2;
    for(int i = 0;i < iters;i++)
      sres += smat1.TMul(smat2);
    for(int i = 0;i < iters;i++)
      sres += smat1.MulT(smat2);
    break;
  case 1: // Mul.
    for(int i = 0;i < iters;i++)
      sres += smat1 * smat2;
  case 2:
    for(int i = 0;i < iters;i++)
      sres += smat1.TMul(smat2);
    break;
  case 3:
    for(int i = 0;i < iters;i++)
      sres += smat1.MulT(smat2);
    break;
  }
  return 0;
}

RealT Evaluate(SMatrixC smat1,SMatrixC smat2,int iters,int method) {
  // Convert matrices.
  TMatrixC<RealT> tmat1 = smat1.TMatrix();
  TMatrixC<RealT> tmat2 = smat2.TMatrix();

  // Time plain matrices.
  DateC start(true);
  testMatrix(tmat1,tmat2,iters,method);
  RealT time1 = (DateC(true) - start).Double();
  //cerr << "Matrix=" << time1 << "\n";
  
  // Time SMatrices.
  start = DateC(true);
  testSMatrix(smat1,smat2,iters,method);
  RealT time2 = (DateC(true) - start).Double();
  //cerr << "SMatrix=" << time2 << "\n";
  return time2/time1;
}

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  IntT iters = opt.Int("i",2000,"Test iterations. ");
  IntT matSize = opt.Int("m",5,"Matrix size. ");
  IntT type1 = opt.Int("m1",0,"Matrix 1 type. 0=Full 1=Diagonal 2=RightUpper 3=LeftLower 4=ScaledIdentity 5=Sparse"); 
  IntT type2 = opt.Int("m2",0,"Matrix 2 type. "); 
  IntT method = opt.Int("op",0,"Operation. 0=All 1=Mul 2=TMul 3=MulT ");
  
  bool testAll = opt.Boolean("a",false,"Test all combinations of matrices.");
  
  opt.Check();
  cout <<"Iterations=" << iters << " Matrix Size=" << matSize << "\n";
  cout << " 0=Full 1=Diagonal 2=RightUpper 3=LeftLower 4=ScaledIdentity 5=Sparse. \n";
  
  cout.precision(2);
  cout.setf(ios_base::fixed);
  if(testAll) {
    for(int i = 0;i < noMatrixTypes;i++) {
      for(int j = 0;j < noMatrixTypes;j++) {
	SMatrixC mat1 = createMatrix(matSize,i);
	SMatrixC mat2 = createMatrix(matSize,j);
	
	RealT ratio = Evaluate(mat1,mat2,iters,method);
	cout  << ratio << " " << flush;
      }
      cout << "\n";
    }
    return 0;
  }
  SMatrixC mat1 = createMatrix(matSize,type1);
  SMatrixC mat2 = createMatrix(matSize,type2);
  RealT ratio = Evaluate(mat1,mat2,iters,method);
  cout << "Ratio=" << ratio << "\n";
  
  return 0;
}



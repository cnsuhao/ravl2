// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/testTSMatrix.cc"

#include "Ravl/TSMatrix.hh"
#include "Ravl/TSMatrixFull.hh"
#include "Ravl/TSMatrixPartial.hh"
#include "Ravl/TSMatrixDiagonal.hh"
#include "Ravl/TSMatrixRightUpper.hh"
#include "Ravl/TSMatrixLeftLower.hh"
#include "Ravl/TSMatrixSparse.hh"
#include "Ravl/TSMatrixPositiveDefinite.hh"
#include "Ravl/TSMatrixScaledIdentity.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"

using namespace RavlN;

int testBasic();
int testDiagonal();
int testRightUpper();
int testLeftLower();
int testSparse();

int main() {
  int ln;
  if((ln = testBasic()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testDiagonal()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testRightUpper()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testLeftLower()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testSparse()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testBasic() {
  cerr << "testBasic(). \n";
  MatrixC fm1(10,10);
  RealT v = 1;
  for(SArray2dIterC<RealT> it(fm1);it;it++)
    *it = v++;
  MatrixC fm2(10,10);
  for(SArray2dIterC<RealT> it(fm2);it;it++)
    *it = v++;
  TSMatrixFullC<RealT> rtsm1(fm1);  
  TSMatrixFullC<RealT> rtsm2(fm2);
  if(rtsm1.Rows() != 10) return __LINE__;
  if(rtsm1.Cols() != 10) return __LINE__;
  
  TMatrixC<RealT> res1 = fm1 * fm2;
  TSMatrixC<RealT> res2 = rtsm1 * rtsm2;
  //  cerr << "Res1=" << res1 << endl;
  // cerr << "Res2=" << res2 << endl;
  if(MatrixC(res1 - res2.TMatrix()).SumOfAbs() > 0.000001)
    return __LINE__;

  TSMatrixC<RealT> t1(2,2);
  t1.Element(0,0,1);
  t1.Element(0,1,2);
  t1.Element(1,0,3);
  t1.Element(1,1,4);
  TSMatrixC<RealT> t2(t1);
  RealT error;
  TSMatrixC<RealT> testR;
  TSMatrixC<RealT> result(2,2);
  result.Element(0,0,7);
  result.Element(0,1,10);
  result.Element(1,0,15);
  result.Element(1,1,22);
  
  // Test 1.
  testR = t1 * t2;
  error = (testR - result).SumOfAbs();
  //cerr << "Mul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 2.
  testR = (t1.T().TMul(t2));
  error = (testR - result).SumOfAbs();
  //cerr << "TTMul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 3.
  testR = (t1.MulT(t2.T()));
  error = (testR - result).SumOfAbs();
  //cerr << "MulTT:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  return 0;
}

int testDiagonal() {
  cerr << "testDiagonal(). \n";
  VectorC fv(10);
  fv.Fill(0);
  TSMatrixDiagonalC<RealT> rtsm(fv);
  return 0;
}

int testRightUpper() {
  cerr << "testRightUpper() \n";
  TSMatrixRightUpperC<RealT> mru(4);
  RealT c = 2;
  for(int i = 0;i < 4;i++)
    for(int j = i;j < 4;j++)
      mru.Element(i,j,c++);
  //cerr <<"Mat=" << mru.TMatrix() << "\n"; 
  TMatrixC<RealT> full = mru.TMatrix(); 
  TSMatrixC<RealT> result = full * full;
  TSMatrixC<RealT> testR = mru * mru;
  //if(MatrixC(res - testR.TMatrix()).SumOfAbs() > 0.000001) return __LINE__;
  TSMatrixC<RealT> t1 = mru;
  TSMatrixC<RealT> t2 = mru;
  // Test 1.
  testR = t1 * t2;
  RealT error = (testR - result).SumOfAbs();
  //cerr << "Mul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 2.
  testR = (t1.T().TMul(t2));
  error = (testR - result).SumOfAbs();
  //cerr << "TTMul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 3.
  testR = (t1.MulT(t2.T()));
  error = (testR - result).SumOfAbs();
  //cerr << "MulTT:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  return 0;
}

int testLeftLower() {
  cerr << "testLeftLower() \n";
  TSMatrixLeftLowerC<RealT> mll(4);
  RealT c = 2;
  for(int i = 0;i < 4;i++)
    for(int j = 0;j <= i;j++)
      mll.Element(i,j,c++);
  //cerr << "mll=" << mll.TMatrix() << "\n";
  TMatrixC<RealT> full = mll.TMatrix(); 
  TSMatrixC<RealT> result = full * full;
  //cerr << "Res=" << result.TMatrix() << "\n";
  TSMatrixC<RealT> t1 = mll;
  TSMatrixC<RealT> t2 = mll;
  // Test 1.
  TSMatrixC<RealT> testR = t1 * t2;
  //cerr << "Tst=" << testR.TMatrix() << "\n";
  
  RealT error = (testR - result).SumOfAbs();
  //cerr << "Mul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 2.
  testR = (t1.T().TMul(t2));
  error = (testR - result).SumOfAbs();
  //cerr << "TTMul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 3.
  testR = (t1.MulT(t2.T()));
  error = (testR - result).SumOfAbs();
  //cerr << "MulTT:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  return 0;
}

int testSparse() {
  cerr << "testSparse() \n";
  TSMatrixSparseC<RealT> sm(10,10);
  sm.Element(2,3,23);
  sm.Element(2,8,28);
  sm.Element(4,5,45);
  cerr << sm.TMatrix() << "\n";
  cerr << sm.T().TMatrix() << "\n";
  TSMatrixC<RealT> sm2 = sm + sm.T();
  cerr << "Sum=" << sm2.TMatrix() << "\n";
  
  return 0;
}

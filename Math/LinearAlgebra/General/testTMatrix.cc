// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

// $Id$

#include "Ravl/TMatrix.hh"

using namespace RavlN;

int Simple();
int Validate();
int ValidateNS();

int main() {
  int line;
  if((line = Simple())) {
    cerr << "test failed on line " << line << "\n";
    return 1;
  }
  if((line = Validate())) {
    cerr << "test failed on line " << line << "\n";
    return 1;
  }
  if((line = ValidateNS())) {
    cerr << "test failed on line " << line << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int Simple() {
  TMatrixC<RealT> mat(2,2);
  mat.Fill(0);
  mat[Index2dC(0,0)] = 1;
  mat[1][1] = 1;
  TMatrixC<RealT> mat2 = mat + mat;
  cerr << mat2;
  return 0;
}

// Simple matrix multiplication validation.

int Validate()
{
  TMatrixC<RealT> t1(2,2);
  t1[0][0] =1;
  t1[0][1] =2;
  t1[1][0] =3;
  t1[1][1] =4;
  TMatrixC<RealT> t2(t1);
  RealT error;
  TMatrixC<RealT> testR;
  TMatrixC<RealT> result(2,2);
  result[0][0] =7;
  result[0][1] =10;
  result[1][0] =15;
  result[1][1] =22;
  
  // Test 1.
  testR = t1 * t2;
  error = TMatrixC<RealT>(testR - result).SumOfAbs();
  cerr << "Mul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
#if 1
  // Test 2.
  testR = (t1.T().TMul(t2));
  error = TMatrixC<RealT>(testR - result).SumOfAbs();
  cerr << "TTMul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 3.
  testR = (t1.MulT(t2.T()));
  error = TMatrixC<RealT>(testR - result).SumOfAbs();
  cerr << "MulTT:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
#endif
  return 0;
}

int ValidateNS()
{
  TMatrixC<RealT> m1(2,3);
  m1[0][0] =1;
  m1[0][1] =2;
  m1[0][2] =3;
  m1[1][0] =4;
  m1[1][1] =5;
  m1[1][2] =6;
  
  TMatrixC<RealT> m2 = m1.T();
  RealT error;
  TMatrixC<RealT> testR;
  TMatrixC<RealT> result = m1 * m2;
  
#if 1
  // Test 1.
  testR = (m1.T().TMul(m2));
  error = TMatrixC<RealT>(testR - result).SumOfAbs();
  cerr << "TTMul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 2.
  testR = (m1.MulT(m2.T()));
  error = TMatrixC<RealT>(testR - result).SumOfAbs();
  cerr << "MulTT:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
#endif
  return 0;
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/TFMatrix.hh"

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
  TFMatrixC<RealT,2,2> mat;
  mat.Fill(0);
  mat[Index2dC(0,0)] = 1;
  mat[1][1] = 1;
  TFMatrixC<RealT,2,2> mat2 = mat + mat;
  cerr << mat2;
  return 0;
}

// Simple matrix multiplication validation.

int Validate()
{
  TFMatrixC<RealT,2,2> t1;
  t1[0][0] =1;
  t1[0][1] =2;
  t1[1][0] =3;
  t1[1][1] =4;
  TFMatrixC<RealT,2,2> t2(t1);
  RealT error;
  TFMatrixC<RealT,2,2> testR;
  TFMatrixC<RealT,2,2> result;
  result[0][0] =7;
  result[0][1] =10;
  result[1][0] =15;
  result[1][1] =22;
  
  // Test 1.
  testR = t1 * t2;
  error = (testR - result).SumOfAbs();
  cerr << "Mul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 2.
  testR = (t1.T().TMul(t2));
  error = (testR - result).SumOfAbs();
  cerr << "TTMul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 3.
  testR = (t1.MulT(t2.T()));
  error = (testR - result).SumOfAbs();
  cerr << "MulTT:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  return 0;
}


int ValidateNS()
{
  TFMatrixC<RealT,2,3> m1;
  m1[0][0] =1;
  m1[0][1] =2;
  m1[0][2] =3;
  m1[1][0] =4;
  m1[1][1] =5;
  m1[1][2] =6;
  
  TFMatrixC<RealT,3,2> m2 = m1.T();
  RealT error;
  TFMatrixC<RealT,3,3> testR;
  TFMatrixC<RealT,3,3> result = m1 * m2;
  
  // Test 1.
  testR = (m1.T().TMul(m2));
  error = (testR - result).SumOfAbs();
  cerr << "TTMul:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  // Test 2.
  testR = (m1.MulT(m2.T()));
  error = (testR - result).SumOfAbs();
  cerr << "MulTT:" << error << "\n";
  if(error > 0.000000001)
    return __LINE__;
  
  return 0;
}

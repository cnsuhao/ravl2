// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Math/testMath.cc"
//! author="Charles Galambos"
//! docentry="Ravl.Core.Math"
//! userlevel=Develop

#include "Ravl/Random.hh"
#include "Ravl/TFMatrix.hh"
#include "Ravl/Stream.hh"
#include "Ravl/ScalMath.hh"
#include "Ravl/Math.hh"

using namespace RavlN;

int testRandom();
int testFMatrixSimple();
int testFMatrixValidate();
int testFMatrixValidateNS();
int testFMatrixVectorOps();
int testFMatrixScalMath();


int main() {
  int line;
  if((line = testRandom()) != 0) {
    cerr << "Error on line: " << line << "\n";
    return 1;
  }
  if((line = testFMatrixSimple())) {
    cerr << "test failed on line " << line << "\n";
    return 1;
  }
  if((line = testFMatrixValidate())) {
    cerr << "test failed on line " << line << "\n";
    return 1;
  }
  if((line = testFMatrixValidateNS())) {
    cerr << "test failed on line " << line << "\n";
    return 1;
  }
  if((line = testFMatrixVectorOps())) {
    cerr << "test failed on line " << line << "\n";
    return 1;
  }
  if((line = testFMatrixScalMath())) {
    cerr << "test failed on line " << line << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int testRandom() {
  cerr <<"Checking random number generator. \n";
  RealT num = 0;
  RealT min = 2;
  RealT max = -1;
  for(IntT i = 0;i < 1000000;i++) 
  {
    IntT rv =  RandomInt();
    num = (RealT)rv / ((RealT) RandomIntMaxValue + 1.0);
    //cerr << "Num=" << num << "\n";
    if(num > 1 || num < 0) {
      cout << "Bad random number:" << num << " RandomInt=" << rv << " (" << i << ")\n";
      return __LINE__;
    }
    if(num < min)
      min = num;
    if(num > max)
      max = num;
  }
  if(min > 0.01) {
    cerr << "Minimum value suspicously large: " << min << " \n";
    return __LINE__;
  }
  if(max < 0.99) {
    cerr << "Maximum value suspicously small: " << max << " \n";
    return __LINE__;
  }
  cerr <<"Values between " << min << " " << max << "\n";
  return 0;
}

int testFMatrixSimple() {
  TFMatrixC<RealT,2,2> mat;
  mat.Fill(0);
  mat[Index2dC(0,0)] = 1;
  mat[1][1] = 1;
  TFMatrixC<RealT,2,2> mat2 = mat + mat;
  cerr << mat2;
  return 0;
}

// Simple matrix multiplication validation.

int testFMatrixValidate()
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


int testFMatrixValidateNS()
{
  TFMatrixC<RealT,3,2> m1;
  m1[0][0] =1;
  m1[0][1] =2;
  m1[1][0] =3;
  m1[1][1] =4;
  m1[2][0] =5;
  m1[2][1] =6;
  
  TFMatrixC<RealT,2,3> m2 = m1.T();
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

int testFMatrixVectorOps() {
  TFVectorC<RealT,2> vec;
  vec[0] = 1;
  vec[1] = 2;
  TFVectorC<RealT,2> vec2;
  vec2[0] = 2;
  vec2[1] = 3;
  if((vec2.T() * vec)[0] != 8) return __LINE__;
  TFMatrixC<RealT,2,2> mat = vec * vec2.T();
  if(mat[0][0] != 2) return __LINE__;
  if(mat[1][0] != 4) return __LINE__;
  if(mat[0][1] != 3) return __LINE__;
  if(mat[1][1] != 6) return __LINE__;  
  return 0;
}

int testFMatrixScalMath() {
  RealT fac = 1.0;
  for(int i = 1;i < 70;i++) {
    fac = fac * (RealT) i;
    RealT zyx = Factorial(i);
    //cerr << "I=" << i << " X=" << zyx << " Y=" << fac << "\n";
    if(!IsSmall(Abs(fac - zyx),fac))
      return __LINE__;
  }
  return 0;
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Matrix.hh"
#include "Ravl/MatrixRUT.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Random.hh"
#include "Ravl/Option.hh"
#include "Ravl/SArr2Iter.hh"
#include "Ravl/VectorMatrix.hh"
#include "Ravl/Matrix2d.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/Matrix4d.hh"
#include "Ravl/MatrixRS.hh"
#include "Ravl/MatrixDecomposition.hh"
#include "Ravl/Vector.hh"

using namespace RavlN;

int testSVD();
int testEigen();
int testMisc();
int testMatrixRUT();
int testDet();
int testLUDecomposition();
int testVector();

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
  if((ln = testMatrixRUT()) != 0) {
    cerr << "testMatrixRUT failed. Line:" << ln << "\n";
    return 1;
  }
  if((ln = testEigen()) != 0) {
    cerr << "testEigen() failed. Line:" << ln << "\n";
    return 1;
  }
  if((ln = testLUDecomposition()) != 0) {
    cerr << "testLUDecomposition() failed. Line:" << ln << "\n";
    return 1;
  }
  if((ln = testDet()) != 0) {
    cerr << "testDet() failed. Line:" << ln << "\n";
    return 1;
  }
  if((ln = testVector()) != 0) {
    cerr << "testVector() failed. Line:" << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}


int testSVD() {
  cerr << "tesSVD() Called \n";
  VectorC D;
  MatrixC U, V;
  MatrixC Test(30,3);
  Test = RandomMatrix(10,20);
  D=SVD(Test,U,V);
  
  MatrixC md(D.Size(),D.Size());
  md.Fill(0);
  md.SetDiagonal(D);
  MatrixC m = U * md * V.T();
  if((m - Test).SumSqr() > 0.000001) return __LINE__;
  return 0;
}

int testEigen() {
  cerr << "testEigen() Called \n";
  MatrixC test = RandomSymmetricMatrix(5);
  VectorMatrixC vm = EigenVectors(test);
  VectorC D = vm.Vector();
  MatrixC md(D.Size(),D.Size());
  MatrixC E = vm.Matrix();
  md.Fill(0);
  md.SetDiagonal(D);
  MatrixC m = E * md * E.Inverse();
  if((m - test).SumSqr() > 0.0000001) return __LINE__;
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

int testMatrixRUT() {
  // test OuterProductRUT(vec).
  
  VectorC vec(1,2,3);
  MatrixRUTC m = OuterProductRUT(vec);
  m.MakeSymmetric();
  MatrixC om = vec.OuterProduct();
  if((om - m).SumSqr() > 0.00000001) return __LINE__;
  
  // test AddOuterProduct(vec).
  m = MatrixRUTC(3);
  m.Fill(0);
  m.AddOuterProduct(vec);
  m.MakeSymmetric();
  if((om - m).SumSqr() > 0.00000001) return __LINE__;
  
  MatrixC t1(2,3);
  t1[0][0] = 1;
  t1[0][1] = 2;
  t1[0][2] = 3;
  t1[1][0] = 4;
  t1[1][1] = 5;
  t1[1][2] = 6;
  
  MatrixC t2(3,2);
  t2[0][0] = 1;
  t2[1][0] = 2;
  t2[2][0] = 3;
  t2[0][1] = 4;
  t2[1][1] = 5;
  t2[2][1] = 6;
  
  MatrixC t3 = t2 * t1;
  m.AddOuterProduct(VectorC(4,5,6));
  m.MakeSymmetric();
  if((m - t3).SumSqr() > 0.00000001) return __LINE__;
  //  cerr << "t3=" << t3<< "\n";
  return 0;
}

int testDet() {
  cerr << "testDet(), Called \n";
  RealT nd;
#if 1
  // Check determinant of a 2 by 2 matrix.
  MatrixC tm = RandomMatrix(2,2);
  nd = tm.Det();
  Matrix2dC m22;
  int i,j;
  for(i = 0;i < 2;i++)
    for(j = 0;j < 2;j++) 
      m22[i][j] = tm[i][j];
  cerr << "2 Det=" << nd << " Mat22=" << m22.Det() << "\n";
  if(Abs(m22.Det() - nd) > 0.000000001) return __LINE__;
  
  // Check determinant of a 3 by 3 matrix.
  tm = RandomMatrix(3,3);
  Matrix3dC m33;
  for(i = 0;i < 3;i++)
    for(j = 0;j < 3;j++)
      m33[i][j] = tm[i][j];
  nd = tm.Det();
  cerr << "3 Det=" << nd << " Mat33=" << m33.Det() << "\n";
  if(Abs(m33.Det() - nd) > 0.000000001) return __LINE__;
  
  // Check determinant of a 4 by 4 matrix.
  tm = RandomMatrix(4,4);
  nd = tm.Det();
  Matrix4dC m44;
  for(i = 0;i < 4;i++)
    for(j = 0;j < 4;j++)
      m44[i][j] = tm[i][j];
  cerr << "4 Det=" << nd << " Mat44=" << m44.Det() << "\n";
  if(Abs(m44.Det() - nd) > 0.000000001) return __LINE__;
#endif
  // Check determinant of a 5 by 5 matrix.
  MatrixRSC rs = RandomSymmetricMatrix(5,5);  
  nd = rs.Det();
  RealT od;
  rs.NearSingularInverse(od);
  if(Abs(nd - od) > 0.00000001) return __LINE__;
  cerr << "5 Det=" << nd << " od=" << od << "\n";
  
  return 0;
}


int testLUDecomposition() {
  cerr << "testLUDecomposition(), Called. \n";
  int n = 3;
#if 1
  //MatrixRSC rs = RandomPositiveDefiniteMatrix(5);  
  MatrixC rs = RandomMatrix(n,n);
#else
  MatrixRSC rs(n);
  rs[0][0] = 2;
  rs[0][1] = 6;
  rs[1][0] = 5;
  rs[1][1] = 23;
#endif
  cerr << "Org=" << rs << "\n";
  RealT d;
#if 0
  if(!LUDecompositionPD(rs,d)) return __LINE__;
  cerr << "Det=" << d << "\n";
#else
  LUDecomposition(rs,d);
#endif
  cerr << "rs=" << rs << "\n";
  MatrixC mat1(n,n);
  MatrixC mat2(n,n);
  mat1.Fill(0);
  mat2.Fill(0);
  for(int i = 0;i < n;i++) {
    mat1[i][i] = 1;
    for(int j = 0;j < n;j++) {
      if(j < i)
	mat1[i][j] = rs[i][j];
      else 
	mat2[i][j] = rs[i][j];
    }
  }
  cerr << "mat1=" << mat1 << "\n";
  cerr << "mat2=" << mat2 << "\n";
  MatrixC res = mat1 * mat2;
  cerr << "Res=" << res << "\n";
  
  return 0;
}

int testVector() {
  VectorC vec2(1,2);
  if(vec2[0] != 1) return __LINE__;
  if(vec2[1] != 2) return __LINE__;
  VectorC vec3(1,2,3);
  if(vec3[0] != 1) return __LINE__;
  if(vec3[1] != 2) return __LINE__;
  if(vec3[2] != 3) return __LINE__;
  VectorC vec4(1,2,3,4);
  if(vec4[0] != 1) return __LINE__;
  if(vec4[1] != 2) return __LINE__;
  if(vec4[2] != 3) return __LINE__;
  if(vec4[3] != 4) return __LINE__;
  
  // Check creation from a fixed size vector.
  FVectorC<3> fv;
  fv[0] = 1;
  fv[1] = 2;
  fv[2] = 3;
  VectorC vec3a(fv);
  if(vec3a[0] != 1) return __LINE__;
  if(vec3a[1] != 2) return __LINE__;
  if(vec3a[2] != 3) return __LINE__;
 
  // Check evil conversions between fixed and general matricies and vectors work...
  
  MatrixC wtoi(2,3);
  wtoi.Fill(0);
  int i = 1;
  for(SArray2dIterC<RealT> it(wtoi);it;it++)
    *it = i++;
  FVectorC<3> worldpoint;  
  worldpoint[0] = 1;
  worldpoint[1] = 2;
  worldpoint[2] = 3;
  FVectorC<2> pixelvalue(wtoi * worldpoint);
  // cerr << "Result=" << pixelvalue << "\n";
  if(pixelvalue[0] != 14) return __LINE__;
  if(pixelvalue[1] != 32) return __LINE__;
  return 0;
}

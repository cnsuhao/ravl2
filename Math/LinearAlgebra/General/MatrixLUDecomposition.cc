// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/MatrixLUDecomposition.cc"

#include "Ravl/MatrixDecomposition.hh"

#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  static const RealT smallValue = 1e-20;
  
  //: LUDecomposition for positive definite matrices.
  
  bool LUDecompositionPD(MatrixC &mat,RealT &det) {
    UIntT k,i,j,n =  mat.Rows();
    det = 1;
    if(n != mat.Cols()) {
      cerr << "LUDecompositionPD(), ERROR: Matrix must be square. \n";
      return false;
    }
    det = mat[0][0];
    for(i = 1;i < n;i++) {
      mat[i][0] = mat[i][0] / mat[0][0];
      for(j = 1;j < i;j++) {
	RealT &z = mat[i][j];
	RealT x = z;
	for(k = 0;k < j;k++)
	  x -= mat[i][k] * mat[k][j];
	z = x;
	if(Abs(mat[j][j])  < smallValue) {
	  cerr << "LUDecompositionPD(), WARNING: Diagonal near zero. \n";
	  mat[i][i] = smallValue;
	}
	x /= mat[j][j];
      }
      for(j = i;j < n;j++) {
	RealT &z = mat[i][j];
	RealT x = z;
	for(UIntT k = 0;k < j;k++)
	  x -= mat[i][k] * mat[k][j];
	z = x;
      }
      det *= mat[i][i];
    }
    return true;
  }
  
  //: LU Decomposition with partial pivoting.
  
  SArray1dC<IntT> LUDecomposition(MatrixC &mat,RealT &d) {
    UIntT n = mat.Rows();
    if(n != mat.Cols()) {
      cerr << "LUDecomposition(), ERROR: Matrix must be square. \n";
      return SArray1dC<IntT>();
    }
    SArray1dC<IntT> perm(n);
    RealT xmax;
    d = 1;
    IntT piv;
    UIntT i,j,k = 0;
    VectorC sv(n);
    for(SArray1dIterC<RealT> it(sv);it;it++,k++) {
      RealT t;
      xmax = 0.0;
      for(BufferAccessIterC<RealT> rit(mat[k],n);rit;rit++)
	if((t = Abs(*rit)) > xmax)
	  xmax = t;
      if(Abs(xmax) < smallValue) {
	cerr << "LUDecomposition(), WARNING: Singular matrix detected on row " << k << " \n";
	return SArray1dC<IntT>();
      }
      *it = 1/xmax;
    }
    for(j = 0;j < n;j++) {
      for(i = 1;i < j;i++) {
	RealT &z = mat[i][j];
	RealT x = z;
	BufferAccessIterC<RealT> row = mat[i];
	for(k = 0;k < i;k++,row++)
	  x -= *row * mat[k][j];
	z = x;
      }
      i = j;
      {
	RealT &z = mat[i][j];
	RealT x = z;
	BufferAccessIterC<RealT> row = mat[i];
	for(k = 0;k < j;k++,row++)
	  x -= *row * mat[k][j];
	z = x;
	xmax = Abs(x) * sv[i];
	piv = i;
      }
      for(i++;i < n;i++) {
	RealT &z = mat[i][j];
	RealT x = z;
	BufferAccessIterC<RealT> row = mat[i];
	for(k = 0;k < j;k++,row++)
	  x -= *row * mat[k][j];
	z = x;
	if((x = (Abs(x) * sv[i])) >= xmax) {
	  xmax = x;
	  piv = i;
	}
      }
      perm[j] = piv;
      if(piv != (IntT) j) {
	mat.SwapRows(j,piv); // Swap rows, could use a row ptr swap here to speed things up.
	d = -d;
	sv[piv] = sv[j];
      }
      RealT &jj = mat[j][j];
      if(Abs(jj) < smallValue)
	jj = smallValue;
      if(j != n) {
	RealT x = 1 / jj;
	for(i = j+1;i < n;i++)
	  mat[i][j] *= x;
      }
      d *= jj; // Compute the determinant.
    }
    return perm;
  }
  
}

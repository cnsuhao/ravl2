// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATRIXC_HEADER
#define RAVLMATRIXC_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/General/Matrix.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Linear Algebra"

#include "Ravl/TMatrix.hh"

namespace RavlN {
  
  class VectorC;
  
  //! userlevel=Normal
  //: Matrix of real values.
  
  class MatrixC
    : public TMatrixC<RealT>
  {
  public:
    MatrixC()
      {}
    //: Default constructor.

    bool IsReal() const;
    //: Test if matrix only contains real values.
    // This will return false if either nan's (Not an number) 
    // or infinite values are found.
    
    MatrixC(UIntT rows,UIntT cols)
      : TMatrixC<RealT>(rows,cols)
      {}
    //: Construct a new matrix of rows x cols.
    
    MatrixC(UIntT rows,UIntT cols,const RealT *data)
      : TMatrixC<RealT>(rows,cols,data)
      {}
    //: Construct a new matrix of rows x cols with row wise array of data.
    
    MatrixC(const TMatrixC<RealT> &oth)
      : TMatrixC<RealT>(oth)
      {}
    //: Base class constructor.
    
    MatrixC(const SArray2dC<RealT> &oth)
      : TMatrixC<RealT>(oth)
      {}
    //: Base class constructor.
    
    bool SolveIP(VectorC &b);
    //: Solve a general linear system  A*x = b
    // The input matix A is this one.  The input
    // vector is b, which is replaced by the ouput x. <p>
    // This matrix is altered to L-U factored form by the computation. <p>
    // If the input matrix is singular, false is returned and
    // true if the operation succeeded.
    
    VectorC Solve(const VectorC &b) const;
    //: Solve a general linear system  A*x = b
    // Where a is this matrix, and X is the returned vector.
    // If matrix is singular a zero length vector is returned.
    
    MatrixC Inverse() const;
    //: Calculate the inverse of this matrix.
    // an invalid matrix is returned if this matrix is
    // singular. This can be tested for by IsValid().

    bool InverseIP();
    //: Calculate the inverse of this matrix in place.
    // Returns false if matrix is singular. <p>
    // Notes:
    // The matrix must be square <p>
    // If the matrix is not stored in a continous area of memory a slightly
    // different routine is used to do the inversion.  

    MatrixC NearSingularInverse(RealT &det) const;
    //: Inverts this matrix and returns determinant of original matrix.
    // This routine is particularly useful when you matrices are near singular
    // as it uses PCA to first rotate co-ordinate axis, so no nasty divisions.
    // See Fukunaga -Introduction to Statistical Pat Rec, page 40.
    
    VectorC SVD() const;
    //: Singular value decomposition, eg. M = U * D * V.T(). 
    // The diagonal matrix D is returned as a vector. Values for the
    // other matrixes are not computed.
    // If the operation failes the returned vector is invalid.
    
    VectorC SVD_IP();
    //: Singular value decomposition, eg. M = U * D * V.T(). 
    // The diagonal matrix D is returned as a vector. Values for the
    // other matrixes are not computed.
    // If the operation failes the returned vector is invalid. <p>
    // NB. This function destory's the contents of this matrix!
    
    VectorC SVD(MatrixC & u, MatrixC & v) const;
    //: Singular value decomposition, eg. M = U * D * V.T(). 
    // The diagonal matrix D is returned as a vector.
    // This also returns the matrix u and v matrixes, the passed
    // matrixes will be used to store the results if they are
    // of the correct size.
    // If the operation failes the returned vector is invalid.
    
    VectorC SVD_IP(MatrixC & u, MatrixC & v);
    //: Singular value decomposition, eg. M = U * D * V.T(). 
    // The diagonal matrix D is returned as a vector.
    // This also returns the matrix u and v matrixes, the passed
    // matrixes will be used to store the results if they are
    // of the correct size.
    // If the operation failes the returned vector is invalid.
    // NB. This function destory's the contents of this matrix!
    
    VectorC EigenValues() const;
    //: Calculate the eigen values of this matrix.
    // This matrix remains unchanged. A vector of the eigen
    // values is returned. <p>
    // If any errors occured a zero length vector is generated.
    
    VectorC EigenValuesIP();
    //: Calculate the eigen values of this matrix.
    // The contents of this matrix is destroyed. A vector of the eigen
    // values is returned.   <p>
    // If any errors occured a zero length vector is generated.
    
    VectorC EigenVectors(MatrixC &E) const;
    //: Calculate the eigen values and vectors of this matrix.
    // A = E*D*E~ where D is the diagonal matrix of eigenvalues
    //   D[i,j] = ret[i] if i=j and 0 otherwise. 'ret' is the
    // returned matrix.
    
    VectorC EigenVectorsIP();
    //: Calculate the eigen values and vectors of this matrix.
    // This matrix is filed with the eigen vectors
    // A = E*D*E~ where D is the diagonal matrix of eigenvalues
    //   D[i,j] = ret[i] if i=j and 0 otherwise. 'ret' is the
    // returned matrix.
    
    RealT MaxEigenValue(VectorC &maxv) const;
    //: Get the maximum eigen value and its vector.
    
    
  };
  
}

#endif

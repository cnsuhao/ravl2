// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MATRIXRUT_HEADER
#define RAVL_MATRIXRUT_HEADER 1
///////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/General/MatrixRUT.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Linear Algebra"

#include "Ravl/Matrix.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Right Upper Triangular matrix.
  // This class contains functions optimised for working with
  // Right Upper Triangular matrix's. <p>
  // The matrix MUST be square.
  
  class MatrixRUTC
    : public MatrixC
  {
  public:
    MatrixRUTC()
    {}
    //: Default constructor.

    MatrixRUTC(UIntT size)
      : MatrixC(size,size)
    {}
    //: Create a new matrix of size * size.
    
    MatrixRUTC(const MatrixC &oth)
      : MatrixC(oth)
    {  RavlAssert(oth.Rows() == oth.Cols()); }
    //: Base constructor.

    MatrixRUTC(const SArray2dC<RealT> &oth)
      : MatrixC(oth)
    {  RavlAssert(oth.Size1() == oth.Size2()); }
    //: Base constructor.
    
    MatrixRUTC Inverse() const;
    //: Calculate the inverse of a upper right triangular matrix.
    // an invalid matrix is returned if this matrix is
    // singular. This can be tested for by IsValid().
    
    bool InverseIP();
    //: Calculate the inverse of a upper right triangular matrix. In place.
    // NOTE: The result is not upper triangular.
    // False is returned if matrix is singular, true otherwise.
    
    void AddOuterProduct(const VectorC &vec);
    //: Add outer product of 'vec' with itself to this matrix.
    
    const MatrixRUTC &operator+=(const MatrixRUTC &mat);
    //: Add another right upper matrix to this one.
    
    void MakeSymmetric();
    //: Make this matrix symmetric.
    // Copy the upper right triangle to the lower left.
    // Note this is an in-place operation.
  };

  MatrixRUTC OuterProductRUT(const VectorC &vec);
  //: Return outer product of 'vec' as a right upper triangular matrix.
  
  bool SolveIP(MatrixRUTC &mat,VectorC &b);
  //: Solve a general linear system  A*x = b
  // The input matix A is this one.  The input
  // vector is b, which is replaced by the ouput x. <p>
  // This matrix is altered to L-U factored form by the computation. <p>
  // If the input matrix is singular, false is returned and
  // true if the operation succeeded.
  
  VectorC Solve(const MatrixRUTC &mat,const VectorC &b);
  //: Solve a general linear system  A*x = b
  // Where a is this matrix, and X is the returned vector.
  // If matrix is singular a zero length vector is returned.
}

#endif

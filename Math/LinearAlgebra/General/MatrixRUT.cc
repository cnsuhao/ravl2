// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/MatrixRUT.cc"

#include "Ravl/MatrixRUT.hh"
#include "Ravl/Vector.hh"
#include "Ravl/CCMath.hh"

namespace RavlN {
  
  //: Calculate the inverse of a upper right triangular matrix.
  // an invalid matrix is returned if this matrix is
  // singular. This can be tested for by IsValid().
  
  MatrixRUTC MatrixRUTC::Inverse() const {
    MatrixRUTC ret = Copy();
    if(!ret.InverseIP()) {
      // Could throw an exception ?
      return MatrixC(); 
    }
    return ret;
  }
  
  bool MatrixRUTC::InverseIP() {
    RavlAlwaysAssert(IsContinuous()); // What should we do now ?
    RavlAlwaysAssertMsg(Cols() == Rows(),"MatrixRUTC::InverseIP(), Matrix must be square to invert ");    
    return ruinv(&(*this)[0][0],Rows()) == 0; // ccmath routine.
  }
  

  //: Add outer product of 'vec' with itself to this matrix.
  
  void MatrixRUTC::AddOuterProduct(const VectorC &vec) {
    SArray2dIterC<RealT> mit(*this);
    int off = 0;
    for(BufferAccessIterC<RealT> it(vec);it;it++) {
      for(BufferAccessIterC<RealT> it2 = it;it2;it2++,mit.NextCol())
	*mit += (*it) * (*it2);
      mit.NextRow(++off);
    }
  }
  
  //: Add another right upper matrix to this one.
  
  const MatrixRUTC &MatrixRUTC::operator+=(const MatrixRUTC &mat) {
    int off = 0;
    for(SArray2dIter2C<RealT,RealT> mit(*this,mat);mit;) {
      mit.NextCol(off++);
      do {
	mit.Data1() += mit.Data2();
      } while(mit.Next()) ;
    }
    return *this;
  }
  
  //: Subtract another right upper matrix from this one.
  
  const MatrixRUTC &MatrixRUTC::operator-=(const MatrixRUTC &mat) {
    int off = 0;
    for(SArray2dIter2C<RealT,RealT> mit(*this,mat);mit;) {
      mit.NextCol(off++);
      do {
	mit.Data1() -= mit.Data2();
      } while(mit.Next()) ;
    }    
    return *this;
  }

  //: Multiply by a constant.
  
  const MatrixRUTC &MatrixRUTC::operator*=(RealT val) {
    int off = 0;
    for(SArray2dIterC<RealT> mit(*this);mit;) {
      mit.NextCol(off++);
      do {
	*mit *= val;
      } while(mit.Next()) ;
    }        
    return *this;
  }
  
  //: Divide by a constant.
  
  const MatrixRUTC &MatrixRUTC::operator/=(RealT val) {
    int off = 0;
    for(SArray2dIterC<RealT> mit(*this);mit;) {
      mit.NextCol(off++);
      do {
	*mit /= val;
      } while(mit.Next()) ;
    }    
    return *this;
  }

  //: Make this matrix symmetric.
  // Copy the upper right triangle to the lower left.
  
  void MatrixRUTC::MakeSymmetric() {
    // Could be faster if we used pointers.
    for(unsigned int i = 0;i < Rows();i++) {
      for(unsigned int j = i + 1;j < Cols();j++)
	(*this)[j][i] = (*this)[i][j];
    }
  }
  
  //: Return outer product of 'vec' as a right upper triangular matrix.
  
  MatrixRUTC OuterProductRUT(const VectorC &vec) {
    MatrixRUTC ret(vec.Size());
    SArray2dIterC<RealT> mit(ret);
    int off = 0;
    for(BufferAccessIterC<RealT> it(vec);it;it++) {
      for(BufferAccessIterC<RealT> it2 = it;it2;it2++,mit.NextCol())
	*mit = (*it) * (*it2);
      mit.NextRow(++off);
    }
    return ret;
  }
  
  //: Solve a general linear system  A*x = b
  // The input matix A is this one.  The input
  // vector is b, which is replaced by the ouput x.
  // This matrix is altered to L-U factored form by the computation.
  
  bool SolveIP(MatrixRUTC &mat,VectorC &b) {
    RavlAlwaysAssertMsg(mat.Cols() == b.Size(),"MatrixRUTC::SolveIP(), Matrix must be the same size as the vector to solve. ");
    return solvru(&mat[0][0],&b[0],mat.Rows()) == 0;
  }
  
  
  //: Solve a general linear system  A*x = b
  // Where a is this matrix, and X is the returned.
  // If matrix is singular a zero length vector is returned.
  
  VectorC Solve(const MatrixRUTC &mat,const VectorC &b) {
    VectorC ret(b.Copy());
    MatrixRUTC tmp(mat.Copy());
    if(!SolveIP(tmp,ret))
      return VectorC();
    return ret;
  }


  
}

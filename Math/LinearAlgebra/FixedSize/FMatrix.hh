// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLFMATRIX_HEADER
#define RAVLFMATRIX_HEADER 1
//////////////////////////////////////////////////
//! rcsid=$Id$
//! file="Ravl/Math/Geometry/Euclidean/FMatrx.hh"
//! lib=RavlMath
//! userlevel=Develop
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Geometry"

#include "Ravl/TFMatrix.hh"
#include "Ravl/FVector.hh"
#include "Ravl/CCMath.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/Exception.hh"
#include "Ravl/Assert.hh"

namespace RavlN {
  
  //! userlevel=Advanced
  //: Real Matrix with templated size.
  
  template<unsigned int N,unsigned int M>
  class FMatrixC
    : public TFMatrixC<RealT,N,M>
  {
  public:
    FMatrixC()
      {}
    //: Default constructor.
    
    FMatrixC(const TFMatrixC<RealT,N,M> &oth)
      : TFMatrixC<RealT,N,M>(oth)
      {}
    //: Base constructor.
    
    bool IsReal() const {
      for(UIntT i = 0;i < N;i++)
	for(UIntT j = 0;j < M;j++)
	  if(IsNan(data[i][j]) || IsInf(data[i][j]))
	    return false;
      return true;
    }
    //: Test if matrix only contains real values.
    // This will return false if either nan's (Not an number) 
    // or infinite values are found.
    
    
    bool SolveIP(FVectorC<N> &b) {
      RavlAssertMsg(N == M,"FMatrixC::SolveIP(), Matrix must be square. ");
      return solv(&(*this)[0][0],&b[0],N) == 0;
    }
    //: Solve a general linear system  A*x = b
    // The input matix A is this one.  The input
    // vector is b, which is replaced by the ouput x. <p>
    // This matrix is altered to L-U factored form by the computation. <p>
    // If the input matrix is singular, false is returned and
    // true if the operation succeeded.
    
    FVectorC<N> Solve(const FVectorC<N> &b) const {
      FMatrixC<N,M> tmp(*this);      
      FMatrixC<N,M> ret(b);      
      RavlAssertMsg(N == M,"FMatrixC::SolveIP(), Matrix must be square. ");
      if(solv(&tmp[0][0],&ret[0],N) != 0) 
	throw ExceptionNumericalC("FMatrixC<N,M>::Solve(), Matrix is singular. ");
      return ret;
    }
    //: Solve a general linear system  A*x = b
    // Where a is this matrix, and X is the returned vector.
    // If matrix is singular a zero length vector is returned.
    
    FMatrixC<N,M> Inverse() const {
      FMatrixC<N,M> ret(*this);
      RavlAssertMsg(N == M,"FMatrixC::Inverse(), Matrix must be square to invert ");
      minv(&ret[0][0],N);
      return ret;
    }
    //: Calculate the inverse of this matrix.
    // NB. This will only work for square matrixes.
    
    FMatrixC<N,M> &InverseIP() {
      RavlAssertMsg(N == M,"FMatrixC::Inverse(), Matrix must be square to invert ");
      minv(&(*this)[0][0],N);
      return *this;
    }
    //: Calculate the inverse of this matrix in place.
    // NB. This will only work for square matrixes.
    
    FVectorC<N> SVD() const {
      FVectorC<N> ret;
      FMatrixC<N,M> tmp(*this);
      if(N > M * 2) { // Pick the best routine.
	if(sv2val(&ret[0],&tmp[0][0],N,M) != 0)
	  throw ExceptionNumericalC("SVD failed.");
      } else {
	if(svdval(&ret[0],&tmp[0][0],N,M) != 0)
	  throw ExceptionNumericalC("SVD failed.");
      }      
      return ret;
    }
    //: Singular value decomposition, eg. M = U * D * V.T(). 
    // The diagonal matrix D is returned as a vector. Values for the
    // other matrixes are not computed.
    // If the operation failes the returned vector is invalid.
    
    FVectorC<N> SVD_IP() {
      FVectorC<N> ret;
      if(N > M * 2) { // Pick the best routine.
	if(sv2val(&ret[0],&(*this)[0][0],N,M) != 0)
	  throw ExceptionNumericalC("SVD failed.");
      } else {
	if(svdval(&ret[0],&(*this)[0][0],N,M) != 0)
	  throw ExceptionNumericalC("SVD failed.");
      }
      return ret;
    }
    //: Singular value decomposition, eg. M = U * D * V.T(). 
    // The diagonal matrix D is returned as a vector. Values for the
    // other matrixes are not computed.
    // If the operation failes an exception is thrown <p>
    // NB. This function destory's the contents of this matrix!
    
    FVectorC<N> SVD(FMatrixC<N,M> & u, FMatrixC<N,M> & v) const {
      FVectorC<N> ret;
      FMatrixC<N,M> tmp(*this);
      if(N > M * 2) { // Pick the best routine.
	if(sv2uv(&ret[0],&tmp[0][0],&u[0][0],N,&v[0][0],M) != 0)
	  throw ExceptionNumericalC("SVD failed.");
      } else {
	if(svduv(&ret[0],&tmp[0][0],&u[0][0],N,&v[0][0],M) != 0)
	  throw ExceptionNumericalC("SVD failed.");
      }
      return ret;
    }
    //: Singular value decomposition, eg. M = U * D * V.T(). 
    // The diagonal matrix D is returned as a vector.
    // This also returns the matrix u and v matrixes, the passed
    // matrixes will be used to store the results if they are
    // of the correct size.
    // If the operation failes an exception will be thrown.
    
    FVectorC<N> SVD_IP(FMatrixC<N,M> & u, FMatrixC<N,M> & v) {
      FVectorC<N> ret;
      if(N > M * 2) { // Pick the best routine.
	if(sv2uv(&ret[0],&(*this)[0][0],&u[0][0],N,&v[0][0],M) != 0)
	  throw ExceptionNumericalC("SVD failed.");
      } else {
	if(svduv(&ret[0],&(*this)[0][0],&u[0][0],N,&v[0][0],M) != 0)
	  throw ExceptionNumericalC("SVD failed.");
      }
      return ret;
    }
    //: Singular value decomposition, eg. M = U * D * V.T(). 
    // The diagonal matrix D is returned as a vector.
    // This also returns the matrix u and v matrixes, the passed
    // matrixes will be used to store the results if they are
    // of the correct size.
    // If the operation failes the returned vector is invalid.
    // NB. This function destory's the contents of this matrix!
    
    FVectorC<N> EigenValues() const {
      RavlAssertMsg(N == M,"MatrixTFC::EigenValues() Matrix must be square. ");
      FVectorC<N> ret;
      FMatrixC<N,M> tmp(*this);
      eigval(&tmp[0][0],&ret[0],N);
      return ret;
    }
    //: Calculate the eigen values of this matrix.
    // This matrix remains unchanged. A vector of the eigen
    // values is returned. <p>
    // If any errors occured a zero length vector is generated.
    
    FVectorC<N> EigenValuesIP() {
      RavlAssertMsg(N == M,"MatrixTFC::EigenValuesIP() Matrix must be square. ");
      FVectorC<N> ret;
      eigval(&(*this)[0][0],&ret[0],N);
      return ret;
    }
    //: Calculate the eigen values of this matrix.
    // The contents of this matrix are destroyed. A vector of the eigen
    // values is returned.   <p>
    // If any errors occured a zero length vector is generated.
    
    FVectorC<N> EigenVectors(FMatrixC<N,M> &E) const {
      RavlAssertMsg(N == M,"FMatrixC::EigenVectorsIP() Matrix must be square. ");
      FVectorC<N> ret;
      FMatrixC<N,M> tmp(*this);
      eigen(&tmp[0][0],&ret[0],N);
      return ret;
    }
    //: Calculate the eigen values and vectors of this matrix.
    // A = E*D*E~ where D is the diagonal matrix of eigenvalues
    //   D[i,j] = ret[i] if i=j and 0 otherwise. 'ret' is the
    // returned matrix.
    
    FVectorC<N> EigenVectorsIP() {
      RavlAssertMsg(N == M,"FMatrixC::EigenVectorsIP() Matrix must be square. ");
      FVectorC<N> ret;
      eigen(&(*this)[0][0],&ret[0],N);
      return ret;
    }
    //: Calculate the eigen values and vectors of this matrix.
    // This matrix is filed with the eigen vectors
    // A = E*D*E~ where D is the diagonal matrix of eigenvalues
    //   D[i,j] = ret[i] if i=j and 0 otherwise. 'ret' is the
    // returned matrix.
    
    RealT MaxEigenValue(FVectorC<N> &maxv) const {
      RavlAlwaysAssertMsg(N == M,"FMatrixC::MaxEigenValue() Matrix must be square. ");
      return evmax(&(*this)[0][0],&maxv[0],N);
    }
    //: Get the maximum eigen value and its vector.

  };
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TMATRIXC_HEADER
#define RAVL_TMATRIXC_HEADER 1
///////////////////////////////////////////////////////////
//! userlevel=Normal
//! docentry="Ravl.Math.Linear Algebra"
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/General/TMatrix.hh"
//! author="Charles Galambos"
//! date="10/09/98"
//! lib=RavlMath

#include "Ravl/SArray2d.hh"
#include "Ravl/SArr2Iter.hh"
#include "Ravl/SArr2Iter2.hh"
#include "Ravl/SArr2Iter3.hh"
#include "Ravl/TVector.hh"
#include "Ravl/BfAccIter.hh"

namespace RavlN {
  //! userlevel=Advanced
  //: Templated matrix's.
  
  template<class DataT>
  class TMatrixC 
    : public SArray2dC<DataT>
  {
  public:
    inline TMatrixC()
    {}
    //: Default constructor.

    inline TMatrixC(const SArray2dC<DataT> &oth)
      : SArray2dC<DataT>(oth)
    {}
    //: Base class constructor.
    
    TMatrixC(const TVectorC<DataT> &vec)
      : SArray2dC<DataT>(vec.Buffer(),vec.Size(),1)
    {}
    //: Treat vector as column matrix.
    // Note: This does not copy the vector, changes
    // made to the matrix will appear in the vector.
    
    inline TMatrixC(SizeT rows,SizeT cols);
    //: Constructor.
    
    inline TMatrixC(SizeT rows,SizeT cols,const DataT *data);
    //: Constructor.
    // With row wise array of initalisations data.
    
    TMatrixC(DataT v1,DataT v2,
	     DataT v3,DataT v4);
    //: Construct a 2 x 2 matrix from given values.
    
    TMatrixC(DataT v1,DataT v2,DataT v3,
	     DataT v4,DataT v5,DataT v6,
	     DataT v7,DataT v8,DataT v9);
    //: Construct a 3 x 3 matrix from given values.
    
    inline SizeT Rows() const
    { return Size1(); }
    //: Return the number of rows
    
    inline SizeT Cols() const
    { return Size2(); }
    //: Return the number of columns
    
    TMatrixC<DataT> operator*(DataT val) const
    { return TMatrixC<DataT>(SArray2dC<DataT>::operator*(val)); }
    //: Multiply by a constant.

    TVectorC<DataT> operator*(const TVectorC<DataT> & vector) const;
    //: Multiplication "TVectorC<DataT>" = "This" * vector
    
    TMatrixC<DataT> operator*(const TMatrixC<DataT> & mat) const;
    //: Multiplication "result" = "this" * "mat"
    
    TMatrixC<DataT> MulT(const TMatrixC<DataT> & B) const;
    //: Multiplication A * B.T()
    
    TMatrixC<DataT> TMul(const TMatrixC<DataT> & B) const;
    //: Multiplication A.T() * B
    
    TVectorC<DataT> TMul(const TVectorC<DataT>& vec) const;
    //: Multiplication A.T() * vec

    TMatrixC<DataT> T() const;
    //: Get transpose of matrix.
    
    static TMatrixC<DataT> Identity(UIntT n);
    //: Returns an identity matrx of n by n.
    // NB. This is a static function and should be called  MatrixC::Identity(n).
    // where n is the size of the matrix.
    
    const TMatrixC<DataT> &SetDiagonal(const TVectorC<DataT> &d);
    //: Set the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.

    const TMatrixC<DataT> &AddDiagonal(const TVectorC<DataT> &d);
    //: Add a vector to the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.

    TMatrixC<DataT> SubMatrix(SizeT size1,SizeT size2)
    { return TMatrixC<DataT>(SArray2dC<DataT>(*this,size1,size2)); }
    //: Get sub matrix of size1,size2.
    // The creates a new access, but does not copy the data itself.
    // The matrix always starts from 0,0.
    
    DataT SumOfAbs() const;
    //: Sum the absolute values of all members of the matrix.
    
    const TMatrixC<DataT> &AddOuterProduct(const TVectorC<DataT> &vec1,const TVectorC<DataT> &vec2);
    //: Add outer product of vec1 and vec2 to this matrix.
    
    const TMatrixC<DataT> &AddOuterProduct(const TVectorC<DataT> &vec1,const TVectorC<DataT> &vec2,const DataT &a);
    //: Add outer product of vec1 and vec2 multiplied by a to this matrix .
    
    const TMatrixC<DataT> &SetSmallToBeZero(const DataT &min);
    //: Set values smaller than 'min' to zero in vector.
  };
  
  //////////////////////////////////////////////////////
  
  template<class DataT>
  inline TMatrixC<DataT>::TMatrixC(SizeT rows,SizeT cols)
    : SArray2dC<DataT>(rows,cols)
  {}
  
  template<class DataT>
  inline TMatrixC<DataT>::TMatrixC(SizeT rows,SizeT cols,const DataT *data) 
    : SArray2dC<DataT>(rows,cols)
  {
    const DataT *at = data;
    for(BufferAccess2dIterC<DataT> it(*this,Size2());it;it++)
      *it = *(at++);
  }

  template<class DataT>
  TMatrixC<DataT>::TMatrixC(DataT v1,DataT v2,
	   DataT v3,DataT v4)
    : SArray2dC<DataT>(2,2)
  {
    (*this)[0][0] = v1;
    (*this)[0][1] = v2;
    (*this)[1][0] = v3;
    (*this)[1][1] = v4;
  }
  
  template<class DataT>
  TMatrixC<DataT>::TMatrixC(DataT v1,DataT v2,DataT v3,
			    DataT v4,DataT v5,DataT v6,
			    DataT v7,DataT v8,DataT v9)
    : SArray2dC<DataT>(3,3)
  {
    (*this)[0][0] = v1;
    (*this)[0][1] = v2;
    (*this)[0][2] = v3;
    (*this)[1][0] = v4;
    (*this)[1][1] = v5;
    (*this)[1][2] = v6;
    (*this)[2][0] = v7;
    (*this)[2][1] = v8;
    (*this)[2][2] = v9;
  }

  
  template<class DataT>
  TVectorC<DataT> TMatrixC<DataT>::operator*(const TVectorC<DataT> & vector) const {
    const SizeT rdim = Rows();
    const SizeT cdim = Cols();
    TVectorC<DataT> out(rdim);
    for (UIntT i = 0; i < rdim; ++i) {
      DataT sum = 0.0;
      for (UIntT k = 0; k < cdim; k++)
	sum += (*this)[i][k] * vector[k];
      out[i] = sum;
    }
    return out;
  }
  
  template<class DataT>
  TMatrixC<DataT> TMatrixC<DataT>::operator*(const TMatrixC<DataT> & mat) const  {
    RavlAssert(Cols() == mat.Rows());
#if 0
    const SizeT rdim = Rows();
    const SizeT cdim = mat.Cols();
    const SizeT dim  = Cols();
    TMatrixC<DataT> out(rdim, cdim);
    for (UIntT r = 0; r < rdim; r++)
      for (UIntT c = 0; c < cdim; c++) {
	RealT sum = 0.0;
	for (UIntT k = 0; k < dim; k++)
	  sum += (*this)[r][k] * mat[k][c];
	out[r][c] = sum;
      }
#else  
    // Do work.
    TMatrixC<DataT> out(Rows(), mat.Cols());
    if(Rows() == 0 || Cols() == 0)
      return out; // Nothing to do !
    BufferAccess2dIterC<DataT> it1(*this,Size2());
    BufferAccess2dIterC<DataT> it2(mat,mat.Size2());
    BufferAccess2dIterC<DataT> ot(out,mat.Size2());
    out.Fill(0);
    do {
      do {
	do {
	  ot.Data() += it1.Data() * it2.Data();
	  ot.NextCol();
	} while(it2.Next()) ;
	ot.RowStart(); // Go back to begining of output row.
      } while(it1.Next()) ;
      ot.NextRow();
      it2.First(mat,mat.Size2());
    } while(it1) ;
#endif    
    return out;
  }

  //: Multiplication A * B.T()
  
  template<class DataT>
  TMatrixC<DataT> TMatrixC<DataT>::MulT(const TMatrixC<DataT> & mat) const {
    // Check assumptions.
    RavlAssert(Cols() == mat.Cols());
    
    // Do work.
    TMatrixC<DataT> out(Rows(), mat.Rows());
    if(Rows() == 0 || Cols() == 0)
      return out; // Nothing to do.
    BufferAccess2dIterC<DataT> it1(*this,Size2());
    BufferAccess2dIterC<DataT> it2(mat,mat.Size2());
    BufferAccess2dIterC<DataT> ot(out,out.Size2());
    do {
      do {
	RealT sum = 0;
	do {
	  sum += it1.Data() * it2.Data();
	  it1.NextCol();
	} while(it2.Next());
	ot.Data() = sum;
	ot.Next();
	if(!it2.IsElm()) 
	  break;
	it1.RowStart();
      } while(1);
      if(!ot.IsElm())
	break;
      it2.First(mat,Size2());
      it1.NextRow();
    } while(1) ;
    return out;
  }
  
  //: Multiplication A.T() * B
  
  template<class DataT>
  TMatrixC<DataT> TMatrixC<DataT>::TMul(const TMatrixC<DataT> & mat) const {
    // Check assumptions.
    RavlAssert(Rows() == mat.Rows());
    
    // Do work.
    TMatrixC<DataT> out(Cols(), mat.Cols());
    if(Rows() == 0 || Cols() == 0)
      return out; // Nothing to do.
    BufferAccess2dIterC<DataT> it1(*this,Size2());
    BufferAccess2dIterC<DataT> it2(mat,Size2());
    BufferAccess2dIterC<DataT> ot(out,Size2());
    out.Fill(0);
    do {
      do {
	do {
	  ot.Data() += it1.Data() * it2.Data();
	  it2.NextCol();
	} while(ot.Next()) ;
	it1.Next();
	if(!ot.IsElm())
	  break;
	it2.RowStart();
      } while(1) ;
      if(!it1.IsElm())
	break;
      it2.NextRow();
      ot.First(out,Size2());
    } while(1) ;
    return(out);
  }
  
  //: Get transpose of matrix.
  
  template<class DataT>
  TMatrixC<DataT> TMatrixC<DataT>::T() const {
    TMatrixC<DataT> ret(Cols(),Rows());
    for(IndexC i = 0;i < Rows();i++)
      for(IndexC j = 0;j < Cols();j++)
	ret[j][i] = (*this)[i][j];
    return ret;
  }

  template<class DataT>
  DataT TMatrixC<DataT>::SumOfAbs() const {
    BufferAccess2dIterC<DataT> it(*this,Size2());
    if(!it)
      return DataT();
    DataT ret(*it);
    for(it++;it;it++)
      ret += Abs(*it);
    return ret;
  }
  
  template<class DataT>
  const TMatrixC<DataT> &TMatrixC<DataT>::AddOuterProduct(const TVectorC<DataT> &vec1,const TVectorC<DataT> &vec2) {
    RavlAssert(Size1() == vec1.Size());
    RavlAssert(Size2() == vec2.Size());
    BufferAccessIterC<DataT> v1(vec1);
    BufferAccess2dIterC<DataT> it(*this,Size2());
    while(it) {
      BufferAccessIterC<DataT> v2(vec2);
      RealT r1 = (*v1);
      do {
	*it += r1 * (*v2);
	v2++;
      } while(it.Next()) ;
      v1++;
    }
    return *this;
  }
  
  template<class DataT>
  const TMatrixC<DataT> &TMatrixC<DataT>::AddOuterProduct(const TVectorC<DataT> &vec1,const TVectorC<DataT> &vec2,const DataT &a) {
    RavlAssert(Size1() == vec1.Size());
    RavlAssert(Size2() == vec2.Size());
    BufferAccessIterC<DataT> v1(vec1);
    BufferAccess2dIterC<DataT> it(*this,Size2());
    while(it) {
      BufferAccessIterC<DataT> v2(vec2);
      DataT r1 = (*v1) * a;
      do {
	*it += r1 * (*v2);
	v2++;
      } while(it.Next()) ;
      v1++;
    }
    return *this;    
  }
  
  template<class DataT>
  TMatrixC<DataT> TMatrixC<DataT>::Identity(UIntT n) {
    TMatrixC<DataT> ret(n,n);
    ret.Fill(0);
    for(UIntT i = 0;i < n;i++)
      ret[i][i] = 1;
    return ret;
  }

  template<class DataT>
  const TMatrixC<DataT> &TMatrixC<DataT>::SetDiagonal(const TVectorC<DataT> &d) {
    RavlAssert(d.Size() == Cols());
    for(UIntT i = 0;i < Cols();i++)
      (*this)[i][i] = d[i];
    return (*this);
  }

  template<class DataT>
  const TMatrixC<DataT> &TMatrixC<DataT>::AddDiagonal(const TVectorC<DataT> &d) {
    RavlAssert(d.Size() == Cols());
    for(UIntT i = 0;i < Cols();i++)
      (*this)[i][i] += d[i];
    return (*this);
  }

  template<class DataT>
  const TMatrixC<DataT> &TMatrixC<DataT>::SetSmallToBeZero(const DataT &min) {
    for(BufferAccess2dIterC<DataT> it(*this,Size2());it;it++)
      if(Abs(*it) < min)
	SetToZero(*it);
    return (*this);
  }

  ///// Some functions from TVectorC<> that return matrixes. //////
  
  template<class DataT>
  TMatrixC<DataT> TVectorC<DataT>::OuterProduct(const TVectorC<DataT> &a) const { 
    TMatrixC<DataT> ret(Size(),a.Size());
    BufferAccessIterC<DataT> v1(*this);
    BufferAccess2dIterC<DataT> it(ret,ret.Size2());
    while(it) {
      BufferAccessIterC<DataT> v2(a);
      RealT r1 = (*v1);
      do {
	*it = r1 * (*v2);
	v2++;
      } while(it.Next()) ;
      v1++;
    }
    return ret;
  }
  
  template<class DataT>
  TMatrixC<DataT> TVectorC<DataT>::OuterProduct(const TVectorC<DataT> &a,RealT b) const {
    TMatrixC<DataT> ret(Size(),a.Size());
    BufferAccessIterC<DataT> v1(*this);
    BufferAccess2dIterC<DataT> it(ret,ret.Size2());
    while(it) {
      BufferAccessIterC<DataT> v2(a);
      RealT r1 = (*v1) * b;
      do {
	*it = r1 * (*v2);
	v2++;
      } while(it.Next()) ;
      v1++;
    }
    return ret;
  }
  
  template<class DataT>
  TMatrixC<DataT> TVectorC<DataT>::OuterProduct() const
  { return OuterProduct(*this); }
  
  template<class DataT>
  TMatrixC<DataT> OuterProduct(const Slice1dC<DataT> &a,const Slice1dC<DataT> &b) { 
    TMatrixC<DataT> ret(a.Size(),b.Size());
    Slice1dIterC<DataT> v1(a);
    BufferAccess2dIterC<DataT> it(ret,ret.Size2());
    while(it) {
      Slice1dIterC<DataT> v2(b);
      do {
	*it = (*v1) * (*v2);
	v2++;
      } while(it.Next()) ;
      v1++;
    }
    return ret;
  }
  //: Outer product of two slices.
  // This treats the slices as vectors.
  
  template<class DataT>
  TMatrixC<DataT> OuterProduct(const Slice1dC<DataT> &a)
  { return OuterProduct(a,a); }
  //: Outer product of a slice with itself.
  // This treats the slice as a vector.
  
  template<class DataT>
  void MulAdd(const TVectorC<DataT> &vec,const TMatrixC<DataT> &mat,const TVectorC<DataT> &add,TVectorC<DataT> &result)
  { result = vec * mat + add; }
  //: Compute result = vec * mat + add;
  // For compatibility with the fixed length vectors.
  
  template<class DataT>
  void Mul(const TVectorC<DataT> &vec,const TMatrixC<DataT> &mat,TVectorC<DataT> &result) 
  { result = vec * mat + add; }
  //: Compute result = vec * mat;
  // For compatibility with the fixed length vectors
  
}

#endif

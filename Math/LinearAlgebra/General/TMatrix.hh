// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTMATRIXC_HEADER
#define RAVLTMATRIXC_HEADER 1
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
    
    inline TMatrixC(SizeT rows,SizeT cols);
    //: Constructor.
    
    inline SizeT Rows() const
      { return Size1(); }
    //: Return the number of rows
    
    inline SizeT Cols() const
      { return Size2(); }
    //: Return the number of columns
    
    TMatrixC<DataT> operator*(RealT val) const
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
    //: Construct an identity matrx of n by n.
    
    const TMatrixC<DataT> &SetDiagonal(const TVectorC<DataT> &d);
    //: Set the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.

    const TMatrixC<DataT> &AddDiagonal(const TVectorC<DataT> &d);
    //: Add a vector to the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.
    
    DataT SumOfAbs() const;
    //: Sum the absolute values of all members of the matrix.
    
    const TMatrixC<DataT> &SetSmallToBeZero(const DataT &min);
    //: Set values smaller than 'min' to zero in vector.
  };
  
  //////////////////////////////////////////////////////
  
  template<class DataT>
  inline 
  TMatrixC<DataT>::TMatrixC(SizeT rows,SizeT cols)
    : SArray2dC<DataT>(rows,cols)
  {}
  
  
  template<class DataT>
  TVectorC<DataT> 
  TMatrixC<DataT>::operator*(const TVectorC<DataT> & vector) const {
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
  TMatrixC<DataT> 
  TMatrixC<DataT>::operator*(const TMatrixC<DataT> & mat) const  {
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
      do {
	*it = (*v1) * (*v2);
	v2++;
      } while(it.Next()) ;
      v1++;
    }
    return ret;
  }
  
  template<class DataT>
  TMatrixC<DataT> TVectorC<DataT>::OuterProduct() const
  { return OuterProduct(*this); }
  
}

#endif

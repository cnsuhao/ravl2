// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TSMATRIXDIAGONAL_HEADER
#define RAVL_TSMATRIXDIAGONAL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlMath
//! author="Charles Galambos"
//! docentry="Ravl.Math.Linear Algebra.Smart Matrix"
//! date="19/8/2002"
//! file="Ravl/Math/LinearAlgebra/General/TSMatrixDiagonal.hh"

#include "Ravl/TSMatrixPartial.hh"
#include "Ravl/SArray1dIter3.hh"

namespace RavlN {
  template<class DataT> class TSMatrixDiagonalC;
  
  //! userlevel=Develop
  //: Diagonal matrix body
  
  template<class DataT>
  class TSMatrixDiagonalBodyC
    : public TSMatrixPartialBodyC<DataT>
  {
  public:
    TSMatrixDiagonalBodyC(int i)
      : TSMatrixPartialBodyC<DataT>(i,i,SArray1dC<DataT>(i))
    {}
    //: Constructor.
    
    TSMatrixDiagonalBodyC(const SArray1dC<DataT> &dat)
      : TSMatrixPartialBodyC<DataT>(dat.Size(),dat.Size(),dat)
    {}
    //: Construct diagonal from an array
    
    virtual RCBodyVC &Copy() const
    { return *new TSMatrixDiagonalBodyC<DataT>(data.Copy()); }
    //: Create a copy of this matrix.
    
    virtual const type_info &MatrixType() const
    { return typeid(TSMatrixDiagonalBodyC<DataT>); }
    //: Find the type of the matrix.
    
    virtual DataT Element(UIntT i,UIntT j) const { 
      if(i != j) return 0;
      return data[i];
    } 
    //: Access element.
    
    virtual void Element(UIntT i,UIntT j,const DataT &val) {
      if(i != j) {
	if(val != 0)
	  cerr << "Attempting to set off diagonal of diagonal matrix. \n";
	return ;
      }
      data[i] = val;
    }
    //: Set element.
    
    virtual Array1dC<DataT> Row(UIntT i) const
    { return Array1dC<DataT>(const_cast<BufferC<DataT> &>(data.Buffer()),
			     RangeBufferAccessC<DataT>(const_cast<DataT *>( &(data[i])),IndexRangeC(i,i))); }
    //: Access a row from the matrix.
    
    virtual Slice1dC<DataT> Col(UIntT j) const { 
      SArray1dC<DataT> &diag = const_cast<SArray1dC<DataT> &>(data);
      return Slice1dC<DataT>(diag.Buffer(),&(diag[0]),IndexRangeC(j,j),1);
    }
    //: Access slice from matrix.
    
    virtual DataT MulSumColumn(UIntT c,const Slice1dC<DataT> &slice) const {  
      if(!slice.Contains(c)) {
	DataT ret;
	SetZero(ret);
	return ret;
      }
      return slice[c] * data[c];      
    }
    //: Multiply column by values from slice and sum them.
    
    virtual DataT MulSumColumn(UIntT c,const Array1dC<DataT> &dat) const { 
      if(!dat.Contains(c)) {
	DataT ret;
	SetZero(ret);
	return ret;
      }
      return dat[c] * data[c];
    }
    //: Multiply column by values from dat and sum them.
    
    virtual TSMatrixC<DataT> T() const { 
      // FIXME: This should really be a copy ?
      return TSMatrixDiagonalC<DataT>(const_cast<TSMatrixDiagonalBodyC<DataT> &>(*this)); 
    }
    //: Get transpose of matrix.
    // This is a no-op.
    
    virtual TSMatrixC<DataT> Mul(const TSMatrixC<DataT> &oth) const;
    //: Get this matrix times 'oth'.
    
    virtual TVectorC<DataT> Mul(const TVectorC<DataT> &oth) const;
    //: Get this matrix times 'oth'.
    
    virtual TSMatrixC<DataT> MulT(const TSMatrixC<DataT> & B) const;
    //: Multiplication A * B.T()
    
    virtual TSMatrixC<DataT> TMul(const TSMatrixC<DataT> & B) const;
    //: Multiplication A.T() * B
    
    virtual TVectorC<DataT> TMul(const TVectorC<DataT> & B) const;
    //: Multiplication A.T() * B
    
    virtual TSMatrixC<DataT> AAT() const;
    //: Return  A * A.T().
    
    virtual TSMatrixC<DataT> ATA() const;
    //: Return  A.T() * A.
    
    virtual TSMatrixC<DataT> IMul(const TSMatrixC<DataT> & B) const;
    //: Multiply B by the inverse of this matrix.
    
    virtual TSMatrixC<DataT> ITMul(const TSMatrixC<DataT> & B) const;
    //: Multiply B by the transpose of the inverse of this matrix.
    
    virtual TMatrixC<DataT> TMatrix(bool) const;
    //: Get as full matrix.
    
    virtual void SetDiagonal(const TVectorC<DataT> &d) { 
      RavlAssert(data.Size() == d.Size());
      data = d.Copy(); 
    }
    //: Set the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.
    
    virtual void AddDiagonal(const TVectorC<DataT> &d) {  
      for(SArray1dIter2C<DataT,DataT> it(data,d);it;it++)
	it.Data1() += it.Data2();
    }
    //: Add a vector to the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.
    
  };
  
  
  //! userlevel=Normal
  //: Diagonal matrix
  
  template<class DataT>
  class TSMatrixDiagonalC
    : public TSMatrixPartialC<DataT>
  {
  public:
    TSMatrixDiagonalC(int i)
      : TSMatrixPartialC<DataT>(*new TSMatrixDiagonalBodyC<DataT>(i))
    {}
    //: Create a diagonal matrix of size i by i .
    // The contents of the matrix are undefined.
    
    TSMatrixDiagonalC(const TVectorC<DataT> &data)
      : TSMatrixPartialC<DataT>(*new TSMatrixDiagonalBodyC<DataT>(data))
    {}
    //: Create a diagonal matrix from a vector.

    TSMatrixDiagonalC(const TSMatrixC<DataT> &mat)
      : TSMatrixPartialC<DataT>(mat)
    {
      if(dynamic_cast<TSMatrixDiagonalBodyC<DataT> *>(&TSMatrixC<DataT>::Body()) == 0)
	Invalidate();
    }
    //: Create a diagonal matrix from a vector.
    
    TSMatrixDiagonalC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    TSMatrixDiagonalC(TSMatrixDiagonalBodyC<DataT> &bod)
      : TSMatrixPartialC<DataT>(bod)
    {}
    //: Body constructor.
    
    TSMatrixDiagonalBodyC<DataT> &Body()
    { return static_cast<TSMatrixDiagonalBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
    const TSMatrixDiagonalBodyC<DataT> &Body() const
    { return static_cast<const TSMatrixDiagonalBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
  public:
    friend class TSMatrixDiagonalBodyC<DataT>;
  };
  
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixDiagonalBodyC<DataT>::Mul(const TSMatrixC<DataT> &mat) const {
    if(mat.MatrixType() == typeid(TSMatrixDiagonalBodyC<DataT>)) {
      TSMatrixDiagonalC<DataT> diag(mat);
      TVectorC<DataT>  tmp(mat.Rows());
      for(SArray1dIter3C<DataT,DataT,DataT> it(tmp,data,diag.Data());it;it++)
	it.Data1() = it.Data2() * it.Data3();
      return TSMatrixDiagonalC<DataT>(tmp);
    }
    RavlAssert(Cols() == mat.Rows());
    const SizeT rdim = Rows();
    const SizeT cdim = mat.Cols();
    TMatrixC<DataT> out(rdim, cdim);
    BufferAccessIterC<DataT> dit(data);
    for (UIntT r = 0; r < rdim; r++,dit++) {
      Array1dC<DataT> ra = mat.Row(r);
      //cerr <<"Row=" << ra << "\n";
      for(BufferAccessIter2C<DataT,DataT> it(ra,RangeBufferAccessC<DataT>(out[r],IndexRangeC(0,cdim)));it;it++)
	it.Data2() = (*dit) * it.Data1();
    }
    return out;
  }
  
  template<class DataT>
  TVectorC<DataT> TSMatrixDiagonalBodyC<DataT>::Mul(const TVectorC<DataT> &oth) const {
    RavlAssert(Rows() == oth.Size());
    TVectorC<DataT> ret(oth.Size());
    for(SArray1dIter3C<DataT,DataT,DataT> it(ret,data,oth);it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixDiagonalBodyC<DataT>::MulT(const TSMatrixC<DataT> & B) const {
    return TSMatrixDiagonalBodyC<DataT>::Mul(B.T());
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixDiagonalBodyC<DataT>::TMul(const TSMatrixC<DataT> & B) const {
    return TSMatrixDiagonalBodyC<DataT>::Mul(B);
  }
  
  template<class DataT>
  TVectorC<DataT> TSMatrixDiagonalBodyC<DataT>::TMul(const TVectorC<DataT> & B) const {
    return TSMatrixDiagonalBodyC<DataT>::Mul(B);
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixDiagonalBodyC<DataT>::AAT() const {
    TSMatrixDiagonalC<DataT> diag(Rows());
    for(SArray1dIter2C<DataT,DataT> it(diag.Data(),data);it;it++)
      it.Data1() = Sqr(it.Data2());
    return diag;
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixDiagonalBodyC<DataT>::ATA() const {
    return TSMatrixDiagonalBodyC<DataT>::AAT();
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixDiagonalBodyC<DataT>::IMul(const TSMatrixC<DataT> & mat) const {
    RavlAssert(Cols() == mat.Rows());
    const SizeT rdim = Rows();
    const SizeT cdim = mat.Cols();
    TMatrixC<DataT> out(rdim, cdim);
    BufferAccessIterC<DataT> dit(data);
    for (UIntT r = 0; r < rdim; r++,dit++) {
      Array1dC<DataT> ra = mat.Row(r);
      for(BufferAccessIter2C<DataT,DataT> it(ra,RangeBufferAccessC<DataT>(out[r],IndexRangeC(0,cdim)));it;it++)
	it.Data2() = it.Data1() / (*dit);
    }
    return out;
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixDiagonalBodyC<DataT>::ITMul(const TSMatrixC<DataT> & B) const 
  { return TSMatrixDiagonalBodyC<DataT>::IMul(B); }
  
  template<class DataT>
  TMatrixC<DataT> TSMatrixDiagonalBodyC<DataT>::TMatrix(bool) const {
    TMatrixC<DataT> ret(Rows(),Cols());
    ret.Fill(0);
    ret.SetDiagonal(data);
    return ret;
  }
}

#endif

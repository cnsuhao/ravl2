// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TSMATRIXTRANSPOSE_HEADER
#define RAVL_TSMATRIXTRANSPOSE_HEADER 1
//! date="22/8/2002"
//! author="Charles Galambos"
//! docentry="Ravl.Math.Linear Algebra.Smart Matrix"

#include "Ravl/TSMatrix.hh"

namespace RavlN {
    template<class DataT> class TSMatrixTransposeC;
  
  //! userlevel=Develop
  //: Transpose matrix body
  
  template<class DataT>
  class TSMatrixTransposeBodyC
    : public TSMatrixBodyC<DataT>
  {
  public:
    TSMatrixTransposeBodyC(const TSMatrixC<DataT> &oth)
      : matrix(oth)
    {}
    //: Constructor.
    
    virtual RCBodyVC &Copy() const
    { return *new TSMatrixTransposeBodyC<DataT>(matrix.Copy()); }
    //: Create a copy of this matrix.
    
    virtual const type_info &MatrixType() const
    { return typeid(TSMatrixTransposeBodyC<DataT>); }
    //: Find the type of the matrix.
    
    virtual DataT Element(UIntT i,UIntT j) const 
    { return matrix.Element(j,i); } 
    //: Access element.
    
    virtual void Element(UIntT i,UIntT j,const DataT &val) 
    { matrix.Element(j,i,val); }
    //: Set element.
    
    virtual Array1dC<DataT> Row(UIntT i) const { 
      Array1dC<DataT> ret(Rows());
      BufferAccessIterC<DataT> it(ret);
      for(int n = 0;n < Rows();n++,it++)
	*it = matrix.Element(n,i);
      return ret;
    }
    //: Access a row from the matrix.
    
    virtual DataT MulSumColumn(UIntT c,const Array1dC<DataT> &dat) const { 
      DataT sum;
      Array1dC<DataT> ra = Row(c);
      IndexRangeC rng = dat.Range();
      rng.ClipBy(ra.Range());
      if(rng.Size() <= 0) {
	SetZero(sum);
	return sum;
      }
      BufferAccessIter2C<DataT,DataT> it(dat,ra,rng);
      sum = it.Data1() * it.Data2();
      for(it++;it;it++)
	sum += it.Data1() * it.Data2();
      return sum;
    }
    //: Multiply column by values from dat and sum them.
    
    virtual void AddIP(const TSMatrixC<DataT> &oth) {
      RavlAssertMsg(0,"TSMatrixTransposeBodyC::AddIP(), not implemented. ");
    }
    //: Add this matrix to 'oth' and return the result.
    // Note the default implementation only works where Row(UIntT), returns a real access
    // to the data in the matrix.
    
    virtual void SubIP(const TSMatrixC<DataT> &oth) {
      RavlAssertMsg(0,"TSMatrixTransposeBodyC::SubIP(), not implemented. ");
    }
    //: Subtract 'oth' from this matrix and return the result.
    // Note the default implementation only works where Row(UIntT), returns a real access
    // to the data in the matrix.
    
    virtual TSMatrixC<DataT> T() const { 
      // FIXME: This should really be a copy ?
      return matrix; 
    }
    //: Get transpose of matrix.
    // This is a no-op.
    
    virtual TSMatrixC<DataT> Mul(const TSMatrixC<DataT> &oth) const
    { return matrix.TMul(oth); }
    //: Get this matrix times 'oth'.
    
    virtual TVectorC<DataT> Mul(const TVectorC<DataT> &oth) const
    { return matrix.TMul(oth); }
    //: Get this matrix times 'oth'.
    
    virtual TSMatrixC<DataT> MulT(const TSMatrixC<DataT> & B) const  { 
      RavlAssert(0); // Could be faster.
      return matrix.Mul(B).T(); 
    }
    //: Multiplication A * B.T()
    
    virtual TSMatrixC<DataT> TMul(const TSMatrixC<DataT> & B) const
    { return matrix.Mul(B); }
    //: Multiplication A.T() * B
    
    virtual TVectorC<DataT> TMul(const TVectorC<DataT> & B) const
    { return matrix.Mul(B); }
    //: Multiplication A.T() * B
    
    virtual TSMatrixC<DataT> IMul(const TSMatrixC<DataT> & B) const
    { return matrix.ITMul(B); }
    //: Multiply B by the inverse of this matrix.
    
    virtual TSMatrixC<DataT> ITMul(const TSMatrixC<DataT> & B) const
    { return matrix.IMul(B); }
    //: Multiply B by the transpose of the inverse of this matrix.

    virtual TSMatrixC<DataT> AAT() const
    { return matrix.ATA(); }
    //: Return  A * A.T().
    
    virtual TSMatrixC<DataT> ATA() const
    { return matrix.AAT(); }
    //: Return  A.T() * A.

    virtual void SetDiagonal(const TVectorC<DataT> &d)
    { matrix.SetDiagonal(d); }
    //: Set the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.
    
    virtual void AddDiagonal(const TVectorC<DataT> &d)
    { matrix.AddDiagonal(d); }
    //: Add a vector to the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.
    
    virtual TMatrixC<DataT> TMatrix(bool) const { 
      RavlAssert(0); // This could be faster.
      return matrix.TMatrix().T(); 
    }
    //: Get as full matrix.
    
    const TSMatrixC<DataT> &Matrix() const
    { return matrix; }
    //: Get scale for matrix.
    
    TSMatrixC<DataT> &Matrix()
    { return matrix; }
    //: Get scale for matrix.
    
    virtual void SetSmallToBeZero(const DataT &min)
    { matrix.SetSmallToBeZero(min); }
    //: Set values smaller than 'min' to zero in vector.
    
    virtual DataT SumOfAbs() const
    { return matrix.SumOfAbs(); }
    //: Sum the absolute values of all members of the matrix.
    
    virtual void SwapRows(int i,int j)
    { RavlAssert(0); }
    //: Swap two rows in the matrix.
    
    virtual void Fill(const DataT &dat)
    { matrix.Fill(dat); }
    //: Fill matrix with values.

  protected:
    TSMatrixC<DataT> matrix;
  };
  
  
  //! userlevel=Normal
  //: Transpose matrix
  
  template<class DataT>
  class TSMatrixTransposeC
    : public TSMatrixC<DataT>
  {
  public:
    TSMatrixTransposeC(int i,const DataT &val)
      : TSMatrixC<DataT>(*new TSMatrixTransposeBodyC<DataT>(i,val))
    {}
    //: Create a diagonal matrix of size i by i .
    // The contents of the matrix are undefined.
    
    TSMatrixTransposeC(const TSMatrixC<DataT> &base)
      : TSMatrixC<DataT>(base)
    {
      if(dynamic_cast<const TSMatrixTransposeBodyC<DataT> *>(&TSMatrixC<DataT>::Body()) == 0)
	Invalidate();
    }
    //: Base constructor.
  protected:
    TSMatrixTransposeC(TSMatrixTransposeBodyC<DataT> &bod)
      : TSMatrixC<DataT>(bod)
    {}
    //: Body constructor.
    
    TSMatrixTransposeBodyC<DataT> &Body()
    { return static_cast<TSMatrixTransposeBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
    const TSMatrixTransposeBodyC<DataT> &Body() const
    { return static_cast<const TSMatrixTransposeBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
  public:
    friend class TSMatrixTransposeBodyC<DataT>;
    
    const TSMatrixC<DataT> &Matrix() const
    { return Body().Matrix(); }
    //: Get scale for matrix.
    
    TSMatrixC<DataT> &Matrix()
    { return Body().Matrix(); }
    //: Get scale for matrix.
  };
  
}


#endif

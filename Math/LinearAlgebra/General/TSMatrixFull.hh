// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TSMATRIXFULL_HEADER
#define RAVL_TSMATRIXFULL_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! date="15/8/2002"
//! lib=RavlMath

#include "Ravl/TSMatrix.hh"
#include "Ravl/TMatrix.hh"

#define RAVL_TSMATERIXFULL_DEFAULT 1

namespace RavlN {
  //! userlevel=Develop
  //: Smart Matrix Body.
  
  template<class DataT>
  class TSMatrixFullBodyC 
    : public TSMatrixBodyC<DataT>
  {
  public:
    TSMatrixFullBodyC()
    {}
    //: Default constructor.
    
    TSMatrixFullBodyC(UIntT rows,UIntT cols)
      : TSMatrixBodyC<DataT>(rows,cols),
	matrix(rows,cols)
    {}
    //: Create a matrix of rows by cols
    
    TSMatrixFullBodyC(const TMatrixC<DataT> &mat)
      : TSMatrixBodyC<DataT>(mat.Rows(),mat.Cols()),
	matrix(mat)
    {}
    //: Constructor.
    
    virtual RCBodyVC &Copy() const
    { return *new TSMatrixFullBodyC<DataT>(matrix.Copy()); }
    //: Create a copy of this matrix.
    
    virtual const type_info &MatrixType() const
    { return typeid(TSMatrixFullBodyC<DataT>); }
    //: Find the type of the matrix.
    
    virtual DataT Element(UIntT i,UIntT j) const 
    { return matrix[i][j]; } 
    //: Access element.
    
    virtual void Element(UIntT i,UIntT j,const DataT &val) 
    { matrix[i][j] = val; }
    //: Set element.
    
    virtual Array1dC<DataT> Row(UIntT i) const{ 
      return Array1dC<DataT>(const_cast<TMatrixC<DataT> &>(matrix).SliceRow(i)); 
    }
    //: Access a row from the matrix.
    
    virtual DataT MulSumColumn(UIntT c,const Array1dC<DataT> &dat) const;
    //: Multiply columb by values from dat and sum them.
    
    virtual TSMatrixC<DataT> T() const
    { return TSMatrixC<DataT>(matrix.T()); }
    //: Get transpose of matrix.

#if !RAVL_TSMATERIXFULL_DEFAULT    
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
#endif
    
    virtual TSMatrixC<DataT> AAT() const
    { return AAT(); }
    //: Return  A * A.T().
    
    virtual TSMatrixC<DataT> ATA() const
    { return ATA(); }
    //: Return  A.T() * A.
    
    virtual void SetDiagonal(const TVectorC<DataT> &d)
    { matrix.SetDiagonal(d); }
    //: Set the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.
    
    virtual void AddDiagonal(const TVectorC<DataT> &d)
    { matrix.AddDiagonal(d); }
    //: Add a vector to the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.

    void AddOuterProduct(const TVectorC<DataT> &vec1,const TVectorC<DataT> &vec2)
    { matrix.AddOuterProduct(vec1,vec2); }
    //: Add outer product of vec1 and vec2 to this matrix.
    
    void AddOuterProduct(const TVectorC<DataT> &vec1,const TVectorC<DataT> &vec2,const DataT &a)
    { matrix.AddOuterProduct(vec1,vec2,a); }
    //: Add outer product of vec1 and vec2 multiplied by a to this matrix .
    
    void SetSmallToBeZero(const DataT &min)
    { matrix.SetSmallToBeZero(min); }
    //: Set values smaller than 'min' to zero in vector.
    
    DataT SumOfAbs() const
    { return matrix.SumOfAbs(); }
    //: Sum the absolute values of all members of the matrix.
    
    void SwapRows(int i,int j)
    { matrix.SwapRows(i,j); }
    //: Swap two rows in the matrix.
    
    TMatrixC<DataT> TMatrix() const
    { return matrix; }
    //: Access as normal matrix.
    
    TMatrixC<DataT> &FullTMatrix()
    { return matrix; }
    //: Access normal matrix.
    
    const TMatrixC<DataT> &FullTMatrix() const
    { return matrix; }
    //: Access normal matrix.
  protected:
    TMatrixC<DataT> matrix;
  };
  
  //! userlevel=Normal
  //: Smart Matrix.
  
  template<class DataT>
  class TSMatrixFullC 
    : public TSMatrixC<DataT>
  {
  public:
    TSMatrixFullC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    TSMatrixFullC(const TMatrixC<DataT> &mat)
      : TSMatrixC<DataT>(*new TSMatrixFullBodyC<DataT>(mat))
    {}
    //: Constructor.
    
    TSMatrixFullC(const TSMatrixC<DataT> &mat)
      : TSMatrixC<DataT>(mat)
    {
      if(dynamic_cast<TSMatrixFullBodyC<DataT> *>(&TSMatrixC<DataT>::Body()) == 0)
	Invalidate();
    }
    //: Base constructor.
    
  protected:
    TSMatrixFullC(TSMatrixFullBodyC<DataT> &bod)
      : TSMatrixC<DataT>(bod)
    {}
    //: Body constructor.
    
    TSMatrixFullBodyC<DataT> &Body()
    { return static_cast<TSMatrixFullBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
    const TSMatrixFullBodyC<DataT> &Body() const
    { return static_cast<const TSMatrixFullBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
  public:
    TMatrixC<DataT> &FullTMatrix()
    { return Body().FullTMatrix(); }
    //: Access normal matrix.
    
    const TMatrixC<DataT> &FullTMatrix() const
    { return Body().FullTMatrix(); }
    //: Access normal matrix.
  };
  
#if !RAVL_TSMATERIXFULL_DEFAULT    
  template<class DataT>  
  TSMatrixC<DataT> TSMatrixFullBodyC<DataT>::Mul(const TSMatrixC<DataT> &oth) const {
    TSMatrixFullC<DataT> ts(oth);
    if(!ts.IsValid())
      return TSMatrixBodyC<DataT>::Mul(oth); // Use default
    return TSMatrixC<DataT>(matrix * ts.FullTMatrix());
  }
  
  template<class DataT>  
  TVectorC<DataT> TSMatrixFullBodyC<DataT>::Mul(const TVectorC<DataT> &oth) const 
  { return matrix * oth; }
  
  template<class DataT>  
  TSMatrixC<DataT> TSMatrixFullBodyC<DataT>::MulT(const TSMatrixC<DataT> & B) const {
    TSMatrixFullC<DataT> ts(B);
    if(!ts.IsValid())
      return TSMatrixBodyC<DataT>::MulT(B); // Use default
    return TSMatrixC<DataT>(matrix.MulT(ts.FullTMatrix()));
  }
  
  template<class DataT>  
  TSMatrixC<DataT> TSMatrixFullBodyC<DataT>::TMul(const TSMatrixC<DataT> & B) const {
    TSMatrixFullC<DataT> ts(B);
    if(!ts.IsValid())
      return TSMatrixBodyC<DataT>::TMul(B); // Use default
    return TSMatrixC<DataT>(matrix.TMul(ts.FullTMatrix()));
  }
  
  template<class DataT>  
  TVectorC<DataT> TSMatrixFullBodyC<DataT>::TMul(const TVectorC<DataT> & B) const 
  { return matrix.TMul(B); }
#endif
  
  template<class DataT>  
  DataT TSMatrixFullBodyC<DataT>::MulSumColumn(UIntT c,const Array1dC<DataT> &dat) const { 
    RavlAssert(dat.Size() == Rows());
    if(dat.Size() < 0) {
      DataT ret;
      SetZero(ret);
      return ret;
    }
    IndexRangeC rng = dat.Range();
    BufferAccessIterC<DataT > it(dat);
    DataT ret = matrix[rng.Min()][c] * (*it);
    UIntT j = rng.Min().V()+1;
    for(it++;it;j++,it++)
      ret += matrix[j][c] * (*it);
    return ret;
  }
  
  ///////////////////////////////////////////////////////////////////
  
  template<class DataT> 
  TSMatrixC<DataT>::TSMatrixC(const TMatrixC<DataT> &mat)
    : RCHandleC<TSMatrixBodyC<DataT> >(*new TSMatrixFullBodyC<DataT>(mat))
  {}

  template<class DataT> 
  TSMatrixC<DataT>::TSMatrixC(UIntT rows,UIntT cols)
    : RCHandleC<TSMatrixBodyC<DataT> >(*new TSMatrixFullBodyC<DataT>(rows,cols))
  {}
  
}


#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TSMATRIXSYMMETRIC_HEADER
#define RAVL_TSMATRIXSYMMETRIC_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! date="15/8/2002"
//! lib=RavlMath
//! docentry="Ravl.Math.Linear Algebra"
//! file="Ravl/Math/LinearAlgebra/General/TSMatrixFull.hh"

#include "Ravl/TSMatrixFull.hh"
#include "Ravl/TSMatrixRightUpper.hh"
#include "Ravl/TSMatrixLeftLower.hh"

namespace RavlN {
  //! userlevel=Develop
  //: Symmetric positive definite matrix.
  
  template<class DataT>
  class TSMatrixSymmetricBodyC 
    : public TSMatrixFullBodyC<DataT>
  {
  public:
    TSMatrixSymmetricBodyC()
    {}
    //: Default constructor.
    
    TSMatrixSymmetricBodyC(UIntT n)
      : TSMatrixFullBodyC<DataT>(n,n)
    {}
    //: Create a matrix of rows by cols
    
    TSMatrixSymmetricBodyC(const TMatrixC<DataT> &mat)
      : TSMatrixFullBodyC<DataT>(mat)
    {}
    //: Constructor.
    
    virtual RCBodyVC &Copy() const
    { return *new TSMatrixSymmetricBodyC<DataT>(matrix.Copy()); }
    //: Create a copy of this matrix.
    
    virtual const type_info &MatrixType() const
    { return typeid(TSMatrixSymmetricBodyC<DataT>); }
    //: Find the type of the matrix.    
    
    virtual void Element(UIntT i,UIntT j,const DataT &val) { 
      matrix[i][j] = val; 
      matrix[j][i] = val; 
    }
    //: Set element.
    
    TSMatrixLeftLowerC<DataT> Cholesky() const;
    //: Perform Cholesky decomposition on this matrix.
    // Find L such that L * L.T() = this matrix.
  protected:
  };
  
  //! userlevel=Normal
  //: Symmetric positive definite matrix.
  
  template<class DataT>
  class TSMatrixSymmetricC 
    : public TSMatrixFullC<DataT>
  {
  public:
    TSMatrixSymmetricC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    TSMatrixSymmetricC(UIntT n)
      : TSMatrixFullC<DataT>(*new TSMatrixSymmetricBodyC<DataT>(mat))
    {}
    //: Create a new symmetric matrix of size n.
    // Note: The contents of the matrix are undefined.
    
    TSMatrixSymmetricC(const TMatrixC<DataT> &mat)
      : TSMatrixFullC<DataT>(*new TSMatrixSymmetricBodyC<DataT>(mat))
    {}
    //: Constructor.
    
    TSMatrixSymmetricC(const TSMatrixC<DataT> &mat)
      : TSMatrixFullC<DataT>(mat)
    {
      if(dynamic_cast<TSMatrixSymmetricBodyC<DataT> *>(&TSMatrixC<DataT>::Body()) == 0)
	Invalidate();
    }
    //: Base constructor.
    
  protected:
    TSMatrixSymmetricC(TSMatrixSymmetricBodyC<DataT> &bod)
      : TSMatrixFullC<DataT>(bod)
    {}
    //: Body constructor.
    
    TSMatrixSymmetricBodyC<DataT> &Body()
    { return static_cast<TSMatrixSymmetricBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
    const TSMatrixSymmetricBodyC<DataT> &Body() const
    { return static_cast<const TSMatrixSymmetricBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
  public:
    TSMatrixLeftLowerC<DataT> Cholesky() const
    { return Body().Cholesky(); }
    //: Perform Cholesky decomposition on this matrix.
    // Find L such that L * L.T() = this matrix.
  };

  
  template<class DataT>
  TSMatrixLeftLowerC<DataT> TSMatrixSymmetricBodyC<DataT>::Cholesky() const {
    // FIXME: This could be speeded up with more iterators and less indexing.
    TSMatrixLeftLowerC<DataT> ret(Rows());
    const int n = Rows();
    for(int i =0;i < n ;i++) {
      Array1dC<DataT> rowi = ret.Row(i);
      for(int j = i;j< n;j++) {
	RealT sum = matrix[i][j];
	Array1dC<DataT> rowj = ret.Row(j);
	for(BufferAccessIter2C<DataT,DataT> it(rowi,rowj,IndexRangeC(0,i-1));it;it++)
	  sum -= it.Data1() * it.Data2();
	if(i == j) {
	  RavlAssertMsg(sum > 0.0,"Matrix is not positive definite. ");
	  ret.Element(i,i,Sqrt(sum));
	} else
	  ret.Element(j,i,sum/ret.Element(i,i));
      }
    }
    return ret;
  }
  
  
}


#endif

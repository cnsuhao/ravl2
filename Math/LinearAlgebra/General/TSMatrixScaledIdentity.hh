// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TSMATRIXSCALEIDENTITY_HEADER
#define RAVL_TSMATRIXSCALEIDENTITY_HEADER 1
//! rcsid="$Id$"
//! lib=RavlMath
//! author="Charles Galambos"
//! docentry="Ravl.Math.Linear Algebra.Smart Matrix"
//! date="19/8/2002"
//! file="Ravl/Math/LinearAlgebra/General/TSMatrixDiagonal.hh"

#include "Ravl/TSMatrixPartial.hh"
#include "Ravl/SArr1Iter3.hh"

namespace RavlN {
  template<class DataT> class TSMatrixScaledIdentityC;
  
  //! userlevel=Develop
  //: ScaledIdentity matrix body
  
  template<class DataT>
  class TSMatrixScaledIdentityBodyC
    : public TSMatrixBodyC<DataT>
  {
  public:
    TSMatrixScaledIdentityBodyC(UIntT i,RealT nscale = 1.0)
      : TSMatrixPartialBodyC<DataT>(i,i),
	scale(nscale)
    {}
    //: Constructor.
    
    virtual RCBodyVC &Copy() const
    { return *new TSMatrixScaledIdentityBodyC<DataT>(Rows(),scale); }
    //: Create a copy of this matrix.
    
    virtual const type_info &MatrixType() const
    { return typeid(TSMatrixScaledIdentityBodyC<DataT>); }
    //: Find the type of the matrix.
    
    virtual DataT Element(UIntT i,UIntT j) const { 
      if(i != j) return 0;
      return scale;
    } 
    //: Access element.
    
    virtual void Element(UIntT i,UIntT j,const DataT &val) {
      RavlAssert(0);
    }
    //: Set element.
    
    virtual Array1dC<DataT> Row(UIntT i) const { 
      Array1dC<DataT> ret(IndexRangeC(i,i));
      ret[i] = scale;
      return ret;
    }
    //: Access a row from the matrix.
    
    virtual DataT MulSumColumn(UIntT c,const Array1dC<DataT> &dat) const { 
      if(!dat.Contains(c)) {
	DataT ret;
	SetZero(ret);
	return ret;
      }
      return dat[c] * scale;
    }
    //: Multiply columb by values from dat and sum them.
    
    virtual TSMatrixC<DataT> T() const { 
      // FIXME: This should really be a copy ?
      return TSMatrixScaledIdentityC<DataT>(const_cast<TSMatrixScaledIdentityBodyC<DataT> &>(*this)); 
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

    virtual TMatrixC<DataT> TMatrix() const;
    //: Get as full matrix.

  protected:
    DataT scale;
  };
  
  
  //! userlevel=Normal
  //: ScaledIdentity matrix
  
  template<class DataT>
  class TSMatrixScaledIdentityC
    : public TSMatrixPartialC<DataT>
  {
  public:
    TSMatrixScaledIdentityC(int i)
      : TSMatrixPartialC<DataT>(*new TSMatrixScaledIdentityBodyC<DataT>(i))
    {}
    //: Create a diagonal matrix of size i by i .
    // The contents of the matrix are undefined.
    
    TSMatrixScaledIdentityC(const TVectorC<DataT> &data)
      : TSMatrixPartialC<DataT>(*new TSMatrixScaledIdentityBodyC<DataT>(data))
    {}
    //: Create a diagonal matrix from a vector.
    
  protected:
    TSMatrixScaledIdentityC(TSMatrixScaledIdentityBodyC<DataT> &bod)
      : TSMatrixPartialC<DataT>(bod)
    {}
    //: Body constructor.
    
    TSMatrixScaledIdentityBodyC<DataT> &Body()
    { return static_cast<TSMatrixScaledIdentityBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
    const TSMatrixScaledIdentityBodyC<DataT> &Body() const
    { return static_cast<const TSMatrixScaledIdentityBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
  public:
    friend class TSMatrixScaledIdentityBodyC<DataT>;
  };
  
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixScaledIdentityBodyC<DataT>::Mul(const TSMatrixC<DataT> &mat) const {
    RavlAssert(Cols() == mat.Rows());
    const SizeT rdim = Rows();
    const SizeT cdim = mat.Cols();
    TMatrixC<DataT> out(rdim, cdim);
    for (UIntT r = 0; r < rdim; r++) {
      Array1dC<DataT> ra = mat.Row(r);
      DataT *at = &(out[r][0]);
      DataT *start = &(at[ra.IMin().V()]);
      const DataT *end1 = &(at[ra.IMax().V()]);
      const DataT *end2 = &(at[Cols()]);
      for(;at != start;at++)
	SetZero(*at);
      DataT *at2 = ra[ra.IMin().V];
      for(;at != end1;at++,at2++)
	*at = scale * (*at2);
      for(;at != end2;at++)
	SetZero(*at);
    }
    return out;
  }
  
  template<class DataT>
  TVectorC<DataT> TSMatrixScaledIdentityBodyC<DataT>::Mul(const TVectorC<DataT> &oth) const {
    RavlAssert(Rows() == oth.Size());
    TVectorC<DataT> ret(oth.Size());
    for(SArray1dIter2C<DataT,DataT> it(ret,oth);it;it++)
      it.Data1() = scale * it.Data2();
    return ret;
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixScaledIdentityBodyC<DataT>::MulT(const TSMatrixC<DataT> & B) const {
    return TSMatrixScaledIdentityBodyC<DataT>::Mul(B.T());
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixScaledIdentityBodyC<DataT>::TMul(const TSMatrixC<DataT> & B) const {
    return TSMatrixScaledIdentityBodyC<DataT>::Mul(B);
  }
  
  template<class DataT>
  TVectorC<DataT> TSMatrixScaledIdentityBodyC<DataT>::TMul(const TVectorC<DataT> & B) const {
    return TSMatrixScaledIdentityBodyC<DataT>::Mul(B);
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixScaledIdentityBodyC<DataT>::AAT() const {
    return TSMatrixScaledIdentityBodyC<DataT>(Rows(),Sqr(scale));
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixScaledIdentityBodyC<DataT>::ATA() const {
    return TSMatrixScaledIdentityBodyC<DataT>::AAT();
  }
  
  template<class DataT>
  TMatrixC<DataT> TSMatrixScaledIdentityBodyC<DataT>::TMatrix() const {
    TMatrixC<DataT> ret(Rows(),Cols());
    ret.Fill(0);
    for(int i = 0;i < Rows();i++)
      ret[i][i] = scale;
    return ret;
  }
}
#endif

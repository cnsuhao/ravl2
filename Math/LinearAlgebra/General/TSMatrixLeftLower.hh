// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TSMATRIXLEFTLOWER_HEADER
#define RAVL_TSMATRIXLEFTLOWER_HEADER 1
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/TSMatrix.hh"
#include "Ravl/Math.hh"

namespace RavlN {
  template<class DataT> class TSMatrixLeftLowerC;
  
  //! userlevel=Develop
  //: LeftLower matrix body
  
  template<class DataT>
  class TSMatrixLeftLowerBodyC
    : public TSMatrixPartialBodyC<DataT>
  {
  public:
    static inline SizeT TriangleSize(int i)
    { return (i * (i+1))/2; }
    //: Size of triangle with size i.
    
    inline SizeT ElementIndex(int i,int j) const
    { return (i * (i+1))/2 + j; }
    //: Find index of element i,j
    
    inline SizeT RowStart(int i) const
    { return (i * (i+1))/2; }
    //: Address of row start.
    
    TSMatrixLeftLowerBodyC(int i)
      : TSMatrixPartialBodyC<DataT>(i,i,SArray1dC<DataT>(TriangleSize(i)))
    {}
    //: Constructor.
    
    TSMatrixLeftLowerBodyC(int i,const SArray1dC<DataT> &ndata)
      : TSMatrixPartialBodyC<DataT>(i,i,ndata)
    {}
    //: Constructor.
    
    virtual RCBodyVC &Copy() const
    { return *new TSMatrixLeftLowerBodyC<DataT>(Rows(),data.Copy()); }
    //: Create a copy of this matrix.
    
    virtual const type_info &MatrixType() const
    { return typeid(TSMatrixLeftLowerBodyC<DataT>); }
    //: Find the type of the matrix.
    
    virtual DataT Element(UIntT i,UIntT j) const { 
      if(j > i)
	return 0;
      return data[ElementIndex(i,j)];
    }
    //: Access element.
    
    virtual void Element(UIntT i,UIntT j,const DataT &val) {
      if(j > i) {
	if(val != 0)
	  cerr << "Attempting to set invalid element of matrix." << i << " " << j << "\n";
	return ;
      }
      data[ElementIndex(i,j)] = val;
    }
    //: Set element.
    
    virtual Array1dC<DataT> Row(UIntT i) const
    { return Array1dC<DataT>(const_cast<BufferC<DataT> &>(data.Buffer()),
			     RangeBufferAccessC<DataT>(const_cast<DataT *>( &(data[RowStart(i)])),IndexRangeC(0,i))); }
    //: Access a row from the matrix.
    
    virtual DataT MulSumColumn(UIntT c,const Array1dC<DataT> &dat) const;
    //: Multiply columb by values from dat and sum them.
    
    virtual TSMatrixC<DataT> T() const;
    //: Get transpose of matrix.
    // This is a no-op.

#if 0    
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
#endif
    
    virtual TMatrixC<DataT> TMatrix() const;
    //: Get as full matrix.
    
    virtual void SetDiagonal(const TVectorC<DataT> &d) { 
      RavlAssert(0);
    }
    //: Set the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.
    
    virtual void AddDiagonal(const TVectorC<DataT> &d) {  
      RavlAssert(0);
    }
    //: Add a vector to the diagonal of this matrix.
    // If d.Size() != Cols() an error is given.
    
  };
  
  //! userlevel=Normal
  //: LeftLower matrix
  
  template<class DataT>
  class TSMatrixLeftLowerC
    : public TSMatrixPartialC<DataT>
  {
  public:
    TSMatrixLeftLowerC(int i)
      : TSMatrixPartialC<DataT>(*new TSMatrixLeftLowerBodyC<DataT>(i))
    {}
    //: Create a diagonal matrix of size i by i .
    // The contents of the matrix are undefined.
    
  protected:
    TSMatrixLeftLowerC(TSMatrixLeftLowerBodyC<DataT> &bod)
      : TSMatrixPartialC<DataT>(bod)
    {}
    //: Body constructor.
    
    TSMatrixLeftLowerBodyC<DataT> &Body()
    { return static_cast<TSMatrixLeftLowerBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
    const TSMatrixLeftLowerBodyC<DataT> &Body() const
    { return static_cast<const TSMatrixLeftLowerBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
  public:
    friend class TSMatrixLeftLowerBodyC<DataT>;
  };
  
  
  template<class DataT>
  DataT TSMatrixLeftLowerBodyC<DataT>::MulSumColumn(UIntT c,const Array1dC<DataT> &dat) const {
    UIntT s = Max((UIntT) dat.Range().Min().V(),c);
    if(!dat.Contains(s)){
      DataT ret;
      SetZero(ret);
      return ret;
    }
    const DataT *at2 = &(dat[s]);
    const DataT *endp = &(at2[dat.Size()-s]);
    const DataT *at = &data[ElementIndex(s,c)];
    DataT sum = (*at2) * (*at);
    s++;
    at += s;
    for(at2++,s++;at2 != endp;s++,at2++) {
      sum += (*at2) * (*at);
      at += s;
    }
    return sum;
  }
  
#if 0
  template<class DataT>
  TSMatrixC<DataT> TSMatrixLeftLowerBodyC<DataT>::Mul(const TSMatrixC<DataT> &mat) const {
    RavlAssert(0);
    return TSMatrixC<DataT>();
  }
  
  template<class DataT>
  TVectorC<DataT> TSMatrixLeftLowerBodyC<DataT>::Mul(const TVectorC<DataT> &oth) const {
    RavlAssert(0);
    return TVectorC<DataT>();
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixLeftLowerBodyC<DataT>::MulT(const TSMatrixC<DataT> & B) const {
    RavlAssert(0);
    return TSMatrixC<DataT>();
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixLeftLowerBodyC<DataT>::TMul(const TSMatrixC<DataT> & B) const {
    RavlAssert(0);
    return TSMatrixC<DataT>();
  }
  
  template<class DataT>
  TVectorC<DataT> TSMatrixLeftLowerBodyC<DataT>::TMul(const TVectorC<DataT> & B) const {
    RavlAssert(0);
    return TVectorC<DataT>();
  }  
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixLeftLowerBodyC<DataT>::AAT() const {
    TSMatrixLeftLowerC<DataT> diag(Rows());
    for(SArray1dIter2C<DataT,DataT> it(diag.Data(),data);it;it++)
      it.Data1() = Sqr(it.Data2());
    return diag;
  }
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixLeftLowerBodyC<DataT>::ATA() const {
    return TSMatrixLeftLowerBodyC<DataT>::AAT();
  }
#endif
  
  template<class DataT>
  TMatrixC<DataT> TSMatrixLeftLowerBodyC<DataT>::TMatrix() const {
    TMatrixC<DataT> ret(Rows(),Cols());
    const DataT *at1 = &(data[0]);
    for(UIntT j = 0;j < Rows();j++) {
      DataT *at2 = &(ret[j][0]);
      const DataT *end = &at2[Cols()];
      DataT *end2 = &(at2[j+1]);
      for(;at2 != end2;at2++,at1++)
	*at2 = *at1;
      for(;at2 != end;at2++)
	SetZero(*at2);
    }
    return ret;
  }

  //: Get transpose of matrix.
  // This is a no-op.
  
  template<class DataT>
  TSMatrixC<DataT> TSMatrixLeftLowerBodyC<DataT>::T() const {
    return TSMatrixC<DataT>(TMatrix().T());
  }
}

#endif

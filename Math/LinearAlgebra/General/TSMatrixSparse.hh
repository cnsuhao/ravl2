// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TSMATRIXSPARSE_HEADER
#define RAVL_TSMATRIXSPARSE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/TSMatrix.hh"
#include "Ravl/InDList.hh"
#include "Ravl/InDLIter.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: DLink with index number
  
  class IndexDLinkC
    : public DLinkC
  {
  public:
    IndexDLinkC(IndexC ind)
      : index(ind)
    {}
    //: Create a link with
    
    IndexC Index() const
    { return index; }
    //: Get index of link.
    
  protected:
    IndexC index;
  };

  //! userlevel=Normal
  //: List of indexed links.
  
  class IndexDListC
    : public IntrDListC<IndexDLinkC>
  {
  public:
    IndexDListC()
    {}
    //: Default constructor.
    
    const IndexDLinkC *Find(int i) const;
    //: Find element with given index.
    // Assumes an ordered list.
    
    bool Insert(IndexDLinkC &newun);
    //: Add an item to the list.
    // returns false if its already present.
    
    IndexRangeC Range() const {
      if(IsEmpty())
	return IndexRangeC();
      return IndexRangeC(First().Index(),Last().Index());
    }
    //: Get range of indexes in list.
  };
  
  template<class DataT>
  class TSMatrixSparseEntryC
  {
  public:
    TSMatrixSparseEntryC(const Index2dC &ind,const DataT &dat)
      : irow(ind[1]),
	icol(ind[0]),
	data(dat)
    {}
    //: Constructor.
    
    TSMatrixSparseEntryC(UIntT i,UIntT j,const DataT &dat)
      : 
	irow(j),
	icol(i),
	data(dat)
    {}
    //: Constructor.
    
    UIntT Row() const
    { return icol.Index().V(); }
    //: Get row.

    UIntT Col() const
    { return irow.Index().V(); }
    //: Get col.
    
    IndexDLinkC &IRow()
    { return irow; }
    //: Access row link.
    
    IndexDLinkC &ICol()
    { return icol; }
    //: Access column link.
    
    const DataT &Data() const
    { return data; }
    //: Access data.
    
    DataT &Data()
    { return data; }
    //: Access data.
    
  protected:
    IndexDLinkC irow;
    IndexDLinkC icol;
    DataT data;
  };
  
  //! userlevel=Develop
  //: Sparse matrix body
  
  template<class DataT>
  class TSMatrixSparseBodyC
    : public TSMatrixBodyC<DataT>
  {
  public:
    TSMatrixSparseBodyC()
    {}
    //: Default constructor.
    
    TSMatrixSparseBodyC(UIntT nrows,UIntT ncols)
      : TSMatrixBodyC<DataT>(nrows,ncols),
	rows(nrows),
	cols(ncols)
    {}
    //: Construct a matrix of the given size.
    
    TSMatrixSparseBodyC(const TMatrixC<DataT> &mat,const DataT &zeroValue = 1e-6);
    //: Construct a sparse matrix for a full matrix.
    // Any elements with an absolute value smaller than 'zeroValue' are taken as zero.
    
  protected:
    static  TSMatrixSparseEntryC<DataT> *RowDLink2Entry(IndexDLinkC *il)
    { return (TSMatrixSparseEntryC<DataT> *) (((char *) il) - (((char *) &((TSMatrixSparseEntryC<DataT> *) 0)->IRow()) - ((char *) 0))); }
    
    static TSMatrixSparseEntryC<DataT> *ColDLink2Entry(IndexDLinkC *il)
    { return (TSMatrixSparseEntryC<DataT> *) (((char *) il) - (((char *) &((TSMatrixSparseEntryC<DataT> *) 0)->ICol()) - ((char *) 0))); }
    
    const TSMatrixSparseEntryC<DataT> *FindEntry(UIntT i,UIntT j) const { 
      const IndexDLinkC *il = rows[i].Find(j);
      if(il == 0) return 0;
      return RowDLink2Entry(const_cast<IndexDLinkC *>(il));
    }
    //: Find an index.
    
    TSMatrixSparseEntryC<DataT> *FindEntry(UIntT i,UIntT j) 
    { return const_cast<TSMatrixSparseEntryC<DataT> *>(((const TSMatrixSparseBodyC<DataT> *)this)->FindEntry(i,j)); }
    //: Find an index.
    
    void Insert(TSMatrixSparseEntryC<DataT> &entry) {
      rows[entry.Row()].Insert(entry.IRow());
      cols[entry.Col()].Insert(entry.ICol());
    }
    //: Insert an entry.
    
    IndexRangeC RowRange(int i) const 
    { return  rows[i].Range(); }
    //: Get range of column's for row i.

    IndexRangeC ColRange(int i) const 
    { return  rows[i].Range(); }
    //: Get range of rows's for column i.
    
  public:
    virtual ~TSMatrixSparseBodyC() {
      for(SArray1dIterC<IndexDListC> it(rows);it;it++) {
	while(!it->IsEmpty())
	  delete RowDLink2Entry(&(it->First()));
      }
    }
    //: Destructor.
    
    virtual RCBodyVC &Copy() const;
    //: Create a copy of this matrix.
    
    virtual const type_info &MatrixType() const
    { return typeid(TSMatrixSparseBodyC<DataT>); }
    //: Find the type of the matrix.
    
    virtual DataT Element(UIntT i,UIntT j) const { 
      const TSMatrixSparseEntryC<DataT> *entry = FindEntry(i,j);
      if(entry == 0) {
	DataT ret;
	SetZero(ret);
	return ret;
      }
      // Some magic to get the address
      return entry->Data();
    }
    //: Access element.
    
    void Element(UIntT i,UIntT j,const DataT &val) {
      TSMatrixSparseEntryC<DataT> *entry = FindEntry(i,j);
      if(val == 0.0) { // If exactly zero erase the entry.
	if(entry != 0)
	  delete entry;
	return ;
      }
      if(entry != 0) {
	entry->Data() = val;
	return ;
      }
      Insert(*new TSMatrixSparseEntryC<DataT>(i,j,val));
    }
    //: Set a matrix element.
    
    virtual Array1dC<DataT> Row(UIntT i) const;
    //: Access a row from the matrix.
    
    virtual DataT MulSumColumn(UIntT c,const Array1dC<DataT> &dat) const;
    //: Multiply columb by values from dat and sum them.
    
    virtual TMatrixC<DataT> TMatrix() const;
    //: Access as a TMatrix.
    
    virtual TSMatrixC<DataT> T() const;
    //: Get transpose of matrix.
  protected:
    SArray1dC<IndexDListC > rows;
    SArray1dC<IndexDListC > cols;
  };

  //! userlevel=Normal
  //: Sparse matrix
  
  template<class DataT>
  class TSMatrixSparseC 
    : public TSMatrixC<DataT>
  {
  public:
    TSMatrixSparseC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    TSMatrixSparseC(UIntT rows,UIntT cols)
      : TSMatrixC<DataT>(*new TSMatrixSparseBodyC<DataT>(rows,cols))
    {}
    //: Create a matrix of the given size.
    // The default matrix is filled with zero's.
    
    TSMatrixSparseC(const TMatrixC<DataT> &mat,const DataT &zeroValue = 1e-6)
      : TSMatrixC<DataT>(*new TSMatrixSparseBodyC<DataT>(mat,zeroValue))
    {}
    //: Construct a sparse matrix for a full matrix.
    // Any elements with an absolute value smaller than 'zeroValue' are taken as zero.
    
  protected:
    TSMatrixSparseC(TSMatrixSparseBodyC<DataT> &bod)
      : TSMatrixC<DataT>(bod)
    {}
    //: Body constructor.
    
    TSMatrixSparseBodyC<DataT> &Body()
    { return static_cast<TSMatrixSparseBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
    const TSMatrixSparseBodyC<DataT> &Body() const
    { return static_cast<const TSMatrixSparseBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
  public:
    friend class TSMatrixSparseBodyC<DataT>;
  };
  
  
  //: Construct a sparse matrix for a full matrix.
  // Any elements with an absolute value smaller than 'zeroValue' are taken as zero.
  
  template<class DataT>
  TSMatrixSparseBodyC<DataT>::TSMatrixSparseBodyC(const TMatrixC<DataT> &mat,const DataT &zeroValue) 
    : TSMatrixBodyC<DataT>(mat.Rows(),mat.Cols())
  {
    BufferAccess2dIterC<DataT> it(mat);
    if(!it)
      return ;
    IndexDListC *rlist = rows[0];
    do {
      IndexDListC *clist = &(cols[0]);
      do {
	if(Abs(*it) > zeroValue) {
	  TSMatrixSparseEntryC<DataT> &entry = *new TSMatrixSparseEntryC<DataT>(it->Index(mat.RefrenceElm()),*it);
	  rlist->InsLast(entry.IRow());
	  clist->InsLast(entry.ICol());
	}
	clist++;
      } while(it.Next()) ;
      rlist++;
    } while(it) ;
  }

  //: Create a copy of this matrix.
  
  template<class DataT>
  RCBodyVC &TSMatrixSparseBodyC<DataT>::Copy() const {
    TSMatrixSparseBodyC<DataT> &newBod = *new TSMatrixSparseBodyC<DataT>(Rows(),Cols());
    IndexDListC *rlist = &(newBod.rows[0]);
    for(UIntT i = 0;i < Rows();i++,rlist++) {
      for(IntrDLIterC<IndexDLinkC> it(rows[i]);it;it++) {
	TSMatrixSparseEntryC<DataT> *entry = RowDLink2Entry(&(*it));
	UIntT ncol = it->Index().V();
	TSMatrixSparseEntryC<DataT> &newentry = *new TSMatrixSparseEntryC<DataT>(i,ncol,entry->Data());
	rlist->InsLast(newentry.IRow());
	newBod.cols[ncol].InsLast(newentry.ICol());
      }
    }
    return newBod;
  }

  
  //: Access a row from the matrix.
  
  template<class DataT>
  Array1dC<DataT> TSMatrixSparseBodyC<DataT>::Row(UIntT i) const {
    Array1dC<DataT> ret(RowRange(i));
    if(ret.IsEmpty())
      return ret;
    DataT *rstart = &(ret[ret.IMin()]);
    DataT *at = rstart;
    IntrDLIterC<IndexDLinkC> it(rows[i]);
    *at = RowDLink2Entry(&(*it))->Data();
    for(it++,at++;it;it++,at++) {
      DataT *next = &(rstart[it->Index().V()]);
      for(;at < next;at++)
	SetZero(*at);
      *at = RowDLink2Entry(&(*it))->Data();
    }
    return ret;
  }
  
  //: Multiply columb by values from dat and sum them.
  
  template<class DataT>
  DataT TSMatrixSparseBodyC<DataT>::MulSumColumn(UIntT c,const Array1dC<DataT> &dat) const {
    DataT sum;
    IntrDLIterC<IndexDLinkC> it(cols[c]);
    for(;it;it++) {
      if(it->Index() < dat.IMin())
	continue;
    }
    if(!it) {
      SetZero(sum);     
      return sum;
    }
    sum = dat[it->Index()] * ColDLink2Entry(&(*it))->Data();
    for(it++;it && it->Index() < dat.IMax();it++)
      sum += dat[it->Index()] * ColDLink2Entry(&(*it))->Data();
    return sum;
  }

  template<class DataT>
  TSMatrixC<DataT> TSMatrixSparseBodyC<DataT>::T() const {
    TSMatrixSparseC<DataT> ret(Cols(),Rows());
    TSMatrixSparseBodyC<DataT> &newBod = ret.Body();
    IndexDListC *rlist = &(newBod.rows[0]);
    for(UIntT i = 0;i < Cols();i++,rlist++) {
      for(IntrDLIterC<IndexDLinkC> it(cols[i]);it;it++) {
	TSMatrixSparseEntryC<DataT> *entry = ColDLink2Entry(&(*it));
	UIntT ncol = it->Index().V();
	TSMatrixSparseEntryC<DataT> &newentry = *new TSMatrixSparseEntryC<DataT>(i,it->Index().V(),entry->Data());
	rlist->InsLast(newentry.IRow());
	newBod.cols[ncol].InsLast(newentry.ICol());
      }
    }
    
    return ret;
  }
  
  template<class DataT>
  TMatrixC<DataT> TSMatrixSparseBodyC<DataT>::TMatrix() const {
    TMatrixC<DataT> ret(Rows(),Cols());
    for(UIntT i = 0;i < Rows();i++) {
      DataT *rstart = &(ret[i][0]);
      DataT *at = rstart;
      for(IntrDLIterC<IndexDLinkC> it(rows[i]);it;it++,at++) {
	DataT *next = &(rstart[it->Index().V()]);
	for(;at < next;at++)
	  SetZero(*at);
	*at = RowDLink2Entry(&(*it))->Data();
      }
      DataT *eor = &(rstart[Cols()]);
      for(;at != eor;at++)
	SetZero(*at);
    }
    return ret;
  }

  
}


#endif

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
    
    IndexDLinkC *Find(int i);
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
    TSMatrixSparseEntryC(Index2dC ind,const DataT &dat)
      : data(dat),
	irow(ind[1]),
	icol(ind[0])
    {}
    //: Constructor.
    
    TSMatrixSparseEntryC(UIntT i,UIntT j,const DataT &dat)
      : data(dat),
	irow(j),
	icol(i)
    {}
    //: Constructor.
    
    UIntT Row() const
    { return icol.Index(); }
    //: Get row.

    UIntT Col() const
    { return irow.Index(); }
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
      : TSMatrixBodyC<DataT>(rows,cols),
	rows(nrows),
	cols(ncols)
    {}
    //: Construct a matrix of the given size.
    
  protected:
    static TSMatrixSparseEntryC<DataT> *RowDLink2Entry(IndexDLinkC *il)
    { return (TSMatrixSparseEntryC<DataT> *) (((char *) il) + (((char *) &((TSMatrixSparseEntryC<DataT> *) 0)->IRow()) - ((char *) 0))); }

    static TSMatrixSparseEntryC<DataT> *ColDLink2Entry(IndexDLinkC *il)
    { return (TSMatrixSparseEntryC<DataT> *) (((char *) il) + (((char *) &((TSMatrixSparseEntryC<DataT> *) 0)->ICol()) - ((char *) 0))); }
    
    TSMatrixSparseEntryC<DataT> *FindEntry(UIntT i,UIntT j) { 
      IndexDLinkC *il = rows[i].Find(j);
      if(il == 0) return 0;
      return RowDLink2Entry(il);
    }
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
	  delete RowDLink2Entry(&it->First());
      }
    }
    //: Destructor.
    
    virtual DataT Element(UIntT i,UIntT j) const { 
      TSMatrixSparseEntryC<DataT> *entry = FindEntry(i,j);
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
  };
}


#endif

#ifndef RAVL_TSMATRIXSPARSEITER_HEADER
#define RAVL_TSMATRIXSPARSEITER_HEADER 1

#include "Ravl/TSMatrixSparse.hh"

namespace RavlN {
  
  
  template<class DataT>
  class TSMatrixSparseRowIterC
  {
  public:
    TSMatrixSparseRowIterC(TSMatrixSparseC<DataT> &mat,IntT row)
      : it(mat.RowList(row))
    {}
    //: Construct from a matrix and a row number
    
    void Next()
    { it.Next(); }
    //: Goto next element.
    
    void operator++(int)
    { it.Next(); }
    //: Goto next element
    
    operator bool() const
    { return it; }
    //: At a valid element ?
    
    DataT &Data()
    { return TSMatrixSparseBodyC<DataT>::RowDLink2Entry(&(*it))->Data(); }
    //: Access data.
    
    DataT &operator*()
    { return Data(); }
    //: Access data.

    const DataT &Data() const
    { return TSMatrixSparseBodyC<DataT>::RowDLink2Entry(*it)->Data(); }
    //: Access data.
    
    const DataT &operator*() const
    { return Data(); }
    //: Access data.
    
    IndexC Index() const
    { return it->Index(); }
    //: Access index of data.
    
  protected:    
    IntrDLIterC<IndexDLinkC> it;
  };



  template<class DataT>
  class TSMatrixSparseColIterC
  {
  public:
    TSMatrixSparseColIterC(TSMatrixSparseC<DataT> &mat,IntT col)
      : it(mat.ColList(col))
    {}
    //: Construct from a matrix and a row number
    
    void Next()
    { it.Next(); }
    //: Goto next element.
    
    void operator++(int)
    { it.Next(); }
    //: Goto next element
    
    operator bool() const
    { return it; }
    //: At a valid element ?
    
    DataT &Data()
    { return TSMatrixSparseBodyC<DataT>::ColDLink2Entry(&(*it))->Data(); }
    //: Access data.
    
    DataT &operator*()
    { return Data(); }
    //: Access data.

    const DataT &Data() const
    { return TSMatrixSparseBodyC<DataT>::ColDLink2Entry(*it)->Data(); }
    //: Access data.
    
    const DataT &operator*() const
    { return Data(); }
    //: Access data.
    
    IndexC Index() const
    { return it->Index(); }
    //: Access index of data.
    
  protected:
    IntrDLIterC<IndexDLinkC> it;
  };

}

#endif

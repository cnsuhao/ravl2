// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDATASET1ITER_HEADER
#define RAVLDATASET1ITER_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DataSet1.hh"
#include "Ravl/CollectionIter.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Iterate through a data set.
  
  template<class DataT>
  class DataSet1IterC {
  public:
    DataSet1IterC()
    {}
    //: Default construtor.
    
    DataSet1IterC(DataSet1C<DataT> &nds)
      : ds(nds),
      index(nds.Index())
    {}
    //: Construct from a data set.
    
    bool IsElm() const
    { return index.IsElm(); }
    //: At a valid element ?
    
    operator bool() const
    { return index.IsElm(); }
    //: At a valid element ?
    
    DataT &Data()
    { return ds.Sample1()[*index]; }
    //: Access sample.
    
    const DataT &Data() const
    { return ds.Sample1()[*index]; }
    //: Access sample.
    
    void Next() 
    { index.Next(); }
    //: Goto next element.
    
    void operator++(int)
    { index++; }
    //: Goto next element.
    
    void First() 
    { index.First(); }
    //: Goto first element.
    
  protected:
    DataSet1C<DataT> ds;
    CollectionIterC<UIntT> index;
  };
  
}



#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDATASET2ITER_HEADER
#define RAVLDATASET2ITER_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/CollectionIter.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Iterate through a data set.
  
  template<class Data1T,class Data2T>
  class DataSet2IterC {
  public:
    DataSet2IterC()
    {}
    //: Default construtor.
    
    DataSet2IterC(DataSet2C<Data1T> &nds)
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
    
    Data1T &Data1()
    { return ds.Sample1()[*index]; }
    //: Access sample.
    
    Data1T &Data2()
    { return ds.Sample2()[*index]; }
    //: Access sample.
    
    const Data1T &Data() const
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
    DataSet2C<Data1T,Data2T> ds;
    CollectionIterC<UIntT> index;
  };
  
}



#endif

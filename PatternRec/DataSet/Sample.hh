// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SAMPLE_HEADER
#define RAVL_SAMPLE_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include "Ravl/DArray1d.hh"
#include "Ravl/Collection.hh"
namespace RavlN {

  template<class SampleT> class DataSet1IterC;
  template<class Sample1T,class Sample2T> class DataSet2IterC;
  template<class Sample1T,class Sample2T,class Sample3T> class DataSet3IterC;
  
  //! userlevel=Normal
  //: Sample of DataT's
  
  template <class DataT> 
  class SampleC 
    : protected DArray1dC<DataT>
  {
  public:
    typedef DataT ElementT;
    //: Type of data in sample.
    
    SampleC(SizeT maxSize=10)
      //: DArray1dC()
    {}
    //: Create a sample of data with a maximum size
    
    SampleC(const SArray1dC<DataT> & dat)
      : DArray1dC<DataT>(dat)
    {}
    //: Create a sample of data from an array
    
    SampleC<DataT> SubSample(const CollectionC<UIntT> &x);
    //: Take a subsample of the given indexes in x.
    
    DataT ExtractEntry(int ind);
    //: Extract an entry from sample.

    UIntT Append(const DataT & dat)
    { return DArray1dC<DataT>::Append(dat).V(); }
    //: Insert a single sample into sample
    
#if 0
    DataT Pick()
      { return CollectionC<DataT>::Pick(); }
    //: Pick a random item from the collection
#endif
    
    SizeT Size() const
      { return DArray1dC<DataT>::Size(); }
    //: Return the number of valid samples in the collection
    
    DataT &operator[](IndexC ind)
      { return DArray1dC<DataT>::operator[](ind); }
    //: Access a sample.
    
    const DataT &operator[](IndexC ind) const
      { return DArray1dC<DataT>::operator[](ind); }
    //: Access a sample.

    friend class DataSet1IterC<DataT>;

    DArray1dC<DataT> &DArray()
    { return *this; }
    //: Access DArray.
    // For internal use only.
    
    const DArray1dC<DataT> &DArray() const
    { return *this; }
    //: Access DArray.
    // For internal use only.

  }; // end of class SampleC 


  //: Take a subsample of this set.
  
  template <class DataT>
  SampleC<DataT> SampleC<DataT>::SubSample(const CollectionC<UIntT> &x) {
    SampleC<DataT> ret(x.Size());
    for(CollectionIterC<UIntT> it(x);it;it++)
      ret.Insert((*this)[*it]);
    return ret;
  }

  //: Extract an entry from sample.
  
  template <class DataT>
  DataT SampleC<DataT>::ExtractEntry(int ind) {
    RavlAssert(Contains(ind));
    DataT ret = (*this)[ind];
    Remove(ind);
    return ret;
  }
  
}

#endif

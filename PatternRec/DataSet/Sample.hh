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
//! file="Ravl/PatternRec/DataSet/Sample.hh"

#include "Ravl/DArray1d.hh"
#include "Ravl/Collection.hh"

namespace RavlN {

  template<class SampleT> class DataSet1IterC;
  template<class Sample1T,class Sample2T> class DataSet2IterC;
  template<class Sample1T,class Sample2T,class Sample3T> class DataSet3IterC;
  template<class SampleT> class SampleIterC;
  
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
      : DArray1dC<DataT>(maxSize,true)
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
    
    SizeT Size() const
    { return DArray1dC<DataT>::Size(); }
    //: Return the number of valid samples in the collection
    
    DataT PickElement(UIntT i);
    //: Pick a item i from the collection
    // Note: The order of the collection is NOT preserved.
    // This minimizes the distruption to the underlying
    // representation by removing an element from the end
    // of the array and placing it in the hole left by 
    // removing 'i'.

    DataT &Nth(UIntT i)
    { return DArray1dC<DataT>::Nth(i); }
    //: Access nth element in sample.
    
    const DataT &Nth(UIntT i) const
    { return DArray1dC<DataT>::Nth(i); }
    //: Access nth element in sample.
    
    DataT Pick()
    { return PickElement(RandomInt() % Size()); }
    //: Pick a random item from the collection
    // Note: The order of the collection is NOT preserved.
    
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

    DataT &First()
    { return DArray1dC<DataT>::First(); }
    //: Access first element in the array.
    
    const DataT &First() const
    { return DArray1dC<DataT>::First(); }
    //: Access first element in the array.
    
    DataT &Last()
    { return DArray1dC<DataT>::Last(); }
    //: Access last element in the array.
    
    const DataT &Last() const
    { return DArray1dC<DataT>::Last(); }
    //: Access last element in the array.
    
    bool IsEmpty() const
    { return DArray1dC<DataT>::IsEmpty(); }
    //: Is this empty ?
    
  }; // end of class SampleC 


  //: Take a subsample of this set.
  
  template <class DataT>
  SampleC<DataT> SampleC<DataT>::SubSample(const CollectionC<UIntT> &x) {
    SampleC<DataT> ret(x.Size());
    for(CollectionIterC<UIntT> it(x);it;it++)
      ret.Insert((*this)[*it]);
    return ret;
  }
  
  template <class DataT>
  DataT SampleC<DataT>::ExtractEntry(int ind) {
    RavlAssert(Contains(ind));
    DataT ret = (*this)[ind];
    Remove(ind);
    return ret;
  }
  
  template <class DataT>
  DataT SampleC<DataT>::PickElement(UIntT i) {
    DataT &val = Nth(i);
    DataT ret = val;
    val = Last();
    RemoveLast();
    return ret;
  }
  
  
}

#endif

#ifndef RAVL_SAMPLEDISCRETE_HEADER
#define RAVL_SAMPLEDISCRETE_HEADER 1
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/Histogram.hh"
#include "Ravl/DArray1dIter.hh"
#include "Ravl/CollectionIter.hh"
#include "Ravl/RCHash.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Sample of discrete objects.
  
  template<class DataT>
  class SampleDiscreteC 
    : public SampleC<DataT>
  {
  public:
    SampleDiscreteC(SizeT maxSize=10)
      : SampleC<DataT>(maxSize)
      {}
    //: Create a sample of data with a maximum size
    
    SampleDiscreteC(const SArray1dC<UIntT> & dat)
      : SampleC<UIntT>(dat)
      {}
    //: Create a sample of data from an array
    
    HistogramC<DataT> Histogram() const;
    //: Compute an occurrence histogram for sample.
    
    HistogramC<DataT> Histogram(const CollectionC<UIntT> &index) const;
    //: Compute an occurrence histogram of given elements.
    
    RCHashC<DataT,CollectionC<UIntT> > ListInstancesOfLabels() const;
    //: List all the instances (by sample no) of each Label in the sample.
    
    RCHashC<DataT,CollectionC<UIntT> > ListInstancesOfLabels(const CollectionC<UIntT> &index) const;
    //: List all the instances (by sample no) of each Label in the sample.
    // If index is set, only search the sample no's given in it.
    
  }; 
  
  
  template<class DataT>
  HistogramC<DataT> SampleDiscreteC<DataT>::Histogram() const {
    HistogramC<DataT> ret;
    for(DArray1dIterC<DataT> it(*this);it;it++)
      ret.Vote(*it);
    return ret;
  }

  template<class DataT>
  HistogramC<DataT> SampleDiscreteC<DataT>::Histogram(const CollectionC<UIntT> &index) const {
    HistogramC<DataT> ret;
    for(CollectionConstIterC<UIntT> it(index);it;it++)
      ret.Vote((*this)[*it]);
    return ret;
  }
  
  //: List all the instances (by sample no) of each Label in the sample.
  // If index is set, only search the sample no's given there.
  
  template<class DataT>  
  RCHashC<DataT,CollectionC<UIntT> > SampleDiscreteC<DataT>::ListInstancesOfLabels() const {
    RCHashC<DataT,CollectionC<UIntT> > ret;
    for(DArray1dIterC<UIntT> it(*this);it;it++)
      ret[(UIntT) it.Index().V()].Insert(*it);
    return ret;
  }
  
  //: List all the instances (by sample no) of each Label in the sample.
  // If index is set, only search the sample no's given there.
  
  template<class DataT>  
  RCHashC<DataT,CollectionC<UIntT> > SampleDiscreteC<DataT>::ListInstancesOfLabels(const CollectionC<UIntT> &index) const {
    RCHashC<DataT,CollectionC<UIntT> > ret;
    for(CollectionConstIterC<UIntT> it(index);it;it++)
      ret[(*this)[*it]].Insert(*it);
    return ret;
  }

}
#endif

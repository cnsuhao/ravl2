// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASET1_HEADER
#define RAVL_DATASET1_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/DataSet1.hh"

#include "Ravl/PatternRec/DataSetBase.hh"
#include "Ravl/Vector.hh"
#include "Ravl/DArray1dIter.hh"

namespace RavlN {
  template<class SampleT> class DataSet1C;
  
  //! userlevel=Develop
  //: Data set 
  
  template <class SampleT> 
  class DataSet1BodyC 
    : public DataSetBaseBodyC
  {
  public:
    DataSet1BodyC(UIntT sizeEstimate)
      : DataSetBaseBodyC(sizeEstimate),
	samp1(sizeEstimate)
    {}
    //: Create an empty dataset.
    
    DataSet1BodyC(const SampleT & samp);
    //: Create a dataset from a sample
    
    SampleT &Sample1()
    { return samp1; }
    //: Access sample.

    const SampleT &Sample1() const
    { return samp1; }
    //: Access sample.
    
    UIntT Append(const typename SampleT::ElementT &data);
    //: Append a data entry.
    // returns its index.
    
    DataSet1C<SampleT> ExtractSample(RealT proportion);
    //: Extract a sample.
    // The elements are removed from this set. NB. The order
    // of this dataset is NOT preserved.
    
    virtual void Shuffle();
    //: Shuffle the order of the dataset.
    
    UIntT Size() const
    { return samp1.Size(); }
    //: Get the size of the dataset.
    
  protected:
    SampleT samp1;
    //: the actual data
    
  };

  //! userlevel=Normal
  //: Data set 
  
  template<class SampleT>
  class DataSet1C
    : public DataSetBaseC
  {
  public:
    DataSet1C()
    {}
    //: Default constructor.
    
    DataSet1C(UIntT sizeEstimate)
      : DataSetBaseC(*new DataSet1BodyC<SampleT>(sizeEstimate))
    {}
    //: Default constructor.
    
    DataSet1C(const SampleT & dat)
      : DataSetBaseC(*new DataSet1BodyC<SampleT>(dat))
      {}
    //: Create a dataset from a sample
    
  protected:    
    DataSet1C(DataSet1BodyC<SampleT> &bod)
      : DataSetBaseC(bod)
      {}
    //: Body constructor.
    
    DataSet1BodyC<SampleT> &Body()
    { return static_cast<DataSet1BodyC<SampleT> &>(DataSetBaseC::Body()); }
    //: Access body.

    const DataSet1BodyC<SampleT> &Body() const
    { return static_cast<const DataSet1BodyC<SampleT> &>(DataSetBaseC::Body()); }
    //: Access body.
    
  public:
    SampleT &Sample1()
    { return Body().Sample1(); }
    //: Access complete sample.
    
    const SampleT &Sample1() const
    { return Body().Sample1(); }
    //: Access complete sample.
    
    UIntT Append(const typename SampleT::ElementT &data)
    { return Body().Append(data); }
    //: Append a data entry.
    // returns its index.
    
    DataSet1C<SampleT> ExtractSample(RealT proportion)
    { return Body().ExtractSample(proportion); }
    //: Extract a sample.
    // The elements are removed from this set. NB. The order
    // of this dataset is NOT preserved.

    UIntT Size() const
    { return Body().Size(); }
    //: Get the size of the dataset.
    
    friend class DataSet1BodyC<SampleT>;
  };
  

  template<class SampleT>
  DataSet1BodyC<SampleT>::DataSet1BodyC(const SampleT & sp)
    : DataSetBaseBodyC(sp.Size()),
      samp1(sp)
  {}
  
  template<class SampleT>
  UIntT DataSet1BodyC<SampleT>::Append(const typename SampleT::ElementT &data) {
    return samp1.Append(data);
  }
  
  template<class SampleT>
  DataSet1C<SampleT> DataSet1BodyC<SampleT>::ExtractSample(RealT proportion) {
    RavlAssert(proportion >= 0 && proportion <= 1);
    UIntT size = Size();
    UIntT entries = (UIntT) (proportion * (RealT) size);
    DataSet1C<SampleT> ret;
    for(;entries > 0;entries--) {
      UIntT entry = RandomInt() % size;
      ret.Append(samp1.PickElement(entry));
      size--;
    }
    return ret;
  }
  
  template<class SampleT>
  void DataSet1BodyC<SampleT>::Shuffle() {
    UIntT size = Size();
    for(DArray1dIterC<typename SampleT::ElementT> it(samp1.DArray());it;it++)
      Swap(*it,samp1.Nth(RandomInt() % size));
  }
  
}

#endif

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

#include "Ravl/PatternRec/DataSetBase.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  template<class SampleT> class DataSet1C;
  
  //! userlevel=Develop
  //: Data set 
  
  template <class SampleT> 
  class DataSet1BodyC 
    : public DataSetBaseBodyC
  {
  public:
    DataSet1BodyC()
    {}
    //: Create an empty dataset.
    
    DataSet1BodyC(const SampleT & samp);
    //: Create a dataset from a sample
    
    DataSet1BodyC(const SampleT & samp,const CollectionC<UIntT> &nindex);
    //: Create a dataset from a sample and an index.
    
    SampleT &Sample1()
    { return samp1; }
    //: Access sample.

    const SampleT &Sample1() const
    { return samp1; }
    //: Access sample.
    
    UIntT Append(const typename SampleT::ElementT &data);
    //: Append a data entry.
    // returns its index.
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

    DataSet1C(bool)
      : DataSetBaseC(*new DataSet1BodyC<SampleT>())
    {}
    //: Default constructor.
    
    DataSet1C(const SampleT & dat)
      : DataSetBaseC(*new DataSet1BodyC<SampleT>(dat))
      {}
    //: Create a dataset from a sample
    
  protected:
    DataSet1C(const SampleT & dat,const CollectionC<UIntT> &nindex)
      : DataSetBaseC(*new DataSet1BodyC<SampleT>(dat,nindex))
      {}
    //: Create a dataset from a sample and an index.
    
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
    
    friend class DataSet1BodyC<SampleT>;
  };
  

  template<class SampleT>
  DataSet1BodyC<SampleT>::DataSet1BodyC(const SampleT & sp)
    : DataSetBaseBodyC(sp.Size()),
      samp1(sp)
  {}

  template<class SampleT>
  DataSet1BodyC<SampleT>::DataSet1BodyC(const SampleT & sp,const CollectionC<UIntT> &nindex)
    : DataSetBaseBodyC(nindex),
      samp1(sp)
  {}

  //: Append a data entry.
  // returns its index.
  
  template<class SampleT>
  UIntT DataSet1BodyC<SampleT>::Append(const typename SampleT::ElementT &data) {
    return samp1.Append(data);
  }
  

}

#endif

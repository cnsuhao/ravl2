// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASET2_HEADER
#define RAVL_DATASET2_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/DataSet2.hh"

#include "Ravl/PatternRec/DataSet1.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  template<class Sample1T,class Sample2T> class DataSet2C;
  
  //! userlevel=Develop
  //: Data set 
  
  template <class Sample1T,class Sample2T> 
  class DataSet2BodyC 
    : public DataSet1BodyC<Sample1T>
  {
  public:
    DataSet2BodyC()
    {}
    //: Default constructor.
    
    DataSet2BodyC(const Sample1T & samp1,const Sample2T & samp2);
    //: Create a dataset from a sample
    
    Sample2T &Sample2()
    { return samp2; }
    //: Access complete sample.

    const Sample2T &Sample2() const
    { return samp2; }
    //: Access complete sample.
    
    UIntT Append(const typename Sample1T::ElementT &data1,const typename Sample2T::ElementT &data2);
    //: Append a data entry.
    // returns its index.
    
  protected:
    Sample2T samp2;
    //: the actual data
  };

  //! userlevel=Normal
  //: Data set 
  
  template<class Sample1T,class Sample2T>
  class DataSet2C
    : public DataSet1C<Sample1T>
  {
  public:
    DataSet2C()
    {}
    //: Default constructor.

    DataSet2C(bool)
      : DataSet1C<Sample1T>(*new DataSet2BodyC<Sample1T,Sample2T>())
    {}
    //: Constructor.
    
    DataSet2C(const Sample1T & dat1,const Sample2T & dat2)
      : DataSet1C<Sample1T>(*new DataSet2BodyC<Sample1T,Sample2T>(dat1,dat2))
      {}
    //: Create a dataset from a sample
    
  protected:
    DataSet2C(DataSet2BodyC<Sample1T,Sample2T> &bod)
      : DataSet1C<Sample1T>(bod)
      {}
    //: Body constructor.
    
    DataSet2BodyC<Sample1T,Sample2T> &Body()
      { return static_cast<DataSet2BodyC<Sample1T,Sample2T> &>(DataSetBaseC::Body()); }
    //: Access body.

    const DataSet2BodyC<Sample1T,Sample2T> &Body() const
      { return static_cast<const DataSet2BodyC<Sample1T,Sample2T> &>(DataSetBaseC::Body()); }
    //: Access body.
    
  public:
    Sample2T &Sample2()
    { return Body().Sample2(); }
    //: Access complete sample.
    
    const Sample2T &Sample2() const
    { return Body().Sample2(); }
    //: Access complete sample.
    
    DataSet2C<Sample1T,Sample2T> Shuffle() const
      { return Body().Shuffle(); }
    //: Shuffle the samples in the dataset
    
    UIntT Append(const typename Sample1T::ElementT &data1,const typename Sample2T::ElementT &data2)
    { return Body().Append(data1,data2); }
    //: Append a data entry.
    // returns its index.
    
    friend class DataSet2BodyC<Sample1T,Sample2T>;
  };
  

  template<class Sample1T,class Sample2T>
  DataSet2BodyC<Sample1T,Sample2T>::DataSet2BodyC(const Sample1T & dat1,const Sample2T &dat2)
    : DataSet1BodyC<Sample1T>(dat1),
      samp2(dat2)
  {}
  
  template<class Sample1T,class Sample2T>
  UIntT DataSet2BodyC<Sample1T,Sample2T>::Append(const typename Sample1T::ElementT &data1,const typename Sample2T::ElementT &data2) {
    UIntT no1 = samp1.Append(data1);
    UIntT no2 = samp2.Append(data2);
    RavlAssert(no1==no2);
    return no1;
  }
  

}

#endif

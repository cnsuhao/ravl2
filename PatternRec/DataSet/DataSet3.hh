// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDATASET3_HEADER
#define RAVLDATASET3_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  template<class Sample1T,class Sample2T,class Sample3T> class DataSet3C;
  
  //! userlevel=Develop
  //: Data set 
  
  template <class Sample1T,class Sample2T,class Sample3T> 
  class DataSet3BodyC 
    : public DataSet2BodyC<Sample1T,Sample2T>
  {
  public:
    DataSet3BodyC(const Sample1T & samp1,const Sample2T & samp2,const Sample3T & samp3);
    //: Create a dataset from a sample
    
    DataSet3BodyC(const Sample1T & samp1,const Sample2T & samp2,const Sample3T & samp3,const CollectionC<UIntT> &nindex);
    //: Create a dataset from a sample and an index.
    
    UIntT Append(const typename Sample1T::ElementT &data1,const typename Sample2T::ElementT &data2,const typename Sample3T::ElementT &data3);
    //: Append a data entry.
    // returns its index.
    
  private:
    Sample3T samp3;
    //: the actual data
  };

  //! userlevel=Normal
  //: Data set 
  
  template<class Sample1T,class Sample2T,class Sample3T>
  class DataSet3C
    : public DataSet2C<Sample1T,Sample2T>
  {
  public:
    DataSet3C()
    {}
    //: Default constructor.
    
    DataSet3C(const Sample1T & dat1,const Sample2T & dat2,const Sample3T & dat3)
      : DataSet2C<Sample1T,Sample2T>(*new DataSet3BodyC<Sample1T,Sample2T,Sample3T>(dat1,dat2,dat3))
      {}
    //: Create a dataset from a sample
    
  protected:
    DataSet3C(const Sample1T & dat1,const Sample2T & dat2,const Sample3T & dat3,const CollectionC<UIntT> &nindex)
      : DataSetBaseC(*new DataSet3BodyC<Sample1T,Sample2T,Sample3T>(dat1,dat2,dat3,nindex))
      {}
    //: Create a dataset from a sample and an index.
    
    DataSet3C(DataSet3BodyC<Sample1T,Sample2T,Sample3T> &bod)
      : DataSetBaseC(bod)
      {}
    //: Body constructor.
    
    DataSet3BodyC<Sample1T,Sample2T,Sample3T> &Body()
      { return static_cast<DataSet3BodyC<Sample1T,Sample2T,Sample3T> &>(DataSetBaseC::Body()); }
    //: Access body.

    const DataSet3BodyC<Sample1T,Sample2T,Sample3T> &Body() const
      { return static_cast<const DataSet3BodyC<Sample1T,Sample2T,Sample3T> &>(DataSetBaseC::Body()); }
    //: Access body.
    
  protected:
    Sample3T &Sample3()
      { return Body().Sample3(); }
    //: Access complete sample.
    
    UIntT Append(const typename Sample1T::ElementT &data1,const typename Sample2T::ElementT &data2,const typename Sample3T::ElementT &data3)
    { return Body().Append(data1,data2,data3); }
    //: Append a data entry.
    // returns its index.
    
    friend class DataSet3BodyC<Sample1T,Sample2T,Sample3T>;
  };
  
  
  template<class Sample1T,class Sample2T,class Sample3T>
  DataSet3BodyC<Sample1T,Sample2T,Sample3T>::DataSet3BodyC(const Sample1T & dat1,const Sample2T &dat2,const Sample3T &dat3)
    : DataSet2BodyC<Sample1T,Sample2T>(dat1,dat2),
      samp3(dat3)
  {}
  
  template<class Sample1T,class Sample2T,class Sample3T>
  DataSet3BodyC<Sample1T,Sample2T,Sample3T>::DataSet3BodyC(const Sample1T & dat1,const Sample2T & dat2,const Sample3T & dat3,const CollectionC<UIntT> &nindex)
    : DataSet2BodyC<Sample1T,Sample2T>(dat1,dat2,nindex),
      samp3(dat3)
  {}
  
  template<class Sample1T,class Sample2T,class Sample3T>
  UIntT DataSet3BodyC<Sample1T,Sample2T,Sample3T>::Append(const typename Sample1T::ElementT &data1,const typename Sample2T::ElementT &data2,const typename Sample3T::ElementT &data3) {
    UIntT no1 = samp1.Append(data1);
    UIntT no2 = samp2.Append(data2);
    UIntT no3 = samp3.Append(data3);
    RavlAssert(no1==no2 && no1==no3);
    return no1;
  }
  

}

#endif

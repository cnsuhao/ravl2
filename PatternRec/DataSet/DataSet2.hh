// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDATASET2_HEADER
#define RAVLDATASET2_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DataSet1.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  template<class Data1T,class Data2T> class DataSet2C;
  
  //! userlevel=Develop
  //: Data set 
  
  template <class Data1T,class Data2T> 
  class DataSet2BodyC 
    : public DataSet1BodyC<Data1T>
  {
  public:
    DataSet2BodyC(const SampleC<Data1T> & samp1,const SampleC<Data2T> & samp2);
    //: Create a dataset from a sample
    
    DataSet2BodyC(const SampleC<Data1T> & samp1,const SampleC<Data2T> & samp2,const CollectionC<UIntT> &nindex);
    //: Create a dataset from a sample and an index.
    
    DataSet2C<Data1T,Data2T> Shuffle() const;
    //: Create a new data set with a random order.
    
    SampleC<Data2T> &Sample2()
      { return samp2; }
    //: Access complete sample.
    
  private:
    SampleC<Data2T> samp2;
    //: the actual data
  };

  //! userlevel=Normal
  //: Data set 
  
  template<class Data1T,class Data2T>
  class DataSet2C
    : public DataSet1C<Data1T>
  {
  public:
    DataSet2C(const SampleC<Data1T> & dat1,const SampleC<Data2T> & dat2)
      : DataSet1C<Data1T>(*new DataSet2BodyC<Data1T,Data2T>(dat1,dat2))
      {}
    //: Create a dataset from a sample
    
  protected:
    DataSet2C(const SampleC<Data1T> & dat1,const SampleC<Data2T> & dat2,const CollectionC<UIntT> &nindex)
      : DataSetBaseC(*new DataSet2BodyC<Data1T,Data2T>(dat1,dat2,nindex))
      {}
    //: Create a dataset from a sample and an index.
    
    DataSet2C(DataSet2BodyC<Data1T,Data2T> &bod)
      : DataSetBaseC(bod)
      {}
    //: Body constructor.
    
    DataSet2BodyC<Data1T,Data2T> &Body()
      { return static_cast<DataSet2BodyC<Data1T,Data2T> &>(DataSetBaseC::Body()); }
    //: Access body.

    const DataSet2BodyC<Data1T,Data2T> &Body() const
      { return static_cast<const DataSet2BodyC<Data1T,Data2T> &>(DataSetBaseC::Body()); }
    //: Access body.
    
  public:
    SampleC<Data2T> &Sample2()
      { return Body().Sample2(); }
    //: Access complete sample.
    
    DataSet2C<Data1T,Data2T> Shuffle() const
      { return Body().Shuffle(); }
    //: Shuffle the samples in the dataset
    
    friend class DataSet2BodyC<Data1T,Data2T>;
  };
  

  template<class Data1T,class Data2T>
  DataSet2BodyC<Data1T,Data2T>::DataSet2BodyC(const SampleC<Data1T> & dat1,const SampleC<Data2T> &dat2)
    : DataSet1BodyC<Data1T>(dat1),
      samp2(dat2)
  {}

  template<class Data1T,class Data2T>
  DataSet2BodyC<Data1T,Data2T>::DataSet2BodyC(const SampleC<Data1T> & dat1,const SampleC<Data2T> & dat2,const CollectionC<UIntT> &nindex)
    : DataSet1BodyC<Data1T>(dat1,nindex),
      samp2(sp)
  {}
  
  template<class Data1T,class Data2T>
  DataSet2C<Data1T,Data2T> DataSet2BodyC<Data1T,Data2T>::Shuffle() const {
    return DataSet2C<Data1T,Data2T>(samp1,samp2,index.Shuffle());
  }
  

}

#endif

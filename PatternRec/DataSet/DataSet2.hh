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
  template<class Sample1T,class Sample2T> class DataSet2C;
  
  //! userlevel=Develop
  //: Data set 
  
  template <class Sample1T,class Sample2T> 
  class DataSet2BodyC 
    : public DataSet1BodyC<Sample1T>
  {
  public:
    DataSet2BodyC(const Sample1T & samp1,const Sample2T & samp2);
    //: Create a dataset from a sample
    
    DataSet2BodyC(const Sample1T & samp1,const Sample2T & samp2,const CollectionC<UIntT> &nindex);
    //: Create a dataset from a sample and an index.
    
    DataSet2C<Sample1T,Sample2T> Shuffle() const;
    //: Create a new data set with a random order.
    
    Sample2T &Sample2()
      { return samp2; }
    //: Access complete sample.
    
  private:
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
    DataSet2C(const Sample1T & dat1,const Sample2T & dat2)
      : DataSet1C<Sample1T>(*new DataSet2BodyC<Sample1T,Sample2T>(dat1,dat2))
      {}
    //: Create a dataset from a sample
    
  protected:
    DataSet2C(const Sample1T & dat1,const Sample2T & dat2,const CollectionC<UIntT> &nindex)
      : DataSetBaseC(*new DataSet2BodyC<Sample1T,Sample2T>(dat1,dat2,nindex))
      {}
    //: Create a dataset from a sample and an index.
    
    DataSet2C(DataSet2BodyC<Sample1T,Sample2T> &bod)
      : DataSetBaseC(bod)
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
    
    DataSet2C<Sample1T,Sample2T> Shuffle() const
      { return Body().Shuffle(); }
    //: Shuffle the samples in the dataset
    
    friend class DataSet2BodyC<Sample1T,Sample2T>;
  };
  

  template<class Sample1T,class Sample2T>
  DataSet2BodyC<Sample1T,Sample2T>::DataSet2BodyC(const Sample1T & dat1,const Sample2T &dat2)
    : DataSet1BodyC<Sample1T>(dat1),
      samp2(dat2)
  {}
  
  template<class Sample1T,class Sample2T>
  DataSet2BodyC<Sample1T,Sample2T>::DataSet2BodyC(const Sample1T & dat1,const Sample2T & dat2,const CollectionC<UIntT> &nindex)
    : DataSet1BodyC<Sample1T>(dat1,nindex),
      samp2(sp)
  {}
  
  template<class Sample1T,class Sample2T>
  DataSet2C<Sample1T,Sample2T> DataSet2BodyC<Sample1T,Sample2T>::Shuffle() const {
    return DataSet2C<Sample1T,Sample2T>(samp1,samp2,index.Shuffle());
  }
  

}

#endif

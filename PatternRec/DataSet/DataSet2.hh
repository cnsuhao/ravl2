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
#include "Ravl/DArray1dIter2.hh"

namespace RavlN {
  template<class Sample1T,class Sample2T> class DataSet2C;
  
  //! userlevel=Develop
  //: Data set 
  
  template <class Sample1T,class Sample2T> 
  class DataSet2BodyC 
    : public DataSet1BodyC<Sample1T>
  {
  public:
    typedef typename Sample2T::ElementT Element2T;
    
    DataSet2BodyC(UIntT sizeEstimate)
      : DataSet1BodyC<Sample1T>(sizeEstimate),
	samp2(sizeEstimate)
    {}
    //: Constructor.
    
    DataSet2BodyC(const Sample1T & samp1,
		  const Sample2T & samp2);
    //: Create a dataset from a sample

    UIntT Append(const Element1T &data1,
		 const Element2T &data2);
    //: Append a data entry.
    // returns its index.
    
    DataSet2C<Sample1T,Sample2T> ExtractSample(RealT proportion);
    //: Extract a sample.
    // The elements are removed from this set. NB. The order
    // of this dataset is NOT preserved.
    
    Sample2T &Sample2()
    { return samp2; }
    //: Access complete sample.
    
    const Sample2T &Sample2() const
    { return samp2; }
    //: Access complete sample.
    
    virtual void Shuffle();
    //: Shuffle the order of the dataset.
    
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
    typedef typename Sample2T::ElementT Element2T;
    
    DataSet2C()
    {}
    //: Default constructor.

    DataSet2C(UIntT sizeEstimate)
      : DataSet1C<Sample1T>(*new DataSet2BodyC<Sample1T,Sample2T>(sizeEstimate))
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
    
    //DataSet2C<Sample1T,Sample2T> Shuffle() const
    //{ return Body().Shuffle(); }
    //: Shuffle the samples in the dataset
    
    UIntT Append(const Element1T &data1,const Element2T &data2)
    { return Body().Append(data1,data2); }
    //: Append a data entry.
    // returns its index.
    
    DataSet2C<Sample1T,Sample2T> ExtractSample(RealT proportion)
    { return Body().ExtractSample(proportion); }
    //: Extract a sample.
    // The elements are removed from this set. NB. The order
    // of this dataset is NOT preserved.
    
    friend class DataSet2BodyC<Sample1T,Sample2T>;
  };

  template<class Sample1T,class Sample2T>
  ostream &operator<<(ostream &s,const DataSet2C<Sample1T,Sample2T> &dat) {
    s << dat.Sample1() << '\n' << dat.Sample2();
    return s;
  }
  //: Output to stream.
  
  template<class Sample1T,class Sample2T>
  istream &operator>>(istream &s,DataSet2C<Sample1T,Sample2T> &dat) {
    Sample1T tmp1;
    Sample2T tmp2;
    s >> tmp1 >> tmp2;
    dat = DataSet2C<Sample1T,Sample2T>(tmp1,tmp2);
    return s;
  }
  //: Read from stream.
  
  template<class Sample1T,class Sample2T>
  BinOStreamC &operator<<(BinOStreamC &s,const DataSet2C<Sample1T,Sample2T> &dat ) {
    s << dat.Sample1() << dat.Sample2();
    return s;
  }
  //: Output to a binary stream.
  
  template<class Sample1T,class Sample2T>
  BinIStreamC &operator>>(BinIStreamC &s,DataSet2C<Sample1T,Sample2T> &dat) {
    Sample1T tmp1;
    Sample2T tmp2;
    s >> tmp1 >> tmp2;
    dat = DataSet2C<Sample1T,Sample2T>(tmp1,tmp2);
    return s;
  }
  //: Read from a binary stream.
  
  
  template<class Sample1T,class Sample2T>
  DataSet2BodyC<Sample1T,Sample2T>::DataSet2BodyC(const Sample1T & dat1,const Sample2T &dat2)
    : DataSet1BodyC<Sample1T>(dat1),
      samp2(dat2)
  {}
  
  template<class Sample1T,class Sample2T>
  UIntT DataSet2BodyC<Sample1T,Sample2T>::Append(const Element1T &data1,const Element2T &data2) {
    UIntT no1 = samp1.Append(data1);
    UIntT no2 = samp2.Append(data2);
    RavlAssert(no1==no2);
    return no1;
  }

  template<class Sample1T,class Sample2T>
  DataSet2C<Sample1T,Sample2T> DataSet2BodyC<Sample1T,Sample2T>::ExtractSample(RealT proportion) {
    RavlAssert(proportion >= 0 && proportion <= 1);
    UIntT size = Size();
    UIntT entries = (UIntT) (proportion * (RealT) size);
    DataSet2C<Sample1T,Sample2T> ret(size);
    for(;entries > 0;entries--) {
      UIntT entry = RandomInt() % size;
      ret.Append(samp1.PickElement(entry),samp2.PickElement(entry));
      size--;
    }
    return ret;
  }
  
  template<class Sample1T,class Sample2T>
  void DataSet2BodyC<Sample1T,Sample2T>::Shuffle() {
    UIntT size = Size();
    for(DArray1dIter2C<Element1T,Element2T> it(Sample1().DArray(),Sample2().DArray());it;it++) {
      UIntT entry = RandomInt() % size;
      Swap(it.Data1(),samp1.Nth(entry));
      Swap(it.Data2(),samp2.Nth(entry));
    }
  }

}

#endif

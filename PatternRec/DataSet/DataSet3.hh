// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASET3_HEADER
#define RAVL_DATASET3_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/DataSet3.hh"

#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/Vector.hh"
#include "Ravl/DArray1dIter3.hh"

namespace RavlN {
  template<class Sample1T,class Sample2T,class Sample3T> class DataSet3C;
  
  //! userlevel=Develop
  //: Data set 
  
  template <class Sample1T,class Sample2T,class Sample3T> 
  class DataSet3BodyC 
    : public DataSet2BodyC<Sample1T,Sample2T>
  {
  public:
    typedef typename Sample1T::ElementT Element1T;
    typedef typename Sample2T::ElementT Element2T;
    typedef typename Sample3T::ElementT Element3T;
    
    DataSet3BodyC(UIntT sizeEstimate)
      : DataSet2BodyC<Sample1T,Sample2T>(sizeEstimate),
	samp3(sizeEstimate)
    {}
    //: Default constructor.
    
    DataSet3BodyC(const Sample1T & samp1,
		  const Sample2T & samp2,
		  const Sample3T & samp3);
    //: Create a dataset from a sample
    
    UIntT Append(const Element1T &data1,
		 const Element2T &data2,
		 const Element3T &data3);
    //: Append a data entry.
    // returns its index.
    
    Sample3T &Sample3()
    { return samp3; }
    //: Access complete sample.
    
    const Sample3T &Sample3() const
    { return samp3; }
    //: Access complete sample.

    DataSet3C<Sample1T,Sample2T,Sample3T> ExtractSample(RealT proportion);
    //: Extract a sample.
    // The elements are removed from this set. NB. The order
    // of this dataset is NOT preserved.    
    
    virtual void Shuffle();
    //: Shuffle the order of the dataset.
    
  protected:
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
    typedef typename Sample1T::ElementT Element1T;
    typedef typename Sample2T::ElementT Element2T;
    typedef typename Sample3T::ElementT Element3T;
    
    DataSet3C()
    {}
    //: Default constructor.
    
    DataSet3C(UIntT sizeEstimate)
      : DataSet2C<Sample1T,Sample2T>(*new DataSet3BodyC<Sample1T,Sample2T,Sample3T>(sizeEstimate))
    {}
    //: Constructor.
    
    DataSet3C(const Sample1T & dat1,const Sample2T & dat2,const Sample3T & dat3)
      : DataSet2C<Sample1T,Sample2T>(*new DataSet3BodyC<Sample1T,Sample2T,Sample3T>(dat1,dat2,dat3))
      {}
    //: Create a dataset from a sample
    
  protected:    
    DataSet3C(DataSet3BodyC<Sample1T,Sample2T,Sample3T> &bod)
      : DataSet2C<Sample1T,Sample2T>(bod)
    {}
    //: Body constructor.
    
    DataSet3BodyC<Sample1T,Sample2T,Sample3T> &Body()
    { return static_cast<DataSet3BodyC<Sample1T,Sample2T,Sample3T> &>(DataSetBaseC::Body()); }
    //: Access body.

    const DataSet3BodyC<Sample1T,Sample2T,Sample3T> &Body() const
    { return static_cast<const DataSet3BodyC<Sample1T,Sample2T,Sample3T> &>(DataSetBaseC::Body()); }
    //: Access body.
    
  public:
    Sample3T &Sample3()
    { return Body().Sample3(); }
    //: Access complete sample.
    
    const Sample3T &Sample3() const
    { return Body().Sample3(); }
    //: Access complete sample.
    
    UIntT Append(const Element1T &data1,const Element2T &data2,const Element3T &data3)
    { return Body().Append(data1,data2,data3); }
    //: Append a data entry.
    // returns its index.
    
    DataSet3C<Sample1T,Sample2T,Sample3T> ExtractSample(RealT proportion)
    { return Body().ExtractSample(proportion); }
    //: Extract a sample.
    // The elements are removed from this set. NB. The order
    // of this dataset is NOT preserved.
    
    friend class DataSet3BodyC<Sample1T,Sample2T,Sample3T>;
  };
  
  template<class Sample1T,class Sample2T,class Sample3T>
  ostream &operator<<(ostream &s,const DataSet3C<Sample1T,Sample2T,Sample3T> &dat) {
    s << dat.Sample1() << '\n' << dat.Sample2() << '\n' << dat.Sample3();
    return s;
  }
  //: Output to stream.
  
  template<class Sample1T,class Sample2T,class Sample3T>
  istream &operator>>(istream &s,DataSet3C<Sample1T,Sample2T,Sample3T> &dat) {
    Sample1T tmp1;
    Sample2T tmp2;
    Sample2T tmp3;
    s >> tmp1 >> tmp2 >> tmp3;
    dat = DataSet3C<Sample1T,Sample2T,Sample3T>(tmp1,tmp2,tmp3);
    return s;
  }
  //: Read from stream.
  
  template<class Sample1T,class Sample2T,class Sample3T>
  BinOStreamC &operator<<(BinOStreamC &s,const DataSet3C<Sample1T,Sample2T,Sample3T> &dat ) {
    s << dat.Sample1() << dat.Sample2() << dat.Sample3();
    return s;
  }
  //: Output to a binary stream.
  
  template<class Sample1T,class Sample2T,class Sample3T>
  BinIStreamC &operator>>(BinIStreamC &s,DataSet3C<Sample1T,Sample2T,Sample3T> &dat) {
    Sample1T tmp1;
    Sample2T tmp2;
    Sample3T tmp3;
    s >> tmp1 >> tmp2 >> tmp3;
    dat = DataSet3C<Sample1T,Sample2T,Sample3T>(tmp1,tmp2,tmp3);
    return s;
  }
  //: Read from a binary stream.

  
  template<class Sample1T,class Sample2T,class Sample3T>
  DataSet3BodyC<Sample1T,Sample2T,Sample3T>::DataSet3BodyC(const Sample1T & dat1,const Sample2T &dat2,const Sample3T &dat3)
    : DataSet2BodyC<Sample1T,Sample2T>(dat1,dat2),
      samp3(dat3)
  {}
  
  template<class Sample1T,class Sample2T,class Sample3T>
  UIntT DataSet3BodyC<Sample1T,Sample2T,Sample3T>::Append(const Element1T &data1,const Element2T &data2,const Element3T &data3) {
    UIntT no1 = samp1.Append(data1);
    UIntT no2 = samp2.Append(data2);
    UIntT no3 = samp3.Append(data3);
    RavlAssert(no1==no2 && no1==no3);
    return no1;
  }
  
  template<class Sample1T,class Sample2T,class Sample3T>
  DataSet3C<Sample1T,Sample2T,Sample3T> DataSet3BodyC<Sample1T,Sample2T,Sample3T>::ExtractSample(RealT proportion) {
    RavlAssert(proportion >= 0 && proportion <= 1);
    UIntT size = Size();
    UIntT entries = (UIntT) (proportion * (RealT) size);
    DataSet3C<Sample1T,Sample2T,Sample3T> ret(size);
    for(;entries > 0;entries--) {
      UIntT entry = RandomInt() % size;
      ret.Append(samp1.PickElement(entry),samp2.PickElement(entry),samp3.PickElement(entry));
      size--;
    }
    return ret;
  }
  
  template<class Sample1T,class Sample2T,class Sample3T>
  void DataSet3BodyC<Sample1T,Sample2T,Sample3T>::Shuffle() {
    UIntT size = Size();
    for(DArray1dIter3C<Element1T,Element2T,Element3T> it(Sample1().DArray(),Sample2().DArray(),Sample3().DArray());
	it;it++) {
      UIntT entry = RandomInt() % size;
      Swap(it.Data1(),samp1.Nth(entry));
      Swap(it.Data2(),samp2.Nth(entry));
      Swap(it.Data3(),samp3.Nth(entry));
    }
  }


}

#endif

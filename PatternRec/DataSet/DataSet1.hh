// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDATASET1_HEADER
#define RAVLDATASET1_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include"Ravl/PatternRec/Sample.hh"
#include"Ravl/Vector.hh"

namespace RavlN {
  template<class DataT> class DataSet1C;
  
  //! userlevel=Develop
  //: Data set 
  
  template <class DataT> 
  class DataSet1BodyC 
    : public RCBodyC
  {
    
  public:
    DataSet1BodyC(const SampleC<DataT> & samp);
    //: Create a dataset from a sample
    
    DataSet1BodyC(const SampleC<DataT> & samp,const CollectionC<UIntT> &nindex);
    //: Create a dataset from a sample and an index.
    
    DataSet1C<DataT> Shuffle() const;
    //: Shuffle the data in the dataset

    SampleC<DataT> &Sample1()
      { return samp1; }
    //: Access complete sample.
    
  private:
    SampleC<DataT> samp1;
    //: the actual data
    
    CollectionC<UIntT> index;
    //: the index into the data

  };

  //! userlevel=Normal
  //: Data set 
  
  template<class DataT>
  class DataSet1C
    : public RCHandleC<DataSet1BodyC<DataT> >
  {
  public:
    DataSet1C(const SampleC<DataT> & dat)
      : RCHandleC<DataSet1BodyC<DataT> >(*new DataSet1BodyC<DataT>(dat))
      {}
    //: Create a dataset from a sample
    
    DataSet1C<DataT> Shuffle() const
      { return Body().Shuffle(); }
    //: Shuffle the samples in the dataset

  protected:
    DataSet1C(const SampleC<DataT> & dat,const CollectionC<UIntT> &nindex)
      : RCHandleC<DataSet1BodyC<DataT> >(*new DataSet1BodyC<DataT>(dat,nindex))
      {}
    //: Create a dataset from a sample and an index.
    
    DataSet1C(DataSet1BodyC<DataT> &bod)
      : RCHandleC<DataSet1BodyC<DataT> >(bod)
      { }
    //: Body constructor.
    
    DataSet1BodyC<DataT> &Body()
      { return RCHandleC<DataSet1BodyC<DataT> >::Body(); }
    //: Access body.

    const DataSet1BodyC<DataT> &Body() const
      { return RCHandleC<DataSet1BodyC<DataT> >::Body(); }
    //: Access body.
    
  public:
    SampleC<DataT> &Sample1()
      { return Body().Sample1(); }
    //: Access complete sample.
    
    friend class DataSet1BodyC<DataT>;
  };
  

  template<class DataT>
  DataSet1BodyC<DataT>::DataSet1BodyC(const SampleC<DataT> & sp)
    : samp1(sp), 
      index(sp.Size())
  {
    // Initialise index.
    
    for(UIntT i=0;i<sp.Size();i++)
      index.Insert(i);
  }
  
  template<class DataT>
  DataSet1C<DataT> DataSet1BodyC<DataT>::Shuffle() const {
    return DataSet1C<DataT>(samp,index.Shuffle());
  }


}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDATASET1_HEADER
#define RAVLDATASET1_HEADER 1
//! rcsid="$Id$"

#include"Ravl/PatternRec/Sample.hh"
#include"Ravl/Vector.hh"

namespace RavlN {
  
  
  template <class DataT> 
  class DataSet1BodyC 
    : public RCBodyC
  {
    
  public:
    DataSet1BodyC(const SampleC<DataT> & samp);
    //: Create a dataset from a sample
     

    DataSet1BodyC<DataT> Shuffle() const;
    //: Shuffle the data in the dataset


  private:
    SampleC<DataT> samp;
    //: the actual data

    CollectionC<UIntT>index;
    //: the index into the data

  };

  
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
    
  };
  

  template<class DataT>
  DataSet1BodyC<DataT>::DataSet1BodyC(const SampleC<DataT> & sp)
    : samp(sp), index(sp.Size())
  {
    // initialise array
 
    for(UIntT i=0;i<sp.Size();i++) {
      index.Insert(i);
    }
  }
  
  template<class DataT>
  DataSet1BodyC<DataT>::Shuffle() const
  {
    
    
  }


}

#endif

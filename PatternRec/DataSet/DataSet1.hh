#ifndef RAVLDATASET1_HEADER
#define RAVLDATASET1_HEADER 1

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

#ifndef RAVLSAMPLELABEL_HEADER
#define RAVLSAMPLELABEL_HEADER 1

#include"Ravl/PatternRec/Sample.hh"
#include"Ravl/Vector.hh"


namespace RavlN {
  
  
  class SampleLabelC 
    : public SampleC<UIntT>
  {
    
  public:
    SampleLabelC(SizeT maxSize=10)
      : SampleC<UIntT>(maxSize)
      {}
    //: Create a sample of data with a maximum size
    
    SampleLabelC(const SArray1dC<UIntT> & dat)
      : SampleC<UIntT>(dat)
      {}
    //: Create a sample of data from an array
    
    
    
  }; // end of class SampleVectorC 
  
}

#endif

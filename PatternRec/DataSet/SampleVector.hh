#ifndef RAVLSAMPLEVECTOR_HEADER
#define RAVLSAMPLEVECTOR_HEADER 1

#include"Ravl/PatternRec/Sample.hh"
#include"Ravl/Vector.hh"


namespace RavlN {
  
  
  class SampleVectorC 
    : public SampleC<VectorC>
  {
    
  public:
    SampleVectorC(SizeT maxSize=10)
      : SampleC<VectorC>(maxSize)
      {}
    //: Create a sample of data with a maximum size
    
    SampleVectorC(const SArray1dC<VectorC> & dat)
      : SampleC<VectorC>(dat)
      {}
    //: Create a sample of data from an array
    
    
    
  }; // end of class SampleVectorC 
  
}

#endif

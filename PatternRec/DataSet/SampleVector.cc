//! rcsid="$Id$"

#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/SArr1Iter.hh"

namespace RavlN {

  //: Find the mean vector.
  
  VectorC SampleVectorC::Mean() {
    SArray1dIterC<VectorC> it(Array());
    if(!it)
      return VectorC();
    VectorC total = *it;
    for(;it;it++)
      total += *it;
    return total/ ((RealT) Size());
  }
  
}


#ifndef RAVLMATHMEANND_HEADER
#define RAVLMATHMEANND_HEADER 1
/////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Radek Marik"
//! date="26.05.1994"
//! docentry="Ravl.Math.Statistics.N-D"

#include "Ravl/MeanNd.hh"

namespace RavlN {
  
  //: Mean in N-D space
  // This class computes the mean of a set of vectors.
  
  class MeanCovarianceNdC 
  : protected MeanNdC
  {
  public:
    MeanCovarianceNdC(SizeT dim = 0)
      : MeanNdC(dim)
      {}
    //: Constructor.
    
    
  };
}

#endif

//! rcsid="$Id$"

#include "Ravl/MeanNd.hh"

namespace RavlN {
  
  //: Reset the counters.
  
  void MeanNdC::Reset() {
    n = 0;
    total.Fill(0);
  }

}

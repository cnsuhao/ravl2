#ifndef RAVL_SAMPLEIO_HEADERS
#define RAVL_SAMPLEIO_HEADERS 1
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/Sample.hh"

#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DArray1dIter.hh"

namespace RavlN {
  
  template<class DataT>
  bool LoadSample(const StringC &filename,SampleC<DataT> &sample,UIntT maxSamples = ((UIntT) -1),const StringC &format = "",bool verbose = false) {
    DPIPortC<DataT> ip;
    if(!OpenISequence(ip,filename,format,verbose))
      return false;
    while(maxSamples-- > 0) {
      DataT dat;
      if(!ip.Get(dat))
	break;
      sample.Append(dat);
    }
    return true;
  }
  //: Load sample from a file sequence 
  
  template<class DataT>
  bool SaveSample(const StringC &filename,const SampleC<DataT> &sample,const StringC &format = "",bool verbose = false) {
    DPOPortC<DataT> ip;
    if(!OpenOSequence(ip,filename,format,verbose))
      return false;
    for(DArray1dIterC<DataT> it(sample.DArray());it;it++) {
      if(!ip.Put(*it))
	return false;
    }
    return true;
  }
  //: Save sample to a file sequence 


}

#endif

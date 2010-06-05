// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SAMPLEIO_HEADERS
#define RAVL_SAMPLEIO_HEADERS 1
//! rcsid="$Id: SampleIO.hh 5240 2005-12-06 17:16:50Z plugger $"
//! author="Charles Galambos"
//! docentry="Ravl.API.Pattern Recognition.Data Set"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/SampleIO.hh"

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

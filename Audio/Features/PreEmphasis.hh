// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_PREEMPHASIS_HEADER
#define RAVLAUDIO_PREEMPHASIS_HEADER 1
//! userlevel=Normal
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlAudioFeatures

#include "Ravl/Audio/Types.hh"
#include "Ravl/DP/StreamOp.hh"
#include "Ravl/Types.hh"
#include "Ravl/SArray1dIter2.hh"

namespace RavlAudioN {
  
  //! userlevel=Develop
  //: PreEmphasis body.
  // Single tap fir filter, tap at n-1
  
  template<typename InT,typename OutT,typename FilterT = RealT>
  class PreEmphasisBodyC 
    : public DPIStreamOpBodyC<InT,OutT>
  {
  public:
    PreEmphasisBodyC(const DPIPortC<InT> &in,FilterT nAlpha = 0.97)
      : DPIStreamOpBodyC<InT,OutT>(in),
	alpha(nAlpha)
    { SetZero(last); }
    //: Constructor.
    
    PreEmphasisBodyC(FilterT nAlpha = 0.97)
      : alpha(nAlpha)
    { SetZero(last); }
    //: Constructor.
    
    virtual OutT Get() {
      OutT ret;
      if(!Get(ret))
	throw DataNotReadyC("Failed to get sample.");
      return ret;
    }
    //: Get next sample
    
    virtual bool Get(OutT &buff) {
      InT in;
      if(!input.Get(in))
	return false;
      FilterT val = static_cast<FilterT>(in);
      buff = static_cast<OutT>(val - last * alpha);
      last = val;
      return true;
    }
    //: Get next sample
    
    virtual IntT GetArray(SArray1dC<OutT> &data) {
      SArray1dC<InT> din(data.Size());
      IntT elems = input.GetArray(din);
      FilterT val;
      for(SArray1dIter2C<InT,OutT> it(din,data);it;it++) {
	val = static_cast<FilterT>(it.Data1());
	it.Data2() = static_cast<OutT>(val - last * alpha);
	last = val;
      }
      return elems;
    }
    //: Get array of samples.
    
  protected:
    FilterT alpha;
    FilterT last;
  };
  
  //! userlevel=Normal
  //: PreEmphasis.
  // Single tap fir filter, tap at n-1
  
  template<typename InT,typename OutT,typename FilterT = RealT>
  class PreEmphasisC 
    : public DPIStreamOpC<InT,OutT>
  {
  public:
    PreEmphasisC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    PreEmphasisC(FilterT alpha)
      : DPEntityC(*new PreEmphasisBodyC<InT,OutT,FilterT>(alpha))
    {}
    //: Constructor.
    
    
  };
  
}


#endif

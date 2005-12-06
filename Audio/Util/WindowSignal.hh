// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_WINDOW_HEADER
#define RAVLAUDIO_WINDOW_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.API.Audio.Feature Extraction"
//! rcsid="$Id$"
//! lib=RavlAudioUtil
//! file="Ravl/Audio/Util/WindowSignal.hh"

#include "Ravl/Audio/Types.hh"
#include "Ravl/DP/StreamOp.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/FixedQueue.hh"

namespace RavlAudioN {
  
  enum RAWindowSignalT { RAWNone,RAWRamp,  RAWHanning,  RAWHamming,RAWBlackman,RAWCustom};
  //: Windowing types.
  // RAWNone - No filtering applied. <br>
  
  //:-
  
  //! userlevel=Develop
  //: Base class for signal windowing..
  
  class WindowSignalBaseC {
  public:
    WindowSignalBaseC(RAWindowSignalT winType,UIntT size);
    //: Constructor.
    
    bool Generate(SArray1dC<RealT> &filter);
    //: Generate the filter.
    
    bool GenerateRamp(SArray1dC<RealT> &filter);
    //: Generate a saw tooth ramp, or 
    
    bool GenerateHanning(SArray1dC<RealT> &filter);
    //: Generate a hanning window.
    
    bool GenerateHamming(SArray1dC<RealT> &filter);
    //: Generate a hamming window.

    bool GenerateBlackman(SArray1dC<RealT> &filter);
    //: Generate a Blackman window.
    
  protected:
    RAWindowSignalT winType;
    UIntT winSize;
  };
  
  //! userlevel=Develop
  //: Window a signal.
  
  template<typename InT,typename OutT,typename FilterT = RealT>
  class WindowSignalBodyC
    : public DPIStreamOpBodyC<InT,SArray1dC<OutT> >,
      public WindowSignalBaseC
  {
  public:
    WindowSignalBodyC(RAWindowSignalT sigType,UIntT frameSize,UIntT frameSeperation)
      : WindowSignalBaseC(sigType,frameSize),
	frameSep(frameSeperation),
	blocks((frameSize / frameSeperation)+1)
    { Generate(filter); }
    //: Contructor.
    // sigType - Type of window to use. <br>
    // frameSize - Size of output frame in samples.<br>
    // frameSeperation - Seperation of successive frames in samples.<br>
    
    WindowSignalBodyC(const SArray1dC<RealT> &nfilter,UIntT frameSeperation)
      : WindowSignalBaseC(RAWCustom,nfilter.Size()),
	frameSep(frameSeperation),
	blocks((nfilter.Size() / frameSeperation)+1),
	filter(nfilter)
    {}
    //: Contructor.
    // nfilter - Filter to use. <br>
    // frameSeperation - Seperation of successive frames in samples.
    
    bool GetBlock(SArray1dC<InT> &blk) {
      UIntT n = this->input.GetArray(blk);
      while(n < blk.Size() && !this->input.IsGetEOS()) {
	SArray1dC<InT> tmp = blk.From(n);
	n += this->input.GetArray(tmp);
      }
      return n == blk.Size();
    }
    //: Get a block of data.
    
    virtual SArray1dC<OutT> Get()  {
      SArray1dC<OutT> ret;
      if(!Get(ret))
	throw DataNotReadyC("Failed to get windowed data. ");
      return ret;
    }
    //: Get next frame.

    virtual bool Get(SArray1dC<OutT> &buff) { 
      buff = SArray1dC<OutT>(filter.Size());
      if(blocks.IsEmpty()) { // First block ?
	SArray1dC<InT> tmp(filter.Size());
	if(!GetBlock(tmp))
	  return false;
	blocks.InsLast(tmp);
      } else {
	SArray1dC<InT> tmp(frameSep);
	if(!GetBlock(tmp))
	  return false;
	blocks.InsLast(tmp);
      }
      UIntT toGo = filter.Size();
      UIntT from = 0;
      UIntT len = 0;
      UIntT start = 0;
      for(FixedQueueRevIterC<SArray1dC<InT> > qit(blocks);toGo > 0;qit++) {
	if(qit->Size() > toGo) {
	  len = toGo;
	  from = 0;
	  start = qit->Size() - toGo;
	  toGo = 0;
	} else {
	  from = toGo - qit->Size();
	  len = qit->Size();
	  start = 0;
	  toGo = from;
	}
	for(SArray1dIter3C<FilterT,OutT,InT> it(filter.From(from,len),
						buff.From(from,len),
						qit->From(start));it;it++)
	  it.Data2() = (OutT) ((FilterT) it.Data1() * it.Data3());
      }
      if(blocks.Size() >= blocks.MaxSize())
	blocks.DelFirst();
      return true;
    }
    //: Get next frame.
    
    SArray1dC<FilterT> &Filter()
    { return filter; }
    //: Access filter.
    
    const SArray1dC<FilterT> &Filter() const
    { return filter; }
    //: Access filter.
    
  protected:
    UIntT frameSep;
    FixedQueueC<SArray1dC<InT> > blocks; 
    SArray1dC<FilterT> filter;
    bool symetric;
  };
  
  //! userlevel=Normal
  //: Window a signal.
  
  template<typename InT,typename OutT,typename FilterT = RealT>
  class WindowSignalC
    : public DPIStreamOpC<InT,SArray1dC<OutT> >
  {
  public:
    WindowSignalC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    WindowSignalC(RAWindowSignalT sigType,UIntT size,UIntT frameSeperation)
      : DPEntityC(*new WindowSignalBodyC<InT,OutT,FilterT>(sigType,size,frameSeperation))
    {}
    //: Constructor.
    // sigType - Type of window to use. <br>
    // frameSize - Size of output frame in samples.<br>
    // frameSeperation - Seperation of successive frames in samples.<br>
    
    WindowSignalC(const SArray1dC<FilterT> &filter,UIntT frameSeperation)
      : DPEntityC(*new WindowSignalBodyC<InT,OutT,FilterT>(filter,frameSeperation))
    {}
    //: Constructor.
    // nfilter - Filter to use. <br>
    // frameSeperation - Seperation of successive frames in samples.
    
  protected:
    WindowSignalBodyC<InT,OutT,FilterT> &Body()
    { return dynamic_cast<WindowSignalBodyC<InT,OutT,FilterT> &>(DPEntityC::Body()); }
    //: Access body.
    
    const WindowSignalBodyC<InT,OutT,FilterT> &Body() const
    { return dynamic_cast<WindowSignalBodyC<InT,OutT,FilterT> &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    SArray1dC<FilterT> &Filter()
    { return Body().Filter(); }
    //: Access filter.
    
    const SArray1dC<FilterT> &Filter() const
    { return Body().Filter(); }
    //: Access filter.
    
  };
}


#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_WINDOW_HEADER
#define RAVLAUDIO_WINDOW_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.Audio.Processing"
//! rcsid="$Id$"
//! lib=RavlAudioUtil

#include "Ravl/Audio/Types.hh"
#include "Ravl/DP/StreamOp.hh"
#include "Ravl/SArray1dIter3.hh"

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
    WindowSignalBodyC(RAWindowSignalT sigType,UIntT size)
      : WindowSignalBaseC(sigType,size)
    { Generate(filter); }
    //: Contructor.
    
    WindowSignalBodyC(const SArray1dC<RealT> &nfilter)
      : WindowSignalBaseC(RAWCustom,nfilter.Size()),
	filter(nfilter)
    {}
    //: Contructor.
    
    bool GetBlock(SArray1dC<InT> &blk) {
      UIntT n = input.GetArray(blk);
      while(n < blk.Size() && !input.IsGetEOS()) {
	SArray1dC<InT> tmp = blk.From(n);
	n += input.GetArray(tmp);
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
      UIntT half = filter.Size()/2;
      if(lastBlock.Size() == 0) { // First block ?
	lastBlock = SArray1dC<InT>(half);
	if(!GetBlock(lastBlock))
	  return false;
      }
      for(SArray1dIter3C<InT,FilterT,OutT> it(lastBlock,filter,buff);it;it++)
	it.Data3() = (OutT) ((FilterT) it.Data1() * it.Data2());
      SArray1dC<InT> blk(half); 
      if(!GetBlock(blk))
	return false;
      for(SArray1dIter3C<InT,FilterT,OutT> it(blk,filter.From(half),buff.From(half));it;it++)
	it.Data3() = (OutT) ((FilterT) it.Data1() * it.Data2());
      lastBlock = blk;
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
    SArray1dC<InT> lastBlock;
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
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    WindowSignalC(RAWindowSignalT sigType,UIntT size)
      : DPEntityC(*new WindowSignalBodyC<InT,OutT,FilterT>(sigType,size))
    {}
    //: Constructor.
    
    WindowSignalC(const SArray1dC<FilterT> &filter)
      : DPEntityC(*new WindowSignalBodyC<InT,OutT,FilterT>(filter))
    {}
    //: Constructor.
    
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

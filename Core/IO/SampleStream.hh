// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SAMPLESTREAM_HEADER
#define RAVL_SAMPLESTREAM_HEADER  1
//! rcsid="$Id$"
//! docentry="Ravl.Core.Data Processing"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="3/12/2003"
//! userlevel=Normal

#include "Ravl/DP/SPort.hh"
#include "Ravl/DP/StreamOp.hh"
#include "Ravl/DP/SPortAttach.hh"

namespace RavlN {
  
  template<class DataT>
  class DPISampleStreamBodyC
    : public DPIStreamOpBodyC<DataT,DataT>,
      public DPSeekCtrlBodyC
  {
  public:
    DPISampleStreamBodyC()
      : startFrame(0),
	sampleRate(1),
	pos(0)
    {}
    //: Constructor

    DPISampleStreamBodyC(const DPIPortC<DataT> &nin,Int64T nSampleRate,Int64T nStartFrame = 0)
      : DPIStreamOpBodyC<DataT,DataT>(nin),
	sinput(SPort(nin)),
	startFrame(nStartFrame),
	sampleRate(nSampleRate),
	pos(0)
    {}
    //: Constructor

    DPISampleStreamBodyC(Int64T nSampleRate,Int64T nStartFrame = 0)
      : startFrame(nStartFrame),
	sampleRate(nSampleRate),
	pos(0)
    {}
    //: Constructor
    
    virtual bool Seek(UIntT off) {
      Int64T newOff = startFrame + (Int64T) off * sampleRate;
      return sinput.Seek64(newOff);
    }
    //: Seek to position in stream.
    
    inline bool DSeek(IntT off) 
    { return sinput.DSeek(off * sampleRate); }
    //: Delta seek
    
    virtual UIntT Tell() const 
    { return (pos - startFrame) / sampleRate; }
    //: Get current position in stream.
    
    virtual UIntT Size() const 
    { return (sinput.Size64() - startFrame) / sampleRate; }
    //: Get size of stream
    
    virtual UIntT Start() const 
    { return (sinput.Start64() - startFrame) / sampleRate; }
    //: First frame.
    
    virtual bool Seek64(Int64T off) {
      Int64T newOff = startFrame + off * sampleRate;
      return sinput.Seek64(newOff);
    }
    //: Seek to position in stream.
    
    inline bool DSeek64(Int64T off) 
    { return sinput.DSeek(off * sampleRate); }
    //: Delta seek
    
    virtual Int64T Tell64() const 
    { return (pos - startFrame) / sampleRate; }
    //: Get current position in stream.
    
    virtual Int64T Size64() const 
    { return (sinput.Size64() - startFrame) / sampleRate; }
    //: Get size of stream
    
    virtual Int64T Start64() const 
    { return (sinput.Start64() - startFrame) / sampleRate; }
    //: First frame.
    
    virtual DataT Get()  {
      DataT ret = sinput.Get();
      if(!sinput.DSeek(sampleRate-1)) {
	if(sampleRate < 0)
	  return ret;
	for(Int64T i = 1;i < sampleRate;i++)
	  input.Discard();
	pos += sampleRate;
      } else
	pos = sinput.Tell64();
      return ret;
    }
    //: Get next piece of data.
    
    virtual bool Get(DataT &buff) { 
      if(!sinput.Get(buff))
	return false;
      if(!sinput.DSeek(sampleRate-1)) {
	if(sampleRate < 0)
	  return false;
	for(Int64T i = 1;i < sampleRate;i++)
	  input.Discard();
	pos += sampleRate;
      } else
	pos = sinput.Tell64();
      return true;
    }
    //: Try and get next piece of data.
    
    void Input(const DPIPortC<DataT> &ins) { 
      DPIStreamOpBodyC<DataT,DataT>::Input(ins);
      sinput = SPort(ins);
    }
    // Setup input port.

    Int64T StartFrame() const
    { return startFrame; }
    //: Access start frame.
    
    Int64T SampleRate() const
    { return sampleRate; }
    //: Sample rate.
    
    void StartFrame(Int64T nStartFrame)
    { startFrame = nStartFrame; }
    //: Access start frame.
    
    void SampleRate(Int64T nSampleRate)
    { sampleRate = nSampleRate; }
    //: Sample rate.
    
  protected:
    DPISPortC<DataT> sinput;
    Int64T startFrame;
    Int64T sampleRate;
    StreamPosT pos;
 };

  template<class DataT>
  class DPISampleStreamC
    : public DPIStreamOpC<DataT,DataT>,
      public DPSeekCtrlC
  {
  public:
    DPISampleStreamC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DPISampleStreamC(const DPIPortC<DataT> &nin,Int64T nSampleRate,Int64T nStartFrame = 0)
      : DPEntityC(*new DPISampleStreamBodyC<DataT>(nin,nSampleRate,nStartFrame))
    {}
    //: Constructor.
    
    DPISampleStreamC(Int64T nSampleRate,Int64T nStartFrame = 0)
      : DPEntityC(*new DPISampleStreamBodyC<DataT>(nSampleRate,nStartFrame))
    {}
    //: Constructor.
    
  protected:
    DPISampleStreamBodyC<DataT> &Body()
    { return dynamic_cast<DPISampleStreamBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
    const DPISampleStreamBodyC<DataT> &Body() const
    { return dynamic_cast<const DPISampleStreamBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    
    DPISampleStreamC<DataT> &operator=(const DPISampleStreamC<DataT> &other)
    { DPEntityC::operator=(other); return *this; }
    //: Assigment 
    
    Int64T StartFrame() const
    { return Body().StartFrame(); }
    //: Access start frame.
    
    Int64T SampleRate() const
    { return Body().SampleRate(); }
    //: Sample rate.
    
    void StartFrame(Int64T nStartFrame)
    { Body().StartFrame(nStartFrame); }
    //: Access start frame.
    
    void SampleRate(Int64T nSampleRate)
    {  Body().SampleRate(nSampleRate); }
    //: Sample rate.
    
    
  };
  
}



#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_AUDIOIO_HEADER
#define RAVLAUDIO_AUDIOIO_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAudioUtil
//! author="Charles Galambos"
//! docentry="Ravl.Audio.IO"

#include "Ravl/DP/Port.hh"
#include "Ravl/Audio/Types.hh"
#include "Ravl/String.hh"
#include "Ravl/TypeName.hh"

namespace RavlAudioN {
  using namespace RavlN;
  
  //: Audio IO base class.
  
  class AudioIOBaseC {
  public:
    AudioIOBaseC();
    //: Default constructor.
    
    AudioIOBaseC(const StringC &fn,int channel,bool forInput,const type_info &type);
    //: Constructor.
    
    virtual ~AudioIOBaseC();
    //: Destructor.
    
    bool IOpen(const StringC &fn,int channel,const type_info &dtype);
    //: Open audio device.
    
    bool OOpen(const StringC &fn,int channel,const type_info &dtype);
    //: Open audio device.
    
    virtual bool SetSampleBits(IntT bits);
    //: Set number of bits to use in samples.
    // returns actual number of bits.
    
    virtual bool SetSampleRate(IntT rate);
    //: Set frequency of samples
    // Returns actual frequency.
    
    virtual bool GetSampleBits(IntT &bits);
    //: Get number of bits to use in samples.
    // returns actual number of bits.
    
    virtual bool GetSampleRate(IntT &rate);
    //: Get frequency of samples
    // Returns actual frequency.
    
    bool Read(void *buf,IntT &len);
    //: Read bytes from audio stream.
    // Returns false if error occured.
    
    bool Write(const void *buf,IntT len);
    //: Write bytes to audio stream.
    // Returns false if error occured.
    
    bool IsOpen() const
    { return false; }
    //: Is stream open ?
    
    bool HandleGetAttr(const StringC &attrName,StringC &attrValue);
    //: Handle get attrib.
    
    bool HandleSetAttr(const StringC &attrName,const StringC &attrValue);
    //: Handle Set attrib.
    
    bool HandleGetAttr(const StringC &attrName,IntT &attrValue);
    //: Get a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as sample rate.
    
    bool HandleSetAttr(const StringC &attrName,const IntT &attrValue);
    //: Set a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as sample rate.
    
    bool HandleGetAttrList(DListC<StringC> &list) const;
    //: Get list of attributes available.
    // This method will ADD all available attribute names to 'list'.
    
  };
  
  //! userlevel=Develop
  //: Audio input port.
  
  template<typename DataT,typename IOClassT> 
  class DPIAudioBodyC
    : public IOClassT,
      public DPIPortBodyC<DataT>
  {
  public:
    DPIAudioBodyC()
    {}
    //: Default constructor.
    
    DPIAudioBodyC(const StringC &dev,int channel)
      : IOClassT(dev,channel,true,typeid(DataT))
    {}
    //: Default constructor.
    
    virtual bool IsGetReady() const
    { return IsOpen(); }
    //: Is some data ready ?
    // true = yes.
    
    virtual bool IsGetEOS() const
    { return !IsOpen(); }
    //: Is data available ?
    
    DataT Get() {
      DataT ret;
      IntT size = sizeof(DataT);
      if(!Read((void *) &ret,size))
	throw DataNotReadyC("Failed to read sample.");
      if(size != sizeof(DataT))
	throw DataNotReadyC("Failed to read sample.");
      return ret;
    }
    //: Get sample from stream.
    
    bool Get(DataT &buff)  { 
      IntT size = sizeof(DataT);
      if(!Read((void *) &buff,size))
	return false;
      return size == sizeof(DataT);
    }
    //: Get sample from stream.
    
    IntT GetArray(SArray1dC<DataT> &data) {
      IntT size = data.Size() * sizeof(DataT);
      if(!Read(&(data[0]),size))
	return 0;
      return size / sizeof(DataT);
    }
    //: Get an array of samples.

    virtual bool GetAttr(const StringC &attrName,StringC &attrValue)
    { return HandleGetAttr(attrName,attrValue); }
    //: Get a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const StringC &attrValue)
    { return HandleSetAttr(attrName,attrValue); }
    //: Set a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue) 
    { return HandleGetAttr(attrName,attrValue); }
    //: Get a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const IntT &attrValue)
    { return HandleSetAttr(attrName,attrValue); }
    //: Set a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttrList(DListC<StringC> &list) const
    { return HandleGetAttrList(list); }
    //: Get list of attributes available.
    // This method will ADD all available attribute names to 'list'.

  };
  
  //! userlevel=Normal
  //: Audio input port.

  template<typename DataT,typename IOClassT> 
  class DPIAudioC
    : public DPIPortC<DataT>
  {
  public:
    DPIAudioC()
      
    {}
    //: Default constructor.
    
    DPIAudioC(const StringC &dev,int channel = 0)
      : DPEntityC(*new DPIAudioBodyC<DataT,IOClassT>(dev,channel))
    {}
    //: Constructor.
  };

  // -----------------------------------------------------------------------
  
  //! userlevel=Develop
  //: Audio input port.
  
  template<typename DataT,typename IOClassT> 
  class DPOAudioBodyC
    : public IOClassT,
      public DPOPortBodyC<DataT>
  {
  public:
    DPOAudioBodyC()
    {}
    //: Default constructor.
    
    DPOAudioBodyC(const StringC &dev,int channel)
      : IOClassT(dev,channel,false,typeid(DataT))
    {}
    //: Default constructor.
    
    virtual bool IsPutReady() const
    { return IsOpen(); }
    //: Is some data ready ?
    // true = yes.
    
    bool Put(DataT &buff) 
    { return Write((void *) &buff,sizeof(DataT)); }
    //: Write sample to stream.
    
    IntT PutArray(const SArray1dC<DataT> &data) {
      if(!Write(&(data[0]),sizeof(DataT) * data.Size()))
	return 0;
      return (IntT) data.Size();
    }
    //: Get an array of samples.
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue)
    { return HandleGetAttr(attrName,attrValue); }
    //: Get a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const StringC &attrValue)
    { return HandleSetAttr(attrName,attrValue); }
    //: Set a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue) 
    { return HandleGetAttr(attrName,attrValue); }
    //: Get a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const IntT &attrValue)
    { return HandleSetAttr(attrName,attrValue); }
    //: Set a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttrList(DListC<StringC> &list) const
    { return HandleGetAttrList(list); }
    //: Get list of attributes available.
    // This method will ADD all available attribute names to 'list'.

  };
  
  //! userlevel=Normal
  //: Audio input port.

  template<typename DataT,typename IOClassT> 
  class DPOAudioC
    : public DPOPortC<DataT>
  {
  public:
    DPOAudioC()
      
    {}
    //: Default constructor.
    
    DPOAudioC(const StringC &dev,int channel)
      : DPEntityC(*new DPOAudioBodyC<DataT,IOClassT>(dev,channel))
    {}
    //: Constructor.
  };
  
}


#endif

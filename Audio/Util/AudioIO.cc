// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAudioUtil
//! file="Ravl/Audio/Util/AudioIO.cc"

#include "Ravl/Audio/AudioIO.hh"
#include "Ravl/DList.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlAudioN {
  
  //: Constructor.
  
  AudioIOBaseC::AudioIOBaseC() {
  }
  
  //: Constructor.
  
  AudioIOBaseC::AudioIOBaseC(const StringC &fn,int channel,bool forInput,const type_info &type) {
  }
  
  //: Destructor.
  
  AudioIOBaseC::~AudioIOBaseC() {
  }
  
  //: Open audio device.
  
  bool AudioIOBaseC::IOpen(const StringC &fn,int channel,const type_info &dtype) {
    return false;
  }
  
  //: Open audio device.
  
  bool AudioIOBaseC::OOpen(const StringC &fn,int channel,const type_info &dtype) {
    return false;
  }
  
  //: Set number of bits to use in samples.
  // returns actual number of bits.
  
  bool AudioIOBaseC::SetSampleBits(IntT bits) {
    return false;
  }
  
  //: Set fequence of samples
  // Returns actual frequency.
  
  bool AudioIOBaseC::SetSampleRate(RealT rate) {
    return false;
  }

  //: Get number of bits to use in samples.
  // returns actual number of bits.
  
  bool AudioIOBaseC::GetSampleBits(IntT &bits) {
    return false;
  }
  
  //: Get fequence of samples
  // Returns actual frequency.
  
  bool AudioIOBaseC::GetSampleRate(RealT &rate) {
    return false;
  } 
  
  //: Read bytes from audio stream.
  // Returns false if error occured.
  
  bool AudioIOBaseC::Read(void *buf,IntT &len) {
    return false;
  }
  
  //: Write bytes to audio stream.
  // Returns false if error occured.
  
  bool AudioIOBaseC::Write(const void *buf,IntT len) {
    return false;
  }
  
  //: Handle get attrib.
  
  bool AudioIOBaseC::HandleGetAttr(const StringC &attrName,StringC &attrValue) {
    if(attrName == "samplerate") {
      RealT rval;
      if(!GetSampleRate(rval)) return false;
      attrValue = StringC(rval);
      return false;
    }
    return false;
  }
  
  //: Handle Set attrib.
  
  bool AudioIOBaseC::HandleSetAttr(const StringC &attrName,const StringC &attrValue) {
    ONDEBUG(cerr << "AudioIOBaseC::HandleSetAttr(), '" << attrName << "' = " << attrValue << "\n");
    if(attrName == "samplerate")
      return SetSampleRate(attrValue.RealValue());
    return false;
  }
  
  //: Get a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as sample rate.
  
  bool AudioIOBaseC::HandleGetAttr(const StringC &attrName,IntT &attrValue) {
    if(attrName == "samplerate") {
      RealT value;
      if(!GetSampleRate(value))
	return false;
      attrValue = Round(value);
      return true;
    }
    return false;
  }
  
  //: Set a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as sample rate.
  
  bool AudioIOBaseC::HandleSetAttr(const StringC &attrName,const IntT &attrValue) {
    ONDEBUG(cerr << "AudioIOBaseC::HandleSetAttr(), '" << attrName << "' = " << attrValue << "\n");
    if(attrName == "samplerate")
      return SetSampleRate((RealT) attrValue);
    return false;
  }
  
  //: Get a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  bool AudioIOBaseC::HandleGetAttr(const StringC &attrName,RealT &attrValue) {
    if(attrName == "samplerate") 
      return GetSampleRate(attrValue);
    return false;
  }
  
  //: Set a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  bool AudioIOBaseC::HandleSetAttr(const StringC &attrName,const RealT &attrValue) {
    ONDEBUG(cerr << "AudioIOBaseC::HandleSetAttr(), '" << attrName << "' = " << attrValue << "\n");
    if(attrName == "samplerate")
      return SetSampleRate(attrValue);
    return false;
  }

  //: Get list of attributes available.
  // This method will ADD all available attribute names to 'list'.
  
  bool AudioIOBaseC::HandleGetAttrList(DListC<StringC> &list) const {
    list.InsLast("samplerate");
    return false;
  }
  
  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  bool AudioIOBaseC::Seek(UIntT off) 
  { return false; }
  
  //: Find current location in stream.
  // May return ((UIntT) (-1)) if not implemented.
  
  UIntT AudioIOBaseC::Tell() const
  { return (UIntT) -1; }
  
  //: Find the total size of the stream.  (assuming it starts from 0)
  // May return ((UIntT) (-1)) if not implemented.
  
  UIntT AudioIOBaseC::Size() const
  { return (UIntT) -1; }
  
}

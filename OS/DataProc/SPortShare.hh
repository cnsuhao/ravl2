// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SPORTSHARE_HEADER
#define RAVL_SPORTSHARE_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.Core.Data Processing.Threads" 
//! rcsid="$Id$"
//! lib=RavlDPMT
//! date="18/9/2003"

#include "Ravl/DP/SPort.hh"
#include "Ravl/DP/SPortAttach.hh"
#include "Ravl/DP/StreamOp.hh"
#include "Ravl/DP/Plug.hh"
#include "Ravl/Threads/Mutex.hh"

namespace RavlN {
  
  template<class DataT>
  class DPISPortShareBodyC
    : public DPIPlugBaseBodyC,
      public AttributeCtrlBodyC
  {
  public:
    DPISPortShareBodyC()
    {}
    //: Default constructor.
    
    DPISPortShareBodyC(const DPISPortC<DataT> &ip)
      : input(ip)
    {}
    //: Constructor.
    
    virtual bool SetPort(const DPIPortBaseC &port) {
      MutexLockC lock(access);
      input = SPort(DPIPortC<DataT>(const_cast<DPIPortBaseC &>(port)));
      return port.IsValid();
    }
    //: set port.
    
    bool SetPort(DPIPortC<DataT> &sp) {
      MutexLockC lock(access);
      input = sp;
      return true;
    }
    //: Set port.
    
    virtual const type_info &InputType() const
    { return typeid(DataT); }
    //: Return type of port.
    
    MutexC &AccessLock()
    { return access; }
    //: Access lock.
    
    DPISPortC<DataT> &Input()
    { return input; }
    //: Access input.
    
    bool Get(UIntT frameNo,DataT &buf) {
      MutexLockC lock(access);
      if(frameNo != lastOffset) {
	if(!input.Seek(frameNo)) {
	  cerr << "DPISPortShareBodyC(), Failed to seek to frame " << frameNo << ".\n";
	  return false;
	}
	lastOffset = frameNo;
      }
      if(input.Get(buf)) {
	lastOffset++;
	return true;
      }
      return false;
    }
    //: Get frameNo from stream.
    
    IntT GetArray(UIntT frameNo,SArray1dC<DataT> &buf) {
      MutexLockC lock(access);
      int n;
      if(frameNo != lastOffset) {
	if(!input.Seek(frameNo)) {
	  cerr << "DPISPortShareBodyC(), Failed to seek to frame " << frameNo << ".\n";
	  return 0;
	}
	lastOffset = frameNo;
      }
      n = input.GetArray(buf);
      lastOffset += n;
      return n;
    }
    //: Get an array of data from stream.

    bool IsGetReady(UIntT frameNo) const {
      MutexLockC lock(access);
      return input.IsGetReady(); 
    }
    //: Is some data ready ?
    // true = yes.
    
    bool IsGetEOS(UIntT frameNo) const {
      MutexLockC lock(access);      
      return input.IsGetEOS();
    }
    //: Has the End Of Stream been reached ?
    // true = yes.

    UIntT Size() const { 
      MutexLockC lock(access);      
      return input.Size(); 
    }
    //: Find the total size of the stream. (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.
    
    UIntT Start() const {
      MutexLockC lock(access);      
      return input.Start(); 
    }
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0

    //:----------------------------------------------------------
    // Attributes
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue) {
      MutexLockC lock(access);
      return input.GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const StringC &attrValue) {
      MutexLockC lock(access);
      return input.SetAttr(attrName,attrValue);
    }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue) {
      MutexLockC lock(access);
      return input.GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const IntT &attrValue) {
      MutexLockC lock(access);
      return input.SetAttr(attrName,attrValue);
    }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,RealT &attrValue) {
      MutexLockC lock(access);
      return input.GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const RealT &attrValue) {
      MutexLockC lock(access);
      return input.SetAttr(attrName,attrValue);
    }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,bool &attrValue) {
      MutexLockC lock(access);
      return input.GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const bool &attrValue) {
      MutexLockC lock(access);
      return input.SetAttr(attrName,attrValue);
    }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttrList(DListC<StringC> &list) const {
      MutexLockC lock(access);
      return input.GetAttrList(list);
    }
    //: Get list of attributes available.
    // This method will ADD all available attribute names to 'list'.
    
    virtual bool GetAttrTypes(DListC<AttributeTypeC> &list) const {
      MutexLockC lock(access);
      return input.GetAttrTypes(list);
    }
    //: Get a list of available attribute types.
    
#if 0
    virtual AttributeTypeC GetAttrType(const StringC &attrName) const {
      MutexLockC lock(access);
      return input.GetAttrType(attrName);
    }
    //: Get type of a particular attribute.
    // Returns an invalid handle if attribute is unknown.
#endif
    
    virtual IntT RegisterChangedSignal(const StringC &attrName,const TriggerC &trig) {
      MutexLockC lock(access);
      return input.RegisterChangedSignal(attrName,trig);
    }
    
    //: Register a value changed signal.
    // Note: This method may not be implemented for all AttributeCtrl's.
    // Returns an id for the trigger, or -1 if operation fails.
    
    virtual bool RemoveChangedSignal(IntT id) {
      MutexLockC lock(access);
      return input.RemoveChangedSignal(id);
    }
    //: Remove a changed signal.
    // Note: This method may not be implemented for all AttributeCtrl's.
    
    virtual bool RegisterAttribute(const AttributeTypeC &attr) {
      MutexLockC lock(access);
      return input.RegisterAttribute(attr);      
    }
    //: Register a new attribute type.
    
  protected:
    DPISPortC<DataT> input;
    UIntT lastOffset;
    MutexC access;
  };
  
  template<class DataT>
  class DPISPortShareC
    : public DPIPlugBaseC,
      public AttributeCtrlC 
  {
  public:
    DPISPortShareC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DPISPortShareC(const DPISPortC<DataT> &ip)
      : DPEntityC(*new DPISPortShareBodyC<DataT>(ip))
    {}
    //: Constructor.

    DPISPortShareC(bool)
      : DPEntityC(*new DPISPortShareBodyC<DataT>())
    {}
    //: Constructor.
    
  protected:
    DPISPortShareC(DPISPortShareBodyC<DataT> &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    DPISPortShareBodyC<DataT> &Body()
    { return static_cast<DPISPortShareBodyC<DataT> &>(DPPlugBaseC::Body()); }
    //: Access body.

    const DPISPortShareBodyC<DataT> &Body() const
    { return static_cast<const DPISPortShareBodyC<DataT> &>(DPPlugBaseC::Body()); }
    //: Access body.
    
  public:
    MutexC &AccessLock()
    { return Body().AccessLock(); }
    //: Access lock.
    
    DPISPortC<DataT> &Input()
    { return Body().Input(); }
    //: Access input.
    
    bool Get(UIntT frameNo,DataT &buf) 
    { return Body().Get(frameNo,buf); }
    //: Get frameNo from stream.
    
    IntT GetArray(UIntT frameNo,SArray1dC<DataT> &buf) 
    { return Body().GetArray(frameNo,buf); }
    //: Get an array of data from stream.
    
    bool IsGetReady(UIntT frameNo) const 
    { return Body().IsGetReady(frameNo); }
    //: Is some data ready ?
    // true = yes.
    
    bool IsGetEOS(UIntT frameNo) const
    { return Body().IsGetEOS(frameNo); }
    //: Has the End Of Stream been reached ?
    // true = yes.        
    
    UIntT Size() const 
    { return Body().Size(); }
    //: Find the total size of the stream. (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.
    
    UIntT Start() const 
    { return Body().Start(); }
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0
    
    operator DPIPortC<DataT> () const;
    //: Convert into a DPIPortC
    
    operator DPISPortC<DataT> () const;
    //: Convert into a DPISPortC
    
    DPIPortC<DataT> Port() const;
    //: Explicitly create a port.
  }; 
    
  //:---------------------------------------------------------------------------------------------
    
  template<class DataT>
  class DPISPortShareClientBodyC
    : public DPStreamOpBodyC,
      public DPISPortBodyC<DataT>
  {
  public:
    DPISPortShareClientBodyC()
    {}
    //: Default constructor.
    
    DPISPortShareClientBodyC(const DPISPortShareC<DataT> &sharedPort)
      : input(sharedPort)
    {}
    //: Constructor.
    
    //:----------------------------------------------------------
    // Get controls
    
    bool Seek(UIntT off)  {
      offset = off;
      return true;
    }
    //: Seek to location in stream.
    // Returns false, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off) {
      if(off < 0) {
	if(offset > (UIntT) -off)
	offset += off;
      else
	offset = 0;
      } else
	offset += off;
      return true;
    }
    //: Delta Seek, goto location relative to the current one.
    // The default behavour of this functions is :
    // Do some error checking then:
    //   Seek((UIntT)((IntT) Tell() + off));
    // if an error occurered (DSeek returned False) then stream
    // position will not be changed.
    
    virtual UIntT Tell() const 
    { return offset; }
    //: Find current location in stream.
    // Defined as the index of the next object to be written or read.
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Size() const
    { return input.Size(); }
    //: Find the total size of the stream. (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Start() const
    { return input.Start(); }
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0
    
    //:----------------------------------------------------------
    // Get controls
    
    virtual bool IsGetReady() const 
    { return input.IsGetReady(offset); }
    //: Is some data ready ?
    // true = yes.
    
    virtual bool IsGetEOS() const 
    { return input.IsGetEOS(offset); }
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual DataT Get()  {
      DataT ret;
      if(!input.Get(offset,ret))
	throw DataNotReadyC("Get failed");
      offset++;
      return ret;
    }
    //: Get next piece of data.
    
    virtual bool Get(DataT &buff) { 
      if(input.Get(offset,buff)) {
	offset++;
	return true;
      }
      return false;
    }
    //: Try and get next piece of data.
    
    virtual IntT GetArray(SArray1dC<DataT> &data) {
      IntT n = input.GetArray(offset,data);
      offset += n;
      return n;
    }
    //: Get an array of data from stream.
    
    virtual bool Discard() { 
      offset++;
      return true;
    }
    //: Discard the next input datum.

    //:----------------------------------------------------------
    // Attributes
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue) 
    { return input.GetAttr(attrName,attrValue); }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const StringC &attrValue) 
    { return input.SetAttr(attrName,attrValue); }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue) 
    { return input.GetAttr(attrName,attrValue); }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const IntT &attrValue) 
    { return input.SetAttr(attrName,attrValue); }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,RealT &attrValue) 
    { return input.GetAttr(attrName,attrValue); }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const RealT &attrValue) 
    { return input.SetAttr(attrName,attrValue); }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,bool &attrValue) 
    { return input.GetAttr(attrName,attrValue); }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const bool &attrValue) 
    { return input.SetAttr(attrName,attrValue); }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttrList(DListC<StringC> &list) const 
    { return input.GetAttrList(list); }
    //: Get list of attributes available.
    // This method will ADD all available attribute names to 'list'.
    
    virtual bool GetAttrTypes(DListC<AttributeTypeC> &list) const 
    { return input.GetAttrTypes(list); }
    //: Get a list of available attribute types.
    
#if 0
    virtual AttributeTypeC GetAttrType(const StringC &attrName) const 
    { return input.GetAttrType(attrName); }
    //: Get type of a particular attribute.
    // Returns an invalid handle if attribute is unknown.
#endif
    
    virtual IntT RegisterChangedSignal(const StringC &attrName,const TriggerC &trig) 
    { return input.RegisterChangedSignal(attrName,trig); }
    
    //: Register a value changed signal.
    // Note: This method may not be implemented for all AttributeCtrl's.
    // Returns an id for the trigger, or -1 if operation fails.
    
    virtual bool RemoveChangedSignal(IntT id) 
    { return input.RemoveChangedSignal(id); }
    //: Remove a changed signal.
    // Note: This method may not be implemented for all AttributeCtrl's.
    
    virtual bool RegisterAttribute(const AttributeTypeC &attr) 
    { return input.RegisterAttribute(attr); }
    //: Register a new attribute type.
    
  protected:
    UIntT offset;
    DPISPortShareC<DataT> input;
  };
  
  //: Shared port.
  
  template<class DataT>
  class DPISPortShareClientC
    : public DPStreamOpC,
      public DPISPortC<DataT>
  {
  public:
    DPISPortShareClientC()
    {}
    //: Default constructor.

    DPISPortShareClientC(bool)
      : DPEntityC(*new DPISPortShareClientBodyC<DataT>())
    {}
    //: Constructor
    
    DPISPortShareClientC(const DPISPortShareC<DataT> &sharedPort)
      : DPEntityC(*new DPISPortShareClientBodyC<DataT>(sharedPort))
    {}
    //: Constructor.
    
  protected:
    DPISPortShareClientC(DPISPortShareClientBodyC<DataT> &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    DPISPortShareClientBodyC<DataT> &Body()
    { return dynamic_cast<DPISPortShareClientBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.

    const DPISPortShareClientBodyC<DataT> &Body() const
    { return dynamic_cast<const DPISPortShareClientBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    
  };
  
  
  template<class DataT>
  DPISPortShareC<DataT>::operator DPIPortC<DataT> () const 
  { return DPISPortShareClientC<DataT>(*this); }
  
  template<class DataT>
  DPISPortShareC<DataT>::operator DPISPortC<DataT> () const
  { return DPISPortShareClientC<DataT>(*this); }  
  
  template<class DataT>
  DPIPortC<DataT> DPISPortShareC<DataT>::Port() const
  { return DPISPortShareClientC<DataT>(*this); }

}


#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPSPORTATTACH_HEADER
#define RAVL_DPSPORTATTACH_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Data Processing.Seekable Ports" 
//! file="Ravl/Core/IO/SPortAttach.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="08/04/1999"
//! userlevel=Default

#include "Ravl/DP/SPort.hh"

namespace RavlN {
  //////////////////////////////
  //! userlevel=Develop
  //: Seek Control attach.
  
  class DPSeekCtrlAttachBodyC
    : virtual public DPSeekCtrlBodyC
  {
  public:
    DPSeekCtrlAttachBodyC(const DPSeekCtrlC &oth = DPSeekCtrlC());
    //: Constructor.
    
    DPSeekCtrlAttachBodyC(const DPPortC &pb,bool smartDefault = true);
    //: Constructor
    
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    
    virtual bool DSeek(IntT off);
    //: Delta Seek, goto location relative to the current one.
    
    virtual UIntT Tell() const;
    //: Find current location in stream.
    
    virtual UIntT Size() const;
    //: Find the total size of the stream.
    
    virtual UIntT Start() const;
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0
    
    virtual void SetSeekCtrl(const DPSeekCtrlC &sc);
    //: Set seek control.
    
  protected:
    DPSeekCtrlC sctrl;
  };
  
  
  //////////////////////////////
  //! userlevel=Advanced
  //: Seek Control attach.
  
  class DPSeekCtrlAttachC
    : public DPSeekCtrlC
  {
  public:
    DPSeekCtrlAttachC()
      : DPEntityC(true)
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DPSeekCtrlAttachC(const DPSeekCtrlC &sctrl)
      : DPEntityC(*new DPSeekCtrlAttachBodyC(sctrl))
      {}
    //: Constructor.
    
    DPSeekCtrlAttachC(const DPPortC &pb,bool smartDefault = true)
      : DPEntityC(*new DPSeekCtrlAttachBodyC(pb,smartDefault))
      {}
    //: Constructor.
  
  protected:
    inline DPSeekCtrlAttachBodyC &Body() 
      { return dynamic_cast<DPSeekCtrlAttachBodyC &>(DPEntityC::Body()); }
    //: Access body.
  
    inline const DPSeekCtrlAttachBodyC &Body() const
      { return dynamic_cast<const DPSeekCtrlAttachBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
  void SetSeekCtrl(const DPSeekCtrlC &sc)
    { Body().SetSeekCtrl(sc); }
  //: Set seek control.
  
  };
  
  ///////////////////////////////////
  //! userlevel=Develop
  //: Seek control attach.
  
  template<class DataT>
  class DPISPortAttachBodyC 
    : public DPISPortBodyC<DataT>,
      public DPSeekCtrlAttachBodyC
  {
  public:
    DPISPortAttachBodyC()
      {}
    //: Default constructor.
    
    DPISPortAttachBodyC(const DPIPortC<DataT> &aport,const DPSeekCtrlC &sc)
      : DPSeekCtrlAttachBodyC(sc),
	port(aport)
      {
	RavlAssert(sctrl.IsValid());
	RavlAssert(port.IsValid());
      }
    //: Constructor.
    // Attach 'aport' to seek ctrl 'sc'
    
    DPISPortAttachBodyC(const DPIPortC<DataT> &aport,bool smartDefault = true)
      : DPSeekCtrlAttachBodyC(aport,smartDefault),
      port(aport)
      {
	RavlAssert(port.IsValid());
      }
    //: Constructor.
    // Attach 'aport' to seek ctrl 'sc'
    
    virtual bool Seek(UIntT off)
      { return sctrl.Seek(off); }
    //: Seek to location in stream.
    
    virtual bool DSeek(IntT off)
      { return sctrl.DSeek(off); }
    //: Delta Seek, goto location relative to the current one.
  
    virtual UIntT Tell() const
      { return sctrl.Tell(); }
    //: Find current location in stream.
  
    virtual UIntT Size() const
      { return sctrl.Size(); }
    //: Find the total size of the stream.
    
    virtual UIntT Start() const
      { return sctrl.Start(); }
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0
    
    virtual bool IsGetReady() const
      { return port.IsGetReady(); }
    //: Is some data ready ?
    // true = yes.
    // Defaults to !IsGetEOS().
    
    virtual bool IsGetEOS() const
      { return port.IsGetEOS(); }
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual const type_info &InputType() const
      { return port.InputType(); }
    //: Input type.
    
    virtual DataT Get() 
      { return port.Get(); }
    //: Get next piece of data.
    
    virtual bool Get(DataT &buff) 
      {  return port.Get(buff); }
    //: Try and get next piece of data.
    
    virtual DPPortC ConnectedTo() const
      { return port; }
    //: What does this connect to ?
    
  protected:
    DPIPortC<DataT> port; 
  };
  
  ///////////////////////////////////
  //! userlevel=Advanced
  //: Seek control attach.
  
  template<class DataT>
  class DPISPortAttachC 
    : public DPISPortC<DataT>,
      protected DPSeekCtrlAttachC
  {
  public:
    DPISPortAttachC()
      : DPEntityC(true)
      {}
    //: Default constructor.
    // Creates an invalid handle.  
    
    DPISPortAttachC(const DPIPortC<DataT> &aport,const DPSeekCtrlC &sc)
      : DPEntityC(*new DPISPortAttachBodyC<DataT>(aport,sc))
      {}
    //: Constructor.
    // Attach 'aport' to seek ctrl 'sc'
    
    DPISPortAttachC(const DPIPortC<DataT> &aport,bool smartDefault = true)
      : DPEntityC(*new DPISPortAttachBodyC<DataT>(aport,smartDefault))
      {}
    //: Constructor.
    // Attach 'aport' to seek ctrl 'sc'
    
    void SetSeekCtrl(const DPSeekCtrlC &sc)
      { DPSeekCtrlAttachC::Body().SetSeekCtrl(sc); }
    //: Set seek control.
    
  };
  
  ///////////////////////////////////
  //! userlevel=Develop
  //: Seek control attach.
  
  template<class DataT>
  class DPOSPortAttachBodyC 
    : public DPOSPortBodyC<DataT>,
      public DPSeekCtrlAttachBodyC
  {
  public:
    DPOSPortAttachBodyC()
      {}
    //: Default constructor.
    
    DPOSPortAttachBodyC(const DPOPortC<DataT> &aport,const DPSeekCtrlC &sc)
      : DPSeekCtrlAttachBodyC(sc),
      port(aport)
      {}
    //: Constructor.
    // Attach 'aport' to seek ctrl 'sc'
    
    DPOSPortAttachBodyC(const DPOPortC<DataT> &aport,bool smartDefault = true)
      : DPSeekCtrlAttachBodyC(aport,smartDefault),
      port(aport)
      {}
    //: Constructor.
    // Attach 'aport' to seek ctrl 'sc'
    
    virtual bool Seek(UIntT off)
      { return sctrl.Seek(off); }
    //: Seek to location in stream.
    
    virtual bool DSeek(IntT off)
      { return sctrl.DSeek(off); }
    //: Delta Seek, goto location relative to the current one.
    
    virtual UIntT Tell() const
      { return sctrl.Tell(); }
    //: Find current location in stream.
    
    virtual UIntT Size() const
      { return sctrl.Size(); }
    //: Find the total size of the stream.
    
    virtual UIntT Start() const
      { return sctrl.Start(); }
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0
    
    virtual void PutEOS()
      { port.PutEOS(); }
    //: Is some data ready ?
    // true = yes.
    // Defaults to !IsGetEOS().
    
    virtual const type_info &OutputType() const
      { return port.OutputType(); }
    //: Input type.
    
    virtual bool Put(const DataT &buff) 
      {  return port.Put(buff); }
    //: Try and get next piece of data.
    
    virtual DPPortC ConnectedTo() const
      { return port; }
    //: What does this connect to ?
    
  protected:
    DPOPortC<DataT> port; 
  };
  
  ///////////////////////////////////
  //! userlevel=Advanced
  //: Seek control attach.
  
  template<class DataT>
  class DPOSPortAttachC 
    : public DPOSPortC<DataT>,
      public DPSeekCtrlAttachC
  {
  public:
    DPOSPortAttachC()
      : DPEntityC(true)
      {}
    //: Default constructor.
    // Creates an invalid handle.  
    
    DPOSPortAttachC(const DPOPortC<DataT> &aport,const DPSeekCtrlC &sc)
      : DPEntityC(*new DPOSPortAttachBodyC<DataT>(aport,sc))
      {}
    //: Constructor.
    // Attach 'aport' to seek ctrl 'sc'
    
    DPOSPortAttachC(const DPOPortC<DataT> &aport,bool smartDefault = true)
      : DPEntityC(*new DPOSPortAttachBodyC<DataT>(aport,smartDefault))
      {}
    //: Constructor.
    // Attach 'aport' to seek ctrl 'sc'
    
  };
  
  template<class DataT>
  DPISPortAttachC<DataT> SPort(const DPIPortC<DataT> &aport) { 
    DPISPortAttachC<DataT> ret(aport);
    if(ret.IsValid()) // Is it a seekable port already ?
      return ret;
    return DPISPortAttachC<DataT>(aport); 
  }
  //: Attempt to turn 'aport' into a seekable port.
  // This checks up the processing line for a seekable port and attaches it
  // where possible.  If none are found then the seek controls are attached to stubs.
  
  template<class DataT>
  DPOSPortAttachC<DataT> SPort(const DPOPortC<DataT> &aport) { 
    DPOSPortAttachC<DataT> ret(aport);
    if(ret.IsValid()) // Is it a seekable port already ?
      return ret;
    return DPOSPortAttachC<DataT>(aport); 
  }
  //: Attempt to turn 'aport' into a seekable port.
  // This checks up the processing line for a seekable port and attaches it
  // where possible.  If none are found then the seek controls are attached to stubs.
  
}


#endif

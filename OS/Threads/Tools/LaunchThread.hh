// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_THREADLAUNCH_HEADER
#define RAVL_THREADLAUNCH_HEADER 1
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Tools/LaunchThread.hh"
//! lib=RavlThreads
//! userlevel=Default
//! docentry="Ravl.OS.Threads"
//! author="Charles Galambos"
//! date="02/07/1999"
//! example=exLaunchThread.cc 

#include "Ravl/Threads/Thread.hh"
#include "Ravl/Threads/ThreadEvent.hh"
#include "Ravl/Calls.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/CallMethodRefs.hh"

namespace RavlN {
  class LaunchThreadC;
  
  //! userlevel=Develop
  //: Launch event body.
  
  class LaunchThreadBodyC 
    : public ThreadBodyC
  {
  public:
    LaunchThreadBodyC(const TriggerC &nse);
    //: Constructor.
    
    virtual int Start();
    //: Called on startup.
    
    ThreadEventC &Done()
    { return done; }
    //: Access done event.

    TriggerC &SigEvent()
    { return se; }
    //: Event to call.
    // NB. This is used by the child thread
    // and should not be modified until after the event 'done'
    // has occured.
    
  protected:    
    void Reset(const TriggerC &nse);
    //: Reset signal event.
    // Setup new event....
    
    TriggerC se;
    //: Event to call.
    
    ThreadEventC done;
    //: Signal when done.
    
    ThreadEventC reStart;
    //: Signal to restart.
    
    friend class LaunchThreadC;
  };
  
  //! userlevel=Normal
  //: Launch event handle.
  
  class LaunchThreadC
    : public ThreadC
  {
  public:
    LaunchThreadC()
    {}
    //: Default constructor.
    
    LaunchThreadC(const TriggerC &nse);
    //: Constructor.

  protected:
    LaunchThreadC(LaunchThreadBodyC &leb)
      : ThreadC(leb)
    {}
    //: Body constructor.
    
    LaunchThreadBodyC &Body()
    { return static_cast<LaunchThreadBodyC &>(ThreadC::Body()); }
    //: Access thread body.
    
    void Reset(const TriggerC &nse)
    { Body().Reset(nse); }
    //: Reset signal event.
    // Setup new event....
    
  public:
    ThreadEventC &Done()
    { return Body().Done(); }
    //: Access done event.
    // This is true when launched event completes.
    
    TriggerC &SigEvent()
    { return Body().SigEvent(); }
    //: Event to call.
    // NB. This is used by the child thread
    // and should not be modified until after the event 'done'
    // has occured.
    
    bool WaitForExit() { 
      Body().Done().Wait(); 
      return true;
    }
    //: Wait for thread to exit.
    
    friend class LaunchThreadBodyC;
  };
  
  ////////////////////////////////////////////////////////////////

  //! userlevel=Normal
  
  inline 
  LaunchThreadC LaunchThread(const TriggerC &nse)
  { return LaunchThreadC(nse); }
  //: Launch a routine on another thread.
  
  inline
  LaunchThreadC LaunchThread(bool (*nFunc)())
  { return LaunchThreadC(Trigger(nFunc)); }
  //: Launch a routine on another thread.

  template<class DataT>
  inline
  LaunchThreadC LaunchThread(bool (*nFunc)(DataT &),const DataT &dat)
  { return LaunchThreadC(Trigger(nFunc,dat)); }
  //: Launch a routine on another thread.

  template<class Data1T,class Data2T>
  inline
  LaunchThreadC LaunchThread(bool (*nFunc)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2)
  { return LaunchThreadC(Trigger(nFunc,dat1,dat2)); }
  //: Launch a routine on another thread.

  template<class Data1T,class Data2T,class Data3T>
  inline
  LaunchThreadC LaunchThread(bool (*nFunc)(Data1T &,Data2T &,Data3T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3)
  { return LaunchThreadC(Trigger(nFunc,dat1,dat2,dat3)); }
  //: Launch a routine on another thread.
  
  template<class ObjT>
  LaunchThreadC LaunchThread(const ObjT &nObj,bool (ObjT::*nFunc)())
  { return LaunchThreadC(Trigger(nObj,nFunc)); }
  //: Launch a method on another thread.
  // This calls a method on a copy of object 'nObj'.
  
  template<class ObjT,class DataT>
  LaunchThreadC LaunchThread(const ObjT &nObj,bool (ObjT::*nFunc)(DataT &),const DataT &nDat) 
  { return LaunchThreadC(Trigger(nObj,nFunc,nDat)); }
  //: Launch a method on another thread.
  // This calls a method on a copy of object 'nObj'.
  
  template<class ObjT,class Data1T,class Data2T>
  LaunchThreadC LaunchThread(const ObjT &nObj,bool (ObjT::*nFunc)(Data1T &,Data2T &),const Data1T &nDat1,const Data2T &nDat2) 
  { return LaunchThreadC(Trigger(nObj,nFunc,nDat1,nDat2)); }
  //: Launch a method on another thread.
  // This calls a method on a copy of object 'nObj'.
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  LaunchThreadC LaunchThread(const ObjT &nObj,bool (ObjT::*nFunc)(Data1T &,Data2T &,Data3T &),const Data1T &nDat1,const Data2T &nDat2,const Data3T &nDat3) 
  { return LaunchThreadC(Trigger(nObj,nFunc,nDat1,nDat2,nDat3)); }
  //: Launch a method on another thread.
  // This calls a method on a copy of object 'nObj'.
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T>
  LaunchThreadC LaunchThread(const ObjT &nObj,bool (ObjT::*nFunc)(Data1T &,Data2T &,Data3T &,Data4T &),const Data1T &nDat1,const Data2T &nDat2,const Data3T &nDat3,const Data4T &nDat4)
  { return LaunchThreadC(Trigger(nObj,nFunc,nDat1,nDat2,nDat3,nDat4)); }
  //: Launch a method on another thread.
  // This calls a method on a copy of object 'nObj'.

  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T>
  LaunchThreadC LaunchThread(const ObjT &nObj,bool (ObjT::*nFunc)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &),const Data1T &nDat1,const Data2T &nDat2,const Data3T &nDat3,const Data4T &nDat4,const Data5T &nDat5)
  { return LaunchThreadC(Trigger(nObj,nFunc,nDat1,nDat2,nDat3,nDat4,nDat5)); }
  //: Launch a method on another thread.
  // This calls a method on a copy of object 'nObj'.
  
  template<class ObjT>
  LaunchThreadC LaunchThreadR(ObjT &nObj,bool (ObjT::*nFunc)())
  { return LaunchThreadC(TriggerR(nObj,nFunc)); }
  //: Launch a method on another thread.
  // This calls a method on a reference to object 'nObj'.
  
  template<class ObjT,class DataT>
  LaunchThreadC LaunchThreadR(ObjT &nObj,bool (ObjT::*nFunc)(DataT &),const DataT &nDat) 
  { return LaunchThreadC(TriggerR(nObj,nFunc,nDat)); }
  //: Launch a method on another thread.
  // This calls a method on a reference to object 'nObj'.
  
  template<class ObjT,class Data1T,class Data2T>
  LaunchThreadC LaunchThreadR(ObjT &nObj,bool (ObjT::*nFunc)(Data1T &,Data2T &),const Data1T &nDat1,const Data2T &nDat2) 
  { return LaunchThreadC(TriggerR(nObj,nFunc,nDat1,nDat2)); }
  //: Launch a method on another thread.
  // This calls a method on a reference to object 'nObj'.
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  LaunchThreadC LaunchThreadR(ObjT &nObj,bool (ObjT::*nFunc)(Data1T &,Data2T &,Data3T &),const Data1T &nDat1,const Data2T &nDat2,const Data3T &nDat3) 
  { return LaunchThreadC(TriggerR(nObj,nFunc,nDat1,nDat2,nDat3)); }
  //: Launch a method on another thread.
  // This calls a method on a reference to object 'nObj'.
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T>
  LaunchThreadC LaunchThreadR(ObjT &nObj,bool (ObjT::*nFunc)(Data1T &,Data2T &,Data3T &,Data4T &),const Data1T &nDat1,const Data2T &nDat2,const Data3T &nDat3,const Data4T &nDat4)
  { return LaunchThreadC(TriggerR(nObj,nFunc,nDat1,nDat2,nDat3,nDat4)); }
  //: Launch a method on another thread.
  // This calls a method on a reference to object 'nObj'.

  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T>
  LaunchThreadC LaunchThreadR(ObjT &nObj,bool (ObjT::*nFunc)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &),const Data1T &nDat1,const Data2T &nDat2,const Data3T &nDat3,const Data4T &nDat4,const Data5T &nDat5)
  { return LaunchThreadC(TriggerR(nObj,nFunc,nDat1,nDat2,nDat3,nDat4,nDat5)); }
  //: Launch a method on another thread.
  // This calls a method on a reference to object 'nObj'.
  
}

#endif

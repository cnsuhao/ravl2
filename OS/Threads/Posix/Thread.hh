// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPTHREADSTHREAD_HEADER
#define RAVLPTHREADSTHREAD_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Posix/Thread.hh"
//! lib=RavlThreads
//! userlevel=Normal
//! docentry="Ravl.OS.Threads"
//! author="Charles Galambos"
//! date="02/07/99"

#if !defined(__sgi__)
#define _GNU_SOURCE 1
#define _POSIX_SOURCE 1
#endif

#if defined(__sol2__)
#include <sys/signal.h>
#endif

#include <pthread.h>
#include "Ravl/RefCounter.hh"

namespace RavlN
{
  //! userlevel=Normal
  
  void Yield();
  //: Yield control of processor
  // call if you wish a brief delay in execution.  
  // Particularly useful if you are forced to poll for an event.
   
  //! userlevel=Normal
  UIntT CurrentThreadID();
  //: Get ID of current running thread.

  extern void *StartThread(void *Data);
  //! userlevel=Develop
  //: Use internally to start threads.
  
  extern void cancellationHandler(void *data);
  //! userlevel=Develop
  //: Called when a thread is cancelled.
  
  //! userlevel=Develop
  //: Thread body.
  
  class ThreadBodyC 
    : public RCBodyVC
  {
  public:
    ThreadBodyC();
    //: Default constructor.

    ~ThreadBodyC();
    //: Destructor.
    
    bool Execute();
    // Start thread running, use this command to start thread running
    // after it has been created.  This function can only be called 
    // once.
        
    void Terminate();
    //: Terminate thread.
    // Call to stop the thread running.
    // THEAD SAFE.
    
    bool SetPriority(int Pri);
    // Set the priority of the process
    // 0 to 32767, Higher faster.
    // THEAD SAFE.
    
    inline UIntT ID() const
      { return ((UIntT) threadID); }
    // Get a unique ID for this thread.
    // NB. An id may no be assigned to the thread until
    // after Execute() has been called.
    // THEAD SAFE.
    
  protected:
    virtual int Start(); 
    //: Called when thread started.  
    // This function should be overloaded
    // is a derived class.  It is called with the new thread after 
    // Execute() is called. 
    
    virtual int End();
    //: Called when thread terminates normally.  
    // Overloading this method
    // is optional.  There is no need to call this function 
    // directly. 

  private:
    void Startup();
    //: Start user code.
    
    void Cancel();
    //: Cancel thread.

    pthread_t threadID;
    bool live; // Set to true after thread is created.
    bool terminatePending; // True if Terminate function has been called.

    friend void *StartThread(void *);
    friend void cancellationHandler(void *data);
  };
  
  //! userlevel=Normal
  //: Thread handle.
  // Note: The thread itself holds a refrence count on the object.
  // this refrence count is held until the thread terminates. Another
  // thread can initiate shutdown by calling the Terminate() function.
  
  class ThreadC 
    : public RCHandleC<ThreadBodyC>
  {
  public:
    ThreadC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    ThreadC(ThreadBodyC &bod)
      : RCHandleC<ThreadBodyC>(bod)
      {}
    //: Body constructor.
    
    ThreadBodyC &Body() 
      { return RCHandleC<ThreadBodyC>::Body(); }
    //: Access body.
    
    const ThreadBodyC &Body() const
      { return RCHandleC<ThreadBodyC>::Body(); }
    //: Access body.
    
  public:
    bool Execute()
      { return Body().Execute(); }
    //: Start thread running.
    // use this command to start thread running
    // after it has been created.  This function can only be called 
    // once.
    
    void Terminate()
      { Body().Terminate(); }
    //: Terminate thread.
    // Call to stop the thread running.
    // THEAD SAFE.
    
    bool SetPriority(int pri)
      { return Body().SetPriority(pri); }
    // Set the priority of the process
    // 0 to 32767, Higher faster.
    // THEAD SAFE.
    
    inline UIntT ID() const
      { return Body().ID(); }
    // Get a unique ID for this thread.
    // NB. An id may no be assigned to the thread until
    // after Execute() has been called.
    // THEAD SAFE.
    
  };

  UIntT ThisThreadID();
  //: Get ID for this thread.
  
}



#endif

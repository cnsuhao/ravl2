// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TIMEDTRIGGERQUEUE_HEADER
#define RAVL_TIMEDTRIGGERQUEUE_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Tools/TimedTriggerQueue.hh"
//! lib=RavlThreads
//! docentry="Ravl.API.OS.Time"
//! author="Charles Galambos"
//! date="23/09/1999"

#include "Ravl/OS/Date.hh"
#include "Ravl/PriQueue.hh"
#include "Ravl/Hash.hh"
#include "Ravl/Threads/Mutex.hh"
#include "Ravl/Threads/Semaphore.hh"
#include "Ravl/Threads/ThreadEvent.hh"
#include "Ravl/Calls.hh"

#define USE_NEW_TIMEDTRIGGERQUEUE 1
// The new timed trigger code doesn't rely the un*x select system call,
// but gives less accurate timing.  

namespace RavlN
{
  class TimedTriggerQueueC;
  
  //! userlevel=Develop
  //: Timed event queue body.
  // This is a queue of routines to be triggered at some point in the future.
  // See the handle class for more details.
  
  class TimedTriggerQueueBodyC 
    : public RCBodyC
  {
  public:
    TimedTriggerQueueBodyC();
    //: Default constuctor

    ~TimedTriggerQueueBodyC();
    //: Destructor.
    // This will not return until shutdown is complete.
    
    UIntT Schedule(RealT t,const TriggerC &se);
    //: Schedule event for running after time 't' (in seconds).
    // Thread safe.
    // Returns an ID for the event, which can
    // be used for canceling it. 
    
    UIntT Schedule(DateC &at,const TriggerC &se);
    //: Schedule event for running.
    // Thread safe.
    // Returns an ID for the event, which can
    // be used for canceling it.
    
    bool Cancel(UIntT eventID);
    //: Cancel pending event.
    // Will return TRUE if event in canceled before
    // it was run.

    void Shutdown();
    //: Shutdown even queue.
    
  protected:
    bool Process();
    //: Process event queue.
    
    MutexC access;
    UIntT eventCount;
    PriQueueC<DateC,UIntT> schedule;
    HashC<UIntT,TriggerC> events;
    bool done;
    ThreadEventC hasShutdown;
    // Queue fd's
#if USE_NEW_TIMEDTRIGGERQUEUE
    SemaphoreC semaSched;
#else
    int rfd,wfd;
#endif
    
    friend class TimedTriggerQueueC;
  };
  
  //! userlevel=Normal
  //: Timed event queue.
  // This is a queue of routines to be triggered at some point in the future.
  // This class creates a new thread which triggers a list of routines
  // in the requested sequence.  A single thread is used to call all the
  // routines, so if any lengthy processing is required it is better to
  // spawn a new thread to complete it.   
  
  class TimedTriggerQueueC 
    : public RCHandleC<TimedTriggerQueueBodyC>
  {
  public:
    TimedTriggerQueueC()
      {}
    //: Default constructor.
    // Creates an invalid handle.

    TimedTriggerQueueC(bool )
      : RCHandleC<TimedTriggerQueueBodyC>(*new TimedTriggerQueueBodyC())
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    TimedTriggerQueueC(TimedTriggerQueueBodyC &bod)
      : RCHandleC<TimedTriggerQueueBodyC>(bod)
      {}
    //: Body constructor.

    TimedTriggerQueueBodyC &Body() 
      { return RCHandleC<TimedTriggerQueueBodyC>::Body(); }
    //: Access body.

    const TimedTriggerQueueBodyC &Body() const
      { return RCHandleC<TimedTriggerQueueBodyC>::Body(); }
    //: Access body.
    
    bool Process()
      { return Body().Process(); }
    //: Used to start internal thread.
  public:
    UIntT Schedule(RealT t,const TriggerC &se)
      { return Body().Schedule(t,se); }
    //: Schedule event for running after time 't' (in seconds).
    // Thread safe.
    // Returns an ID for the event, which can
    // be used for canceling it. 
    
    UIntT Schedule(DateC &at,const TriggerC &se)
      { return Body().Schedule(at,se); }
    //: Schedule event for running.
    // Thread safe.
    // Returns an ID for the event, which can
    // be used for canceling it.
    
    bool Cancel(UIntT eventID)
      { return Body().Cancel(eventID); }
    //: Cancel pending event.
    // Will return TRUE if event in canceled before
    // it was run.
    
    void Shutdown()
      { Body().Shutdown(); }
    //: Shutdown even queue.
    // NB. This will block until shutdown is complete
    
    friend class TimedTriggerQueueBodyC;
  };
  
  
}

#endif

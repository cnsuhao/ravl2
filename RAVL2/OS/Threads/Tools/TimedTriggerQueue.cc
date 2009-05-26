// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/TimedTriggerQueue.cc"

// Need the following to get timeval...
#include "Ravl/config.h"
#if RAVL_OS_SOLARIS
#define __EXTENSIONS__ 1
#endif

#ifdef __sgi__
#undef _POSIX_C_SOURCE
#include <standards.h>
#endif

#include "Ravl/Threads/TimedTriggerQueue.hh"

#if !USE_NEW_TIMEDTRIGGERQUEUE
extern "C" {
#include <unistd.h>
#include <sys/types.h>
#ifdef __sgi__
#include <bstring.h>
#endif
#include <sys/time.h>
#include <sys/select.h>
#include <string.h>
};
#endif

#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/Exception.hh"

#define DODEBUG 0

#if DODEBUG 
#include "Ravl/String.hh"
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

struct timeval;

namespace RavlN
{

  //: Default constuctor
  
  TimedTriggerQueueBodyC::TimedTriggerQueueBodyC() 
    : eventCount(0),
      done(false),
      semaSched(0)
  {
#if !USE_NEW_TIMEDTRIGGERQUEUE
    int iofds[2];
    if(pipe(iofds) != 0) 
      throw ExceptionOperationFailedC("TimedTriggerQueueBodyC(), Failed to open pipe. \n");
    rfd = iofds[0];
    wfd = iofds[1];
#endif
    LaunchThread(TimedTriggerQueueC(*this,RCLH_CALLBACK),&TimedTriggerQueueC::Process);
  }
  
  //: Destructor.
  
  TimedTriggerQueueBodyC::~TimedTriggerQueueBodyC() {
  }
  
  //: Called when owning handles drops to zero.
  
  void TimedTriggerQueueBodyC::ZeroOwners() {
    // Start shutdown
    done = true;
    
#if !USE_NEW_TIMEDTRIGGERQUEUE
    IntT nEvent = 0;
    if(write(wfd,&nEvent,sizeof(IntT)) != sizeof(IntT))
      cerr << "TimedTriggerQueueBodyC::Schedule(), WARNING: Failed to write to schedule queue.  \n";
#endif
    
    // Pass back to parent on principle.
    RCLayerBodyC::ZeroOwners();
  }
  
  //: Shutdown even queue.
  
  void TimedTriggerQueueBodyC::Shutdown() {
    done = true;
#if !USE_NEW_TIMEDTRIGGERQUEUE
    IntT nEvent = 0;
    if(write(wfd,&nEvent,sizeof(IntT)) != sizeof(IntT))
      cerr << "TimedTriggerQueueBodyC::Schedule(), WARNING: Failed to write to schedule queue.  \n";
#endif
  }
  
  //: Schedule event for running after time 't' (in seconds).
  
  UIntT TimedTriggerQueueBodyC::Schedule(RealT t,const TriggerC &se) {
    DateC at(true); // Set to now.
    at += t; // Add delay...
    return Schedule(at,se);
  }
  
  //: Schedule event for running.
  // Thread safe.
  
  UIntT TimedTriggerQueueBodyC::Schedule(DateC &at,const TriggerC &se) {
    if(!se.IsValid())
      return 0;
    MutexLockC holdLock(access);
    do {
      eventCount++;
      if(eventCount == 0)
	eventCount++;
    } while(events.IsElm(eventCount));
    int nEvent = eventCount; 
    schedule.Insert(at,nEvent);
    events[nEvent] = se;
    holdLock.Unlock();
    ONDEBUG(cerr << "TimedTriggerQueueBodyC::Schedule() Event " << nEvent << " at " << at.Text() << " \n");
#if USE_NEW_TIMEDTRIGGERQUEUE
    semaSched.Post();
#else
    if(write(wfd,&nEvent,sizeof(IntT)) != sizeof(IntT))
      cerr << "TimedTriggerQueueBodyC::Schedule(), WARNING: Failed to write to schedule queue.  \n";
#endif
    return eventCount;
  }
  
  //: Process event queue.
  
  bool TimedTriggerQueueBodyC::Process() {
    ONDEBUG(cerr << "TimedTriggerQueueBodyC::Process(), Called. \n");
#if !USE_NEW_TIMEDTRIGGERQUEUE
    int reterr;
    struct timeval timeout;
    fd_set readSet;
    FD_ZERO(&readSet);
#endif
    MutexLockC holdLock(access);
    holdLock.Unlock();
    do {
      holdLock.Lock();
      // Are any events scheduled ??
      if(!schedule.IsElm()) { 
	ONDEBUG(cerr << "Waiting for event to be scheduled. Size:" << schedule.Size() << "\n");
	holdLock.Unlock();
#if !USE_NEW_TIMEDTRIGGERQUEUE
	FD_SET(rfd,&readSet);
	reterr = select(rfd+1,&readSet,0,0,0);
	// New events pending ?
	if(reterr > 0) { 
	  if(FD_ISSET(rfd,&readSet)) {
	    UIntT nevent;
	    if(read(rfd,&nevent,sizeof(UIntT)) != sizeof(UIntT))
	      cerr << "WARNING: TimedTriggerQueueBodyC::Process() Failed to read event queue. \n";
	  }
	}
#else
	semaSched.Wait();
#endif
	ONDEBUG(cerr << "Re-checking event queue.\n");
	continue; // Go back and check...
      }
      DateC nextTime = schedule.TopKey();
      DateC toGo = nextTime - DateC(true);
      ONDEBUG(cerr << "Next scheduled event in " << toGo.Double() << " seconds\n");
      if(toGo.Double() < 0.001) { // Might as well do it now...
	int eventNo = schedule.GetTop();
	ONDEBUG(cerr << "Executing event  " << eventNo << "\n");
	TriggerC ne = events[eventNo];
	events.Del(eventNo); // Remove from queue.
	holdLock.Unlock(); // Unlock before invoke the event, incase it wants to add another.
	if(ne.IsValid()) // Check if event has been canceled.
	  ne.Invoke();
	ONDEBUG(else cerr << "Event cancelled. \n");
	continue; // Check for more pending events.
      }
      holdLock.Unlock();
      // Wait for delay, or until a new event in scheduled.
#if !USE_NEW_TIMEDTRIGGERQUEUE
      FD_SET(rfd,&readSet);
      timeout.tv_sec = toGo.TotalSeconds();
      timeout.tv_usec = toGo.USeconds();
      reterr = select(rfd+1,&readSet,0,0,&timeout);
      if(reterr > 0) { // New events pending ?
	if(FD_ISSET(rfd,&readSet)) {
	  UIntT nevent;
	  if(read(rfd,&nevent,sizeof(UIntT)) != sizeof(UIntT))
	    cerr << "WARNING: TimedTriggerQueueBodyC::Process() Failed to read event queue. \n";
	}
      }
#else
      semaSched.Wait(toGo.Double());
#endif
      ONDEBUG(cerr << "Time to check things out.\n");
    } while(!done);
    return true;
   }
  
  //: Cancel pending event.
  // Will return TRUE if event in canceled before
  // it was run.
  
  bool TimedTriggerQueueBodyC::Cancel(UIntT eventID) {
    MutexLockC holdLock(access);
    if(!events.IsElm(eventID))
      return false;
    events[eventID].Invalidate(); // Cancel event.
    return true;
  }

}

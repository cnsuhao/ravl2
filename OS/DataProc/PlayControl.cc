// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlDPMT
//! file="Ravl/OS/DataProc/PlayControl.cc"

#include "Ravl/DP/PlayControl.hh"

#define FORCE_AT 0

#define DPDEBUG 0
#if DPDEBUG 
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Default constructor.
  
  DPPlayControlBodyC::DPPlayControlBodyC()
    : inc(1),
      ok(true),
      pause(false),
      sema(0),
      passEOS(true),
      start(0),
      end((UIntT) -1),
      playMode(0),
      subStart(0),
      subEnd(0),
      doneRev(false),
      at(0)
  {}
  
  //: Constructor.
  
  DPPlayControlBodyC::DPPlayControlBodyC(const DPSeekCtrlC &nCntrl,bool nPassEOS,UIntT nstart,UIntT nend)
    : inc(1),
      ok(true),
      pause(false),
      sema(0),
      ctrl(nCntrl),
      passEOS(nPassEOS),
      start(nstart),
      end(nend),
      playMode(0),
      subStart(1),
      subEnd(1),
      doneRev(false),
      at(nstart)
  {
    if(ctrl.IsValid()) {
      UIntT len =  ctrl.Size();
      if(end >= len) {
	if(len != ((UIntT) -1))
	  end = len -1;
	else 
	  end = len;
      }
      MutexLockC lock(access);
      if(start != ((UIntT) -1))
	ctrl.Seek(start);
      else
	start = ctrl.Start();
      at = ctrl.Tell();
    }
    if(start == ((UIntT) -1))
      start = 0;
    if(at == -1)
      at = 0;
    lastFrame = start;
    ONDEBUG(cerr << "Start : "<< start << " at:" << at<< " End:" << end <<"\n");
  }
  
  //: Open new video stream.
  // Access must be locked when calling this function.
  bool DPPlayControlBodyC::Open(const DPSeekCtrlC &nCntrl) {
    if(!nCntrl.IsValid())
      return false;
    inc = 1;
    ok = true;
    ctrl = nCntrl;
    // Preserve sequence limits ???
    start = ctrl.Start();
    at = start;
    ctrl.Seek(start);
    UIntT sSize = ctrl.Size();
    if(sSize != ((UIntT) -1))
      end = sSize -1;
    else
      end = sSize;
    return true;
  }
  
  //: Destructor.
  
  DPPlayControlBodyC::~DPPlayControlBodyC() {
    // Try and make sure anything wait on us is free to continue.
    passEOS = true;
    pause = false;
    while(!sema.TryWait())
      sema.Post();
    sema.Post(); // Then post one more.
  }
  
  
  //: Set increments.
  // 1 == Normal play 
  // -1=Reverse play 
  // 2=Double speed forward etc..
  
  IntT DPPlayControlBodyC::Speed(IntT ninc) { 
    inc = ninc;  
    return inc;
  }
  
  //: Where are we in the stream ?
  
  UIntT DPPlayControlBodyC::Tell() const { 
    RavlAssert(ctrl.IsValid());
#if FORCE_AT
    MutexLockC lock(access);
    UIntT ret =  ctrl.Tell();
    if((IntT) ret != at) {
      cerr << "WARNING: Position mismatch: At:" << at << " Actual:" << ret << "\n";
      const_cast<DPPlayControlBodyC &>(*this).at = ret;
    }
    // Unlock access here.
    return ret;
#else
    return at;
#endif
  }
  
  //: How long is the stream ?
  
  UIntT DPPlayControlBodyC::Size() const { 
    RavlAssert(ctrl.IsValid());
    MutexLockC lock(access);
    return ctrl.Size(); 
    // Unlock access here.
  }
  
  //: Seek to an absolute position in stream
  
  bool DPPlayControlBodyC::Seek(UIntT pos) { 
    RavlAssert(ctrl.IsValid());
    MutexLockC lock(access);
    IntT seekto = pos;
    
    // Compensate for 'inc'
    if(pos != end) {
      if(inc >= 1) {
	if(((seekto - inc) >= (int) start) && ((seekto -inc) <= (int)end))
	  seekto = pos - inc;
      } else {
	if((( seekto - (inc-1)) >= (int) start) && ((seekto -(inc-1)) <= (int)end))
	  seekto = pos - (inc-1);
      }
    } else
      inc = 1;
    
    // Do the seek.
    
    if(!ctrl.Seek(seekto)) {
      cerr << "WARNING: Seek to " << pos <<" failed. \n";
      return false;
    }
    ONDEBUG(cerr << "DPPlayControlBodyC::Seek(), Seek to :" << pos << " (Comp:" << seekto << ") Tell:" << ctrl.Tell() << "\n");
    at = seekto;
    if(pause) { // Make sure it gets displayed if we're paused.
      lock.Unlock();// Unlock access.
      if(sema.Count() < 1)
	sema.Post(); // Display at least one frame.
    }
    return true;
  }
  
  //: Pause playing.
  
  void DPPlayControlBodyC::Pause() { 
    ONDEBUG(cerr << "DPPlayControlBodyC::Pause(), Called\n");
    while(sema.Count() > 0) {
      if(!sema.TryWait())
	break;
    }
    pause = true; 
    ONDEBUG(cerr << "DPPlayControlBodyC::Pause(), Done. @" << ctrl.Tell() << "\n");
  }
  
  //: Continue playing.
  
  void DPPlayControlBodyC::Continue() { 
    if(!pause)
      return ;
    pause = false; 
    if(sema.Count() < 1)
      sema.Post();
  }
  
  //: Move 'frames' forward or backward.
  
  void DPPlayControlBodyC::Jog(IntT frames) {
    ONDEBUG(cerr << "DPPlayControlBodyC::Jog(), " << frames << "\n");
    if(!pause)
      Pause();
    //MutexLockC lock(access);
    inc = frames;
    //CheckUpdate();
    //lock.Unlock(); // Unlock access before post.
    if(sema.Count() < 1)
      sema.Post(); // Display at least one frame.
  }
  
  //: Check state of stream BEFORE get.
  // This assumes the input stream is locked by the calling function.
  
  bool DPPlayControlBodyC::CheckUpdate() {
    ONDEBUG(cerr << "-------------------------------\n@ " << at << " Mode=" << playMode <<  " Inc:" << inc << " Tell:" << ctrl.Tell() <<" End=" << end << "\n");
    bool ret = true;
#if FORCE_AT
    if(at != ctrl.Tell()) {
      cerr << "WARNING: Position mismatch: At:" << at << " Actual:" << ctrl.Tell() << "\n";    
      at = ctrl.Tell();
    }
#endif
    switch(playMode) 
      {
      case 0: break; // 0-Once through 
      case 1: // 1-Once through sub seq. 
	if(inc > 0) {
	  if(at >= subEnd) {
	    inc = 0; // Stop.
	    Pause();
	  }
	} else {
	  if(at < subStart) {
	    inc = 0; // Stop.
	    Pause();
	  }
	}
	break;
      case 2: // Loop.
	if(inc > 0) {
	  if(at > subEnd) {
	    if(!ctrl.Seek(subStart)) {
	      cerr << "WARNING: Seek to " << subStart <<" failed. \n";
	    } else
	      at = subStart;
	  }
	} else {
	  if(at < subStart) {
	    if(!ctrl.Seek(subEnd)) {
	      cerr << "WARNING: Seek to " << subEnd <<" failed. \n";
	    } else
	      at = subEnd;
	  }
	} 
	break;
      case 3: // Palindrome.
	if(inc > 0) {
	  if(at > subEnd && !doneRev) {
	    inc *= -1; // Reverse direction
	    doneRev = true;
	  } else
	    doneRev = false;
	} else {
	  if(at <= subStart && !doneRev) {
	    inc *= -1; // Reverse direction
	    doneRev = true;
	  } else
	    doneRev = false;
	}
	break;      
      }
    if(inc >= 1) {
      if((at + inc) <= ((IntT) end)) { // before end ?
	at += (inc-1);
	if(inc > 1) {
	  if(!ctrl.DSeek(inc-1)) {
	    cerr << "DSeek failed : " << inc -1 << "\n";
	    at = ctrl.Tell();
	  }
	}
      } else { 
	ONDEBUG(cerr << "Hit end : "<< at << " Inc:" << inc <<"\n");
	// Failed, hit end.
	if(end != ((UIntT) -1) && playMode < 2) {
	  if(!ctrl.Seek(end)) // Show last frame.
	    cerr << "Warning: Seek to end failed. \n";
	  at = end;
	  inc = 0;
	  Pause();
	}
      }
    } else {
      // inc is negative
      at += (inc-1);
      if((at + inc) >= ((IntT) start)) {
	if(!ctrl.DSeek(inc-1)) {
	  ONDEBUG(cerr << "DSeek failed : "<< at << "  Inc:" << inc-1 <<" Start@ " << start << "\n");
	}
      } else {
	ONDEBUG(cerr << "Hit start : "<< at << "  Inc:" << inc <<" Start@ " << start << "\n");
	if(start != ((UIntT) -1) && playMode < 2) {
	  if(!ctrl.Seek(start))
	    cerr << "Warning: Seek to start failed. \n";
	  at = start;
	  inc = 0;
	  Pause();
	}
      }
    }
    
    // Place will be incremented by next read.
    lastFrame = at++;
    // Check for last frame in sequence.
    if(lastFrame == (int) end)
      at = end;
    ONDEBUG(cerr << " Last frame :" << lastFrame << " Tell:" << ctrl.Tell() << " At:" << at << "\n");  
    return ret;
  }
  
  //: Goto beginning of sequence. (for GUI)
  
  void DPPlayControlBodyC::ToBeginning() {
    Speed(1);
    ONDEBUG(cerr << "DPPlayControlBodyC::ToBeginning(), Called. Start=" << start << " Mode=" << playMode << "\n");
    switch(playMode) {
    case 0:
      Seek(start);
      break;
    case 1: // Sub sequence.
    case 2: // Loop
    case 3: // Palindrome.
      Seek(subStart);
    default:
      Seek(start);
      break;
    }
  }
  
  //: Fast forward. (for GUI)
  
  void DPPlayControlBodyC::FastFwd() {
    Speed(4); 
    Continue();
  }
  
  //: Play forward. (for GUI)
  void DPPlayControlBodyC::PlayFwd() {
    Speed(1); 
    Continue();
  }
  
  //: Go forward 1 frame. (for GUI)
  
  void DPPlayControlBodyC::JogFwd()
  { Jog(1); }
  
  //: Stop (for GUI)
  
  void DPPlayControlBodyC::Stop() {
    Speed(0);
    Pause();
  }
  
  //: Go backward 1 frame. (for GUI)
  
  void DPPlayControlBodyC::JogBkw()
  { Jog(-1); }
  
  //: Play backward. (for GUI)
  
  void DPPlayControlBodyC::PlayBkw() {
    Speed(-1); 
    Continue();
  }
  
  //: Play backward. (for GUI)
  
  void DPPlayControlBodyC::FastBkw() {
    Speed(-4); 
    Continue();
  }
  
  //: Goto end of sequence. (for GUI)
  
  void DPPlayControlBodyC::ToEnd() {
    if(FixedEnd() == ((UIntT) -1)) 
      return ;
    Pause();  
    
    switch(playMode) {
    case 0:
      Seek(end);
      break;
    case 1: // Sub sequence.
    case 2: // Loop
    case 3: // Palindrome.
      Seek(subEnd);
    default:
      Seek(end);
      break;
    }
  }
  
  //: Goto position in sequence. (for GUI)
  void DPPlayControlBodyC::SeekTo(UIntT loc) {
    Seek(loc);
  }
  
  
  /////////////////////////////////////////////////
  //: Body constructor.
  
  DPPlayControlC::DPPlayControlC(const DPPlayControlBodyC &bod)
    : DPEntityC((DPPortBodyC &) bod)
  {}
  
}

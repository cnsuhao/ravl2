// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! rcsid="$Id: testTimedTriggerQueue.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/testTimedTriggerQueue.cc"
//! author="Charles Galambos"
//! docentry="Ravl.API.OS.Time"
//! userlevel=Develop

#include "Ravl/Threads/TimedTriggerQueue.hh"
#include "Ravl/Random.hh"
#include <math.h>

using namespace RavlN;

const int noTests = 10;

DateC when[noTests];

bool MarkTime(int &i) {
  when[i] = DateC(true); // Mark now.
  //  cerr << " i:" << i << "\n";
  return true;
}

const RealT maxTimerError = 0.04;

int main()
{
  cerr << "Running test... \n";
  TimedTriggerQueueC eventQueue(100);
  Sleep(0.01);  // Give event queue time to setup properly...
  DateC requestedTime[noTests];
  int i;
  for(i = 0;i < 10;i++) {
    requestedTime[i] = DateC(true) + Random1();    
    eventQueue.Schedule(requestedTime[i],Trigger(MarkTime,i));
  }
  Sleep(1.1);  // Wait for all events to take place.
  for(i = 0;i < 10;i++) {
    RealT diff = (requestedTime[i] - when[i]).Double();
    cerr << "Timing error:" << diff << "\n";
    if(fabs(diff) > maxTimerError) {
      cerr << "ERROR: Timing out of spec \n";
      return 1;
    }
  }
  cerr << "TEST PASSED.\n";
  return 0; 
}


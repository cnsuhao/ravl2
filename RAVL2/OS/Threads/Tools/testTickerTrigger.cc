// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id: testTickerTrigger.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/testTickerTrigger.cc"
//! docentry="Ravl.API.OS.Time"
//! author="Charles Galambos"
//! userlevel=Develop

#include "Ravl/Threads/TickerTrigger.hh"
#include "Ravl/Atomic.hh"
#include "Ravl/OS/DeadLineTimer.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

ravl_atomic_t callcount;

class ExampleC
{
public: 
  bool DoIt()
    {
      ravl_atomic_inc(&callcount);
      //cerr << "Done " << dec << atomic_read(&callcount) << ". \n";
      return true;
    }  
};

int main()
{

  cerr << "Starting tick test. \n";
  ravl_atomic_set(&callcount,0);
  
  ExampleC ae;
  
  TickerTrigger(0.2,ae,&ExampleC::DoIt);
  TickerTrigger(0.2,ae,&ExampleC::DoIt);
  
  cerr << "Waiting 10 seconds. \n";
  
  DeadLineTimerC dlt(10.0);
  dlt.WaitForIt();
  
  int result = ravl_atomic_read(&callcount);
  int targ = 100;
  cerr << "Result : " << result << "  Target:" << targ << "\n";
  
  if(result < (targ - 6) || result > (targ + 6)) {
    cerr << "Result out of range. \n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

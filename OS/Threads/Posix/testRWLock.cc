// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Posix/testRWLock.cc"

#include "Ravl/Threads/RWLock.hh"
#include "Ravl/Threads/Thread.hh"
#include "Ravl/Threads/Semaphore.hh"

#include <iostream.h>
#include <stdlib.h>
#include <assert.h>

using namespace RavlN;

RWLockC *ARWLock;
SemaphoreC *Done;

int Val1 = 0;
int Val2 = 0;
int Val3 = 0;

bool pass = true;

class RWLTestBodyC 
  : public ThreadBodyC 
{
public:
  RWLTestBodyC(int nNum) { Num = nNum; }

  virtual int Start(void);
private:
  int Num;
};

class RWLTestC 
  : public ThreadC 
{
public:
  RWLTestC(int nNum)
    : ThreadC(*new RWLTestBodyC(nNum))
    {}
};

int RWLTestBodyC::Start(void) {  
  for(;Num > 0;Num--) {
    if((rand() % 20) == 0) {      // Check old values.
      
      ARWLock->RdLock();
      if(Val1 != Val2)
	pass = false;
      if(Val2 != Val3)
	pass = false;
      Yield();
      if(Val1 != Val3)
	pass = false;
      Yield();
      if(Val1 != Val3)
	pass = false;
      ARWLock->UnlockRd();
      
    } else {
      
      ARWLock->WrLock();  // Write new values.
      Val1 = rand();
      Yield();
      Val2 = Val1;
      Yield();
      Val3 = Val2;
      Yield();
      ARWLock->UnlockWr();
      
    }
    Yield();
  }
  Done->Post();
  return 0;
}

static const int TestSize = 8;

int main() {
  int i;
  cerr << "Starting RWLock test. \n";
  
  Done = new SemaphoreC(0);
  ARWLock = new RWLockC();
  
  // Boil the RWLock for a bit.
  for(i = 0;i < TestSize;i++)
    RWLTestC(10000).Execute();
  
  for(i = 0;i < TestSize;i++) {
    Done->Wait();
    cerr << i << " \n";
  }
  
  if(pass) {
    cerr << "Test completed ok. \n";
    exit(0);
  }
  cerr << "ERROR in test.. \n";
  exit(1);
}

////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Threads/RWLock.hh"
#include "Ravl/MTLocks.hh"
#include <iostream.h>

void IncPThreadSysDBLock()
{}

using namespace PThread;

static const int noLocks = 2;

RWLockC posixDBRWLock[2];

static void CheckLockID(int &lockId) {
  if(lockId >= noLocks || lockId < 0) {
    cerr << "SysDBLockImpl.cc: Illegal lock selected " << lockId << "\n";
    lockId = 0;
  }
}

void DoPTSysDBReadLock(int lockId) 
{ 
  CheckLockID(lockId);
  posixDBRWLock[lockId].RdLock(); 
}

void DoPTSysDBWriteLock(int lockId)
{
  CheckLockID(lockId);
  posixDBRWLock[lockId].WrLock(); 
}

void DoPTSysDBUnlockRd(int lockId)
{ 
  CheckLockID(lockId);
  posixDBRWLock[lockId].UnlockRd();
}

void DoPTSysDBUnlockWr(int lockId)
{ 
  CheckLockID(lockId);
  posixDBRWLock[lockId].UnlockWr(); 
}

int DoPTSysGetThreadID() 
{
#if 0
  VThread *thrd = VThread::GetCurrentThread();
  if(thrd == 0)
    return 0; 
  return (int) thrd->GetID();
#else
  return -1;
#endif
}


// Install race resolution function into the refrence counting mechanism.

class PThreadInitC {
public:
  PThreadInitC()
  { 
    sysDBReadLock = DoPTSysDBReadLock;
    sysDBWriteLock = DoPTSysDBWriteLock;
    sysDBUnlockRd = DoPTSysDBUnlockRd;
    sysDBUnlockWr = DoPTSysDBUnlockWr;
  }
};

PThreadInitC doVThreadInitC;

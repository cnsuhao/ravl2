#ifndef VAM_BASE_HH
#define VAM_BASE_HH

#include "Ravl/Threads/MemoryItem.hh"
#include "Ravl/Threads/VamAccess.hh"

#include "Ravl/Threads/RWLock.hh"
#include "Ravl/Threads/ConditionalMutex.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

//! userlevel=Develop

//: Base body class for body of memory storage component
class VAMBodyBaseC : public RCBodyC 
{
 public:
  VAMBodyBaseC(const StringC MemName, int Verbosity);
  virtual ~VAMBodyBaseC();

  virtual void Add(const MemoryItemC& Item) = 0;
  //: Add item to memory.

  virtual void End() = 0;
  //: No more items to be added to this memory

  virtual VAMAccessC GetMemoryAccess(const StringC& Name, 
                                      const TimeCodeC& Start, 
                                      const TimeCodeC& End) = 0;
  //: Creates memory access. 
  //Name - unique name for access (usually name of the module which is trying to get access)
  //Start and End are boundaries for access

  void ReleaseMemoryAccess(const StringC& Name);
  //: Removes memory access from internal reference table 
  //Name - name of access

  virtual void ForgetUnwanted() = 0;
  //: Delete any unwanted items

  virtual void Clean(const TimeCodeC& Time) = 0;
  //: Delete elements up to time Time

  virtual void Dump() const = 0;
  //: Dump memory contents

  void RdLock(bool Lock) const
    { (Lock) ? lock.RdLock() : lock.UnlockRd(); }
  //: Lock / unlock memory for reading

  void SleepUnlocked() const;
  //: Sleep and unlock the memory in the meantime

  virtual void SaveTop(XMLOStreamC &Strm) const = 0;
  //: Save module entry in memory contents table

  virtual void SaveItem(const MemoryItemC& item) = 0;
  //: Save item to XML stream.
  
  virtual void Load(XMLIStreamC &Strm, const TimeCodeC& Start,
                    const TimeCodeC& End) = 0;
  //: Loads elements in memory from stream
  
  const StringC& MemoryName() const 
    { return memName; }  

  StringC& MemoryName()
    { return memName; }  

  bool WasLoaded() const
    { return wasLoaded; }

  bool ReadyForAccess() const
    { return memoryReadyForAccess; }

  virtual void Stop(bool StopFlag = true) = 0;

  bool AskedToStop() const
    { return askedToStop; }

  int GetVerbosityLevel() const 
    { return verbosity; }

  StringC& Attr(const StringC& AttrName)
    { return attr[AttrName]; }
    
 protected:
  StringC memName;  
  HashC<StringC, VAMAccessC> accesses; // table of access objects to the memory
  bool wasLoaded; // true if module was read from file (not computed in this session)
  bool memoryReadyForAccess;
  bool askedToStop;

  //  Alex: We need a description of this locking process.  Why 3 of them?
  mutable RWLockC lock; // to coordinate reading from and writing to memory
  mutable ConditionalMutexC sync; // to allow modules to wait for input
  mutable RWLockC accessesLock; // lock for accesses hash table
  int verbosity;
    
  RCHashC<StringC,StringC> attr; //memory attributes
};

enum MemTypeE { NoRamEC, VamAllInRamEC, VamInRamImOnDiskEC };

//! userlevel=Develop
//: The memory storage component of a MemModuleC
// Provides storage for time sequence of data, including:<ul>
//<li>  a list of time-stamped memory elements MemoryItemC</li>
//<li>  means of access by other modules</li>
//<li>  locking for shared memory access</li>
//</ul>

class VAMC : public RCHandleC<VAMBodyBaseC> 
{
 public:
  VAMC(const StringC& MemName, MemTypeE MemType, int Verbosity);

  VAMC(VAMBodyBaseC* body) : RCHandleC<VAMBodyBaseC>(body) 
    {}

  void Add(const MemoryItemC& Item)
    { BodyPtr()->Add(Item); }
  //: Add item to memory.

  void End()
    { BodyPtr()->End(); }
  //: No more items to be added to this memory

  VAMAccessC GetMemoryAccess(const StringC& Name, 
                              const TimeCodeC& Start, 
                              const TimeCodeC& End) 
    { return BodyPtr()->GetMemoryAccess(Name, Start, End); }
  //: Creates memory access. 

  void ReleaseMemoryAccess(const StringC& Name) 
    { BodyPtr()->ReleaseMemoryAccess(Name); }
  //: Removes memory access from internal reference table 
  // the access object could still exist but main memory will not care about it

  void ForgetUnwanted()
    { BodyPtr()->ForgetUnwanted(); }
  //: Delete any unwanted items

  void Clean(const TimeCodeC& Time = TimeCodeC(RavlConstN::maxInt, 50)) 
    { BodyPtr()->Clean(Time); }
  //: Delete elements up to time Time

  void Dump() const
    { BodyPtr()->Dump(); }
  //: Dump memory contents

  void RdLock(bool Lock) const
    { BodyPtr()->RdLock(Lock); }
  //: Lock / unlock memory for reading

  void SleepUnlocked() const
    { BodyPtr()->SleepUnlocked(); }
  //: Sleeps and unlocks the memory in the meantime

  void SaveTop(XMLOStreamC &Strm) const
    { BodyPtr()->SaveTop(Strm); }
  //: Save module entry in memory contents table

  void SaveItem(const MemoryItemC& item)
  {  BodyPtr()->SaveItem(item); }
  //: Save item to XML stream.
  
  void Load(XMLIStreamC &Strm, const TimeCodeC& Start, const TimeCodeC& End)
    { return BodyPtr()->Load(Strm, Start, End); }
  //: Loads elements in memory from stream
  // Start and End define read boundaries
  // Returns time code of first and last mem ements in Start and End
  
  const StringC& MemoryName() const 
    { return BodyPtr()->MemoryName(); };

  StringC MemoryName() 
    { return BodyPtr()->MemoryName(); };

  bool WasLoaded() const
    { return BodyPtr()->WasLoaded(); };

  bool ReadyForAccess() const
    { return BodyPtr()->ReadyForAccess(); }

  void Stop(bool StopFlag = true)
    { BodyPtr()->Stop(StopFlag); }

  bool AskedToStop() const
    { return BodyPtr()->AskedToStop(); }

  int GetVerbosityLevel() const
    { return BodyPtr()->GetVerbosityLevel(); };

  StringC Attr(const StringC& AttrName)
    { return BodyPtr()->Attr(AttrName); }
    
protected:  
  VAMBodyBaseC* BodyPtr()
    { return &Body(); }
  //: access proper Body though pointer not through reference!

  const VAMBodyBaseC* BodyPtr() const
    { return &Body(); }
  //: access proper Body though pointer not through reference!
};


#endif


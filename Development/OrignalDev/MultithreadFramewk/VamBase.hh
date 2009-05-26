#ifndef VAM_BASE_HH
#define VAM_BASE_HH

#include "Ravl/Threads/MemoryItem.hh"

#include "Ravl/Threads/RWLock.hh"
#include "Ravl/Threads/ConditionalMutex.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

class VAMAccessC;

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

  virtual VAMAccessC& GetMemoryAccess(const StringC& Name, 
                                      const TimeCodeC& Start, 
                                      const TimeCodeC& End) = 0;
  //: Creates memory access. 
  //Name - uniqe name for access (usually name of the module which is trying to get access)
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
  VAMC(const StringC& MemName, MemTypeE MemType, const StringC& Param,
       int Verbosity);

  VAMC(VAMBodyBaseC* body) : RCHandleC<VAMBodyBaseC>(body) 
    {}

  void Add(const MemoryItemC& Item)
    { BodyPtr()->Add(Item); }
  //: Add item to memory.

  void End()
    { BodyPtr()->End(); }
  //: No more items to be added to this memory

  VAMAccessC& GetMemoryAccess(const StringC& Name, 
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

  StringC& MemoryName() 
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

  StringC& Attr(const StringC& AttrName)
    { return BodyPtr()->Attr(AttrName); }
    
protected:  
  VAMBodyBaseC* BodyPtr()
    { return &Body(); }
  //: access proper Body though pointer not through reference!

  const VAMBodyBaseC* BodyPtr() const
    { return &Body(); }
  //: access proper Body though pointer not through reference!
};

//! userlevel=Develop
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//: Body for VAMAccessC
class VAMAccessBodyBaseC : public RCBodyC
{
public:
  VAMAccessBodyBaseC(const TimeCodeC& Start, const TimeCodeC& End, bool Eof = false) 
    : startTc(Start), endTc(End), eof(Eof)
    {}
  //: constructor
  // Start and End are the boundaries for access

  virtual ~VAMAccessBodyBaseC() 
    {};

  virtual VAMAccessBodyBaseC* Copy() const = 0;
  //: make a copy of access

  void SetBounds(const TimeCodeC& Start, const TimeCodeC& End);
  //: changes bounds of memory access
  // This moves poiter to time Start

  virtual const MemoryItemC& Peek() const = 0;
  //: returns current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  virtual const DurationC& PeekDuration() const = 0;
  //: returns duration of current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid values if there is no current item

  virtual StringC PeekInfo() const = 0;
  //: returns string information about current memory item

  virtual const MemoryItemC& Get() = 0;
  //: Move memory pointer to next item and returns the item
  // Waits until item is available

  virtual const DurationC& GetDuration() = 0;
  //: Move memory pointer to next item and returns its duraion
  // Waits until item is available

  virtual const MemoryItemC& Get(const TimeCodeC& Tc) = 0;
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // Waits until item is available

  virtual const DurationC& GetDuration(const TimeCodeC& Tc) = 0;
  //: Move memory pointer to next item after time Tc (item.Start() could be == Tc)
  // and returns its duraion.
  // Waits until item is available

  virtual const MemoryItemC& GetNoWait() = 0;
  //: Gets next item from memory
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  virtual const DurationC& GetNoWaitDuration() = 0;
  //: Same as GetDuration(), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  virtual const MemoryItemC& GetNoWait(const TimeCodeC& Tc) = 0;
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  virtual const DurationC& GetNoWaitDuration(const TimeCodeC& Tc) = 0;
  //: Same as GetDuration(const TimeCodeC& Tc), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  virtual const TimeCodeC& Tell() const = 0; 
  //: returns time of last accessed memory element
  //this fuction can be called from different threads for same object
  //possibly needs locking
  
  //------------------------------- iterator movement functions --------------------------
  virtual bool MoveToFirst(bool NoWait) = 0;
  //:moves iterator to first element
  //returns true if movement was successful
  
  virtual bool MoveTo(const TimeCodeC& Tc, bool NoWait) = 0;
  //: moves iterator to certain time
  //returns true if movement was successful
  
  virtual bool Next(bool NoWait) = 0;
  //:moves iterator to next item
  //returns true if movement was successful
  
  virtual bool Prev() = 0;
  //:moves iterator to prev item
  //returns true if movement was successful
  
  //------------------------------- data access functions --------------------------------
  virtual const MemoryItemC& operator*() const = 0;
  //:access to current item
  
  virtual const MemoryItemC* operator->() const = 0;
  //:access to current item
  
  virtual const DurationC& ItemDuration() const = 0;
  //:duration of current item
  
  bool Eof() const
    { return eof; }
  //: true then the end of file element is reached
protected:
  TimeCodeC startTc, endTc; 
  //: time constraints for the memory access
  bool eof;
};

//! userlevel=Normal
//: Provides thread-safe read-only access to another module's memory
// Needs to be a separate class from VAMC, to allow for multiple access.
// In fact it is iterator through memory.
class VAMAccessC : public RCHandleC<VAMAccessBodyBaseC> 
{
public:
  VAMAccessC() : RCHandleC<VAMAccessBodyBaseC>(NULL) 
    {}
  //: Default constructor makes incorrect object

  VAMAccessC(VAMAccessBodyBaseC* body) : RCHandleC<VAMAccessBodyBaseC>(body) 
    {}

  VAMAccessC Copy() const
    { return VAMAccessC(BodyPtr()->Copy()); }
  //: copy

  void SetBounds(const TimeCodeC& Start, const TimeCodeC& End)
    { BodyPtr()->SetBounds(Start, End); }
  //: changes bounds of memory access
  // This moves pointer to time Start

  void SetBounds(const DurationC& Duration)
    { BodyPtr()->SetBounds(Duration.Start(), Duration.End()); }
  //: changes bounds of memory access
  // This moves pointer to time Start
  
  const MemoryItemC& Peek() const
    { return BodyPtr()->Peek(); }
  //: returns current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  const DurationC& PeekDuration() const
    { return BodyPtr()->PeekDuration(); }
  //: returns duration of current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid values if there is no current item

  StringC PeekInfo() const
    { return BodyPtr()->PeekInfo(); }
  //: returns string information about current memory item

  const MemoryItemC& Get() 
    { return BodyPtr()->Get(); }
  //: Gets next item from memory
  // Waits until item is available

  const DurationC& GetDuration()
    { return BodyPtr()->GetDuration(); }
  //: Move memory pointer to next item and returns its duraion
  // Waits until item is available

  const MemoryItemC& Get(const TimeCodeC& Tc)
    { return BodyPtr()->Get(Tc); }
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // Waits until item is available

  const DurationC& GetDuration(const TimeCodeC& Tc) 
    { return BodyPtr()->GetDuration(Tc); }
  //: Move memory pointer to next item after time Tc (item.Start() could be == Tc)
  // and returns its duraion.
  // Waits until item is available

  const MemoryItemC& GetNoWait()
    { return BodyPtr()->GetNoWait(); }
  //: Gets next item from memory
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  const DurationC& GetNoWaitDuration()
    { return BodyPtr()->GetNoWaitDuration(); }
  //: Same as GetDuration(), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  const MemoryItemC& GetNoWait(const TimeCodeC& Tc)
    { return BodyPtr()->GetNoWait(Tc); }
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  const DurationC& GetNoWaitDuration(const TimeCodeC& Tc)
    { return BodyPtr()->GetNoWaitDuration(Tc); }
  //: Same as GetDuration(const TimeCodeC& Tc), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  const TimeCodeC& Tell() const 
    { return BodyPtr()->Tell(); }
  //: returns time of last accessed memory element

  //------------------------------- iterator movement functions --------------------------
  bool MoveToFirst(bool NoWait)
    { return BodyPtr()->MoveToFirst(NoWait); }
  //:moves iterator to first element
  //returns true if movement was successful
  
  bool MoveTo(const TimeCodeC& Tc, bool NoWait)
    { return BodyPtr()->MoveTo(Tc, NoWait); }
  //: moves iterator to certain time
  //returns true if movement was successful
  
  bool Next(bool NoWait)
    { return BodyPtr()->Next(NoWait); }
  //:moves iterator to next item
  //returns true if movement was successful
  
  bool Prev()
    { return BodyPtr()->Prev(); }
  //:moves iterator to prev item
  //returns true if movement was successful
  
  //------------------------------- data access functions --------------------------------
  const MemoryItemC& operator*() const
    { return BodyPtr()->operator*(); }
  //:access to current item
  
  const MemoryItemC* operator->() const
    { return BodyPtr()->operator->(); }
  //:access to current item
  
  const DurationC& ItemDuration() const
    { return BodyPtr()->ItemDuration(); }
  //:duration of current item
  
  bool Eof() const
    { return BodyPtr()->Eof(); }
  //: true then the end of file element is reached

  long LongBodyPtr() const
    { return long(BodyPtr()); }// for debugging only
protected:
  VAMAccessBodyBaseC* BodyPtr()
    { return &Body(); }
  //: access proper Body though pointer not through reference!

  const VAMAccessBodyBaseC* BodyPtr() const
    { return &Body(); }
  //: access proper Body though pointer not through reference!
};


//! userlevel=Develop
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//: Provides thread-safe read-only access to several modules memory
// In fact it is several VAMAccessC classes
class VAMJointAccessBodyC : public RCBodyC 
{
public:
  VAMJointAccessBodyC() 
    : eof(false), curStart(-1, 50), curEnd(-1, 50), startTc(-1, 50), endTc(-1, 50)
    {}
  //: constructor

  virtual ~VAMJointAccessBodyC() 
    {};

  void SetBounds(const TimeCodeC& Start, const TimeCodeC& End);
  //: changes bounds of memory access
  // This moves pointer to time Start

  void AddAccess(const StringC& AccName, VAMAccessC& Access);
  //:Add access to managed set of accesses

  void RemoveAccess(const StringC& AccName);
  //:Remove access from set

  const MemoryItemC& Peek(const StringC& AccName) const;
  //: returns current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  StringC PeekInfo(const StringC& AccName) const;
  //: returns string information about current memory item

  const TimeCodeC& Tell() const
    { return curStart; }
  //: returns start time of last accessed memory element
  //this fuction can be called from different threads for same object
  //possibly needs locking
  
  //------------------- iterator movement functions --------------------------
  bool MoveToFirst(bool NoWait);
  //:moves iterator to first element
  //returns true if movement was successful
  
  bool MoveTo(const TimeCodeC& Tc, bool NoWait);
  //: moves iterator to certain time
  //returns true if movement was successful
  
  bool Next(bool NoWait);
  //:moves iterator to next item
  //returns true if movement was successful
  
  bool Prev();
  //:moves iterator to prev item
  //returns true if movement was successful
  
  //------------------------------- data access functions --------------------------------
  const MemoryItemC& operator[](const StringC& AccName) const
    { return Peek(AccName); }
  //:access to current item
  
  bool Eof() const
    { return eof; }
  //: true then the end of file element is reached in one of mem acceses
protected:
  RCHashC<StringC, VAMAccessC> accTable;
  bool eof;
  TimeCodeC curStart, curEnd;
  TimeCodeC startTc, endTc;
};

//! userlevel=Normal
//: Provides synchronised, thread-safe read-only access to several modules memory
// <p> This is an iterator to index jointly through several other memory modules in parallel.  It is synchronised in that it will only return memory items that have the same timecode.  It skips over any other items.</p>
// <p> Where items have durations of more than one frame, and there is only partial temporal overlap between the various items, it is currently not clear what gets returned.</p>

class VAMJointAccessC : public RCHandleC<VAMJointAccessBodyC> 
{
public:
  VAMJointAccessC() : RCHandleC<VAMJointAccessBodyC>(new VAMJointAccessBodyC())
    {}
  //: constructor

  ~VAMJointAccessC() 
    {};

  void SetBounds(const TimeCodeC& Start, const TimeCodeC& End)
    { Body().SetBounds(Start, End); }
  //: changes bounds of memory access
  // This moves pointer to time Start

  void SetBounds(const DurationC& Duration)
    { Body().SetBounds(Duration.Start(), Duration.End()); }
  //: changes bounds of memory access
  // This moves pointer to time Start
  
  void AddAccess(const StringC& AccName, VAMAccessC& Access)
    { Body().AddAccess(AccName, Access); }
  //:Add access to managed set of accesses

  void RemoveAccess(const StringC& AccName)
    { Body().RemoveAccess(AccName); }
  //:Remove access from set

  const MemoryItemC& Peek(const StringC& AccName) const
    { return Body().Peek(AccName); }
  //: returns current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  StringC PeekInfo(const StringC& AccName) const
    { return Body().PeekInfo(AccName); }
  //: returns string information about current memory item

  const TimeCodeC& Tell() const
    { return Body().Tell(); }
  //: returns start time of last accessed memory element
  //this fuction can be called from different threads for same object
  //possibly needs locking
  
  //------------------- iterator movement functions --------------------------
  bool MoveToFirst(bool NoWait)
    { return Body().MoveToFirst(NoWait); }
  //:moves iterator to first element
  //returns true if movement was successful
  
  bool MoveTo(const TimeCodeC& Tc, bool NoWait)
    { return Body().MoveTo(Tc, NoWait); }
  //: moves iterator to certain time
  //returns true if movement was successful
  
  bool Next(bool NoWait)
    { return Body().Next(NoWait); }
  //:moves iterator to next item
  //returns true if movement was successful
  
  bool Prev()
    { return Body().Prev(); }
  //:moves iterator to prev item
  //returns true if movement was successful
  
  //------------------------------- data access functions --------------------------------
  const MemoryItemC& operator[](const StringC& AccName) const
    { return Body().operator[](AccName); }
  //:access to current item
  
  bool Eof() const
    { return Body().Eof(); }
  //: true then the end of file element is reached in one of mem acceses
protected:
};

#endif


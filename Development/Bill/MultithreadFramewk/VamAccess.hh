#ifndef VAM_ACCESS_HH
#define VAM_ACCESS_HH

#include "Ravl/Threads/MemoryItem.hh"

#include "Ravl/Threads/RWLock.hh"
#include "Ravl/Threads/ConditionalMutex.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

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
  // This moves pointer to time Start

  virtual const MemoryItemC Peek() const = 0;
  //: returns current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  virtual const DurationC PeekDuration() const = 0;
  //: returns duration of current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid values if there is no current item

  virtual StringC PeekInfo() const = 0;
  //: returns string information about current memory item

  virtual const MemoryItemC Get() = 0;
  //: Move memory pointer to next item and returns the item
  // Waits until item is available

  virtual const DurationC GetDuration() = 0;
  //: Move memory pointer to next item and returns its duraion
  // Waits until item is available

  virtual const MemoryItemC Get(const TimeCodeC& Tc) = 0;
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // Waits until item is available

  virtual const DurationC GetDuration(const TimeCodeC& Tc) = 0;
  //: Move memory pointer to next item after time Tc (item.Start() could be == Tc)
  // and returns its duration.
  // Waits until item is available

  virtual const MemoryItemC GetNoWait() = 0;
  //: Gets next item from memory
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  virtual const DurationC GetNoWaitDuration() = 0;
  //: Same as GetDuration(), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  virtual const MemoryItemC GetNoWait(const TimeCodeC& Tc) = 0;
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  virtual const DurationC GetNoWaitDuration(const TimeCodeC& Tc) = 0;
  //: Same as GetDuration(const TimeCodeC& Tc), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  virtual const TimeCodeC Tell() const = 0; 
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
  virtual const MemoryItemC operator*() const = 0;
  //:access to current item
  
  virtual const MemoryItemC* operator->() const = 0;
  //:access to current item
  
  virtual const DurationC ItemDuration() const = 0;
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
  
  const MemoryItemC Peek() const
    { return BodyPtr()->Peek(); }
  //: returns current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  const DurationC PeekDuration() const
    { return BodyPtr()->PeekDuration(); }
  //: returns duration of current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid values if there is no current item

  StringC PeekInfo() const
    { return BodyPtr()->PeekInfo(); }
  //: returns string information about current memory item

  const MemoryItemC Get() 
    { return BodyPtr()->Get(); }
  //: Gets next item from memory
  // Waits until item is available

  const DurationC GetDuration()
    { return BodyPtr()->GetDuration(); }
  //: Move memory pointer to next item and returns its duraion
  // Waits until item is available

  const MemoryItemC Get(const TimeCodeC& Tc)
    { return BodyPtr()->Get(Tc); }
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // Waits until item is available

  const DurationC GetDuration(const TimeCodeC& Tc) 
    { return BodyPtr()->GetDuration(Tc); }
  //: Move memory pointer to next item after time Tc (item.Start() could be == Tc)
  // and returns its duraion.
  // Waits until item is available

  const MemoryItemC GetNoWait()
    { return BodyPtr()->GetNoWait(); }
  //: Gets next item from memory
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  const DurationC GetNoWaitDuration()
    { return BodyPtr()->GetNoWaitDuration(); }
  //: Same as GetDuration(), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  const MemoryItemC GetNoWait(const TimeCodeC& Tc)
    { return BodyPtr()->GetNoWait(Tc); }
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  const DurationC GetNoWaitDuration(const TimeCodeC& Tc)
    { return BodyPtr()->GetNoWaitDuration(Tc); }
  //: Same as GetDuration(const TimeCodeC& Tc), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  const TimeCodeC Tell() const 
    { return BodyPtr()->Tell(); }
  //: returns time of last accessed memory element

  //------------------------------- iterator movement functions --------------------------
  bool MoveToFirst(bool NoWait=false)
    { return BodyPtr()->MoveToFirst(NoWait); }
  //:moves iterator to first element
  //returns true if movement was successful
  
  bool MoveTo(const TimeCodeC& Tc, bool NoWait=false)
    { return BodyPtr()->MoveTo(Tc, NoWait); }
  //: moves iterator to certain time
  //returns true if movement was successful
  
  bool Next(bool NoWait=false)
    { return BodyPtr()->Next(NoWait); }
  //:moves iterator to next item
  //returns true if movement was successful
  
  bool Prev()
    { return BodyPtr()->Prev(); }
  //:moves iterator to prev item
  //returns true if movement was successful
  
  //------------------------------- data access functions --------------------------------
  const MemoryItemC operator*() const
    { return BodyPtr()->operator*(); }
  //:access to current item
  
  const MemoryItemC* operator->() const
    { return BodyPtr()->operator->(); }
  //:access to current item
  
  const DurationC ItemDuration() const
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
  VAMJointAccessBodyC() :
    eof(false),
    curStart(-1, 50), curEnd(-1, 50),
    startTc(0, 50),   endTc(RavlConstN::maxInt, 50)
    {}
  //: Constructor
  // Sets current permitted access interval to be "forever"

  virtual ~VAMJointAccessBodyC() 
    {};

  void AddAccess(const StringC& AccName, VAMAccessC& Access);
  //: Add access to managed set of accesses

  void RemoveAccess(const StringC& AccName);
  //: Remove access from set

  const MemoryItemC Peek(const StringC& AccName) const;
  //: Returns current memory item without changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  StringC PeekInfo(const StringC& AccName) const;
  //: returns string information about current memory item

  const TimeCodeC Tell() const
    { return curStart; }
  //: returns start time of last accessed memory element
  
  DurationC Duration() const
    { return DurationC(curStart,curEnd); }
  //: Duration of current joint intersection

  //:-------------------------------
  //: Iterator movement functions

  void SetBounds(const TimeCodeC& Start, const TimeCodeC& End);
  //: Sets bounds of memory access
  // This moves pointer to first intersection starting at or after <code>Tc</code>.

  bool MoveToFirst();
  //: Moves iterator to first element within current time bounds
  // Returns true if movement was successful
  
  bool MoveTo(const TimeCodeC& Tc);
  //: Moves iterator to certain time
  // Moves to first intersection starting at or after <code>Tc</code>.
  // Returns true if movement was successful
  
  bool Next();
  //: Moves iterator to next item
  // Returns true if movement was successful
  // Note that the next intersection <i>may</i> include one or
  // more (but not all) of the current accesses.<br>
  
  bool Prev();
  //: Moves iterator to prev item
  //returns true if movement was successful
  
  //:-------------------------------
  //: Data access functions

  const MemoryItemC operator[](const StringC& AccName) const
    { return Peek(AccName); }
  //: Access to current item
  
  bool Eof() const
    { return (   (curStart < startTc)
              || (curEnd > endTc)
              || (curEnd < curStart)
              || eof); }
  //: True if current element is not within current valid time interval


protected:
  RCHashC<StringC, VAMAccessC> accTable;
  bool eof;
  TimeCodeC curStart, curEnd; // duration of current joint access (intersection of all accesses, I guess??)
  TimeCodeC startTc, endTc;   // duration of current scope for which access is permitted

  class JointAccExceptionC : public ExceptionC {
    public:
    JointAccExceptionC() : ExceptionC("Getting next item failed")
      {}
  };

  void getNext(VAMAccessC& acc);
  //: Wrapper for conditions around successful getting of next individual access
  // Maybe should be subsumed into VAMAccessC::Next()??
  // Throws JointAccExceptionC on failure

  bool NextIntersection();
  //: Finds next set of jointly intersecting items
  // Does not move pointer if currently in non-empty intersection
  // Returns true if non-empty intersection is found.

};

//! userlevel=Normal
//: Provides synchronised, thread-safe read-only access to several modules memory
// <p> This is an iterator to index jointly through several other memory modules in parallel.  It is synchronised in that it will only return memory items that have jointly intersecting timecodes.  It skips over any other items.</p>

class VAMJointAccessC : public RCHandleC<VAMJointAccessBodyC> 
{
public:
  VAMJointAccessC() : RCHandleC<VAMJointAccessBodyC>(new VAMJointAccessBodyC())
    {}
  //: Constructor
  // Sets current permitted access interval to be "forever"

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

  const MemoryItemC Peek(const StringC& AccName) const
    { return Body().Peek(AccName); }
  //: returns current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  StringC PeekInfo(const StringC& AccName) const
    { return Body().PeekInfo(AccName); }
  //: returns string information about current memory item

  const TimeCodeC Tell() const
    { return Body().Tell(); }
  //: returns start time of last accessed memory element
  //this fuction can be called from different threads for same object
  //possibly needs locking
  
  DurationC Duration() const
    { return Body().Duration(); }
  //: Duration of current joint intersection

  //:-------------------------------
  //: Iterator movement functions

  bool MoveToFirst()
    { return Body().MoveToFirst(); }
  //: Moves iterator to first element
  // Returns true if movement was successful
  
  bool MoveTo(const TimeCodeC& Tc)
    { return Body().MoveTo(Tc); }
  //: Moves iterator to first intersection at or after <code>Tc</code>
  // Returns true if movement was successful
  
  bool Next()
    { return Body().Next(); }
  //: Moves iterator to next intersecting item
  // Returns true if movement was successful
  // Note that the next intersection <i>may</i> include one or
  // more (but not all) of the current accesses.<br>
  
  bool Prev()
    { return Body().Prev(); }
  //: Moves iterator to previous intersecting item
  // Returns true if movement was successful
  
  //:-------------------------------
  //: Data access functions

  const MemoryItemC operator[](const StringC& AccName) const
    { return Body().operator[](AccName); }
  //:access to current item
  
  bool Eof() const
    { return Body().Eof(); }
  //: True if not within current valid time interval

protected:
};




#endif


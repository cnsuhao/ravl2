#ifndef VAM_ALL_IN_RAM_HH
#define VAM_ALL_IN_RAM_HH

#include "Ravl/Threads/VamBase.hh"

#include "Ravl/DList.hh"
#include "Ravl/CDLIter.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

//! userlevel=Develop
//: in-RAM implementation of a memory body
class VAMAllInRamBodyC : public VAMBodyBaseC 
{
public:
  VAMAllInRamBodyC(const StringC& MemName, const StringC& SavePrefix, 
                   int Verbosity) : 
    VAMBodyBaseC(MemName, Verbosity) 
    { savePrefix = SavePrefix; };

  void Add(const StringC& Name, const TimeCodeC& Start, const TimeCodeC& End, 
           const MemoryAttributesC& Attrs, const ImageC<ByteRGBValueC>& Frame);
  //: Adds item to memory as before, but with name other than memory name.

  void End();
  //: No more items to be added to this memory

  VAMAccessC& GetMemoryAccess(const StringC& Name, 
                              const TimeCodeC& Start, 
                              const TimeCodeC& End);
  //: Creates memory access. 

  void ForgetUnwanted();
  //: Delete any unwanted items

  void Clean(const TimeCodeC& Time);		
  //: Delete elements up to time Time

  void Dump() const;
  //: Dump memory contents

  virtual void Save(ostream &strm) const;
  //: Saves all current elements in memory into stream

  virtual void Save(XMLOStreamC &Strm) const;
  //: Saves all current elements in memory into stream

  virtual void Load(XMLIStreamC &strm, TimeCodeC& Start, TimeCodeC& End);
  //: Loads elements in memory from stream
  
private:
  DListC<MemoryItemC> items;
  StringC savePrefix; // prefix for saving images
};

//-----------------------------------------------------------------------------
class VAMAccessAllInRamBodyC : public VAMAccessBodyBaseC
{
public:
  VAMAccessAllInRamBodyC(const VAMBodyBaseC* VamBodyPtr, 
                         const DListC<MemoryItemC>& Items,
                         const TimeCodeC& Start, 
                         const TimeCodeC& End);
  //: constructor

  virtual ~VAMAccessAllInRamBodyC() 
    {};
  //: destructor

  virtual MemoryItemC Peek() const 
    { return curItem; }
  //: returns current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  virtual DurationC PeekDuration() const
    { return curItem.Duration(); }
  //: returns duration of current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid values if there is no current item

  StringC PeekInfo() const
    { return curItem.Dump(true); }
  //: returns string information about current memory item

  virtual MemoryItemC Get();
  //: Move memory pointer to next item and returns the item
  // Waits until item is available

  virtual DurationC GetDuration();
  //: Move memory pointer to next item and returns its duraion
  // Waits until item is available

  virtual MemoryItemC Get(const TimeCodeC& Tc);
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // Waits until item is available

  virtual DurationC GetDuration(const TimeCodeC& Tc);
  //: Move memory pointer to next item after time Tc (item.Start() could be == Tc)
  // and returns its duraion.
  // Waits until item is available

  virtual MemoryItemC GetNoWait();
  //: Gets next item from memory
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  virtual DurationC GetNoWaitDuration();
  //: Same as GetDuration(), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  virtual MemoryItemC GetNoWait(const TimeCodeC& Tc);
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  virtual DurationC GetNoWaitDuration(const TimeCodeC& Tc);
  //: Same as GetDuration(const TimeCodeC& Tc), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  virtual const TimeCodeC& Tell() const
    { return curItem.Start(); }
  //: returns time of last accessed memory element
  //this fuction can be called from different threads for same object
  //possibly needs locking
private:
  ConstDLIterC<MemoryItemC> iter; // points to previous item
  MemoryItemC curItem;
  const VAMBodyBaseC* vamBodyPtr; // pointer to memory (for lock/unlock operations)

  void PrepareGet();
  void PrepareGet(const TimeCodeC& Tc);
  void PrepareGetNoWait();
  void PrepareGetNoWait(const TimeCodeC& Tc);
};

#endif


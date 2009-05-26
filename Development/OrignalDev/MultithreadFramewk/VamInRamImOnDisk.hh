#ifndef VAM_IN_RAM_IM_ON_DISK_HH
#define VAM_IN_RAM_IM_ON_DISK_HH

#include "Ravl/Threads/VamBase.hh"
#include "Ravl/Threads/MemoryItemXMLdisk.hh"

#include "Ravl/DList.hh"
#include "Ravl/CDLIter.hh"
#include "Ravl/Tuple3.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

//! userlevel=Develop
//: in-RAM implementation of a memory body image stored on disk
class VAMInRamImOnDiskBodyC : public VAMBodyBaseC 
{
public:
  VAMInRamImOnDiskBodyC(const StringC& MemName, const StringC& SavePrefix,
                        int Verbosity);

  virtual ~VAMInRamImOnDiskBodyC();

  void Add(const MemoryItemC& Item);
  //: Add item to memory.

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

  virtual void Stop(bool StopFlag = true);
  //: Set flag for module to pick up and stop

  virtual void SaveTop(XMLOStreamC &Strm) const;
  //: Save module entry in memory contents table

  void SaveItem(const MemoryItemC& item);
  //: Save item to XML stream.
  
  virtual void Load(XMLIStreamC &Strm, const TimeCodeC& Start, const TimeCodeC& End);
  //: Loads elements in memory from stream
  
private: 
  DListC<MemoryItemC> items;
  StringC savePrefix;        // prefix for saving images
  XMLOStreamC xmlStream;     // stream for XML output
  bool xmlStreamOpen;        // flag xmlStream is open (IsOpen method does not work) 
  StringC xmlFileName;       // name of the XML file to read/write items from/to
  TimeCodeC loadStart, loadEnd;
  void LoadItems();          // read items from file
  void OpenXMLStream();      // prepare XML stream
};

//-----------------------------------------------------------------------------
class VAMAccessInRamImOnDiskBodyC : public VAMAccessBodyBaseC
{
public:
  VAMAccessInRamImOnDiskBodyC(const VAMBodyBaseC* VamBodyPtr,
                              const DListC<MemoryItemC>& Items,
                              const TimeCodeC& Start, const TimeCodeC& End);
  //: constructor

  virtual ~VAMAccessInRamImOnDiskBodyC() 
    {};

  virtual VAMAccessBodyBaseC* Copy() const;
  //: make a copy of access

  virtual const MemoryItemC& Peek() const;
  //: returns current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid item if there is no current one

  virtual const DurationC& PeekDuration() const;
  //: returns duration of current memory item whithout changing memory pointer
  // Does not wait for item. Returns invalid values if there is no current item

  virtual StringC PeekInfo() const;
  //: returns string information about current memory item

  virtual const MemoryItemC& Get();
  //: Move memory pointer to next item and returns the item
  // Waits until item is available

  virtual const DurationC& GetDuration();
  //: Move memory pointer to next item and returns its duraion
  // Waits until item is available

  virtual const MemoryItemC& Get(const TimeCodeC& Tc);
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // Waits until item is available

  virtual const DurationC& GetDuration(const TimeCodeC& Tc);
  //: Move memory pointer to next item after time Tc (item.Start() could be == Tc)
  // and returns its duraion.
  // Waits until item is available

  virtual const MemoryItemC& GetNoWait();
  //: Gets next item from memory
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  virtual const DurationC& GetNoWaitDuration();
  //: Same as GetDuration(), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  virtual const MemoryItemC& GetNoWait(const TimeCodeC& Tc);
  //: Gets next item after time Tc from memory (item.Start() could be == Tc)
  // This "get" does not wait.  If an item is available it returns it; 
  // otherwise it returns an invalid memory item.

  virtual const DurationC& GetNoWaitDuration(const TimeCodeC& Tc);
  //: Same as GetDuration(const TimeCodeC& Tc), but the function does not wait for the item
  // If an item is available it returns its duration; 
  // otherwise it returns an invalid duration.

  virtual const TimeCodeC& Tell() const
    { return curItem.Start(); }
  //: returns time of last accessed memory element
  //this fuction can be called from different threads for same object
  //possibly needs locking
  
  //------------------------------- iterator movement functions --------------------------
  virtual bool MoveToFirst(bool NoWait);
  //:moves iterator to first element
  //returns true if movement was successful
  
  virtual bool MoveTo(const TimeCodeC& Tc, bool NoWait);
  //: moves iterator to certain time
  //returns true if movement was successful
  
  virtual bool Next(bool NoWait);
  //:moves iterator to next item
  //returns true if movement was successful
  
  virtual bool Prev();
  //:moves iterator to prev item
  //returns true if movement was successful
  
  //------------------------------- data access functions --------------------------------
  virtual const MemoryItemC& operator*() const;
  //:access to current item
  
  virtual const MemoryItemC* operator->() const;
  //:access to current item
  
  virtual const DurationC& ItemDuration() const;
  //:duration of current item
  
private:
  VAMAccessInRamImOnDiskBodyC(const TimeCodeC& Start, const TimeCodeC& End,
                              const bool Eof, const ConstDLIterC<MemoryItemC>& Iter,
                              const MemoryItemC& CurItem, const VAMC& Vam);
  void PrepareGet();
  void PrepareGetNoWait();

  ConstDLIterC<MemoryItemC> iter; // points to current item. 
                                  // the only case it points to previous item
                                  // then curItem is invalid
  MemoryItemC curItem;
  //const VAMBodyBaseC* vamBodyPtr; // pointer to memory (for lock/unlock operations)
  const VAMC vam;                 // reference counted memory storage
};

#endif

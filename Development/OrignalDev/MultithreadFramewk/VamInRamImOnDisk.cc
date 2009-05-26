#include "Ravl/Threads/VamInRamImOnDisk.hh"

#include "Ravl/IO.hh"
#include "Ravl/CDLIter.hh"


//-----------------------------------------------------------------------------
VAMInRamImOnDiskBodyC::VAMInRamImOnDiskBodyC(const StringC& MemName,
                                             const StringC& SavePrefix,
                                             int Verbosity)
                     :  VAMBodyBaseC(MemName, Verbosity),
                        savePrefix(SavePrefix + "/"),
                        xmlStream(""), xmlStreamOpen(false)
{
}
//-----------------------------------------------------------------------------
VAMInRamImOnDiskBodyC::~VAMInRamImOnDiskBodyC()
{
  if(verbosity > 7)
    cout << "VAMInRamImOnDiskBodyC::~VAMInRamImOnDiskBodyC called:" << MemoryName() << endl;

  //empty list of memory items
  items.Empty();

  //close xml file properly
  if(xmlStreamOpen)
  {
    xmlStream.EndTag();
    xmlStream.Close();
    xmlStreamOpen = false;
  }
  
  if(verbosity > 7)
    cout << "VAMInRamImOnDiskBodyC::~VAMInRamImOnDiskBodyC done:" << MemoryName() << endl;
}
//-----------------------------------------------------------------------------
//: Add item to memory.
void VAMInRamImOnDiskBodyC::Add(const MemoryItemC& Item) 
{
  if(!memoryReadyForAccess)
  {
    StringC err = StringC("VAMInRamImOnDiskBodyC::Add:Trying to write to VAM, which supposed to be read from file: ") + MemoryName();
    cerr << err << endl;
    throw ExceptionC(err);
  }
  
  //create xml file if it is not created yet
  if(!xmlStreamOpen)
  {
    OpenXMLStream();
  }

  //create MemoryItemC with body MemoryItemXMLDiskBodyC using
  //MemoryItemXMLDiskBodyC copy constructor
  //this can be done by creating MemoryItemXMLDiskC class
  //and this is exactly what will go into constructor
  //Cons: does not look similar to other RAVL classes
  //Pros: no MemoryItemXMLDiskC class needs to be defined
  //      (ie less source code and easy to change interface of class)
  MemoryItemXMLDiskBodyC* newItemBodyPtr = new MemoryItemXMLDiskBodyC(*Item.BodyPtr());
  MemoryItemC newItem(newItemBodyPtr);

  //set path to images
  newItemBodyPtr->SetPrefix(savePrefix + memName + "/");

  //dump images on disk
  newItemBodyPtr->DumpImages();

  //add XML to file
  SaveItem(newItem);

  //add item to list
  sync.Lock();
  lock.WrLock();
  if(verbosity > 10)
    cout << "Adding elem in " << MemoryName() 
         << " time: " << Item.Start() << " - " << Item.End() << endl;
  items += newItem;
  lock.UnlockWr();
  sync.Broadcast();
  sync.Unlock();
}

//-----------------------------------------------------------------------------
void VAMInRamImOnDiskBodyC::Stop(bool StopFlag)
{
  sync.Lock();
  lock.WrLock();
  askedToStop = StopFlag;
  if(verbosity > 10)
    cout << "Stopping in " << MemoryName() << endl;
  lock.UnlockWr();
  sync.Broadcast();
  sync.Unlock();
}

//-----------------------------------------------------------------------------
//: No more items to be added to this memory
void VAMInRamImOnDiskBodyC::End() 
{
  if(!memoryReadyForAccess)
  {
    StringC err = StringC("VAMInRamImOnDiskBodyC::Add:Trying to write to VAM, which supposed to be read from file: ") + MemoryName();
    cerr << err << endl;
    throw ExceptionC(err);
  }
  
  //create xml file if it is not created yet
  if(!xmlStreamOpen)
  {
    OpenXMLStream();
  }

  sync.Lock();
  lock.WrLock();
  if(items.IsEmpty())
    items += MemoryItemC(1);
  else 
  {
    items += MemoryItemC(items.Last().End()+1);
  }
  lock.UnlockWr();
  sync.Broadcast();
  sync.Unlock();
}

//-----------------------------------------------------------------------------
//: Delete elements up to time Time
void VAMInRamImOnDiskBodyC::Clean(const TimeCodeC& Time)
{
  lock.WrLock();
  // delete any items before this time
  while (!items.IsEmpty() && (items.First().End() < Time)) 
    items.DelFirst();
  lock.UnlockWr();
}

//-----------------------------------------------------------------------------
//: Delete any unwanted items
void VAMInRamImOnDiskBodyC::ForgetUnwanted() 
{
  // find oldest access to this list
  StringC oldest; TimeCodeC time;
  accessesLock.RdLock();
  for (HashIterC<StringC, VAMAccessC>ma(accesses); ma; ++ma) 
  {
    TimeCodeC t = ma->Tell();
    if ((oldest == "") || (t < time)) 
    {
      oldest = ma.Key(); 
      time = t;
    }
  }
  accessesLock.UnlockRd();

  Clean(time);
}

//-----------------------------------------------------------------------------
//: Dump memory contents
void VAMInRamImOnDiskBodyC::Dump() const 
{
  RdLock(true);
  for (ConstDLIterC<MemoryItemC> i(items); i; ++i) 
    cout << i->Dump() << endl;
  RdLock(false);
}

//-----------------------------------------------------------------------------
//: Creates memory access. 
VAMAccessC& VAMInRamImOnDiskBodyC::GetMemoryAccess(const StringC& Name, 
                                                   const TimeCodeC& Start, 
                                                   const TimeCodeC& End)
{
  accessesLock.WrLock();

  if(!memoryReadyForAccess)
    LoadItems();
  
  VAMAccessC *maPtr = accesses.Lookup(Name);
  if(maPtr != NULL)
  {
    StringC err = StringC("VAMInRamImOnDiskBodyC::GetMemoryAccess:Trying to get memory access for second time: ") + Name;
    cerr << err << endl;
    throw ExceptionC(err);
  }
  accesses.Insert(Name, VAMAccessC(new VAMAccessInRamImOnDiskBodyC(this, items,
                                                                   Start, End)));
  VAMAccessC& retVal = accesses[Name];
  accessesLock.UnlockWr();
  if(verbosity >= 2)
    cout << MemoryName() << " created access: " << Name << endl;
  return retVal;
}

//-----------------------------------------------------------------------------
//: Saves all elements in memory into stream
void VAMInRamImOnDiskBodyC::SaveTop(XMLOStreamC &Strm) const
{
  // ----------------------------- put reference to file ----------------------
  //write timecode element
  Strm.StartTag(MemoryName());
  // Alex: where do these attributes get set?  I feel they belong in MemModuleC, not here.
  for(HashIterC<StringC, StringC> attrIter(attr); attrIter; attrIter++)
  {
    Strm.SetAttrib(attrIter.Key(), attrIter.Data());
  }
  Strm.SetAttrib("file", xmlFileName);
  Strm.EndTag();
}

//-----------------------------------------------------------------------------
void VAMInRamImOnDiskBodyC::SaveItem(const MemoryItemC& item)
{
  try
  {
    RdLock(true);    // lock memory
    // Get access to MemoryItemC body, which must be of MemoryItemXMLDiskBodyC class.
    // To ensure correct transformation use dynamic_cast rather than simple type conversion.
    // This all done since MemoryItemC does not have Save method
    // (this method is only specific to XML implementation, therefore it was excluded from base class)
    const MemoryItemXMLDiskBodyC *itemCurPtr = dynamic_cast<const MemoryItemXMLDiskBodyC *>(item.BodyPtr());
    itemCurPtr->Save(xmlStream);
    xmlStream.os().flush(); //flush xml stream
    RdLock(false);    // unlock memory
  }
  catch( ... )
  {
    RdLock(false);    // unlock memory
    throw;
  }
}

//-----------------------------------------------------------------------------
//: Loads elements in memory from stream  
void VAMInRamImOnDiskBodyC::Load(XMLIStreamC &Strm, const TimeCodeC& Start, const TimeCodeC& End)
{
  memoryReadyForAccess = false;
  loadStart = Start;
  loadEnd = End;
  try
  {
    // ----------------------  read fileName from stream
    StringC tagName;
    XMLTagOpsT readTagRes;
    readTagRes = Strm.ReadTag(tagName, attr);
    if(readTagRes != XMLBeginTag)
      throw ExceptionInvalidStreamC("VAMInRamImOnDiskBodyC::Load: Missed 'begin' tag");
    memName = tagName;
    xmlFileName = attr["file"];
    savePrefix = xmlFileName.before(memName + ".xml");
    if(verbosity > 0)
      cout << "prepare module '" << memName << "' from " << xmlFileName << endl
           << "prefix:" << savePrefix << endl;

    readTagRes = Strm.ReadTag(tagName);
    if(readTagRes != XMLEndTag)
      throw ExceptionInvalidStreamC("VAMInRamImOnDiskBodyC::Load:Missed 'end' tag.");
    // ------------ Items will be loaded when memory access will be created
  }
  catch( ... )
  {
    cerr << "Caught exception in VAMInRamImOnDiskBodyC::Load\n";
    throw;
  }
  wasLoaded = true;
}

//-----------------------------------------------------------------------------
void VAMInRamImOnDiskBodyC::LoadItems()
{
  if(verbosity > 5)
    cout << "locking memory\n";
  sync.Lock();
  lock.WrLock();  // lock memory
  items.Empty();
  TimeCodeC lastReadElemTime;
  try
  {
    StringC tagName;
    XMLTagOpsT readTagRes;
    if(verbosity > 0)
      cout << "reading module '" << memName << "' from " << xmlFileName << endl
           << "prefix:" << savePrefix << endl;
    XMLIStreamC partStream(xmlFileName);

    if(!partStream.IsOpen() || partStream.eof() || !partStream)
      throw ExceptionC("VAMInRamImOnDiskBodyC::LoadItems:Can't open stream for reading memory");

    readTagRes = partStream.ReadTag(tagName);
    if(readTagRes != XMLBeginTag)
    {
      StringC msg(StringC("VAMInRamImOnDiskBodyC::LoadItems:Missed 'begin' tag, name: \"") + tagName + "\" (possibly mem file empty or not found)");
      throw ExceptionInvalidStreamC(msg);
    }
    if(tagName != memName)
      throw ExceptionInvalidStreamC(StringC("VAMInRamImOnDiskBodyC::LoadItems:Missed <") + memName + "> tag in file " + xmlFileName);

    //read items
    int itemCounter = 0;
    while(partStream.PeekTag(tagName) == XMLBeginTag)
    {
      MemoryItemXMLDiskBodyC* newItemBodyPtr = new MemoryItemXMLDiskBodyC();

      //create new MemoryItemC
      MemoryItemC newItem(newItemBodyPtr);

      //set path to images
      newItemBodyPtr->SetPrefix(savePrefix + memName + "/");

      newItemBodyPtr->Load(partStream);

      lastReadElemTime = newItem.Start();

      if(verbosity > 10)
        cout << "item start: " << newItem.Start() << "  end: " << newItem.End() << endl;
      if((!loadStart.IsValid() || newItem.Start() >= loadStart) && 
         (!loadEnd.IsValid()   || newItem.Start() <= loadEnd) )
      {
        if(verbosity > 10)
          cout << "inserting item into memory\n";
        items.InsLast(newItem);
        itemCounter++;
      }
    }
    if(verbosity > 5)
      cout << "finishing reading\n";

    //stop if not all Duration is read
    if(loadEnd.IsValid() && lastReadElemTime < loadEnd)
    {
      cerr << "Error while reading module: " << memName << endl;
      cerr << "There are not enough memory items to load from file" << endl;
      cerr << "  Last elem read: " << lastReadElemTime << endl;
      cerr << "  Must read: " << loadEnd << endl;
//      throw ExceptionC("There are not enough memory items to load from file");    
    }

    if(itemCounter == 0)
    {
      cerr << "Error: no items were read in " << memName << endl;
      throw ExceptionC("No items were read from file");        
    }

    readTagRes = partStream.ReadTag(tagName);
    if(readTagRes != XMLEndTag)
      throw ExceptionInvalidStreamC("VAMInRamImOnDiskBodyC::LoadItems:Missed 'end' tag.");
    
    if(verbosity > 5)
      cout << "closing stream\n";
    partStream.Close(); //close file
    
    //add eof item
    if(verbosity > 5)
      cout << "adding eof element\n";
    items.InsLast(MemoryItemC(items.Last().End() + 1)); 
    if(verbosity > 5)
      cout << "done\n";
  }
  catch(const ExceptionInvalidStreamC& ex)
  {
    lock.UnlockWr();
    sync.Broadcast();
    sync.Unlock();
    cerr << "Caught exception ExceptionInvalidStreamC in VAMInRamImOnDiskBodyC::LoadItems while loading memory\n"
        << "\"" << ex.Text() << "\"" << endl;
    throw;
  }
  catch(const ExceptionC& ex)
  {
    lock.UnlockWr();
    sync.Broadcast();
    sync.Unlock();
    cerr << "Caught exception ExceptionC in VAMInRamImOnDiskBodyC::LoadItems while loading memory\n"
        << "\"" << ex.Text() << "\"" << endl;
    throw;
  }
  catch( ... )
  {
    lock.UnlockWr();
    sync.Broadcast();
    sync.Unlock();
    cerr << "Caught exception in VAMInRamImOnDiskBodyC::LoadItems while loading memory\n";
    throw;
  }
  if(verbosity > 5)
    cout << "unlocking memory\n";
  lock.UnlockWr();
  sync.Broadcast();
  sync.Unlock();
  if(verbosity > 0)
    cout << "Items read: " << items.Size() << endl;
  memoryReadyForAccess = true;
}

//-----------------------------------------------------------------------------
// prepare XML stream
void VAMInRamImOnDiskBodyC::OpenXMLStream()
{
  xmlFileName = savePrefix + MemoryName() + ".xml";
  xmlStream = XMLOStreamC(xmlFileName);
  if(!xmlStream.IsOpen())
    throw ExceptionC("VAMInRamImOnDiskBodyC::OpenXMLStream:Can't open stream for writing memory");
  
  xmlStream.StartTag(MemoryName());
  xmlStream.StartContents();
  xmlStreamOpen = true;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
VAMAccessInRamImOnDiskBodyC::VAMAccessInRamImOnDiskBodyC(
                                  const VAMBodyBaseC* VamBodyPtr,
                                  const DListC<MemoryItemC>& Items,
                                  const TimeCodeC& Start, const TimeCodeC& End)
  : VAMAccessBodyBaseC(Start, End), 
    iter(Items),
    curItem(MemoryItemC()), 
    vam((VAMBodyBaseC*)VamBodyPtr)
{
  --iter; //make iter point to previous elem
}

VAMAccessInRamImOnDiskBodyC::VAMAccessInRamImOnDiskBodyC(const TimeCodeC& Start,
                                                         const TimeCodeC& End,
                                                         const bool Eof,
                                                         const ConstDLIterC<MemoryItemC>& Iter,
                                                         const MemoryItemC& CurItem,
                                                         const VAMC& Vam)
                            : VAMAccessBodyBaseC(Start, End, Eof),
                              iter(Iter), curItem(CurItem.Copy()), vam(Vam)
{
}
                                                         

//: make a copy of access
VAMAccessBodyBaseC* VAMAccessInRamImOnDiskBodyC::Copy() const
{
  VAMAccessBodyBaseC* newAccess = new VAMAccessInRamImOnDiskBodyC(startTc, endTc, eof,
                                                                  iter, curItem, vam);
  return newAccess;
}

//: returns current memory item whithout changing memory pointer
// Does not wait for item. Returns invalid item if there is no current one
const MemoryItemC& VAMAccessInRamImOnDiskBodyC::Peek() const
{
  return curItem;
}

//-----------------------------------------------------------------------------
//: returns current memory item whithout changing memory pointer
// Does not wait for item. Returns invalid item if there is no current one
const DurationC& VAMAccessInRamImOnDiskBodyC::PeekDuration() const
{
  return curItem.Duration();
}

//-----------------------------------------------------------------------------
//: returns string information about current memory item
StringC VAMAccessInRamImOnDiskBodyC::PeekInfo() const
{ 
  if(!curItem.IsValid()) //iter points to previous elem
  {
    ((VAMAccessInRamImOnDiskBodyC*)this)->PrepareGetNoWait(); //try to move iter
  }
  return curItem.Dump(60); 
}

//-----------------------------------------------------------------------------
//: Gets item from memory and then increments memory pointer
// Waits until item is available
const MemoryItemC& VAMAccessInRamImOnDiskBodyC::Get()
{
  PrepareGet();
  return Peek();
}

//-----------------------------------------------------------------------------
//: Gets item from memory and then increments memory pointer
// Waits until item is available
const DurationC& VAMAccessInRamImOnDiskBodyC::GetDuration()
{
  PrepareGet();
  return curItem.Duration();
}

//-----------------------------------------------------------------------------
//: Points to next item after time tc from memory
// Waits until item is available
const MemoryItemC& VAMAccessInRamImOnDiskBodyC::Get(const TimeCodeC& Tc)
{
  do
  {
    PrepareGet();
  } while(!curItem.Eof() && curItem.Start() < Tc);

  return Peek();
}
//-----------------------------------------------------------------------------

//: Points to next item after time tc from memory
// Waits until item is available
const DurationC& VAMAccessInRamImOnDiskBodyC::GetDuration(const TimeCodeC& Tc)
{
  do
  {
    PrepareGet();
  } while(!curItem.Eof() && curItem.Start() < Tc);
  return curItem.Duration();
}

//-----------------------------------------------------------------------------
//: Gets last item from memory, if available
// This "get" does not wait.  If an item is available it returns it; 
// otherwise it returns an invalid memory item.
const MemoryItemC& VAMAccessInRamImOnDiskBodyC::GetNoWait()
{
  PrepareGetNoWait();
  return Peek();
}

//-----------------------------------------------------------------------------
//: Gets last item from memory, if available
// This "get" does not wait.  If an item is available it returns it; 
// otherwise it returns an invalid memory item.
// do not care about image in memory item
const DurationC& VAMAccessInRamImOnDiskBodyC::GetNoWaitDuration()
{
  PrepareGetNoWait();
  return curItem.Duration();
}

//-----------------------------------------------------------------------------
//: Gets next item after time Tc from memory (item.Start() could be == Tc)
// This "get" does not wait.  If an item is available it returns it; 
// otherwise it returns an invalid memory item.
const MemoryItemC& VAMAccessInRamImOnDiskBodyC::GetNoWait(const TimeCodeC& Tc)
{
  do
  {
    PrepareGetNoWait();
    if(!curItem.IsValid()) //there is no available item to get
    {
      break;
    }
  }
  while(!curItem.Eof() && curItem.Start() < Tc);
  return Peek();
}

//-----------------------------------------------------------------------------
//: Gets next item after time Tc from memory (item.Start() could be == Tc)
// This "get" does not wait.  If an item is available it returns it; 
// otherwise it returns an invalid memory item.
const DurationC& VAMAccessInRamImOnDiskBodyC::GetNoWaitDuration(const TimeCodeC& Tc)
{
  do
  {
    PrepareGetNoWait();
    if(!curItem.IsValid()) //there is no available item to get
    {
      break;
    }
  } while(!curItem.Eof() && curItem.Start() < Tc);
  return curItem.Duration();
}

//-----------------------------------------------------------------------------
//:moves iterator to first element
//returns true if movement was successful
bool VAMAccessInRamImOnDiskBodyC::MoveToFirst(bool NoWait)
{
  //shift iter to before begining
  vam.RdLock(true);
  iter.First();
  iter--;
  vam.RdLock(false);

  //read first item
  NoWait ? PrepareGetNoWait() : PrepareGet();
  return curItem.IsValid();
}
//-----------------------------------------------------------------------------
//: moves iterator to certain time
//returns true if movement was successful 
//curItem.Start <= Tc and curItem.End >= Tc
//If there is no item with Start=Tc and NoWait=true iterator points to
//the last awailable item and returns false
bool VAMAccessInRamImOnDiskBodyC::MoveTo(const TimeCodeC& Tc, bool NoWait)
{
  if(Tc.IsValid())
  {
    while(curItem.Start() > Tc)
    {
      bool res = Prev();
      if(!res)
        return false;
    }
    while(curItem.End() < Tc)
    {
      bool res = Next(NoWait);
      if(!res || eof)
        return false;
    }
  }
  else
  {
    MoveToFirst(NoWait);
  }
  return curItem.IsValid() && (curItem.Start() <= Tc) && (curItem.End() >= Tc);
}

//-----------------------------------------------------------------------------
//:moves iterator to next item
//returns true if movement was successful
bool VAMAccessInRamImOnDiskBodyC::Next(bool NoWait)
{
  NoWait ? PrepareGetNoWait() : PrepareGet();
  return curItem.IsValid();
}

//-----------------------------------------------------------------------------
//:moves iterator to prev item
//returns true if movement was successful
bool VAMAccessInRamImOnDiskBodyC::Prev()
{
  bool res = false; //result of movement
  if(curItem.IsValid())
  {    
    if(curItem.Duration().Start() == startTc) {			// added by fei
      eof = true;						// added by fei
      return false;						// added by fei
    }			
    
    vam.RdLock(true);
    if(!iter.IsFirst())
    {
      iter--;
      curItem = iter->Copy(); //make a copy of memory item
      res = true;
    }
    vam.RdLock(false);
    eof = curItem.Eof();
  }
  return res && curItem.IsValid();
}

//-----------------------------------------------------------------------------
//:access to current item
const MemoryItemC& VAMAccessInRamImOnDiskBodyC::operator*() const
{
  if(!curItem.IsValid()) //iter points to previous elem
  {
    ((VAMAccessInRamImOnDiskBodyC*)this)->PrepareGetNoWait(); //try to move iter
  }
  return curItem;
}

//-----------------------------------------------------------------------------
//:access to current item
const MemoryItemC* VAMAccessInRamImOnDiskBodyC::operator->() const
{
  if(!curItem.IsValid()) //iter points to previous elem
  {
    ((VAMAccessInRamImOnDiskBodyC*)this)->PrepareGetNoWait(); //try to move iter
  }
  return &curItem;
}

//-----------------------------------------------------------------------------
//:duration of current item
const DurationC& VAMAccessInRamImOnDiskBodyC::ItemDuration() const
{
  if(!curItem.IsValid()) //iter points to previous elem
  {
    ((VAMAccessInRamImOnDiskBodyC*)this)->PrepareGetNoWait(); //try to move iter
  }
  return curItem.Duration();
}

//-----------------------------------------------------------------------------
void VAMAccessInRamImOnDiskBodyC::PrepareGet()
{
  if(vam.GetVerbosityLevel() > 10)
    cout << "PrepareGet for " << vam.MemoryName()
         << "  curTime: " << curItem.Start() << endl;
  if(eof)
    return;
  if(endTc.IsValid() && curItem.Start() >= endTc)
  {
    curItem = MemoryItemC(endTc+1);
  }
  else
  {
    vam.RdLock(true);

    bool needToStop = false;
    if(vam.AskedToStop())
      needToStop = true;
    else
    {
      do
      {
        while(iter.IsLast()) 
        {
          if(vam.GetVerbosityLevel() > 10)
            cout << "Sleepeing in while\n";
          vam.SleepUnlocked();  // will lock when it comes out
          if(vam.AskedToStop())
          {
            needToStop = true;
            break;
          }
        }
        if(needToStop)
          break;

        //go to current item (iter point to previous item)
        ++iter;

        if(!iter) // this *should* never happend 
        {
          cerr << "Error in VAMAccessInRamImOnDiskBodyC::PrepareGet()\n";
          throw ExceptionC("Error in VAMAccessInRamImOnDiskBodyC::PrepareGet()");    
        }
      } while(!iter->Eof() && (startTc.IsValid() && iter->Start() < startTc));
    }
    if(needToStop)
      curItem = MemoryItemC(1);//eof item
    else
      curItem = iter->Copy(); //make a copy of memory item

    vam.RdLock(false);
  }
  
  if(!curItem.IsValid())
  {
    cerr << "Error in VAMAccessInRamImOnDiskBodyC::PrepareGet():invalid item\n";
    throw ExceptionC("Error in VAMAccessInRamImOnDiskBodyC::PrepareGet():invalid item");    
  }

  eof = curItem.Eof();

  if(vam.GetVerbosityLevel() > 10)
    cout << "Ok PrepareGet for " << vam.MemoryName()
         << "  current time: " << curItem.Start()<< endl;
}

//-----------------------------------------------------------------------------
void VAMAccessInRamImOnDiskBodyC::PrepareGetNoWait()
{
  if(eof)
    return; 
  if(curItem.IsValid() && endTc.IsValid() && curItem.Start() >= endTc) //eof
  {
    curItem = MemoryItemC(endTc+1);
  }
  else
  {
    vam.RdLock(true);
    do
    {
      if(!iter.IsLast()) 
      {
        //go to current item (iter point to previous item)
        ++iter;
      } 
      else
      {   //return default memory item with negative time
        curItem = MemoryItemC();
        vam.RdLock(false);
        eof = curItem.Eof();
        return;
     }
    } while(!iter->Eof() && (startTc.IsValid() && iter->Start() < startTc));
    curItem = iter->Copy(); //make a copy of memory item
    vam.RdLock(false);
  }
  eof = curItem.Eof();
}

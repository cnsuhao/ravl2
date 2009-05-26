#include "Ravl/Threads/VamAllInRam.hh"

#include "Ravl/CDLIter.hh"

//: Adds item to memory
void VAMAllInRamBodyC::Add(const StringC& Name, 
                           const TimeCodeC& Start, const TimeCodeC& End, 
                           const MemoryAttributesC& Attrs, 
                           const ImageC<ByteRGBValueC>& Image) 
{
  sync.Lock();
  lock.WrLock();
//  cout << "Adding elem in " << MemoryName() << " time: " << End << endl;
  items += MemoryItemC(Name, DurationC(Start, End), Attrs, Image);
  currentIndex = Start;
  lock.UnlockWr();
  sync.Broadcast();
  sync.Unlock();
}

//: No more items to be added to this memory
void VAMAllInRamBodyC::End() 
{ 
  sync.Lock();
  lock.WrLock();
  if (items.IsEmpty()) 
    items += MemoryItemC(currentIndex+1); 
  else 
  {
    items += MemoryItemC(items.Last().End()+1); 
  }
  lock.UnlockWr();
  sync.Broadcast();
  sync.Unlock();
}

//: Delete elements up to time Time
void VAMAllInRamBodyC::Clean(const TimeCodeC& Time)
{
  lock.WrLock();
  // delete any items before this time
  while (!items.IsEmpty() && (items.First().End() < Time)) 
    items.DelFirst();
  lock.UnlockWr();
}

//: Delete any unwanted items
void VAMAllInRamBodyC::ForgetUnwanted() 
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

//: Dump memory contents
void VAMAllInRamBodyC::Dump() const 
{
  RdLock(true);
  for (ConstDLIterC<MemoryItemC> i(items); i; ++i) 
    cout << i->Dump() << endl;
  RdLock(false);
}

//: Creates memory access. 
VAMAccessC& VAMAllInRamBodyC::GetMemoryAccess(const StringC& Name, 
                                              const TimeCodeC& Start, 
                                              const TimeCodeC& End)
{
  accessesLock.WrLock();
  VAMAccessC *maPtr = accesses.Lookup(Name);
  if(maPtr != NULL)
  {
    StringC err = StringC("Trying to get memory access for second time:") + Name;
    cerr << err << endl;
    throw ExceptionC(err);
  }
  accesses.Insert(Name, VAMAccessC(new VAMAccessAllInRamBodyC(this, items, Start, End)));
  VAMAccessC& retVal = accesses[Name];
  accessesLock.UnlockWr();

  return retVal;
}

//: Saves all current elements in memory into stream
void VAMAllInRamBodyC::Save(ostream &strm) const
{
  RdLock(true);    // lock memory
  for(ConstDLIterC<MemoryItemC> itemCur(items); itemCur && !itemCur->Eof(); ++itemCur) 
  {
    StringC name = savePrefix + itemCur->Start().ToText() + ".ppm";
    strm << "<item>"; 
    itemCur->Save(strm, name);
    strm << "</item>\n";
  }
  RdLock(false);    // unlock memory
}

//: Saves all current elements in memory into stream
void VAMAllInRamBodyC::Save(XMLOStreamC &Strm) const
{
  Strm.StartTag(StringC("m_") + MemoryName());
  Strm.StartContents();
  RdLock(true);    // lock memory
  for(ConstDLIterC<MemoryItemC> itemCur(items); itemCur && !itemCur->Eof(); ++itemCur) 
  {
    char buf[21];
    snprintf(buf, 20, "%06i", int(itemCur->Start().getFrameCount()));
    StringC name = savePrefix + StringC(buf) + ".png";
    itemCur->Save(Strm, name);
  }
  RdLock(false);    // unlock memory
  Strm.EndTag();
}

//: Loads elements in memory from stream  
void VAMAllInRamBodyC::Load(XMLIStreamC &Strm, TimeCodeC& Start, TimeCodeC& End)
{
  sync.Lock();
  lock.WrLock();  // lock memory
  items.Empty();
  try
  {
    //read name
    StringC tagName;
    XMLTagOpsT readTagRes;
    readTagRes = Strm.ReadTag(tagName);
    if(readTagRes != XMLBeginTag)
      throw ExceptionInvalidStreamC("VAMAllInRamBodyC::Load:Missed 'begin' tag");
    memName = tagName.after("m_");
    cout << "reading memory for module:" << memName << endl;
    
    //read items
    while(Strm.PeekTag(tagName) == XMLBeginTag)
    {
      MemoryItemC item;
      item.Load(Strm);
      if((!Start.IsValid() || item.Start() >= Start) && 
         (!End.IsValid()   || item.Start() <= End))
      {
        items.InsLast(item);
      }
    }

    readTagRes = Strm.ReadTag(tagName);
    if(readTagRes != XMLEndTag)
      throw ExceptionInvalidStreamC("VAMAllInRamBodyC::Load:Missed 'end' tag.");

    //stop if not all Duration is read
    if(End.IsValid() && items.Last().End() < End)
    {
      throw ExceptionC("There are not enough memory items to load from file");    
    }

    //correct start and end
    Start = items.First().Start();
//    End = Min(End, items.Last().End());
    
    //add eof item
    items.InsLast(MemoryItemC(items.Last().End()+1)); 
  }
  catch( ... )
  {
    lock.UnlockWr();
    sync.Broadcast();
    sync.Unlock();
    cout << "Caught exception in VAMAllInRamBodyC::Load\n";
    throw;
  }
  lock.UnlockWr();
  sync.Broadcast();
  sync.Unlock();
  cout << "Items read:" << items.Size() << endl;
  wasLoaded = true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
VAMAccessAllInRamBodyC::VAMAccessAllInRamBodyC(const VAMBodyBaseC* VamBodyPtr, 
                                               const DListC<MemoryItemC>& Items,
                                               const TimeCodeC& Start, 
                                               const TimeCodeC& End)
  : VAMAccessBodyBaseC(Start, End), iter(Items), vamBodyPtr(VamBodyPtr)
{
  --iter; //make iter point to previous elem
}

//: Move memory pointer to next item and returns the item
// Waits until item is available
MemoryItemC VAMAccessAllInRamBodyC::Get()
{
  PrepareGet();
  return curItem;
}

//: Move memory pointer to next item and returns its duraion
// Waits until item is available
DurationC VAMAccessAllInRamBodyC::GetDuration()
{
  PrepareGet();
  return curItem.Duration();
}

//: Gets next item after time Tc from memory (item.Start() could be == Tc)
// Waits until item is available
MemoryItemC VAMAccessAllInRamBodyC::Get(const TimeCodeC& Tc)
{ 
  PrepareGet(Tc); 
  return curItem;
}

//: Move memory pointer to next item after time Tc (item.Start() could be == Tc)
// and returns its duraion.
// Waits until item is available
DurationC VAMAccessAllInRamBodyC::GetDuration(const TimeCodeC& Tc)
{
  PrepareGet(Tc); 
  return curItem.Duration();
}

//: Gets next item from memory
// This "get" does not wait.  If an item is available it returns it; 
// otherwise it returns an invalid memory item.
MemoryItemC VAMAccessAllInRamBodyC::GetNoWait()
{
  PrepareGetNoWait();
  return curItem;
}

//: Same as GetDuration(), but the function does not wait for the item
// If an item is available it returns its duration; 
// otherwise it returns an invalid duration.
DurationC VAMAccessAllInRamBodyC::GetNoWaitDuration()
{
  PrepareGetNoWait();
  return curItem.Duration();
}

//: Gets next item after time Tc from memory (item.Start() could be == Tc)
// This "get" does not wait.  If an item is available it returns it; 
// otherwise it returns an invalid memory item.
MemoryItemC VAMAccessAllInRamBodyC::GetNoWait(const TimeCodeC& Tc)
{
  PrepareGetNoWait(Tc);
  return curItem;
}

//: Same as GetDuration(const TimeCodeC& Tc), but the function does not wait for the item
// If an item is available it returns its duration; 
// otherwise it returns an invalid duration.
DurationC VAMAccessAllInRamBodyC::GetNoWaitDuration(const TimeCodeC& Tc)
{
  PrepareGetNoWait(Tc);
  return curItem.Duration();
}


void VAMAccessAllInRamBodyC::PrepareGet()
{
//  cout << "Get from " << mem.MemoryName() << endl;

  vamBodyPtr->RdLock(true);
  while(!curItem.Eof() && (!curItem.IsValid() || curItem.Start() < startTc))
  {
    while(iter.IsLast()) 
    {
      //cout << "Sleepeing in while\n";
      vamBodyPtr->SleepUnlocked(); // will lock when it comes out
    }

    //go to current item (iter point to previous item)
    ++iter;

    if(iter) // this *should* always be true
    {
      curItem = *iter;
    } 
    else
    {
      cerr << "Error in VAMAccessAllInRamBodyC::PrepareGet()\n";
      throw ExceptionC("Error in VAMAccessAllInRamBodyC::PrepareGet()");    
    }
  }
  vamBodyPtr->RdLock(false);

  if(curItem.Start() >= endTc)
    curItem = MemoryItemC(endTc); //curItem is eof
  eof = curItem.Eof();
}

void VAMAccessAllInRamBodyC::PrepareGet(const TimeCodeC& Tc)
{
  while(!curItem.Eof() && (!curItem.IsValid() || curItem.Start() < Tc))
  {
    PrepareGet();
  }
}

void VAMAccessAllInRamBodyC::PrepareGetNoWait()
{
  vamBodyPtr->RdLock(true);
  while(!curItem.Eof() && (!curItem.IsValid() || curItem.Start() < startTc))
  {
    if(!iter.IsLast()) 
    {
      //go to current item (iter points to previous item)
      ++iter;
      curItem = *iter;
    } 
    else
    {   
      curItem = MemoryItemC();//curItem is invalid
      break;
    }
  }
  vamBodyPtr->RdLock(false);
  if(curItem.IsValid() && curItem.Start() >= endTc)
    curItem = MemoryItemC(endTc); //curItem is eof
  eof = curItem.Eof();
}

void VAMAccessAllInRamBodyC::PrepareGetNoWait(const TimeCodeC& Tc)
{
  while(!curItem.Eof() && (!curItem.IsValid() || curItem.Start() < Tc))
  {
    PrepareGetNoWait();
    if(!curItem.IsValid()) //there is no available item to get
    {
      break;
    }
  }
}



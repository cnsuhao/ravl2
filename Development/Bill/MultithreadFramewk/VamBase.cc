#include "Ravl/Threads/VamBase.hh"
#include "Ravl/Threads/VamAccess.hh"
#include "Ravl/Threads/VamInRamImOnDisk.hh"
#include "Ravl/Threads/MemModules.hh"

#include "Ravl/OS/Filename.hh"

VAMBodyBaseC::VAMBodyBaseC(const StringC MemName, int Verbosity) 
  : memName(MemName), wasLoaded(false), memoryReadyForAccess(true),
    askedToStop(false)
{
  verbosity = Verbosity;
  if(verbosity > 0)
    cout << "Creating VAM:" << memName << endl;
}

VAMBodyBaseC::~VAMBodyBaseC()
{
  if(verbosity > 0)
    cout << "Destroying VAM:" << memName << endl;
}

//: Sleep and unlock the memory in the meantime
void VAMBodyBaseC::SleepUnlocked() const 
{
  RdLock(false);
  sync.Lock(); // because the following Wait() unlocks it 
  sync.Wait();
  sync.Unlock();// because the Wait() locks it on waking
  RdLock(true);
}

//: Removes memory access from internal reference table 
void VAMBodyBaseC::ReleaseMemoryAccess(const StringC& Name)
{
  accessesLock.WrLock();
  VAMAccessC *maPtr = accesses.Lookup(Name);
  if(maPtr == NULL)
  {
    cerr << "VAMBodyBaseC::ReleaseMemoryAccess:Trying to release memory access which is not connected:" << Name << endl;
  }  
  else
  {
    accesses.Del(Name);
  }  
  accessesLock.UnlockWr();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
VAMC::VAMC(const StringC& MemName, MemTypeE MemType, int Verbosity) 
{
  const StringC& memRoot = ModuleManager.RootDir();
  switch(MemType)
  {
  case NoRamEC:
    cout << "Creating temp vam!\n";
    break;
    /*
  case VamAllInRamEC:
  {
    FilenameC savePrefix = memRoot + "/" + MemName + "/";
    if(Verbosity > 0)
      cout << "Save prefix:" << savePrefix << endl;
    savePrefix.MakeDir();
    operator=(VAMC(new VAMAllInRamBodyC(MemName, savePrefix, Verbosity))); 
    break;
  }
    */
  case VamInRamImOnDiskEC:
  {
    if (!FilenameC(memRoot).IsDirectory()) throw ExceptionC("VAMC::VAMC: Invalid root for memory storage: \"" + memRoot + "\"");
    FilenameC savePrefix = memRoot + "/" + MemName + "/";
    if(Verbosity > 0)
      cout << "Save prefix:" << savePrefix << endl;
    savePrefix.MakeDir(); 
    if(!savePrefix.IsDirectory() || !savePrefix.IsWritable()) 
      {
        cerr << "Can not create output directory: "<< savePrefix <<" !\n";
        throw ExceptionC("VAMC::VAMC: memory output is compulsory for VamInRamImOnDiskEC");
      } 
    operator=(VAMC(new VAMInRamImOnDiskBodyC(MemName, memRoot, Verbosity))); 
    break;
  }
  default:
    cerr << "Memory system type " << MemType << " not found" << endl;
    exit (-1);
  }//end of switch
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//: changes bounds of memory access
// This moves pointer to time Start
void VAMAccessBodyBaseC::SetBounds(const TimeCodeC& Start, const TimeCodeC& End)
{ 
  startTc = Start; 
  endTc = End; 
  eof = false; 
  if(startTc.IsValid())
  {
    MoveTo(startTc, false);
  }
  else
  {
    MoveToFirst(false);
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//:Add access to managed set of accesses
void VAMJointAccessBodyC::AddAccess(const StringC& AccName, VAMAccessC& Access)
{
  if(accTable.IsElm(AccName))
  {
    cerr << "VAMMultyAccessBody::AddAccess:Trying to add access which is already in the set\n";
    throw ExceptionC("VAMMultyAccessBody::AddAccess:Trying to add access which is already in the set");
  }
  accTable.Insert(AccName, Access);
}

//:Remove access from set
void VAMJointAccessBodyC::RemoveAccess(const StringC& AccName)
{
  if(accTable.Del(AccName))
  {
    cerr << "VAMMultyAccessBody::RemoveAccess:Trying to remove access which is not in the set\n";
    throw ExceptionC("VAMMultyAccessBody::RemoveAccess:Trying to remove access which is not in the set");
  }
}

//: returns current memory item whithout changing memory pointer
// Does not wait for item. Returns invalid item if there is no current one
const MemoryItemC VAMJointAccessBodyC::Peek(const StringC& AccName) const
{
  const VAMAccessC *accPtr = accTable.Lookup(AccName);
  if(!accPtr)
  {
    cerr << "VAMMultyAccessBody::Peek:VAM accesss \"" << AccName << "\" is not in the set\n";
    throw ExceptionC("VAMMultyAccessBody::Peek:VAM accesss is not in the set");
  }
  return accPtr->Peek();
}

//: returns string information about current memory item
StringC VAMJointAccessBodyC::PeekInfo(const StringC& AccName) const
{
  const VAMAccessC *accPtr = accTable.Lookup(AccName);
  if(!accPtr)
  {
    cerr << "VAMMultyAccessBody::PeekInfo:VAM accesss \"" << AccName << "\" is not in the set\n";
    throw ExceptionC("VAMMultyAccessBody::PeekInfo:VAM accesss is not in the set");
  }
  return accPtr->PeekInfo();
}

//------------------- iterator movement functions --------------------------
//: changes bounds of memory access
// This moves pointer to time Start
void VAMJointAccessBodyC::SetBounds(const TimeCodeC& Start, const TimeCodeC& End)
{ 
  startTc = Start; 
  endTc = End; 
  MoveTo(startTc);
}

//:moves iterator to first element
//returns true if movement was successful
bool VAMJointAccessBodyC::MoveToFirst()
{
  curStart = curEnd = startTc;
  return NextIntersection();
}

//: moves iterator to certain time
//returns true if movement was successful

bool VAMJointAccessBodyC::MoveTo(const TimeCodeC& Tc)
{
  curStart = curEnd = Tc;
  return NextIntersection();
}


//: Moves iterator to next item
// Returns true if movement was successful

bool VAMJointAccessBodyC::Next()
{
  // Search for the *next* period that intersects *maximally* with all the access items:
  // It follows that one or more of the current items must finish exactly at the end of the intersection period,
  // so to get the joint access to move on, we move curStart past current period
  // then look for next intersection

  curStart = curEnd = curEnd + 1;
  return NextIntersection();
}


//: Wrapper for conditions around successful getting of next individual access
// Maybe should be subsumed into VAMAccessC::Next()??

void VAMJointAccessBodyC::getNext(VAMAccessC& acc) {
  if(!acc.Next() || acc.Eof() || (acc.ItemDuration().Start() > endTc)) {
    eof |= acc->Eof();
    throw (JointAccExceptionC());  // can't find one
  }
}


//: Moves iterator to next set of jointly intersecting items
// Returns true if movement was successful
// Assumes startTc, endTc are already set

bool VAMJointAccessBodyC::NextIntersection()
{
  try {
    // Move accesses forward to current time where necessary
    for(HashIterC<StringC, VAMAccessC> acc(accTable); acc.IsElm(); acc.Next()) {
      while (acc->ItemDuration().Start() < curStart)  getNext(*acc);
    }
    // If the duration of each item overlaps with those of all of the others, a joint intersection is guaranteed.  (Take my word for it.)
    // The algorithm actually works the other way round:
    // if item duration from any access A is earlier than and non-overlapping with any of the others, there is no intersection,
    // so get next item of A and go round the loop again
    bool needAnotherIteration;
    do {
      needAnotherIteration = false;
      for(HashIterC<StringC, VAMAccessC> acc1(accTable); acc1.IsElm(); acc1.Next()) {
        bool acc1Intersected = true;
        for(HashIterC<StringC, VAMAccessC> acc2(accTable); acc2.IsElm(); acc2.Next()) {
          if (acc1->ItemDuration() < acc2->ItemDuration())  acc1Intersected = false; // -> acc1 too early
        }
        if (!acc1Intersected) { // if acc1 too early, get another one
          getNext(*acc1);  // can't find one
          needAnotherIteration = true;
        }
      }
    } while (needAnotherIteration);
  }
  catch (JointAccExceptionC) {
    // set current interval to trigger invalid iterator
    curEnd = endTc;
    curStart = curEnd + 1;
    return false;
  }

  // find duration of intersection of all accesses
  DurationC intersection(startTc, endTc);
  for(HashIterC<StringC, VAMAccessC> acc(accTable); acc.IsElm(); acc.Next()) {
    intersection = intersection && acc->ItemDuration();
  }
  curStart = intersection.Start();
  curEnd = intersection.End();
  return !eof && (intersection.IsValid());
}


//:moves iterator to prev item
//returns true if movement was successful
bool VAMJointAccessBodyC::Prev()
{
  bool retVal = true;

  //check possibility of movement back
  if(startTc.IsValid())
  {
    for(HashIterC<StringC, VAMAccessC> curSrc(accTable); curSrc.IsElm() && retVal; curSrc.Next())
    {
      retVal &= curSrc->Tell() > startTc;
    }
  }
  
  //calclulate beginning of previous item
  TimeCodeC targetTC(RavlConstN::maxInt, 50);
  for(HashIterC<StringC, VAMAccessC> curSrc(accTable); curSrc.IsElm() && retVal; curSrc.Next())
  {
    retVal &= curSrc->Prev();
    const MemoryItemC& item = curSrc->Peek();
    if(retVal && item.IsValid())
    {
      TimeCodeC tc = item.Start();
      if(tc.IsValid() && tc < targetTC)
      {
        targetTC = tc;
      }
    }
  }
  
  //sync all sources
  for(HashIterC<StringC, VAMAccessC> curSrc(accTable); curSrc.IsElm() && retVal; curSrc.Next())
  {
    retVal &= MoveTo(targetTC);
  }
  
  curStart = targetTC;

  //check eof
  eof = false;
  for(HashIterC<StringC,VAMAccessC> it(accTable); it.IsElm() && !eof; it.Next())
  {
    eof |= it->Eof();
  }
  return retVal;
}


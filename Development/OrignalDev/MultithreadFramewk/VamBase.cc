#include "Ravl/Threads/VamBase.hh"

#include "Ravl/Threads/VamInRamImOnDisk.hh"

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
VAMC::VAMC(const StringC& MemName, MemTypeE MemType, const StringC& Param,
           int Verbosity) 
{
  switch(MemType)
  {
  case NoRamEC:
    cout << "Creating temp vam!\n";
    break;
    /*
  case VamAllInRamEC:  // Param is save prefix
  {
    FilenameC savePrefix = Param + "/" + MemName + "/";
    if(Verbosity > 0)
      cout << "Save prefix:" << savePrefix << endl;
    savePrefix.MakeDir();
    operator=(VAMC(new VAMAllInRamBodyC(MemName, savePrefix, Verbosity))); 
    break;
  }
    */
  case VamInRamImOnDiskEC: // Param is save prefix and it is compulsory!
  {
    const StringC lc("loadConstructor");
    if(Param.contains(lc))
    {
      FilenameC savePrefix = StringC(Param).after(lc);
      operator=(VAMC(new VAMInRamImOnDiskBodyC(MemName, savePrefix, Verbosity))); 
    }
    else
    {
      FilenameC savePrefix = Param + "/" + MemName + "/";
      if(Verbosity > 0)
        cout << "Save prefix:" << savePrefix << endl;
      savePrefix.MakeDir(); 
      if(!savePrefix.IsDirectory() || !savePrefix.IsWritable()) 
      {
        cerr << "Can not create output directory!\n";
        throw ExceptionC("VAMC::VAMC:memory output is compulsory for VamInRamImOnDiskEC");
      } 
      operator=(VAMC(new VAMInRamImOnDiskBodyC(MemName, Param, Verbosity))); 
    }
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
const MemoryItemC& VAMJointAccessBodyC::Peek(const StringC& AccName) const
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

//:moves iterator to first element
//returns true if movement was successful
bool VAMJointAccessBodyC::MoveToFirst(bool NoWait)
{
  bool retVal(true);

  curStart = startTc;
  for(HashIterC<StringC,VAMAccessC> it(accTable); it.IsElm(); it.Next())
  {
    retVal &= it->MoveToFirst(NoWait);
    TimeCodeC tc = it->Tell();
    if(tc.IsValid() && curStart < tc)
    {
      curStart = tc;
    }
  }
  
  //sinchronise accesses
  if(curStart.IsValid()) 
  {
    retVal &= MoveTo(curStart, NoWait);
  }
  return retVal;
}

//: moves iterator to certain time
//returns true if movement was successful
bool VAMJointAccessBodyC::MoveTo(const TimeCodeC& Tc, bool NoWait)
{
  bool retVal(true);

  curStart = startTc;
  for(HashIterC<StringC,VAMAccessC> it(accTable); it.IsElm(); it.Next())
  {
    //cout << it.Key() << endl;
    retVal &= it->MoveTo(Tc, NoWait);
    TimeCodeC tc = it->Tell();
    if(tc.IsValid() && curStart < tc)
    {
      curStart = tc;
    }
  }
  
  if(curStart != Tc)
  //it is not possible to move to Tc. some sources have start time after Tc
  //try to align sources to that time
  {
    for(HashIterC<StringC,VAMAccessC> it(accTable); it.IsElm(); it.Next())
    {
      retVal &= it->MoveTo(curStart, NoWait);
      TimeCodeC tc = it->Tell();
      if(tc.IsValid() && curStart != tc)
      {
        //time intervals are not aligned, actually it is an error
        break;
      }
    }
  }
  
  //check eof
  eof = false;
  for(HashIterC<StringC,VAMAccessC> it(accTable); it.IsElm() && !eof; it.Next())
  {
    //cout << it.Key() << endl;
    eof |= it->Eof();
  }
  retVal &= curStart == Tc; //all accesses moved to time Tc
  return retVal;
}

//:moves iterator to next item
//returns true if movement was successful
//need to change to simplier version using MoveTo function FIXME (AK)
bool VAMJointAccessBodyC::Next(bool NoWait)
{
  //cout << "VAMMultyAccessBody::Next:entering: " << endl;
  if(eof)
    return false;
    
  //calclulate end of current item
  TimeCodeC targetTC(-1);
  for(HashIterC<StringC, VAMAccessC> curSrc(accTable); curSrc.IsElm(); curSrc.Next())
  {
    const MemoryItemC& item = curSrc->Peek();
    if(item.IsValid())
    {
      TimeCodeC tc = item.End();
      if(tc.IsValid() && tc > targetTC)
      {
        targetTC = tc;
      }
    }
  }

  //create next timecode
  ++targetTC;

  //check boundary (paranoid)
  if(targetTC < startTc)
    targetTC = startTc;

  //cout << "target time code: " << targetTC << endl;
  
  //position all sources to same time
  bool stable;  // true if all sources match
  do // keep iterating until all sources match
  {  
    stable = true;

    //cout << "cur time code: " << targetTC << endl;

    //loop over all sources
    for(HashIterC<StringC, VAMAccessC> curSrc(accTable); curSrc.IsElm(); curSrc.Next())
    {
      //cout << "checking next source: " << curSrc.Key() << endl;

      // get current memory time
      DurationC curMemItemDuration = curSrc->ItemDuration();

      // check curMemItemDuration and catch up with time if necessary
      while(true)
      {
        //cout << "Cur item start time: " << curMemItemDuration.Start() << endl;

        bool needToReadMemory = false;
        if(curMemItemDuration.IsValid()) // curMemItem must be valid for any kind of stop
        {
          if(curSrc->Eof())  // end of memory
          {
            //cout << "VAMMultyAccessBodyC::Next:return false because of eof in:" << endl;
            eof = true;
            return false;
          }

          if(endTc.IsValid()) //check if current memory item is out of upper time boundary
          { 
            if(curMemItemDuration.End() > endTc) 
            {
              //cout << "VAMMultyAccessBodyC::Next:return false because of upper boundary in:" << endl;
              eof = true;
              return false;
            }
          }
        
          if(curMemItemDuration.Start() == targetTC) // exact match
          {
            //cout << "this input is syncronised\n";
            break;
          } 
          else if(curMemItemDuration.Start() > targetTC)  //change targetTC
          {
            targetTC = curMemItemDuration.Start();
            stable = false; //need to check all sources again
            //cout << "update targetTC to " << targetTC << endl;
            break;
          } 
          else // if(curMemItemDuration.Start() < targetTC) //try to catch up with time
          {
            //cout << "try to catch up with time\n";
            //cout << "targetTime:" << targetTC
            //     << "\ncurMemItem.Time:" << curMemItemDuration.Start() << endl;
            needToReadMemory = true;
          }
        }
        else
        {
          //cout << "Cur item is invalid\n";
          needToReadMemory = true;
        }

        if(needToReadMemory)
        {
          //read next memory item, possibly wait for it
          //cout << "reading memory:" << curSrc.Key() << endl;
          //cout << " curMemItemDuration.Start()" << curMemItemDuration.Start() << endl;
          if(!curSrc->Next(NoWait))
          {
            cout << "Can not move pointer\n";
            return false;
          }
          curMemItemDuration = curSrc->ItemDuration();      
          //cout << " curMemItemDuration.Start()" << curMemItemDuration.Start() << endl;
          //cout << "read ok\n";
        }
      } // end of while(true)
    }
  } while (!stable);
  //cout << "VAMMultyAccessBodyC::Next:normal return:" << endl;
  
  curStart = targetTC;
  return true;
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
  TimeCodeC targetTC(100000000);
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
  
  //sinc all sources
  for(HashIterC<StringC, VAMAccessC> curSrc(accTable); curSrc.IsElm() && retVal; curSrc.Next())
  {
    retVal &= MoveTo(targetTC, true);
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


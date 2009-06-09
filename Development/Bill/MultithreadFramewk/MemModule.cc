#include "Ravl/StringList.hh"
#include "Ravl/DList.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/Option.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/CDLIter.hh"

#include "Ravl/Threads/MemModule.hh"
#include "Ravl/Threads/MemModules.hh"

using namespace RavlN;


MemModuleBodyC::MemModuleBodyC(const StringC& ModuleName)
  : moduleName(ModuleName),
    options(StringListC("")),
    verbosity(0),
    logVerb(1),
    memory(ModuleName, VamInRamImOnDiskEC, verbosity),
    devnull("/dev/null"),
    state(Uninitialised), 
    stateLock(true)
{}


//: Sets up logs and options for running 
bool MemModuleBodyC::Init(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd)
{
  Memory().Attr("options") = Params;
  options = OptionC(StringListC(moduleName)+=Params);
  verbosity = options.Int("mv", 0,"Verbosity for memory management.");
  logVerb = options.Int("v", 1,"Verbosity for log file.");
  FilenameC logFile(LogDir + "/" + moduleName + ".log");
  log = OStreamC(logFile);
  RavlAssertMsg(log, "Couldn't open " + logFile);
  if(ShowLogWnd) {
    StringC logViewStr = StringC("xterm -sl 1000 -T ") + moduleName +
        " -e tail -f " + logFile + " &";
    if(verbosity > 0)
      cout << "starting log: " << logViewStr << endl;
    system (logViewStr.chars());
  }
#ifdef HAVE_PERSISTENT_MEMORY
  reuseData = options.Boolean("R", false, "re-use data from last run.");
  cerr << "reuse data: " << reuseData << endl;
  if(!reuseData) {
    items.Clean();
  }
#endif
  if(verbosity > 0)
    cout << "Verbosity level for module " << moduleName << " is " << verbosity << endl;
  return true;
}


//: Launches the module as a separate thread
void MemModuleBodyC::Launch(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd) 
{
  //  RavlAlwaysAssertMsg(0, "Module should not be launched: " + moduleName);

  MutexLockC lock(stateLock);

  //check if module is already running
  if (state != Uninitialised) {
    if(memory.WasLoaded()) {
      if(verbosity > 0)  cout << "Using loaded module:" << ModuleName() << endl;
    }
    // Module is already running, nothing to do!
    return;
  }
    
  MemModuleBodyC::Init(Params, LogDir, ShowLogWnd);
  state = Running;
  lock.Unlock();
  
  TriggerC processTrigger = Trigger(MemModuleC(*this), &MemModuleC::Thread);
  //threadDone.Reset();
  LaunchThread(processTrigger);
  
  if(verbosity > 0)
    cout << "launched " << ModuleName() << endl;
}


void MemModuleBodyC::RunNoThread(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd) 
{
  //check if module is already running
  if (state != Uninitialised) {
    if(memory.WasLoaded()) {
      if(verbosity > 0)  cout << "Using loaded module:" << ModuleName() << endl;
    }
    // Module is already running, nothing to do!
    return;
  }

  MemModuleBodyC::Init(Params, LogDir, ShowLogWnd);
  state = Running;
  MemModuleBodyC::Thread();
}


//: Sleeps until module is finished
bool MemModuleBodyC::Wait() {
  if(!memory.WasLoaded() && IsUsed()) {
    threadDone.Wait();
    if(verbosity > 0)
      cout << "Module " << ModuleName() << " has finished" << endl;
    return true;
  }
  return false;
}

//: A wrapper for the memory process to be launched
bool MemModuleBodyC::Thread() {
  bool success(false);
  try { 
    success = Run();
  }
  catch (ExceptionC ex) {
    cerr << "Ravl Exception caught in Module \"" << ModuleName() << "\"\n" << ex.Text() << endl;
    success = false;
  }
  catch(const std::exception& ex) {
    cerr << "exception in " << ModuleName() << ":" << ex.what() << endl;
    success = false;
  }
  catch (...) {
    cerr << "Exception caught in Module \"" << ModuleName() << "\"\n" << endl;
    success = false;
  }
  if(!success)
    cerr << ModuleName() << " finished with possibly bad results!\n";
  Close(); 

  if(verbosity > 0)
    cout << "Module " << ModuleName() << " [" << ID() << "] closing..." << endl;
  log << "Module closing..." << endl;
  threadDone.Post();

  MutexLockC lock(stateLock);
  state = Finished;
  return success;
}


//: Removes memory access from internal reference table of VAM
// the access object could still exist but main memory will not care about it
void MemModuleBodyC::ReleaseAccess(const StringC& Source) 
{ 
  if(verbosity > 0)
    cout << "Removing access from " << ModuleName() << " to " << Source << endl;

  VAMAccessC access;
  if(!ipSources.Lookup(Source, access)) //source is not created
  {
    cerr << "MemModuleBodyC::ReleaseAccessToSource:Trying to release access which was not created\n";
    throw ExceptionC("MemModuleBodyC::ReleaseAccessToSource:Trying to release access which was not created");
  }
  ModuleManager[Source].Memory().ReleaseMemoryAccess(ModuleName());
  ipSources.Del(Source);
}

//: Releases all memory accesses to other modules
void MemModuleBodyC::ReleaseAllAccesses()
{
  if(verbosity > 1)
    cout << "MemModuleBodyC::ReleaseAllAccesses in " << ModuleName() << " called\n";
  while(!ipSources.IsEmpty())
  {
    HashIterC<StringC, VAMAccessC> i(ipSources);
    if(verbosity > 7)
      cout << "Releasing: " << i.Key() << endl;
    ReleaseAccess(i.Key());
    if(verbosity > 7)
      cout << "Ok\n";
  }
  if(verbosity > 1)
    cout << "MemModuleBodyC::ReleaseAllAccesses in " << ModuleName() << " done\n";
}


//: Returns memory access. If there is no one it creates it
VAMAccessC MemModuleBodyC::GetAccess(const StringC& Source,
                                      const TimeCodeC& Start, 
                                      const TimeCodeC& End)
{
  VAMAccessC access;
  if(!ipSources.Lookup(Source, access)) //create access
  {
    //create memory access
    if(verbosity > 0)
      cout << "adding access from " << ModuleName() << " to " << Source << endl;
    ipSources.Insert(Source, 
      ModuleManager.AccessModule(Source).Memory()
                     .GetMemoryAccess(ModuleName(), Start, End));
  }
  return ipSources[Source];
}

//: Returns joint access to several sources. It creates accesses to sources or uses already created
// Note: it uses already created accesses! 
//       If you need several accesses to one source use RemoveAccess function.
VAMJointAccessC MemModuleBodyC::GetJointAccess(const StringListC& SourceNames,
                                               const TimeCodeC& Start, 
                                               const TimeCodeC& End)
{
  VAMJointAccessC jointAccess;
  for(ConstDLIterC<StringC> curSrc(SourceNames); curSrc; ++curSrc)
  {
    VAMAccessC access = GetAccess(*curSrc);
    jointAccess.AddAccess(*curSrc, access);
  }
  if(Start.IsValid() && End.IsValid())
    jointAccess.SetBounds(Start, End);
  return jointAccess;
}                               


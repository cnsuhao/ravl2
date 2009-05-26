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

MemModuleBodyC::MemModuleBodyC(const MemModulesC &OtherMemModules,
                               int Verbosity,
                               MemTypeE MemType, const StringC& MemParam)
  : options(StringListC("")), 
    verbosity(Verbosity),
    memory("", MemType, MemParam, verbosity),
    log(""),
    valid(true),
    otherMemModules(OtherMemModules),
    running(false),
    finished(true)
{
}

MemModuleBodyC::MemModuleBodyC(MainModuleFuncT Func, const StringC& ModuleName, 
                               const MemModulesC &OtherMemModules,
                               const StringC& Params, const FilenameC& LogDir,
                               MemTypeE MemType, const StringC& MemParam,
                               bool ShowLogWnd)
  : options(OptionC(StringListC(ModuleName)+=Params)),
    verbosity(options.Int("mv", 0,"Verbosity for memory managemnt.")),
    memory(ModuleName, MemType, MemParam, verbosity),
    log(LogDir + "/" + ModuleName + ".log"),
    valid(true),
    otherMemModules(OtherMemModules),
    running(false),
    finished(false)
{
  if(ShowLogWnd)
  {
    StringC logViewStr = StringC("xterm -T ") + ModuleName +
        " -e tail -f " + LogDir + "/" + ModuleName + ".log &";
    if(verbosity > 0)
      cout << "starting log:" << logViewStr << endl;
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
    cout << "Verbosity level for module " << ModuleName << " is " << verbosity << endl;
  processTrigger = TriggerR(*this, &MemModuleBodyC::Thread, Func);
}

MemModuleBodyC::~MemModuleBodyC()
{
  ReleaseAllAccesses();
}

//: Returns memory access. If there is no one it creates it
VAMAccessC& MemModuleBodyC::GetAccess(const StringC& Source,
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
      otherMemModules[Source].Memory().GetMemoryAccess(ModuleName(), 
                                                       Start, End));
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
    jointAccess.AddAccess(*curSrc, GetAccess(*curSrc));
  }
  if(Start.IsValid() && End.IsValid())
    jointAccess.SetBounds(Start, End);
  return jointAccess;
}                               

//: Removes memory access from internal reference table of VAM
// the access object could still exist but main memory will not care about it
void MemModuleBodyC::ReleaseAccess(const StringC& Source) 
{ 
  if(verbosity > 0)
    cout << "removing access from " << ModuleName() << " to " << Source << endl;

  VAMAccessC *maPtr = ipSources.Lookup(Source);
  if(maPtr == NULL) //source is not created
  {
    cerr << "MemModuleBodyC::ReleaseAccessToSource:Trying to release access which was not created\n";
    throw ExceptionC("MemModuleBodyC::ReleaseAccessToSource:Trying to release access which was not created");
  }
  otherMemModules[Source].Memory().ReleaseMemoryAccess(ModuleName());
  ipSources.Del(Source);
}

//: Releases all memory accesses to other modules
void MemModuleBodyC::ReleaseAllAccesses()
{
  if(verbosity > 1)
    cout << "MemModuleBodyC::ReleaseAllAccesses called\n";
  while(!ipSources.IsEmpty())
  {
    HashIterC<StringC, VAMAccessC> i(ipSources);
    if(verbosity > 7)
      cout << "Releasing:" << i.Key() << endl;
    ReleaseAccess(i.Key());
    if(verbosity > 7)
      cout << "Ok\n";
  }
  if(verbosity > 1)
    cout << "MemModuleBodyC::ReleaseAllAccesses done\n";
}

//: Launches the module as a separate thread
void MemModuleBodyC::Launch() 
{
  if(!WasLoaded()) 
  {
    processThread = LaunchThread(processTrigger);
    if(verbosity > 0)
      cout << "launched " << ModuleName() << endl;
  }
}

//: Sleeps until module is finished
bool MemModuleBodyC::Wait()
{ 
  if(!WasLoaded()) 
  {
    if(!finished)
    {
      processThread.WaitForExit();
      if(verbosity > 0)
        cout << "Module " << ModuleName() << " has finished" << endl;
      return true;
    }
  }
  return false;
}

//: A wrapper for the memory process to be launched
bool MemModuleBodyC::Thread(bool(*func)(MemModuleBodyC&)) {
  bool success(false);
  running = true;
  try { 
    success = func(*this);
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
  running = false;
  finished = true;
  if(verbosity > 0)
    cout << "Module " << ModuleName() << " [" << ID() << "] closing..." << endl;
  log << "Module closing..." << endl;
  return success;
}

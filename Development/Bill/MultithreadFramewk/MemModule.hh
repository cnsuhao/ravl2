#ifndef MEMMODULE_HH
#define MEMMODULE_HH

#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/StringList.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/Option.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/IO.hh"
#include "Ravl/Threads/ThreadEvent.hh"

#include "Ravl/Threads/VamBase.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

class MemModulesC;

//! userlevel=Develop
//: Body of a memory module + associated process call
// This is the class that specific modules inherit

class MemModuleBodyC : public RCBodyVC {

 public:

  //:-----------------
  //: Constructor / destructor
  MemModuleBodyC(const StringC& ModuleName);
  //: Constructor from process name

  virtual ~MemModuleBodyC() { 
    ReleaseAllAccesses();
  }

 protected:  
  //:-----------------
  //: Running specific modules
  // These functions are generally used by the derived module classes when running the module.
  // They do not appear in the handle.

  VAMAccessC GetAccess(const StringC& Source,
                        const TimeCodeC& Start = TimeCodeC(-1, 50), 
                        const TimeCodeC& End = TimeCodeC(RavlConstN::maxInt, 50));
  //: Returns memory access to source. 
  // If the source memory is not available, the source module is launched as a separate thread.
  
  VAMJointAccessC GetJointAccess(const StringListC& Sources,
                                 const TimeCodeC& Start = TimeCodeC(-1, 50), 
                                 const TimeCodeC& End = TimeCodeC(RavlConstN::maxInt, 50));
  //: Returns joint access to several sources.  
  // <p> The access will iterate
  //   through the sources synchronously, i.e. returning a set of memory items
  //   that have intersecting timecodes.</p>
  // <p> If you need to get several items from one module for each item of
  //   another module, use nested loops with separate accesses instead.</p>
  // 
  // <p> If you need several accesses to one source use RemoveAccess function.</p>

  void Add(const MemoryItemC& Item)
    { memory.Add(Item); }
  //: Adds item to memory

  OptionC Options()
    { return options; }
  //: Returns options for memory module

  OStreamC& Log(IntT Verbosity=0)
    { return (logVerb >= Verbosity) ? log : devnull; }
  //: Log message 
  // Logs message if module logging verbosity >= arg.<br>
  // Default is to log regardless

  template <class PixelT>
  void Log(IntT Verbosity, const StringC& Dest, const RavlImageN::ImageC<PixelT>& Img) const
    { if (logVerb >= Verbosity) RavlN::Save(Dest, Img); }
  //: Save/display image

  bool Verbosity(IntT Verbosity) const 
    { return (logVerb >= Verbosity); }
  //: Test if given verbosity is above threshold for log
  // True if given verbosity >= default verbosity level

  IntT Verbosity() const 
    { return (logVerb); }
  //: Verbosity level used for log

public:
  //:-----------------
  //: The remaining functions mirror the handle functions

  void Load(XMLIStreamC &Strm, const TimeCodeC& Start, const TimeCodeC& End)
    {
      Memory().Load(Strm, Start, End) ;
      MutexLockC lock(stateLock);
      state = Finished;
    }
  //: Loads elements in memory from XML stream

  bool Init(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd);
  //: Initialise ready for running
  //!param: params - parameters for process in form of string of options
  //!param: logDir - directory for log file
  //!param: ShowLogWnd - show module progress log in separate window
  // Not needed if module is loaded from memory

  void Launch(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd);
  //: Launches the module as a separate thread
  //!param: params - parameters for process in form of string of options
  //!param: logDir - directory for log file
  //!param: ShowLogWnd - show module progress log in separate window

  void RunNoThread(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd) ;
  //: Runs the module without threading
  //!param: params - parameters for process in form of string of options
  //!param: logDir - directory for log file
  //!param: ShowLogWnd - show module progress log in separate window

  virtual bool Run()=0;
  //: Run the actual code of the specific module

  bool Wait();
  //: Sleeps until module is finished
  // Returns true if really waited

  const VAMC& Memory() const
    { return memory; }
  //: Returns the memory of this module for reading

  VAMC& Memory()
    { return memory; }
  //: Returns the memory of this module for reading

  StringC ModuleName() const
    { return memory.MemoryName(); }
  //: Returns module name

  IntT ID()
  { if(memory.WasLoaded()) return -1; else return (SizeT) this; }
  //: Returns thread ID of this module

  void Close() 
    { memory.End(); }
  //: No more items to be added to this memory

  bool Thread();
  //: A wrapper for the memory process to be launched
  // Does anything that is common to all processes

  bool IsUsed() const  {
    MutexLockC lock(stateLock);
    return (state != Uninitialised);
  }
  
  bool IsRunning() const { 
    MutexLockC lock(stateLock);
    return (state == Running);
  }

  void Stop(bool StopFlag = true)
    { memory.Stop(StopFlag); }
  //: stop processing nicely

  bool AskedToStop() const
    { return memory.AskedToStop(); }

  void ReleaseAccess(const StringC& Source);
  //: Removes memory access from internal reference table of VAM
  // It also removes it from list of inputs for this module

  void ReleaseAllAccesses();
  //: Removes all memory accesses to other modules



 private:
  StringC moduleName;  // used to pass name from constructor to memory
  OptionC options;   // to pass options through to processes
  ThreadEventC threadDone;  // signals that thread is finished
  
  HashC<StringC, VAMAccessC> ipSources;  // list of i/ps from other module memories
  int verbosity; // verbosity for memory system and base module
  int logVerb;   // verbosity for applicatino modules
  VAMC memory;  // memory items for this module
  OStreamC log;     // for logging interesting moments
  OStreamC devnull; // for disposing of uninteresting log messages

  // items that deal with the current state of the module
  typedef enum {Uninitialised, Running, Finished} ModuleStateT; // possible module states
  ModuleStateT state; // current module state
  mutable MutexC stateLock;  // lock for state

  MemModuleBodyC(const MemModuleBodyC &);
  //: Disable body copy constructor.
  // no definition -> linker error
  
};

//! userlevel=Normal
//:  A memory module.

// <p> Includes:</p> <ul>
// <li> the data storage (VAMC)</li>
// <li> associated call to process that generates the data</li>
// <li> links (MemoryAccessC) to other modules to get data from</li>
// <li> means of launching itself off as a separate thread</li>
// </ul>
// <p> Individual modules inherit the <a href="MemModuleBodyC.html">body
//   class</a> only, which has additional functionality for accessing and
//   manipulating the module contents.</p>

class MemModuleC : public RCHandleC<MemModuleBodyC>
{
 protected:
  MemModuleC(MemModuleBodyC &bod)
    : RCHandleC<MemModuleBodyC>(bod)
    {}
  //: Body constructor.

 public:
  MemModuleC()
    {}
  //: Default constructor.
  // Creates an invalid handle.
  
  void Load(XMLIStreamC &Strm, const TimeCodeC& Start, const TimeCodeC& End)
    { Body().Load(Strm, Start, End); }
  //: Loads elements in memory from XML stream

  bool Init(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd)
    { return Body().Init(Params, LogDir, ShowLogWnd); }
  //: Sets up logs and options for running
  //!param: params - parameters for process in form of string of options
  //!param: logDir - directory for log file
  //!param: ShowLogWnd - show module progress log in separate window

  void Launch(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd)
    { Body().Launch(Params, LogDir, ShowLogWnd); }
  //: Launches the module as a separate thread if needed
  //!param: params - parameters for process in form of string of options
  //!param: logDir - directory for log file
  //!param: ShowLogWnd - show module progress log in separate window
  // It checks that module has not been run and results are not available; if neither, it launches the thread

  void RunNoThread(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd)
    { Body().RunNoThread(Params, LogDir, ShowLogWnd); }
  //: Runs the module without threading
  //!param: params - parameters for process in form of string of options
  //!param: logDir - directory for log file
  //!param: ShowLogWnd - show module progress log in separate window

  bool Wait()
    { return Body().Wait(); }
  //: Sleeps until module is finished
  
  VAMC Memory() const
    { return Body().Memory(); }
  //: Returns the memory of this module for reading

  StringC ModuleName() const 
    { return Body().ModuleName(); }
  //: Returns module name
  
  IntT ID()
    { return Body().ID(); }
  //: Returns thread ID of this module

  void Close()
    { Body().Close(); }
  //: No more items to be added to this memory

  bool Thread()
    { return Body().Thread(); }
  //: A wrapper for the memory process to be launched
  // Does anything that is needed for all processes

  bool IsUsed() const  
  { return Body().IsUsed(); }
  //: Is used ?
  
  bool IsRunning() const
    { return Body().IsRunning(); }

  void Stop(bool StopFlag)
    { Body().Stop(StopFlag); }
  //: stop processing nicely

  bool AskedToStop() const
    { return Body().AskedToStop(); }

  void ReleaseAccess(const StringC& Source)
    { Body().ReleaseAccess(Source); }
  //: Removes memory access from internal table

  void ReleaseAllAccesses()
    { Body().ReleaseAllAccesses(); }
  //: Removes all memory accesses

  friend void MemModuleBodyC::Launch(const StringC& Params, const FilenameC& LogDir, bool ShowLogWnd);

};
  
#endif

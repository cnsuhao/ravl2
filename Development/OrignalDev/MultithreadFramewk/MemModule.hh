#ifndef MEMMODULE_HH
#define MEMMODULE_HH

#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/Trigger.hh"
#include "Ravl/StringList.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/Option.hh"
#include "Ravl/OS/Filename.hh"

#include "Ravl/Threads/VamBase.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

class MemModulesC;

//! userlevel=Develop
//: Body of a memory module + associated process call

class MemModuleBodyC;
typedef bool(*MainModuleFuncT)(MemModuleBodyC&);

class MemModuleBodyC : public RCBodyC {
 public:

//  MemModuleBodyC()
//    :  memType("none"), options(StringListC()), 
//       items("default constructor MemModuleBodyC()"), valid(false)
//
//  {}
  //: Default constructor must not be used

   MemModuleBodyC(const MemModulesC &OtherMemModules,
                  int Verbosity,
                  MemTypeE MemType, const StringC& MemParam);
  //: Load constructor 

   MemModuleBodyC(MainModuleFuncT Func, const StringC& ModuleName,
                  const MemModulesC &OtherMemModules,
                  const StringC& params, const FilenameC& logDir,
                  MemTypeE MemType, const StringC& MemParam,
                  bool ShowLogWnd);
  //: Constructor from process and process arguments
  //!param: func - the process associated with the memory component
  //!param: ModuleName - name of the memory component
  //!param: params - parameters for process in form of string of options
  //!param: logDir - directory for log file
  //!param: MemType - type of memory (currently implemented VamAllInRam)
  //!param: MemParam - parameter for memory class (SavePrefix for VamAllInRamImOnDisk)

   ~MemModuleBodyC();

  void Launch();
  //: Launches the module as a separate thread

  bool Wait();
  //: Sleeps until module is finished
  // returns true if really waited

  const VAMC& Memory() const
    { return memory; }
  //: Returns the memory of this module for reading

  VAMC& Memory()
    { return memory; }
  //: Returns the memory of this module for reading

  StringC& ModuleName()
    { return memory.MemoryName(); }
  //: Returns module name

  const StringC& ModuleName() const 
    { return memory.MemoryName(); }
  //: Returns module name

  void Add(const MemoryItemC& Item)
    { memory.Add(Item); }
  //: Adds item to memory

  VAMAccessC& GetAccess(const StringC& Source,
                        const TimeCodeC& Start = TimeCodeC(-1, 50), 
                        const TimeCodeC& End = TimeCodeC(RavlConstN::maxInt, 50));
  //: Returns memory access to source. If there is no one it creates it.
  
  VAMJointAccessC GetJointAccess(const StringListC& SourceNames,
                                 const TimeCodeC& Start = TimeCodeC(-1, 50), 
                                 const TimeCodeC& End = TimeCodeC(RavlConstN::maxInt, 50));
  //: Returns joint access to several sources. It creates accesses to sources or uses already created
  // Note: it uses already created accesses! 
  //       If you need several accesses to one source use RemoveAccess function.

  void ReleaseAccess(const StringC& Source);
  //: Removes memory access from internal reference table of VAM
  // also removes it from list of inputs for this module

  void ReleaseAllAccesses();
  //: Removes all memory accesses to other modules

  OptionC& Options()
    { return options; }
  //: Returns options for memory module

  OStreamC& Log()
    { return log; }
  //: Access to logging stream for module

  IntT ID()
  { if(WasLoaded()) return -1; else return processThread.ID(); }
  //: Returns thread ID of this module

  void Close() 
    { memory.End(); }
  //: No more items to be added to this memory

  bool Thread(bool(*func)(MemModuleBodyC&));
  //: A wrapper for the memory process to be launched
  // Does anything that is needed for all processes

  operator bool() const
    { return valid; }
  //: True if this is a valid module (e.g. properly constructed)

  bool IsRunning() const
    { return running; }

  void Stop(bool StopFlag = true)
    { memory.Stop(StopFlag); }
  //: stop processing nicely

  bool WasLoaded() const
    { return memory.WasLoaded(); }

  bool AskedToStop() const
    { return memory.AskedToStop(); }
 private:
  MemModuleBodyC(const MemModuleBodyC &); // no definition, linker error
  //: Disable copy constructor.
  
  TriggerC processTrigger;
  LaunchThreadC processThread;
  HashC<StringC, VAMAccessC> ipSources;  // the actual i/ps for the module
  OptionC options;   // to pass options through to processes
  int verbosity;
  VAMC memory;  // memory items for this module
  OStreamC log; // for logging interesting moments to some forgotten file
  bool valid;
  const MemModulesC& otherMemModules; //for read only access to other modules
  bool running; // true if module is running

  //in theory 'finished' must be covered by RWLock, 
  //but current modules slow therefore everything shold work ok by now
  bool finished; 
};

//! userlevel=Normal
//:  A memory module.

// Includes: <ul>
// <li> the data storage (VAMC)</li>
// <li> associated call to process that generates the data</li>
// <li> links (MemoryAccessC) to other modules to get data from</li>
// <li> means of launching itself off as a separate thread</li>
// </ul>

class MemModuleC : public RCHandleC<MemModuleBodyC>
{
 public:

//  MemModuleC()
//    : RCHandleC<MemModuleBodyC>(*new MemModuleBodyC())
//  {}
  //: Default constructor

   MemModuleC(const MemModulesC &OtherMemModules,
              int Verbosity, MemTypeE MemType, const StringC& MemParam)
    : RCHandleC<MemModuleBodyC>(*new MemModuleBodyC(OtherMemModules,
                                                    Verbosity, MemType, MemParam))
    {}
   //: Load constructor 

   MemModuleC(MainModuleFuncT Func, const StringC& ModuleName,
             const MemModulesC &OtherMemModules,
             const StringC& Params, const FilenameC& LogDir,
             MemTypeE MemType, const StringC& MemParam,
             bool ShowLogWnd)
    : RCHandleC<MemModuleBodyC>(*new MemModuleBodyC(Func, ModuleName, 
                                                    OtherMemModules,
                                                    Params, LogDir,
                                                    MemType, MemParam,
                                                    ShowLogWnd))
    {}
  //: Constructor from process and process arguments
  //!param: func - the process associated with the memory component
  //!param: ModuleName - name of the memory component
  //!param: ipNames - array of names of other memory components needed for i/p to the process
  //!param: params - parameters for process in form of string of options
  
  void ReleaseAccess(const StringC& Source)
    { Body().ReleaseAccess(Source); }
  //: Removes memory access from internal table

  void ReleaseAllAccesses()
    { Body().ReleaseAllAccesses(); }
  //: Removes all memory accesses

  void Launch()
  { Body().Launch(); }
  //: Launches the module as a separate thread

  bool Wait()
  { return Body().Wait(); }
  //: Sleeps until module is finished
  
  VAMC Memory() const
    { return Body().Memory(); }
  //: Returns the memory of this module for reading

  StringC& ModuleName() 
    { return Body().ModuleName(); }
  //: Returns module name
  
  const StringC& ModuleName() const 
    { return Body().ModuleName(); }
  //: Returns module name
  
  void Add(const MemoryItemC& Item)
    { Body().Add(Item); }
  //: Adds item to memory

  OptionC Options()
    { return Body().Options(); }
  //: Returns options for memory module

  IntT ID()
    { return Body().ID(); }
  //: Returns thread ID of this module

  void Close()
    { Body().Close(); }
  //: No more items to be added to this memory

  operator bool() const
    { return Body().operator bool(); }
  //: True if this is a valid module (e.g. properly constructed)
  
  bool Thread(bool(*func)(MemModuleBodyC&))
    { return Body().Thread(func); }
  //: A wrapper for the memory process to be launched
  // Does anything that is needed for all processes

  bool IsRunning() const
    { return Body().IsRunning(); }

  void Stop(bool StopFlag)
    { Body().Stop(StopFlag); }
  //: stop processing nicely

  bool WasLoaded() const
    { return Body().WasLoaded(); }

  bool AskedToStop() const
    { return Body().AskedToStop(); }
 protected:
  MemModuleC(MemModuleBodyC &body)
    : RCHandleC<MemModuleBodyC>(body)
    {}
  //: Body constructor.
};
  
#endif

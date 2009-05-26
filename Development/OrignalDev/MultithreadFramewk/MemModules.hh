#ifndef MEMMODULES_HH
#define MEMMODULES_HH

#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/StringList.hh"
#include "Ravl/RCHash.hh"

#include "Ravl/Threads/MemModule.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

//! userlevel=Normal
//: The set of memory modules and their interconnection
//  A collection of MemModuleC memory modules, together with means of starting them as separate threads, and a means of visualising the memory contents.

class MemModulesC
{
 public:
   
  MemModulesC(const FilenameC& MemOutDir, const StringC& CommandLine, UIntT Verbosity);
  //: Constructor
  //!param: MemOutDir - the directory where the memory will be stored
  //!param: CommandLine - the command line used to run the program, for future reference
  //!param: Verbosity - controls level of diagnostic information of the memory system

  ~MemModulesC();
  //: Destructor


  //!section: Setup methods, that should be called before modules are launched
  void ShowDviDisplay()
  { textDisplay = true; }
  //: Show memory contents as text in xdvi window

  void ShowLogWindows()
  { showLogWnds = true; }
  //: Show module logs in separate xterms

  void ForgetMemory()
  { forget = true; }
  //: Forget memory contents that is no longer wanted

  void SetLogDir(const FilenameC& Dir)
  { logDir = Dir; }
  //: Set directory for module log files.
  // Default is memory directory + "/log"

  void SetOptionsFile(const FilenameC& OptFile);
  //: Set name for file containing module options. 
  // If not set, no module options are read. <br>
  // Each line of the file consists of a module name followed by a set of options for that module in a format to be processed by OptionC.

  bool RegisterModuleFunction(MainModuleFuncT Func, const StringC& ModuleName)
  { return modulesMainFunctions.Insert(ModuleName, Func); }
  //: Register a main memory function
  //!param: Func - the process associated with the memory module
  //!param: ModuleName - name of the memory module
    
  //!section: Module access functions

  MemModuleC& operator[] (const StringC& name);
  //: Access the named module (thread safe)

  const MemModuleC& operator[] (const StringC& name) const;
  //: Access the named module (thread safe)

  RCHashC<StringC,StringC>& OptionsTab() {return optionsTab;}
  //: Table of options lists for the modules

  const RCHashC<StringC,StringC>& OptionsTab() const {return optionsTab;}
  //: Table of options lists for the modules

  StringListC GetModulesList() const;
  //: Returns list of names of currently launched modules

  //!section: Starting, running and stopping the system

  void Launch(const StringListC& ops);
  //: Launches all required modules
  // Determines which modules are needed in addition to those in "ops", and launches them all

  void Wait();
  //:  Waits for the threads to finish

  void StopProcessing(bool StopFlag = true);
  //:Stop processing if StopFlag = true
  // You can call this function many time with no harm<br>
  // If StopFlag = false it clears stop flag in all modules

  bool IsEndOfSession() const 
    { return endOfSession; }
  //: True if memory processes have all finished

  //!section: Miscellaneous

  void Load(const FilenameC& DirName, int StartField, int NumFields);
  //: Loads precomputed memory contents from set of files

  friend ostream &operator<< (ostream &strm, const MemModulesC &mem); 

 protected:
  MemModuleC& CreateAndLaunchMemModule(const StringC& ModuleName);
  //: create and launch mem module (thread safe)

  void AddIps(const StringC& op);
  //: Finds required i/p modules for module recursively

  bool ListMemory();
  //: Displays memory contents as a text window
  // The display is updated at regular intervals

  void Load(XMLIStreamC &Strm, const TimeCodeC& Start, const TimeCodeC& End, const StringC& inPrefix);
  //: Loads all memory from stream  

  void Save(const FilenameC& DirName);
  //: Saves top-level XML file

  void Save(XMLOStreamC &Strm) const;
  //: Saves top-level into XML stream

  bool textDisplay;  
  bool forget;
  bool endOfSession;
  LaunchThreadC textDisplayThread;
  FilenameC logDir;
  RCHashC<StringC,StringC> optionsTab;
  UIntT verbosity;
  HashC<StringC,MemModuleC> modules;
  HashC<StringC,MainModuleFuncT> modulesMainFunctions;
  //  Alex: I don't understand why these 2 locks are necessary, because only one thread seems to be running when they are used.
  mutable MutexC modulesTableLock; // to coordinate accesses to list of modules
  mutable MutexC endOfSessionLock; // for correct display
  FilenameC memoryDir;
  bool showLogWnds;
  StringC commandLine; // command line used to create precomputed memory (if any)
};

ostream &operator<< (XMLOStreamC &strm, const MemModulesC &mem); 
//: Outputs short-term memory in text form

#endif

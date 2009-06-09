#include "Ravl/Threads/MemModules.hh"
#include "Vampire/MiniList.hh"

#include "Ravl/EntryPnt.hh"
#include "Ravl/Option.hh"

//! docentry="Vampire"
//! userlevel = Normal
//: Creates list of memory modules and launches them

using namespace RavlN;

int Server(int argc, char* argv[]) {
  OptionC opt(argc, argv, true);
  //storage related options
  StringC       stream(opt.String ("i",   "./tmp.jpg", "input video stream"));
  StringC       aStream(opt.String ("ai",  "", "input audio stream"));
  UIntT     noOfFrames(opt.Int    ("n",   -1, "no. of frames"));
  IntT      startFrame(opt.Int    ("sf",  0,  "Start frame"));
  StringC      startTC(opt.String ("st",  "00:00:00:00", "Start timecode"));
  FilenameC   memInDir(opt.String ("mi",  "", "Directory for memory loading"));
  FilenameC  memOutDir(opt.String ("mo",  "/tmp/vampiremem", "Directory for storing memory"));
  int       startField(opt.Int    ("I",   -1, "Start field to load from memory storage (default: beginning of memory)"));
  int   numberOfFields(opt.Int    ("N",   -1, "Number of fields to load from memory storage (default: until end of memory)"));
  //processing related options
  StringC  optionsFile(opt.String ("opt", "options", "File containing option strings for modules (empty string -> default values)"));
  StringListC  outputs(opt.List   ("T",   "shotBoundary", "List of desired target modules"));
  bool          forget(opt.Boolean("F",   false, "forget unwanted data in memory"));
  StringC maskName(opt.String     ("mask", StringC(getenv("PROJECT_OUT"))+"/share/data/mask.png", "Mask to exclude image regions from tracking (black = omit point)"));
  //debug options
  bool     textDisplay(opt.Boolean("t",   false, "display memory as text"));
  UIntT      verbosity(opt.Int    ("v",   0, "Verbosity for modules manager"));
  StringC       logDir(opt.String ("l",   "", "log file directory"));
  bool     showLogWnds(opt.Boolean("sl",   false, "show windows with logs"));
  opt.DependXor("sf st");
  opt.Check();
  try {
    if (opt.IsOnCommandLine("st")) {
      TimeCodeC tc(startTC);
      if (!tc.IsValid()) throw ExceptionC("Invalid start time code: "+startTC);
      startFrame = tc.getFrameCount();
    }
    // create the memory system
    ModuleManager.Init(memOutDir, argc, const_cast<const char**>(argv), verbosity);
    if (textDisplay)            ModuleManager.ShowDviDisplay();
    if (showLogWnds)            ModuleManager.ShowLogWindows();
    if (forget)                 ModuleManager.ForgetMemory();
    if (!logDir.IsEmpty())      ModuleManager.SetLogDir(logDir);
    if (!optionsFile.IsEmpty()) ModuleManager.SetOptionsFile(optionsFile);

    // register all modules needed for *this* application
    RegisterModules();
    cout << "Modules are: " << ModuleManager.GetModulesList() << endl;
    // read precomputed memory if there is any
    if(!memInDir.IsEmpty()) {
      ModuleManager.Load(memInDir, startField, numberOfFields);
    }

    if(!stream.IsEmpty()) {
      ModuleManager.OptionsTab()["frame"] += StringC(" -i ") + stream;
    }
    if(noOfFrames > 0) {
      ModuleManager.OptionsTab()["frame"] += StringC(" -n ") + noOfFrames;
    }
    if(startFrame > 0) {
      ModuleManager.OptionsTab()["frame"] += StringC(" -s ") + startFrame;
    }
    if(!aStream.IsEmpty())
      ModuleManager.OptionsTab()["frame"] += StringC(" -ai ") + aStream;

    ModuleManager.Launch(outputs);  // launch the required modules

    ModuleManager.Wait();  // & wait for them to finish
  } 
  catch(const ExceptionC& Exc)
  {
    cerr << "ExceptionC caught and processed in main:\n" << Exc.Text() << endl;
    return -1;
  } 
  catch(const std::exception& ex) 
  {
    cerr << " Exception: " << ex.what() << " in " << argv[0] << endl;
    return -1;
  } 
  catch(...) 
  {
    cerr << "Unknown exception in " << argv[0] << endl;
    return -1;
  }

  return (0);
}


RAVL_ENTRY_POINT(Server);


#include "Ravl/SArray1d.hh"
#include "Ravl/DArray1dIter.hh"
#include "Ravl/CDLIter.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/IO.hh"
#include "Ravl/HashIter.hh"
  
#include "Ravl/Threads/MemModules.hh"

MemTypeE MyMemType = VamInRamImOnDiskEC; //hardwired for a while, will be parameter

//: Constructor
MemModulesC::MemModulesC(const FilenameC& memOutDir, const StringC& CommandLine, UIntT Verbosity)
  : textDisplay(false), forget(false), endOfSession(false), 
    logDir(memOutDir + "/log"), verbosity(Verbosity), modulesTableLock(true), 
    memoryDir(memOutDir), showLogWnds(false), commandLine(CommandLine)
{
  if (!((memoryDir.Exists() && memoryDir.IsDirectory() && memoryDir.IsWritable()) || memoryDir.MakeDir()))
    throw ExceptionC("Can't create directory for writing memory: " + memOutDir);
}

MemModulesC::~MemModulesC()
{
  if(verbosity > 1)
    cout << "MemModulesC::~MemModulesC called\n";
  modulesTableLock.Lock();

  for(HashIterC<StringC, MemModuleC> curModule(modules); curModule; curModule++)
  {
    if(verbosity > 7)
      cout << "Release accesses in:" << curModule.Key() << endl;
    curModule->ReleaseAllAccesses();
    if(verbosity > 7)
      cout << "Done\n";
  }

  modulesTableLock.Unlock();
  if(verbosity > 1)
    cout << "MemModulesC::~MemModulesC done\n";
}

//: Set name for file containing module options.  
void MemModulesC::SetOptionsFile(const FilenameC& OptFile)
{
  if (OptFile.IsReadable() && !OptFile.IsDirectory()) {
    if(verbosity > 0)
      cout << "Reading options from \"" << OptFile << "\"" << endl;
    IStreamC in(OptFile);
    StringC s;
    while (in) {
      readline(in,s);
      if (!s.IsEmpty()) optionsTab.Insert(s.before(' '), s.after(' '));
    }
  }
  else if (!OptFile.IsEmpty())
    cout << "Could not read options file \"" << OptFile << "\"" << endl;
}


//: create and launch mem module
MemModuleC& MemModulesC::CreateAndLaunchMemModule(const StringC& ModuleName)
{
  modulesTableLock.Lock();

  //check if module is already running
  if(modules.IsElm(ModuleName))
  {
    MemModuleC *mmPtr = modules.Lookup(ModuleName);
    modulesTableLock.Unlock();

    if(!mmPtr->WasLoaded())
    {
      StringC err = StringC("Attempt to run module for second time:") + ModuleName;
      cerr << err << endl;
      throw ExceptionC(err);
    }
    if(verbosity > 0)
      cout << "Using loaded module:" << ModuleName << endl;

    return *mmPtr;
  }

  if(verbosity > 0)
    cout << "Creating and launching module:" << ModuleName << endl;
  
  //check if module registered
  if(!modulesMainFunctions.IsElm(ModuleName))
  {
    StringC err = StringC("Attempt to run not registered module:") + ModuleName;
    cerr << err << endl;
    throw ExceptionC(err);
  }

  //create mem module and add to the list of modules
  modules.Insert(ModuleName,
                 MemModuleC(modulesMainFunctions[ModuleName], ModuleName, 
                            *this, optionsTab[ModuleName], logDir, 
                            MyMemType, memoryDir, showLogWnds)); 

  // Alex: Why the pointer type?
  MemModuleC* newModule = modules.Lookup(ModuleName);
  newModule->Memory().Attr("options") = optionsTab[ModuleName];

  //Launch module
  newModule->Launch();

  modulesTableLock.Unlock();

  return *newModule;
}

//: Access the named module
const MemModuleC& MemModulesC::operator[] (const StringC& name) const 
{ 
  modulesTableLock.Lock();
  const MemModuleC *mmPtr = modules.Lookup(name);
  if(mmPtr != NULL) 
  {
    modulesTableLock.Unlock();
    return *mmPtr;
  }
//  cout << "Accessing not existing module:" << name << endl;
//  cout << "Error for constant object\n";
//  exit(-1);

  //allow to run modules for constant object
  const MemModuleC& newModule = ((MemModulesC*)this)->CreateAndLaunchMemModule(name);

  modulesTableLock.Unlock();
  return newModule;
}

//: Access the named module
MemModuleC& MemModulesC::operator[] (const StringC& name) 
{
  modulesTableLock.Lock();
  MemModuleC *mmPtr = modules.Lookup(name);

  if(mmPtr != NULL) 
  {
    modulesTableLock.Unlock();
    return *mmPtr;
  }

  MemModuleC& newModule = CreateAndLaunchMemModule(name);

  modulesTableLock.Unlock();
  return newModule;
}

//: Launches the modules as a set of separate threads
void MemModulesC::Launch(const StringListC& ModulesList) 
{  
  // A good moment to check that the log directory is there
  logDir.MakeDir();
  if (!(logDir.IsDirectory() && logDir.IsWritable())) {
    cerr << "Cannot write to log directory " << logDir
         << "; setting to /dev/null"<<endl;
    logDir = "/dev/null";
  }

  // Launch the modules
  for (ConstDLIterC<StringC> i(ModulesList); i; ++i) 
    CreateAndLaunchMemModule(*i);

  // If wanted, set the xdvi display going as another thread
  if (textDisplay) 
    textDisplayThread = LaunchThread(TriggerR(*this, &MemModulesC::ListMemory));
}

//:  Waits for the threads to finish. Wait for only currently running modules.
void MemModulesC::Wait() 
{
  bool waited;
  do
  {
    waited = false;

    StringListC modulesList = GetModulesList();
  
    for(ConstDLIterC<StringC> moduleName(modulesList); moduleName; ++moduleName) 
    {
      // Could these 2 lines be: if (*this)[*moduleName].Wait();  ?
      MemModuleC& curModule = operator[](*moduleName);
      if(curModule.Wait())
      {
        waited = true;  //Alex: what is this line for? Will only be true if module was loaded from file
      }
    }
  } while(waited);

  if(verbosity > 0)
    cout << "All modules have finished" << endl;
  this->Save(memoryDir);
  endOfSessionLock.Lock();
  endOfSession = true;
  endOfSessionLock.Unlock();
  if (textDisplay) 
    textDisplayThread.WaitForExit();
  //output top level XML file
}

void MemModulesC::StopProcessing(bool StopFlag)
{
  StringListC modulesList = GetModulesList();

  for(ConstDLIterC<StringC> moduleName(modulesList); moduleName; ++moduleName)
  {
    MemModuleC& curModule = operator[](*moduleName);
    curModule.Stop(StopFlag);
  }
}

//: returns list of names of currently launched modules
StringListC MemModulesC::GetModulesList() const
{
  StringListC modulesList;
  modulesTableLock.Lock();

  for(HashIterC<StringC, MemModuleC> curModule(modules); curModule; curModule++)
    modulesList.InsLast(curModule->ModuleName());

  modulesTableLock.Unlock();
  return modulesList;
}


void PrintTablePreampleLatex(OStreamC &Stream, 
                             const SArray1dC<StringC> &Names1, 
                             const SArray1dC<StringC> &Names2)
{
  int numCols = Names1.Size();

  Stream << "\\newpage";
  Stream << "\\begin{tabular}{|";
  for(int j = 0; j < numCols; j++)  
    Stream << "c|";  

  Stream << "}\\hline" << endl;

  Stream << "{\\bf " << Names1[0] << "}";
  for(int j = 1; j < numCols; j++)  
    Stream << "&{\\bf " << Names1[j] << "}";  
  Stream << "\\\\\n";

  Stream << "\\ [" << Names2[0] << "]";
  for(int j = 1; j < numCols; j++)  
    Stream << "\\ &[" << Names2[j] << "]";  
  Stream << "\\\\\n";

  Stream <<  "\\hline" << endl;
}

void PrintTableBottomLatex(OStreamC &Stream)
{
  Stream << "\\hline";
  Stream << "\\hline\\end{tabular}" << endl;
}

//: Displays memory contents using Latex / xdvi
bool MemModulesC::ListMemory() {
  bool firstTime(true);  // used to fire up xdvi 1st time round
  bool lastTime(false);  // 1 more pass needed after memory threads finished

  do {
    endOfSessionLock.Lock();
    if (endOfSession) 
      lastTime = true;
    endOfSessionLock.Unlock();

    StringListC modulesList = GetModulesList();
  
    // This forgetting bit isn't really part of display, but it is a handy place to put it, except that it will only work in text display mode
    // forget what is not wanted
    if (forget) {
      for(ConstDLIterC<StringC> moduleName(modulesList); moduleName; ++moduleName) 
      {
        if (verbosity>=2) cout<< "Forgetting unwanted memory" << endl;
        operator[](*moduleName).Memory().ForgetUnwanted();
      }
    }
    //open file
    OStreamC latex(logDir+"/log.tex");

    // Latex preamble
    latex << "\\documentclass[10pt]{article}"
          << "\\usepackage{fancyhdr} \\doublerulesep 0.5pt"
          << "\\voffset 0pt \\topmargin 0pt \\headheight 1em \\headsep 0.5em \\topskip 0pt \\textheight 120mm \\textwidth 800mm\\pagestyle{fancy}\\renewcommand{\\headrulewidth}{0pt}\\lhead{page \\thepage\\ of \\pageref{end}}\\cfoot{}\n"
          << "\\begin{document} \\tiny\\tt\n";

    //table preample
    int numOfModules = modulesList.Size(); 
    SArray1dC<StringC> names1(numOfModules+1), names2(numOfModules+1);
    names1[0] = "image \\#";
    names2[0] = StringC(CurrentThreadID());
    int colNum = 1;
    for(ConstDLIterC<StringC> moduleName(modulesList); moduleName; ++moduleName) 
    {
      MemModuleC& curModule = operator[](*moduleName);
      names1[colNum] = *moduleName;  // module names as headers
      if(curModule.IsRunning())
        names1[colNum] += " *";
      names2[colNum] = StringC(curModule.ID()); // module thread IDs
      colNum++;
    }

    // monitors on the memory contents
    // SArray1dC<MonitorHandle> access(wanted.Size());
    // initialise access to memory & lock it
    //    for(ConstDLIterC<StringC> j(wanted); j; j++, ++i) {
    //      access[i] = ((*this)[*j].Memory().Monitor(Constraints(*j)));
    //      (*this)[*j].Memory().RdLock(true);
    //    }

    //prepare table with memory accesses
    HashC<StringC, VAMAccessC> accessesTable;
    for(ConstDLIterC<StringC> moduleName(modulesList); moduleName; ++moduleName) 
    {
      MemModuleC& curModule = operator[](*moduleName);
      accessesTable.Insert(*moduleName, 
                           curModule.Memory().GetMemoryAccess("displayModule",
                                            TimeCodeC(-1, 50),
                                            TimeCodeC(RavlConstN::maxInt, 50)));
      curModule.Memory().ReleaseMemoryAccess("displayModule");
    }

    // go through memory and create body of table
    bool endOfMemory = false;
    int lineCount = 0;
    bool needToPrintBottomOfTable = false;
    for (TimeCodeC time(0, 50); !endOfMemory; ++time) {
//      cout << "time: " << time << endl;
      if(lineCount == 0 && !needToPrintBottomOfTable)
      {
//        cout << "printing table preamble\n";
        PrintTablePreampleLatex(latex, names1, names2);
        needToPrintBottomOfTable = true;
      }

      //prepare one line for output
      StrOStreamC line;  // build o/p line here to avoid outputting empty lines
      line << time.getFrameCount();
      endOfMemory = true;
      bool lineInfo(false); // true when >=1 list has something worth printing
      // for each list, get info relevant to current time code
      for(ConstDLIterC<StringC> moduleName(modulesList); moduleName; ++moduleName) 
      {
        //MemModuleC& curModule = operator[](*moduleName);

        line << "&";
        VAMAccessC& memAccess = accessesTable[*moduleName];

        // catch up with current time if possible
        DurationC itemDuration = memAccess.PeekDuration();
//        cout << "1cur time:" << time << "\titem end " << item.End() << endl;
        while(!memAccess.Eof() && (time > itemDuration.End()))  
        {
//          cout << "1cur time:" << time << "\titem end " << item.End() << endl;
          itemDuration = memAccess.GetNoWaitDuration();
          if(!itemDuration.IsValid())
            break; //no more items available
        }
//        cout << "2cur time:" << time << "\titem end " << item.End() << endl;
        if(!itemDuration.IsValid()) //default constructor for memory item was used
        {
//          cout << "no more memory items in: " << *moduleName << endl;
          continue; //no items in this VAM
        }
        if (!memAccess.Eof()) 
        {
          // if start of next item overlaps with this, move on to next
          /* disabled, because its not supported by the Monitor primitive
          if (!i->IsLast() && (time == i->NextData().Start()))  (*i)++;
          */
          // if item contains current time, o/p something
          if ((time >= itemDuration.Start()) && (time <= itemDuration.End())) 
          {
            lineInfo = true;
            if (time == itemDuration.Start()) 
              line << memAccess.PeekInfo();
              //line << itemDuration.Start() << " - " << itemDuration.End();
              //line << item.Dump(true);
            else if (time == itemDuration.End()) 
              line << "$\\bot$";
            else  
              line << '.';
          }
          endOfMemory = false;
        }
        else //print end of memory
        {
          lineInfo = true;
          if (time == itemDuration.Start()) 
            line << "--- EOF ---";
        }
      }

      if (lineInfo) 
      {
        latex << line.String() << "\\\\\n";
        if(++lineCount >= 50 && needToPrintBottomOfTable) //start new table
        {
          PrintTableBottomLatex(latex);
          lineCount = 0;
          needToPrintBottomOfTable = false;
        }
      }
    }

    // unlock memory
    //    for(ConstDLIterC<StringC> i(wanted); i; i++)  (*this)[*i].Memory().RdLock(false);
 
    if(needToPrintBottomOfTable)
    {
      PrintTableBottomLatex(latex);    
    }

    if(lastTime)
    {
      latex << "\n\n\nAll process finished!\n";
    }

    //finish document
    latex << "\\label{end}\\end{document}" << endl;
    latex.Close();

    //compile and show latex document
    StringC cmd("cd "+logDir+" && latex log >log.cmp && mv log.dvi logShow.dvi");
    system(cmd.chars());
    if (firstTime) {
      StringC xdvi("xdvi "+logDir+"/logShow -s 7 -paper 35x100 -offsets 0 -expert -keep -geometry 1200x480+0+0 &");
      system (xdvi.chars());
      firstTime=false;
    }
    else {
        // I don't understand why I should need to signal to xdvi-xaw3d.bin rather than xdvi, but there you go
      system ("killall -s 10 xdvi-xaw3d.bin");
    }

    if (!lastTime)  Sleep(5);
  } while (!lastTime);
  return true;
}

//: Loads precomputed memory contents from set of files
void MemModulesC::Load(const FilenameC&DirName,
                 int StartField, int NumFields)
{
  try {
    if(verbosity > 0)
      cout << "Reading memory dir:" << DirName << endl;
    if (!DirName.Exists()) 
      throw ExceptionC("Can't find memory directory " + DirName);
    StringC inPrefix = DirName+"/mem.xml";
    XMLIStreamC memStream(inPrefix);

    //how to check if file is open??? FIXME
    if(!memStream.IsOpen() || memStream.eof() || !memStream)
      throw ExceptionInvalidStreamC("Can't open stream for reading memory");
    
    StringC tagName;
    XMLTagOpsT readTagRes;
    readTagRes = memStream.ReadTag(tagName);
    if(readTagRes != XMLBeginTag)
      throw ExceptionInvalidStreamC("Main:Missed 'begin' tag (possibly mem file not found)");
    if(tagName != "all")
      throw ExceptionInvalidStreamC("Main:Missed <all> tag");
    
    //read command line
    readTagRes = memStream.ReadTag(tagName);
    if(readTagRes != XMLBeginTag)
      throw ExceptionInvalidStreamC("Main:Missed 'begin' tag");
    if(tagName != "commandLine")
      throw ExceptionInvalidStreamC("Main:Missed <commandLine> tag");
    StringC oldCommandLine;
    memStream >> oldCommandLine;
    if(verbosity > 0)
      cout << "Command line:" << oldCommandLine << endl;
    
    readTagRes = memStream.ReadTag(tagName);
    if(readTagRes != XMLEndTag)
      throw ExceptionInvalidStreamC("Main:Missed 'end' tag");
    
    //read memmodules
    TimeCodeC start = StartField >= 0 ? TimeCodeC(StartField, 50) : 
      TimeCodeC(-1, 50);
    TimeCodeC end   = NumFields  >= 0 ? TimeCodeC(StartField + NumFields, 50) : 
      TimeCodeC(-1, 50);
    
    this->Load(memStream, start, end, inPrefix);
    
    memStream.Close();
  }
  catch( ... ) {
    cerr << "Exception loading memory from " << DirName << endl;
    throw;
  }
}

//: Saves top level XML file
void MemModulesC::Save(const FilenameC& DirName)
{
  try {
    XMLOStreamC memStream(DirName+"/mem.xml");
    if(!memStream.IsOpen())
      throw ExceptionC("Can't open stream for writing top-level memory XML");
    
    memStream.StartTag("all");
    memStream.StartContents();
    
    //save command line
    memStream.StartTag("commandLine");
    memStream.StartContents();
    memStream << commandLine;
    memStream.EndTag();
    
    //save all memory modules
    this->Save(memStream);
    
    memStream.EndTag();
    memStream.Close();
  }
  catch( ... ) {
    cerr << "unhandled exception in storing top-level XML file\n";
    throw;
  }
}

//: Load memory from stream
void MemModulesC::Load(XMLIStreamC &Strm, const TimeCodeC& Start, const TimeCodeC& End, const StringC& inPrefix)
{
  if(verbosity > 0)
    cout << "loading memory modules from stream " << Start << " - " << End << endl;

  StringC tagName;
  XMLTagOpsT readTagRes;
  readTagRes = Strm.ReadTag(tagName);
  if(readTagRes != XMLBeginTag)
    throw ExceptionInvalidStreamC("MemModulesC::Load:Missed 'begin' tag");
  if(tagName != "memory")
    throw ExceptionInvalidStreamC("MemModulesC::Load:Missed <memory> tag");

  TimeCodeC start(Start); 
  TimeCodeC end(End);

  while(Strm.PeekTag(tagName) == XMLBeginTag)
  {
    if(verbosity > 0)
      cout << "Loading module:" << tagName << endl;

    //read module
    //verbosity of the module will be set to verbosity for memory management
    MemModuleC module(*this, verbosity,
                      MyMemType, "loadConstructor" + inPrefix);
    module.Memory().Load(Strm, start, end);
    if(module.ModuleName().IsEmpty())
      throw ExceptionInvalidStreamC("MemModulesC::Load:Error loading module.");
      
    if(verbosity > 5)
      cout << "  Start:" << start << "\t end:" << end << endl;

    modulesTableLock.Lock();
    MemModuleC *mmPtr = modules.Lookup(module.ModuleName());

    if(mmPtr != NULL) 
    {
      *mmPtr = module; //horrible if the thread is running FIXME
      cout << "rewriting existing module\n";
    }
    else
    {
      modules.Insert(module.ModuleName(), module);
    }
    modulesTableLock.Unlock();

    if(verbosity > 0)
      cout << "Module " << tagName << " loaded successfuly\n";
  }

  readTagRes = Strm.ReadTag(tagName);
  if(readTagRes != XMLEndTag)
    throw ExceptionInvalidStreamC("MemModulesC::Load:Missed 'end' tag.");

  //go though all modules and clean head up to time start
//  modulesTableLock.Lock();
//  for(HashIterC<StringC, MemModuleC> curModule(modules); curModule; curModule++)
//  {
//    curModule->Memory().Clean(start);
//  }
//  modulesTableLock.Unlock();

  if(verbosity > 0)
    cout << "all memory modules loaded\n";
}


//: Saves memory contents table into stream
void MemModulesC::Save(XMLOStreamC &Strm) const
{
  if(verbosity > 0)
    cout << "saving memory\n";
  StringListC modulesList = GetModulesList();

  Strm.StartTag("memory");
  Strm.StartContents();
  for(ConstDLIterC<StringC> moduleName(modulesList); moduleName; ++moduleName) 
  {  
    const MemModuleC& curModule = operator[](*moduleName);
    curModule.Memory().SaveTop(Strm);
  }
  Strm.EndTag();

  if(verbosity > 0)
    cout << "memory saved\n";
}

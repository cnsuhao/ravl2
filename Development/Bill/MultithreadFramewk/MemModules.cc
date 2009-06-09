#include "Ravl/SArray1d.hh"
#include "Ravl/DArray1dIter.hh"
#include "Ravl/CDLIter.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/IO.hh"
#include "Ravl/HashIter.hh"
  
#include "Ravl/Threads/MemModules.hh"

MemModulesC ModuleManager;

//: Constructor
MemModulesC::MemModulesC()
  : textDisplay(false), forget(false), endOfSession(false), 
    verbosity(0), modulesTableLock(true), showLogWnds(false)
{}

MemModulesC::~MemModulesC()
{
  if(verbosity > 1)
    cout << "MemModulesC::~MemModulesC called\n";
  
  MutexLockC lock(modulesTableLock);
  
  for(HashIterC<StringC, MemModuleC> curModule(modules); curModule; curModule++)
  {
    if (curModule->IsUsed()) {
      if(verbosity > 7)
        cout << "Release accesses in: " << curModule.Key() << endl;
      curModule->ReleaseAllAccesses();
      if(verbosity > 7)
        cout << "Done\n";
    }
    if (curModule->References() != 1)
      cout << curModule->References() << " reference(s) for " << curModule.Key() << endl;
  }
  
  if(verbosity > 1)
    cout << "MemModulesC::~MemModulesC done\n";
}


//: Initialiser
void MemModulesC::Init(const FilenameC& memOutDir, int argc, const char* argv[], UIntT Verbosity)
{
  verbosity = Verbosity;
  memoryDir = memOutDir;
  for (int i(0); i<argc; ++i) {
    commandLine += StringC(argv[i]) + StringC(" ");
  }
  if (!((memoryDir.Exists() && memoryDir.IsDirectory() && memoryDir.IsWritable()) || memoryDir.MakeDir()))
    throw ExceptionC("Can't create directory for writing memory: " + memOutDir);

  // Check that the log directory is there
  logDir = memOutDir + "/log";
  logDir.MakeDir();
  if (!(logDir.IsDirectory() && logDir.IsWritable())) {
    cerr << "Cannot write to log directory " << logDir
         << "; setting to /dev/null"<<endl;
    logDir = "/dev/null";
  }

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


//: Access the named module
const MemModuleC MemModulesC::operator[] (const StringC& name) const 
{ 
  MutexLockC lock(modulesTableLock);
  RavlAssertMsg(modules.IsElm(name), "Cannot create access to non-existent source: " + name);
  const MemModuleC module = *modules.Lookup(name);
  return module;
}

//: Access the named module
MemModuleC MemModulesC::operator[] (const StringC& name) 
{
  MutexLockC lock(modulesTableLock);
  RavlAssertMsg(modules.IsElm(name), "Cannot create access to non-existent source: " + name);
  return *modules.Lookup(name);
}

//: Access the named module, launching it if necessary
const MemModuleC MemModulesC::AccessModule(const StringC& name) const 
{ 
  MutexLockC lock(modulesTableLock);
  const MemModuleC module = (*this)[name];
  if (module.IsUsed())  return module;
  lock.Unlock();
  return LaunchMemModule(name);
}


//: Launch mem module thread

MemModuleC MemModulesC::LaunchMemModule(const StringC& ModuleName) const
{
  MutexLockC lock(modulesTableLock);
  
  MemModuleC module;
  
  //check if module registered
  if(!modules.Lookup(ModuleName,module)) {
    StringC err = StringC("Attempting to launch unregistered module: ") + ModuleName;
    cerr << err << endl;
    throw ExceptionC(err);
  }
    
  if(verbosity > 0)
    cout << "Creating and launching module: " << ModuleName << endl;
  
  // Initialise mem module and launch it
  StringC moduleOptions;
  if (optionsTab.IsElm(ModuleName))  moduleOptions = optionsTab[ModuleName];
  module.Launch(moduleOptions, logDir, showLogWnds);
  
  return module;
}


//: Launches the modules as a set of separate threads
void MemModulesC::Launch(const StringListC& ModulesList) 
{  
  // Launch the modules
  for (ConstDLIterC<StringC> i(ModulesList); i; ++i) {
    LaunchMemModule(*i);
  }
  // If wanted, set the xdvi display going as another thread
  if (textDisplay) 
    textDisplayThread = LaunchThread(TriggerR(*this, &MemModulesC::ListMemory));
}

//:  Waits for the threads to finish. Wait for only currently running modules.
void MemModulesC::Wait() 
{  
  bool done;
  do { //  need to repeat 'cos not all modules are launched 1st time round
    done = true;
    for(HashIterC<StringC,MemModuleC> i(modules); i; ++i) {
      if (i->IsUsed()) {
        if (i->IsRunning())  done = false;
        i->Wait();
      }
    }
  } while (!done);

  if(verbosity > 0)
    cout << "All modules have finished" << endl;
  this->Save();
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
    MemModuleC curModule = operator[](*moduleName);
    curModule.Stop(StopFlag);
  }
}

//: returns list of names of currently launched modules
StringListC MemModulesC::GetModulesList() const
{
  StringListC modulesList;
  MutexLockC lock(modulesTableLock);
  
  for(HashIterC<StringC, MemModuleC> curModule(modules); curModule; curModule++)
    modulesList.InsLast(curModule->ModuleName());

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
      MemModuleC curModule = operator[](*moduleName);
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
      MemModuleC curModule = operator[](*moduleName);
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
    StringC inPrefix = DirName+"/";
    XMLIStreamC memStream(inPrefix+"mem.xml");

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
    TimeCodeC start = (StartField >= 0)
      ? TimeCodeC(StartField, 50)
      : TimeCodeC(-1, 50);
    TimeCodeC end  = (NumFields >= 0)
      ? TimeCodeC(StartField + NumFields - 1, 50)
      : TimeCodeC(RavlConstN::maxInt, 50);
    
    this->Load(memStream, start, end, inPrefix);
    
    memStream.Close();
  }
  catch(ExceptionC ex) {
    cerr << "Exception loading memory from " << DirName << endl;
    cerr << ex.Text() << endl;
    throw;
  }
  catch( ... ) {
    cerr << "Exception loading memory from " << DirName << endl;
    throw;
  }
}

//: Saves top level XML file
void MemModulesC::Save()
{
  try {
    XMLOStreamC memStream(memoryDir+"/mem.xml");
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
    if (!modules.IsElm(tagName)) {
      throw ExceptionInvalidStreamC("MemModulesC::Load: unknown module: " + tagName);
    }
    MemModuleC module = *modules.Lookup(tagName);
    if (module.IsUsed()) {
      throw ExceptionInvalidStreamC("MemModulesC::Load: cannot load running module: " + tagName);
    }
    module.Load(Strm, start, end);
    if(module.ModuleName().IsEmpty())
      throw ExceptionInvalidStreamC("MemModulesC::Load: error loading module: " + tagName);
      
    if(verbosity > 5)
      cout << "  Start:" << start << "\t end:" << end << endl;

    if(verbosity > 0)
      cout << "Module " << tagName << " loaded successfuly\n";
  }

  readTagRes = Strm.ReadTag(tagName);
  if(readTagRes != XMLEndTag)
    throw ExceptionInvalidStreamC("MemModulesC::Load:Missed 'end' tag.");

  if(verbosity > 0)
    cout << "all memory modules loaded\n";
}


//: Saves memory contents table into stream
void MemModulesC::Save(XMLOStreamC &Strm) const
{
  if(verbosity > 0)
    cout << "saving memory\n";

  Strm.StartTag("memory");
  Strm.StartContents();
  for(HashIterC<StringC,MemModuleC> i(modules); i; ++i) 
    if (i->IsUsed())  i->Memory().SaveTop(Strm);
  Strm.EndTag();

  if(verbosity > 0)
    cout << "memory saved\n";
}

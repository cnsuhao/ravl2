//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/SourceTools/VCPP.hh"
#include "Ravl/SourceTools/RCSFile.hh"
#include "Ravl/TemplateFile.hh"
#include "Ravl/Date.hh"
#include <fstream.h>

namespace RavlN {

  HashC<StringC, DListC<StringC> > _projectList; 
  
  // This contains a list of source files for each project accessed by project name
  //
  // a project is either: library    -  src/dir/*     x.lib     x.dsp
  //                      executable -  src/x/x.cpp   x.exe     x.dsp
  //
  // the first string in the list is library or executable
  // could be improved ...
  
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------
  // Constructor.
  
  ConvertVCPP::ConvertVCPP(StringC nDir,StringC nRoot,StringC nWork,
			   StringC ndosdrive, StringC ndospath, StringC ndostemp,
			   bool pback, bool doexecs, bool doone,
			   bool Enabled)
    : root(nRoot),
      work(nWork),
      dosdrive(ndosdrive),
      dospath(ndospath),
      dostemp(ndostemp),
      arrow(" -> "),
      putBack(pback),
      execs(doexecs),
      one(doone)
  {
    if(putBack)
      arrow = " <- ";
    // Remove leading '/' from path if there.
    if(dospath.firstchar() == '/')
      dospath = dospath.after(0);
  }
  
  // -----------------------------------------------------------------------------
  // Open a new directory.

  BRCPtrC<SrcCheckC> 
  ConvertVCPP::NewSrc(StringC dir,bool Enabled) {
    return *new ConvertVCPP(dir,
			    root,
			    work + '/' + dir.NameComponent(),
			    dosdrive, dospath, dostemp,
			    putBack, execs, one,
			    Enabled);
  }
  
  // -----------------------------------------------------------------------------
  //////////////////////////////////////////
  //: Do operation on local directory.
  // Return 
  //  true=Continue.
  //  false=Abort.

  bool ConvertVCPP::DoOp()  {
    // Check this directory supports VCPP.
    if(Defs().Value("DONOT_SUPPORT").contains("VCPP")) {
      SetSkipSubdir(true);
      return true;
    }
    StringC supportOnly = Defs().Value("SUPPORT_ONLY");
    if(!supportOnly.IsEmpty()) {
      if(!supportOnly.contains("VCPP")) {
	SetSkipSubdir(true);
	return true;
      }
    }
    
    // Make sure directories exist.
    if(!root.Exists()) root.MakeDir();
    if(!work.Exists()) work.MakeDir();
    
    // Lets make sure the directories are ready for libraries and binaries
    StringC optLib = root + "/lib/opt";
    StringC debugLib = root + "/lib/debug";
    StringC binDir = root + "/bin";
    if(!optLib.Exists()) optLib.MakeDir();
    if(!debugLib.Exists()) debugLib.MakeDir();
    if(!binDir.Exists()) binDir.MakeDir();
    
    
    // Process the header files
    // ------------------------
    
    // Get a list of the header files
    StringListC headers = Defs().Value("HEADERS");
    
    // Make sure header directory exists.
    StringC package =  Defs().Value("PACKAGE");
    if(package.IsEmpty())
      package="Ravl";
    StringC hdrDir = root + "/inc/" + package;
    if(!hdrDir.Exists()) { 
      if(!hdrDir.MakeDir()) {
	cerr << "ERROR: Failed to make dir : " << hdrDir << "\n";
	return false;
      }
    }
    
    // Change the headerfiles to lower case and call Update() for each file
    for(DLIterC<StringC> it(headers);it.IsElm();it.Next()) {
      RCSFileC mainLine = CWD() + '/' + it.Data();
      StringC basename = it.Data().Copy();
      basename.downcase();
      StringC vcpp = hdrDir + '/' + basename;
      if(IsVerbose())
	cout << "Hdr:" << mainLine << arrow << vcpp << endl;
      Update(vcpp,mainLine);
    }
    
    // Now lets process the source files
    // ---------------------------------
    StringListC sources = Defs().Value("SOURCES");
    sources += StringListC(Defs().Value("LOCAL_FILES"));
    sources += StringListC(Defs().Value("LOCALHEADERS"));
    
    // Find a name for the library, 
    // will be used for the project file and VCPP library name
    
    StringC projName;
    if (one) projName = "theLib";
    else     projName = Defs().Value("PLIB");
    if(projName.IsEmpty())
      projName = work.NameComponent(); // If no PLIB given, use directory name.
    
    // Create a new hash element if it does not exist
    if(!_projectList.IsElm(projName)) {
      cout << "New Lib: " << projName << endl;
      _projectList[projName].InsLast("library");  
    }
    
    // Loop over src files  
    for(DLIterC<StringC> it(sources);it.IsElm();it.Next()) {
      RCSFileC mainLine = CWD() + '/' + it.Data();
      
      // Work out what the file should be called to keep vcpp happy.
      
      StringC basename;
      int at = it.Data().index(".cc",-1);
      if(at <= 0) {
	at = it.Data().index(".cxx",-1);
	if(at <= 0)
	  at = it.Data().index(".c",-1);
      }
      bool isSource;
      if(at > 0) { // Is it a cc or cxx file ?
	basename = it.Data().before(at) + ".cpp";
	isSource = true;
      } else {
	basename = it.Data().Copy();
	isSource = false;
      }
      
      basename.downcase();
      StringC vcpp =  work + '/' + basename;
      
      if(IsVerbose())
	cout << "Src:" << mainLine << arrow << vcpp << endl;
      
      // Add entry to project file.
      if(isSource) {
	_projectList[projName].InsLast(vcpp.Copy());
      }
      
      Update(vcpp,mainLine);
    }
    
    StringC libname = projName.Copy();
    
    
    if (!execs) return true;

    // Now lets process the exectables
    // -------------------------------
    StringListC mains = Defs().Value("MAINS");
    
    for (DLIterC<StringC> it(mains);it.IsElm();it.Next()) {

      // get the basename
      int at = it.Data().index(".cc",-1);
      if(at == 0) {
	cerr << "Error parsing MAINS " << it.Data() << endl;
	continue;
      }
      // Find a name for the project
      StringC projName = it.Data().before(at);
      StringC basename = it.Data().before(at) + ".cpp";
      
      // Create a new hash element if it does not exist
      if(!_projectList.IsElm(projName)) cout << "New Exec: " << projName << endl;
      //    _projectList[projName].InsLast("executable");  
      _projectList[projName].InsLast(libname);  
      
      RCSFileC mainLine = CWD() + '/' + it.Data();
      
      // Work out what the file should be called to keep vcpp happy. 
      basename.downcase();
      StringC vcpp =  work + '/' + basename;
      
      if(IsVerbose())
	cout << "Main:" << mainLine << arrow << vcpp << endl;
      
      // Add entry to project file.
      _projectList[projName].InsLast(vcpp.Copy());
      
      Update(vcpp,mainLine);
    }
    
    return true;
  }
  
  // -----------------------------------------------------------------------------
  //: This is the guts to do the forward or reverse copy
  // taking care of check in etc
  
  bool ConvertVCPP::Update(StringC vcpp,RCSFileC &mainLine) {
    if(!putBack) { 
      // Install new files.
      mainLine.Update(); // Make sure mainline file is current.
      if(!mainLine.Exists()) {
	cerr << "WARNING: Can't find src file : " << mainLine << "\n";
	return false;
      }
      
      if(vcpp.Exists()) {
	if(vcpp.LastModTime() > mainLine.Filename().LastModTime())
	  return true; // File is upto date.
      }
      // Check the destination is writeable.
      if(vcpp.Exists()) {
	if(!vcpp.IsWritable()) {
	  FilePermissionC perm = vcpp.Permissions();
	  perm.SetUserReadWrite(); // Make sure user has read/write.
	  if(!vcpp.SetPermissions(perm)) {
	    cerr << "ERROR: Failed to get write permission for file : " << vcpp << "\n";
	    return false;
	  }
	}
      }
      // Do the copy.
      if(!mainLine.CopyTo(vcpp)) {
	cerr << "ERROR: Failed to update file : " << vcpp << "\n";
	return false;
      }
      return true;
    } 
    
    // Put files back.
    
    if(!mainLine.IsCheckedOut())
      mainLine.CheckOut(); // Check it out.
    if(!vcpp.Exists()) {
      cerr << "ERROR: Failed to checkout file " << mainLine << " for update. \n";
      return false;
    }
    ifstream in1(vcpp);
    ofstream in2(mainLine.Filename());
    if(!in1) {
      cerr << "ERROR: Failed to open file :" << vcpp << " for update." <<endl;
      return false;
    }
    if(!in2) {
      cerr << "ERROR: Failed to open file :" << mainLine << " for update." << endl;
      return false;
    }
    
    // As we all know DOS has additional junk \CR\LF
    // this neatly removes them on the way back to Unix
    // (they are not inserted on the way there)
    
    const int buffsize = 4096;
    char buff[buffsize];
    do {
      in1.read(buff,buffsize);
      int at = 0;
      char *place = buff;
      char *start = buff;
      char *end = &buff[in1.gcount()];
      for(;place != end;place++) {
	if(*place == 0x0d) { // Cut out these chars.
	  if(at != 0) 
	    in2.write(start,at); // Write upto here.
	  start = place;
	  start++; // Skip this char.
	  at = 0;
	} else
	  at++;
      }
      in2.write(start,at); // Write out the rest.
    } while(in1) ;
    return true;  
  }
  
  
  
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------
  void
  ConvertVCPP::CreateProjectFiles(const StringC & StaticLibTemplate,
				  const StringC & ConsoleAppTemplate) {
    StringC projDir = root + "/proj/";
    if(!projDir.Exists()) projDir.MakeDir();
    
    // Loop over all the projects we must create files for
    for(HashIterC<StringC, DListC<StringC> > It(_projectList);It.IsElm();It.Next()) {
      
      bool lib = (It.Data().First()=="library");

      // Only create project file if source files present
      if(It.Data().Size()<=0) continue; // with next project
      
      StringC projFile = projDir + It.Key() +  ".dsp";
      cout << "Creating Project File: " << projFile << endl;
      ofstream ofs(projFile);
      
      StringC tfile;
      if (lib) tfile = StaticLibTemplate;
      else     tfile = ConsoleAppTemplate;
      TemplateFileC tf(tfile,ofs);
      
      StringC projName  = It.Key();
      StringC allsrcfiles;
      
      // Each src file must be listed in the project file
      // ignore the first string
      ConstDLIterC<StringC> Src(It.Data());
      Src.Next();
      for(;Src.IsElm();Src.Next()) {
	
	// strip off the top of the unix path except for src/module/abc.cpp
	StringC srcfile = Src.Data().Copy();
	int i=srcfile.index("/src/") + 1;
	srcfile = srcfile.from(i);
	
	// Yes ... I know its inefficient but I am feeling lazy!
	allsrcfiles += "#Begin Source File\r\n";
	allsrcfiles += "SOURCE=" + dosdrive + ":/" + dospath + "/"
	  + srcfile + "\r\n";
	allsrcfiles += "#End Source File\r\n\r\n";
      }
      
      tf.SetVar("PROJECT_NAME",     projName);
      tf.SetVar("TEMP_DIR",         dostemp);
      tf.SetVar("VCPP_SRC_ROOT",    StringC(dosdrive + ":/" + dospath));
      tf.SetVar("ALL_THE_SRC_FILES",allsrcfiles);
      
      
      /*
	Lost GetLibC files - maybe at home
	
	//: If it is an executable lets try and make a guess at which libraries are needed to make an executable
	if(!lib) {
	GetLibC lib(".", "/vol/vssp/local/beta/");
	StringC Ravllibs;
	for(ConstDLIterC<StringC>StIt(lib.getLibDepNames(It.Data().First()));StIt.IsElm();StIt.Next()) {
	Ravllibs += StIt.Data() + ".lib ";
	}
	tf.SetVar("RAVL_LIBS", Ravllibs);
	}
      */
      
      //: lets build the workspace file
      tf.Build();
      ofs.close();
      
    }// end of projects  
  }
  
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------
  
  void
  ConvertVCPP::CreateWorkspaceFile() {
    StringC wf = root + '/' + "Ravl.dsw";
    ofstream wsf(wf);
    
    StringC ls = root + '/' + "Proj.lst";
    ofstream lsf(ls);
    
    wsf << "Microsoft Developer Studio Workspace File, Format Version 6.00\r\n";
    wsf << "# WARNING: DO NOT EDIT OR DELETE THIS WORKSPACE FILE!\r\n";
    
    
    for(HashIterC<StringC, DListC<StringC> > It(_projectList);It.IsElm();It.Next()) {
      if(It.Data().Size()>1) {
	wsf << "\r\n###############################################################################\r\n\r\n";
	wsf << "Project: \"" << It.Key() << "\"=.\\proj\\" << It.Key() 
	    << ".dsp - Package Owner=<4>\r\n\r\n";
	wsf << "Package=<5>\r\n{{{\r\n";
	wsf << "}}}\r\n\r\n";
	wsf << "Package=<4>\r\n{{{\r\n";
	if (one && (It.Key()!="theLib")) {
	  wsf << "    Begin Project Dependency\r\n";
	  wsf << "    Project_Dep_Name theLib\r\n";
	  wsf << "    End Project Dependency\r\n";
	}
	wsf << "}}}\r\n\r\n";
	
	lsf << dosdrive << ":/" << dospath << "/proj/"  << It.Key() << ".dsp\r\n";
      }
    }
    
    wsf << "###############################################################################\r\n\r\n";
    wsf << "Global:\r\n\r\n";
    wsf << "Package=<5>\r\n{{{\r\n}}}\r\n\r\nPackage=<3>\r\n{{{\r\n}}}\r\n\r\n";
    wsf << "###############################################################################\r\n\r\n";

    lsf.close();
    wsf.close();
  }
  
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------
  
  void
  ConvertVCPP::CreateRAVLported(const StringC & StaticLibTemplate, const StringC & RAVLported) {
    
    //: Lets get the listed of RAVL ported libraries
    ifstream fs(RAVLported);
    DListC<StringC>portedList;
    StringC next;
    fs >> next;
    while(fs) {
      portedList.InsLast(next.Copy());
      fs >> next;
    }
    fs.close();
    
    StringC allsrcfiles;
    
    //: we want to get all the source files to make one big DSP
    for(ConstDLIterC<StringC>It(portedList);It.IsElm();It.Next()) {
      // Each src file must be listed in the project file
      // ignore the first string
      ConstDLIterC<StringC> Src(_projectList[It.Data()]);
      Src.Next();
      for(;Src.IsElm();Src.Next()) {
	
	// strip off the top of the unix path except for src/module/abc.cpp
	StringC srcfile = Src.Data().Copy();
	int i=srcfile.index("/src/") + 1;
	srcfile = srcfile.from(i);
	
	// Yes ... I know its inefficient but I am feeling lazy!
	allsrcfiles += "#Begin Source File\r\n";
	allsrcfiles += "SOURCE=" + dosdrive + ":/" + dospath + "/"
	  + srcfile + "\r\n";
	allsrcfiles += "#End Source File\r\n\r\n";
      }
      
    }
    
    allsrcfiles="";
    
    //: First lets create a project file file
    StringC projDir = root + "/proj/";
    if(!projDir.Exists()) projDir.MakeDir();
    StringC projName  = "RAVLported";
    StringC projFile = projDir + projName +  ".dsp";
    cout << "Creating Project File: " << projFile << endl;
    
    ofstream ofs(projFile);
      
    StringC tfile = StaticLibTemplate;
    
    TemplateFileC tf(tfile,ofs);
    
    tf.SetVar("PROJECT_NAME",     projName);
    tf.SetVar("TEMP_DIR",         dostemp);
    tf.SetVar("VCPP_SRC_ROOT",    StringC(dosdrive + ":/" + dospath));
    tf.SetVar("ALL_THE_SRC_FILES",allsrcfiles);
    
    tf.Build();
    ofs.close();
    
    //: Next we want to make our own workspace file with just relevant libraries
    StringC wf = root + '/' + "RAVLported.dsw";
    ofstream wsf(wf);
    
    
    //: Now lets write the workspace file
    wsf << "Microsoft Developer Studio Workspace File, Format Version 6.00\r\n";
    wsf << "# WARNING: DO NOT EDIT OR DELETE THIS WORKSPACE FILE!\r\n";
    
    
    //: First we want to write the MASTER library that depends on all ported libraries
    wsf << "\r\n###############################################################################\r\n\r\n";
    wsf << "Project: \"" << projName << "\"=.\\proj\\" << projName << ".dsp - Package Owner=<4>\r\n\r\n";
    wsf << "Package=<5>\r\n{{{\r\n";
    wsf << "}}}\r\n\r\n";
    wsf << "Package=<4>\r\n{{{\r\n";
    for(ConstDLIterC<StringC>It(portedList);It.IsElm();It.Next()) {
      wsf << "    Begin Project Dependency\r\n";
      wsf << "    Project_Dep_Name " << It.Data() << "\r\n";
      wsf << "    End Project Dependency\r\n";
    }
    wsf << "}}}\r\n\r\n";
    
    
    for(ConstDLIterC<StringC>It(portedList);It.IsElm();It.Next()) {
      if(It.Data().Size()>1) {
	
	wsf << "\r\n###############################################################################\r\n\r\n";
	wsf << "Project: \"" << It.Data() << "\"=.\\proj\\" << It.Data() << ".dsp - Package Owner=<4>\r\n\r\n";
	wsf << "Package=<5>\r\n{{{\r\n";
	wsf << "}}}\r\n\r\n";
	wsf << "Package=<4>\r\n{{{\r\n";
	wsf << "}}}\r\n\r\n";
	
      }
    }
    
    wsf << "###############################################################################\r\n\r\n";
    wsf << "Global:\r\n\r\n";
    wsf << "Package=<5>\r\n{{{\r\n}}}\r\n\r\nPackage=<3>\r\n{{{\r\n}}}\r\n\r\n";
    wsf << "###############################################################################\r\n\r\n";
    
    wsf.close();
    
  }


}

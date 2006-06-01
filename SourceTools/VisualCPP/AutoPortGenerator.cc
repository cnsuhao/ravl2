// This file is part of VCPP, Visual C++ porting tool for QMake projects 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/SourceTools/VisualCPP/AutoPortGenerator.cc"
//! lib=RavlAutoPort

#include "Ravl/SourceTools/AutoPortGenerator.hh"
#include "Ravl/OS/Filename.hh"

#define DODEBUG 1
#if DODEBUG 
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor
  
  AutoPortGeneratorBodyC::AutoPortGeneratorBodyC(AutoPortSourceC &nsrc,StringC &templLoc,StringC &noutput,const StringC &_projectOut, const ExtLibTableC & _extLibs) 
    : TemplateComplexBodyC(templLoc),
      outputDir(noutput),
      projectOut(_projectOut),
      extLibs(_extLibs),
      src(nsrc)
  {
    Init();
  }
  
  //: Setup template stuff.
  
  void AutoPortGeneratorBodyC::Init() {
    HSetC<StringC> npresets;
    npresets += StringC("FilePattern");
    npresets += StringC("FileObject");
    SetupPresets(npresets);
    Scan(templFile);
    filePattern = GetVar("FilePattern");
    fileObject = GetVar("FileObject");    

    // Setup commands ?
    SetupCommand("forall",*this,&AutoPortGeneratorBodyC::Forall);
    SetupCommand("dos",*this,&AutoPortGeneratorBodyC::Dos);
    SetupCommand("pathback",*this,&AutoPortGeneratorBodyC::PathBack);
    
  }
  
  //: Lookup variable.
  // if found put value into 'buff' and return true.
  // otherwise return false.
  
  bool AutoPortGeneratorBodyC::Lookup(const StringC &varname,StringC &buff) {
    if(varname == "libname") {
      LibInfoC &li = CurLibInfo();
      if(li.IsValid())
	buff = li.Name();
      else {
	buff = StringC("*unknown*");
	cerr << "ERROR: Variable 'libname' requested outside  library. Current target:" << target <<"\n";
      }
      return true;
    }
    if(varname == "package") { // Package for header file.
      buff = context.Top().HeaderInfo().Package();
      return true;
    }
    if(varname == "srcfile") { // Source file for header.
      buff = context.Top().HeaderInfo().SrcFile();
      ONDEBUG(cerr << "srcfile="  << context.Top().HeaderInfo().SrcFile() << "\n");
      return true;
    }
    if(varname == "target") {
      buff = target;
      return true;
    }
    if(varname == "filename") { // Get the full path.
      buff = CurFilename();
      ONDEBUG(cerr << "Filename="  << CurFilename() << "\n");
      return true;
    }
    if(varname == "name") { // Get the full path.
      buff = CurName();
      ONDEBUG(cerr << "name="  << CurFilename() << "\n");
      return true;
    }
    if(varname == "rootname") { // Just get the root name of the file.
      buff = FilenameC(CurFilename()).NameComponent();
      return true;
    }
    if(varname == "pathname") { // Get the path to the file.
      buff = FilenameC(CurFilename()).PathComponent();
      return true;
    }
    if(varname == "outputfile") {
      buff = outputfile;
      return true;
    }
    if(varname == "ProjectOut") {
      buff = projectOut;
    }
    if(varname == "ExtraInclude") {
      //: Need to add extra include paths

      //: First lets make an exclusive list of all libraries
      DListC<StringC>exclusive;
      HashC<StringC, DListC<StringC> >deps = src.Deps();
      for(DLIterC<StringC>it(context.Top().UsesLibs());it;it++) {
	if(deps.IsElm(*it)) {
	  for(DLIterC<StringC>inIt(deps[*it]);inIt;inIt++) 
	    if(!exclusive.Contains(*inIt)) exclusive.InsLast(*inIt);
	}
	if(!exclusive.Contains(*it)) exclusive.InsLast(*it);
      }
      
      //: Now we want to check if there are any external libraries
      //: and add the include paths
      DListC<StringC>includePaths;
      for(DLIterC<StringC>it(exclusive);it;it++) {
	if(extLibs.IsElm(*it)) {
	  for(DLIterC<StringC>inIt(extLibs[*it].IncludePaths());inIt;inIt++) 
	    if(!includePaths.Contains(*inIt)) includePaths.InsLast(*inIt);
	}
      }

      //: Now make a single string of all includes
      buff="";
      for(DLIterC<StringC>it(includePaths);it;it++) 
	buff += (StringC)" /I " + (StringC)"\"" + *it + (StringC)"\"";
    }


    if(varname == "ProgExtraLibPath") {
      //: Need to add extra include paths

      //: First lets make an exclusive list of all libraries
      DListC<StringC>exclusive;
      HashC<StringC, DListC<StringC> >deps = src.Deps();
      for(DLIterC<StringC>it(context.Top().UsesLibs());it;it++) {
	if(deps.IsElm(*it)) {
	  for(DLIterC<StringC>inIt(deps[*it]);inIt;inIt++) 
	    if(!exclusive.Contains(*inIt)) exclusive.InsLast(*inIt);
	}
	if(!exclusive.Contains(*it)) exclusive.InsLast(*it);
      }

      //: Now we want to check if there are any external libraries
      //: and add the include paths
      DListC<StringC>libPaths;
      for(DLIterC<StringC>it(exclusive);it;it++) {
	if(extLibs.IsElm(*it)) {
	  for(DLIterC<StringC>inIt(extLibs[*it].LibPaths());inIt;inIt++) 
	    if(!libPaths.Contains(*inIt)) libPaths.InsLast(*inIt);
	}
      }

      //: Now make a single string of all includes
      buff="";
      for(DLIterC<StringC>it(libPaths);it;it++) 
	  buff += (StringC)" /LIBPATH:" + (StringC)"\"" + *it + (StringC)"\"";
    }

    if(varname == "ProgExtraLib") {
      //: Need to add extra include paths

      //: First lets make an exclusive list of all libraries
      DListC<StringC>exclusive;
      HashC<StringC, DListC<StringC> >deps = src.Deps();
      for(DLIterC<StringC>it(context.Top().UsesLibs());it;it++) {
	if(deps.IsElm(*it)) {
	  for(DLIterC<StringC>inIt(deps[*it]);inIt;inIt++) 
	    if(!exclusive.Contains(*inIt)) exclusive.InsLast(*inIt);
	}
	if(!exclusive.Contains(*it)) exclusive.InsLast(*it);
      }

      //: Now we want to check if there are any external libraries
      for(DLIterC<StringC>it(exclusive);it;it++) {
	if(extLibs.IsElm(*it)) {
	  StringC str;
	  for(DLIterC<StringC>inIt(extLibs[*it].Libs());inIt;inIt++) 
	    str += (StringC)" " +  *inIt;
	  *it = str;
	}
      }
      //: Now make a single string of all libs
      buff="";
      exclusive.Reverse();
      for(DLIterC<StringC>it(exclusive);it;it++) 
	if(!it.Data().contains("opt") && !it.Data().IsEmpty()) {
	  if(!it.Data().contains(".lib")) *it += ".lib";
	  buff += (StringC)" " +  *it;
	}
    }

    if(varname == "Back_ProjectOut") {
      if(!projectOut.IsEmpty() && projectOut[0] == '.') // Relative path.
	buff = StringC("..\\") + projectOut;
      else
	buff = projectOut;
    }
    if(TemplateComplexBodyC::Lookup(varname,buff))
      return true;
    
    return true;
  }

  //: Generate a DOS filename.
  
  bool AutoPortGeneratorBodyC::Dos(StringC &data) {
    StringC newstuff = Interpret(data);
    newstuff.gsub("/","\\");
    output.Top() << newstuff;
    return true;
  }
  
  //: Generate path back from a file.
  // So 'MyDir1/MySubDir/filename' will become '../../'
  
  bool AutoPortGeneratorBodyC::PathBack(StringC &data) {
    // Is string empty ?
    if(data.IsEmpty())
      return true;
    StringC idata = Interpret(data);
    
    idata.gsub("/./","/");
    
    IntT slashes = idata.freq('/');
    if(idata[0] == '/') // Is it an absolute path?
      slashes--;
    ONDEBUG(cerr << "AutoPortGeneratorBodyC::PathBack '" << idata << "' Slashes=" << slashes << "\n");
    for(int i = 0;i < slashes;i++)
      output.Top() << "../";
    return true;
  }

  //: For all template function.
  
  bool AutoPortGeneratorBodyC::Forall(StringC &data) {
    int templStart = data.index(':');
    if(templStart < 1) {
      cerr << "Malformed 'forall' in template. '" << data << "' ignoring \n";
      return false;
    }    
    StringC typedata = data.before(templStart);

    // Check for a condition in the for loop.
    StringC condition;
    IntT condInd =typedata.index(',');
    if(condInd >= 0) {
      condition = typedata.after(condInd);
      //cerr << "Found condition '" << condition << "'\n";
      typedata = typedata.before(condInd);
      if(typedata == "") {
	cerr << "Malformed 'forall' in template. '" << data << "' ignoring \n";
	return false;
      }
     }
    
    // Variable in the element type ?
    if(typedata[0] == '$') {
      typedata = typedata.after(0);
      StringC buff;
      if(!Lookup(typedata,buff)) {
	cerr << "Unknown variable. '" << typedata << "' in forall. \n";
	return false;
      }
      typedata = buff;
      //cerr << "Got variable in  '" << typedata << "' in forall. \n";
    }
    
    StringC subtempltxt = data.after(templStart);    
    TextFileC subTextBuff(subtempltxt,true,true);
    // Libraries.
    if(typedata == "libs") {
      ONDEBUG(cerr << "forall libs:\n");
      for(HashIterC<StringC,LibInfoC> it(src.Libs());it;it++) {
	context.Push(ContextC(*it));
	BuildSub(subTextBuff);
	context.DelTop();
      }
      return true;
    }
    if(typedata == "useslibs") {
      ONDEBUG(cerr << "forall useslibs: " << context.Top().UsesLibs().Size() << " Type=" << context.Top().ctype << " Name=" << context.Top().HeaderInfo().Name() << "\n");
      for(DLIterC<StringC> it(context.Top().UsesLibs());it;it++) {
	ONDEBUG(cerr << " " << *it << "\n");
	context.Push(ContextC(*it));
	BuildSub(subTextBuff);
	context.DelTop();
      }
      return true;
    }
    // Source code.
    if(typedata == "sources") {
      ONDEBUG(cerr << "forall sources:\n");
      DListC<StringC> lst = context.Top().Sources();
      for(DLIterC<StringC> it(lst);it;it++) {
	context.Push(ContextC(*it));
	ONDEBUG(cerr << "For all Sources=" << *it << "\n");
	BuildSub(subTextBuff);
	context.DelTop();
      }	
      return true;
    }
    if(typedata == "headers") {
      ONDEBUG(cerr << "forall headers:\n");
      DListC<HeaderInfoC> lst = context.Top().Headers();
      for(DLIterC<HeaderInfoC> it(lst);it;it++) {
	context.Push(ContextC(*it));
	BuildSub(subTextBuff);
	context.DelTop();
      }	
      return true;
      
    }
    // Programs.
    if(typedata == "mains" || typedata == "examples" || typedata == "tests") {
      ONDEBUG(cerr << "forall exe, type=" << typedata << " :\n");
      DListC<ProgInfoC> pi;
      if(typedata == "mains")
	pi = src.Mains();
      else if(typedata == "examples")
	pi = src.Examples();
      else
	pi = src.Tests();
      for(DLIterC<ProgInfoC> it(pi);it;it++) {
	context.Push(ContextC(*it));
	BuildSub(subTextBuff);	
	context.DelTop();
      }
      return true;
    }

    cerr << "ERROR: Unknown forall object :" << typedata << "\n";
    return false;
  }

  //: Make a file name for an object.
  StringC AutoPortGeneratorBodyC::MakeFilename(const StringC &obj) {
    StringC ret;
    if(!outputDir.IsEmpty()) {
      if(outputDir[outputDir.Size()-1] != filenameSeperator)
        ret = outputDir + filenameSeperator + filePattern;
    }
    else
      ret = filePattern;
    ret.gsub("%",obj);
    
    ret = Interpret(ret);
    
    // Save current target filename.
    outputfile = ret;
    return ret;
  }

  //: Build output files.
  
  bool AutoPortGeneratorBodyC::BuildFiles() {
    if(fileObject == "none") 
      return true;
    if(fileObject == "one") {
      ONDEBUG(cerr << "************** File one  **************************** \n");
      target = "one";
      StringC fn = MakeFilename("");
      cerr << "Building file:'" << fn << "'\n";
      Build(fn);
      return true;
    }
    if(fileObject == "lib") {
      for(HashIterC<StringC,LibInfoC> it(src.Libs());it;it++) {
	ONDEBUG(cerr << "************** File lib  Name=" << it->Name() << " **************************** \n");
	target = it.Key();
	context.Push(ContextC(*it));
	StringC fn = MakeFilename(it.Key());
	Build(fn);
	context.DelTop();
      }
      return true;
    }
    if(fileObject == "mains" || fileObject == "examples" || fileObject == "tests") {
      DListC<ProgInfoC> pi;
      if(fileObject == "mains")
	pi = src.Mains();
      else if(fileObject == "examples")
	pi = src.Examples();
      else
	pi = src.Tests();
      for(DLIterC<ProgInfoC> it(pi);it;it++) {
	ONDEBUG(cerr << "************** File context Name=" << it->Name() << " Type=" << fileObject << " **************************** \n");
	ONDEBUG(cerr << " Libs=" << it->UsesLibs().Size() << " First=" << ( it->UsesLibs().IsEmpty() ? StringC("NULL") : it->UsesLibs().First() ) << "\n");
	target = it->Name();
	context.Push(ContextC(*it));
	StringC fn = MakeFilename(it->Name());
	ONDEBUG(cerr << " Libs=" << context.Top().progInfo.UsesLibs().Size() << " " << context.Top().UsesLibs().Size() << "\n");
	Build(fn);	
	context.DelTop();
      }
      return true;
    }
    
    if(fileObject == "headers") {
      for(HashIterC<StringC,LibInfoC> it(src.Libs());it;it++) {
	ONDEBUG(cerr << "************** File header  Name=" << it->Name() << " **************************** \n");
        DListC<HeaderInfoC> hdrInfo = it.Data().Headers();
        for(DLIterC<HeaderInfoC> hit(hdrInfo);hit;hit++) {
          target = hit->Name(); // Set current target.
          context.Push(ContextC(*hit));
          StringC outName = FilenameC(CurFilename()).NameComponent();
          StringC fn = MakeFilename(outName);
          Build(fn);
          context.DelTop();
        }
      }
      
      return true;
    }
    cerr << "Unknown file object : '" << fileObject << "'\n";
    return false;
  }

}

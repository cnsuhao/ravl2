///////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/SourceTools/AutoPortGenerator.hh"
#include "Ravl/OS/Filename.hh"

namespace RavlN {
  
  //: Constructor
  
  AutoPortGeneratorBodyC::AutoPortGeneratorBodyC(AutoPortSourceC &nsrc,StringC &templLoc,StringC &noutput) 
    : TemplateComplexBodyC(templLoc),
      output(noutput),
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
  }

  //: Lookup variable.
  // if found put value into 'buff' and return true.
  // otherwise return false.
  
  bool AutoPortGeneratorBodyC::Lookup(const StringC &varname,StringC &buff) {
    if(varname == "libname") {
      buff = CurLibInfo().Name();
      return true;
    }
    if(varname == "filename") { // Get the full path.
      buff = CurFilename();
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
    if(TemplateComplexBodyC::Lookup(varname,buff))
      return true;
    
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
      for(HashIterC<StringC,LibInfoC> it(src.Libs());it;it++) {
	context.Push(ContextC(*it));
	BuildSub(subTextBuff);
	context.DelTop();
      }
      return true;
    }
    // Source code.
    if(typedata == "sources" || typedata == "headers") {
      if(!context.Top().libInfo.IsValid()) {
	cerr << "ERROR: No lib context for 'forall:source'. \n";
	return false;
      }
      DListC<StringC> lst;
      if(typedata == "sources")
	lst = context.Top().Sources();
      else
	lst = context.Top().Headers();
      for(DLIterC<StringC> it(lst);it;it++) {
	context.Push(ContextC(*it));
	BuildSub(subTextBuff);
	context.DelTop();
      }	
      return true;
    }
    // Programs.
    if(typedata == "mains" || typedata == "examples" || typedata == "tests") {
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
    StringC ret = filePattern.Copy();
    ret.gsub("%",obj);
    return ret;
  }

  //: Build output files.
  
  bool AutoPortGeneratorBodyC::BuildFiles() {
    if(fileObject == "none") 
      return true;
    if(fileObject == "one") {
      StringC fn = MakeFilename("");
      cerr << "Building file:'" << fn << "'\n";
      Build(fn);
      return true;
    }
    if(fileObject == "lib") {
      for(HashIterC<StringC,LibInfoC> it(src.Libs());it;it++) {
	StringC fn = MakeFilename(it.Key());
	context.Push(ContextC(*it));
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
	StringC fn = MakeFilename(it->Name());
	context.Push(ContextC(*it));
	Build(fn);	
	context.DelTop();
      }
    }
    cerr << "Unknown file object : '" << fileObject << "'\n";
    return false;
  }

}

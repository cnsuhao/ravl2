// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Source Tools"
//! lib=RavlSourceTools
//! file="Ravl/SourceTools/CodeManager/docSubst.cc"

#include "Ravl/Option.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/Text/TextFile.hh"
#include "Ravl/Text/TextCursor.hh"
#include "Ravl/SourceTools/DefsFile.hh"
#include "Ravl/SourceTools/SourceCodeManager.hh"
#include "Ravl/SourceTools/SourceFile.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/OS/Filename.hh"


using namespace RavlN;

class SubstsC
{
public:
  SubstsC()
    {}
  //: Default constructor.
  
  SubstsC(const StringC &l,const StringC &o,const StringC &n,bool v,bool dr)
    : label(l),
      original(o),
      newun(n),
      verbose(v),
      dryRun(dr)
    {}
  //: Constructor.
  
  bool Process(StringC &dir,DefsMkFileC &where);
  //: Process a directory.
  
  bool IsVerbose() const
  { return verbose; }
  //: In verbose mode ?

  bool DoSubst(TextFileC &hdrfile);
  //: Subsitute value.
  
protected:
  StringC label;
  StringC original;
  StringC newun;
  bool verbose;
  bool dryRun;
};

//: Process a directory.

bool SubstsC::Process(StringC &dir,DefsMkFileC &where) {
  if(IsVerbose())
    cerr << "Processing: " << dir << "\n";
  StringListC hdrs(where.Value("HEADERS"));
  for(DLIterC<StringC> it(hdrs);it.IsElm();it.Next()) {
    if(it.Data().length() <= 3) {
      cerr << "WARNING: Short header file name detected :'" << it.Data() << "'\n";
      continue; // Far too short !
    }
    if(!it.Data().matches(".hh",it.Data().length()-3)) {
      //cerr << "WARNING: Non C++ header file ignored:'" + it.Data() + "'\n";
      continue; // C++ Headers only.
    }
    FilenameC file(dir + '/' + it.Data());
    //cerr << file << " ";
    //cerr << " (" << file << ")";
    if(!file.Exists()) {
      cerr <<"WARNING: No access to file:" << file << "\n";
      continue; // No access to file.
    }
    TextFileC hdrfile(file); 
    hdrfile.SetReadonly(false);
    
    if(!hdrfile.IsLoaded()) {
      cerr << "ERROR: Failed to load file '" << file << "'\n";
      continue;
    }
    
    // Update variable
    
    DoSubst(hdrfile); 
    
    // Update repository
    
    if(hdrfile.IsModified()) {
      if(!dryRun)
	cerr << "Updating " << file <<endl;
      else
	cerr << "Updating " << file << " (dryrun)" << endl;
      if(!dryRun) {
	if(!hdrfile.Save())
	  cerr << "Failed to save file '" << file << "' \n"; 
      }
    }
  }
  return true;
}

//: Subsitute value.

bool SubstsC::DoSubst(TextFileC &buff) {
  // FIXME - Var could turn out to be a prefix of something else ??
  IntT atline = buff.FindLineMatch("//! " + label);
  if(atline < 0)
    return false; // Not found...
  if(buff[atline].gsub(original,newun) > 0)
    buff.SetModified();
  return true;
}



int doHeaders(int nargs,char **argv) {
  OptionC option(nargs,argv,true);
  FilenameC fn = option.CharArr("i",".","Input filename. ");
  bool rec = option.Boolean("r",true,"recurse into subdirectories. ");
  bool all = option.Boolean("a",false,"Go into inactive directories as well. ");
  bool verb = option.Boolean("v",false,"Verbose mode.");
  bool dryRun = option.Boolean("d",false,"Do a dry run.");
  
  StringC label = option.CharArr("l","docentry","Label to change.");
  StringC oValue = option.CharArr("lo","","Original value. ");
  StringC nValue = option.CharArr("ln","","New value ");
  option.Check();
  
  SubstsC op(label,oValue,nValue,verb,dryRun);
  
  SourceCodeManagerC chkit(fn);
  if(verb)
    chkit.SetVerbose(true);
  
  chkit.ForAllDirs(Trigger(op,&SubstsC::Process,StringC(""),DefsMkFileC("")),all); 
  
  return 0;
}

RAVL_ENTRY_POINT(doHeaders);




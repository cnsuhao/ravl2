// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlSourceTools
//! file="Ravl/SourceTools/CodeManager/annotate.cc"

#include "Ravl/Option.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/SourceTools/DefsFile.hh"
#include "Ravl/SourceTools/SourceCodeManager.hh"
#include "Ravl/SourceTools/SourceFile.hh"
#include "Ravl/Text/TextFile.hh"
#include "Ravl/Text/ConfigFile.hh"
#include "Ravl/OS/Filename.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

using namespace RavlN;

bool verb = false;
bool dryRun = false;
bool setFileloc = false;
HashC<Tuple2C<StringC,StringC>,TextFileC> srcHeaders;// Tuple is license, file extension
HashC<StringC,StringC> defaultVars;
StringC defaultLicense = "LGPL";
StringC defaultOrganisation;
StringC defaultName;
StringC defaultDesc;

static bool CheckDirectory(StringC &dir,DefsMkFileC &defs) {
  if(verb)
    cerr << "Checking '" << dir << "' \n";
  StringListC source = defs.AllSources();
  StringC lib = defs["PLIB"].TopAndTail();
  StringC dirLicense = upcase(defs["LICENSE"]).TopAndTail();
  if(dirLicense.IsEmpty())
    dirLicense = defaultLicense; // Setup default license.

  // Sort out info for license header.
  StringC name = defs["PACKAGENAME"].TopAndTail();	
  StringC desc = defs["DESCRIPTION"].TopAndTail();
  ONDEBUG(cerr << "PackageName=" << name << " Description=" << desc << "\n");
  if(name.IsEmpty()) {
    name = defaultName;
    desc = defaultDesc;
  }
  StringC org = defs["ORGANISATION"].TopAndTail();
  if(org.IsEmpty())
    org = defaultOrganisation;
  
  for(DLIterC<StringC> it(source);it;it++) {
    FilenameC fn(dir + filenameSeperator + *it);
    StringC ext = fn.Extension();
    if(ext == "xpm") 
      continue; // Ignore xpm's.
    if(!fn.Exists()) {
      cerr << "ERROR: Source file '" << fn << "' does not exist. \n";
      return false;
    }
    if(!fn.IsWritable()) {
      cerr << "ERROR: Source file '" << fn << "' is not writable. \n";
      return false;
    }
    SourceFileC theFile;
    if(!theFile.Load(fn)) {
      cerr << "Failed to load file '" << fn << "'\n";
      continue;
    }
    StringC license = theFile.GetDocValue("license");
    if(license.IsEmpty())
      license = dirLicense;
    TextFileC hdr = srcHeaders[Tuple2C<StringC,StringC>(license,ext)];
    if(!hdr.IsValid() && license != "own") {
      if(verb)
	cerr << "WARNING: Don't know how to attach licence header to '" << fn << "' Ext:'" << ext << "' with license '" << license << "'\n";
      continue;
    }
    if(verb)
      cerr << "Checking file :" << fn << "\n";
    if(license != "own") {// Does file have its own license ?
      // We should check which license to acutaly use.
      theFile.CheckHeader(hdr,StringC(),name,desc,org);
    }
    for(HashIterC<StringC,StringC> it(defaultVars);it;it++) {
      ONDEBUG(cerr << "Checking var '" << it.Key() <<  "' \n");
      theFile.CheckDocVar(it.Key(),it.Data());
    }
    if(!lib.IsEmpty()) {
      if(theFile.FileType() != "Make" && theFile.FileType() != "Perl" && theFile.FileType() != "Java")
	theFile.CheckDocVar("lib",lib,true); // Force lib be correct.
    }
    if(setFileloc) // If its an absolute path.
      theFile.CheckDocVar("file",StringC('"') + fn + StringC('"'),true); // Force the file location to be correct.
    if(theFile.IsModified()) {
      cerr << "Updated file :" << fn << "\n";
      if(!dryRun)
	theFile.Save();
    }
    
  }
  return true;
}

bool SetupHeaders(const StringC &cfgFile) {
  ConfigFileC conf;
  if(!conf.Load(cfgFile)) {
    cerr << "ERROR: Failed to load config file '" << cfgFile << "' \n";
    return false;
  }
  // Setup default license.
  StringC cfgLicense = conf["license"];
  if(!cfgLicense.IsEmpty())
    defaultLicense = cfgLicense;
  defaultLicense.upcase(); // Always use upper case.
  defaultOrganisation = conf["organisation"];
  defaultName = conf["projectName"];
  defaultDesc = conf["projectDescription"];
  
  ConfigFileC hdrs = conf.Section("Headers");
  if(hdrs.IsValid()) {
    for(DLIterC<StringC> it(hdrs.ListSections());it;it++) {
      ConfigFileC cf = hdrs.Section(*it);
      StringC text = cf["text"];
      if(text.IsEmpty()) {
	cerr << "WARNING: No header text for '" << *it <<"'\n";
	continue; 
      }
      TextFileC hdrText(text,true);
      StringListC exts(cf["extensions"],", ");
      StringC license = cf["license"];
      if(license.IsEmpty())
	license = defaultLicense;
      license.upcase();
      for(DLIterC<StringC> it(exts);it;it++)
	srcHeaders[Tuple2C<StringC,StringC>(license,*it)] = hdrText;
    }
  }
  ConfigFileC dv = conf.Section("DefaultVars");
  if(dv.IsValid()) {
    for(ConfigFileIterVarC it(dv.IterVars());it;it++) {
      ONDEBUG(cerr << "Default value for '" << it.Key() << "' is '" << it.Data() << "'\n"); 
      defaultVars[it.Key()] = it.Data();
    }
  }
  
  return true;
}

int main(int nargs,char **argv) {
  OptionC option(nargs,argv);
  StringC fn = option.String("i",".","Input filename. ");
  StringC hdrConfig = option.String("c",PROJECT_OUT "/share/RAVL/CodeManager/fixSource.cfg","File to use a header. ");
  dryRun = option.Boolean("d",false,"Do a dry run. Don't change anything. ");
  setFileloc = option.Boolean("fl",setFileloc,"If true the file location will be updated. ");
  bool all = option.Boolean("a",true,"Go into inactive directories as well. ");
  verb = option.Boolean("v",false,"Verbose mode.");
  option.Check();
  
  if(!SetupHeaders(hdrConfig)) 
    return 1;
  
  SourceCodeManagerC chkit(fn);
  if(verb)
    chkit.SetVerbose(true);
  
  chkit.ForAllDirs(CallFunc2C<StringC&,DefsMkFileC&,bool>(&CheckDirectory),all);
  
  return 0;
}

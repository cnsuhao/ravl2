// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
/////////////////////////////////////////////////////////////
// SrcCheck.cc
//! rcsid="$Id$"
//! lib=RavlSourceTools

#include "Ravl/SourceTools/SourceCodeManager.hh"
#include "Ravl/StringList.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/BlkQueue.hh"
#include <iostream.h>

namespace RavlN {

  /////////////////////////////////
  // Default constructor.
  
  SourceCodeManagerC::SourceCodeManagerC() 
  {}
  
  SourceCodeManagerC::SourceCodeManagerC(const StringC &adir,bool doEnabled)
    : rootDir(adir.Copy()),
      skipSub(false)
  {}
  
  //: Access a defs file.
  
  DefsMkFileC &SourceCodeManagerC::DefsMkFile(const StringC &name) {
    DefsMkFileC *lu = defsFiles.Lookup(name);
    if(lu != 0)
      return *lu;
    DefsMkFileC &df = defsFiles[name];
    df = DefsMkFileC(rootDir + filenameSeperator + name);
    return df;
  }
  
  //: For all directories in project do 'op'.
  
  bool SourceCodeManagerC::ForAllDirs(CallFunc2C<StringC,DefsMkFileC,bool> op,bool inActiveAsWell = false) {
    BlkQueueC<StringC> toDo;
    toDo.InsLast(".");
    while(!toDo.IsEmpty()) {
      StringC at = toDo.Pop();
      StringC dir;
      if(at != ".")
	dir = rootDir + filenameSeperator + at;
      else
	dir = rootDir;
      DefsMkFileC defs = DefsMkFileC(dir + filenameSeperator + "defs.mk");
      if(verbose)
	cout << "Processing directory '" << dir << "'\n";
      if(!op(dir,defs)) {
	if(verbose) 
	  cerr << "SourceCodeManagerC::ForAll(), Error processing directory :'" << dir << "'\n";
	break;
      }
      // Sort out subdirectories.
      StringListC subDirs = defs.Nested();
      for(DLIterC<StringC> it(subDirs);it;it++)
	toDo.InsLast(at + filenameSeperator + *it);
    }
    return true;
  }

  
#if 0
  
  ////////////////////////////////
  // Load all sub-directories.
  
  bool SourceCodeManagerC::LoadNested(bool recurse,bool loadAll,IntT CurDepth) {    
    if(CurDepth > MaxRecurseDepth) {
      cerr << "ERROR: Maximum recursion depth reached in " << dir << " ."<< endl;
      return false;
    }
    
    StringC strdirs = defs.Value("NESTED");
    if(strdirs.IsEmpty())
      return true; // Nothing to do.
    StringListC subdirs(strdirs); // Split string into list.
    for(DLIterC<StringC> sit(subdirs);sit.IsElm();sit.Next()) {
      StringC adirn;
      bool isEnabled = true;
      adirn = sit.Data().before(".r");
      if(adirn.IsEmpty()) {
	isEnabled = false;
	adirn = sit.Data();
      }
      FilenameC subdirname = dir + '/' + adirn;
      if(!subdirname.IsDirectory()) {
	if(!MissingSubDir(subdirname))
	  return false;
	if(!subdirname.IsDirectory())  // May have been fixed ?
	  continue; // Ignore and continue if not.
      }
      if(IsVerbose())
	cerr << "Loading:" << subdirname << "\n";
      if(!(isEnabled || loadAll))
	continue;
      BRCPtrC<SourceCodeManagerC> newdir = NewSrc(subdirname,isEnabled);
      if(newdir.IsNull()) {
	cerr << "WARNING: Failed to open " << subdirname << "." << endl;
	continue;
      }
      children.InsLast(newdir);
      if(IsVerbose())
	newdir->SetVerbose(true);
      if(recurse) {
	if(!newdir->LoadNested(recurse,loadAll,CurDepth+1))
	  return false;
      }
    }
    return true;
  }


  //: Called if sub directory missing.

  bool SourceCodeManagerC::MissingSubDir(StringC &subdirname) {
    cerr << "WARNING: Sub-directory " << subdirname << " not found from " << dir << "/defs.mk" << endl;
    return true;
  }
  
  ///////////////////////////
  // Do operation on local directory.
  
  bool SourceCodeManagerC::DoOp() {
    // Do nothing....
  return true; // That was easy.
  }
  
  ///////////////////////////
  // Call DoOp on subdirectories.
  
  bool SourceCodeManagerC::DoNested(bool all) {
    if(!DoOp())
      return false;
    if(skipSub) // Skip subdirectories ?
      return true;
    DLIterC<BRCPtrC<SourceCodeManagerC> > sit(children);
    for(;sit.IsElm();sit.Next()) {
      if(!all && !sit.Data()->IsEnabled())
	continue;
      if(!sit.Data()->DoNested(all))
	return false;
    }
    return true;
  }
#endif  
  
}

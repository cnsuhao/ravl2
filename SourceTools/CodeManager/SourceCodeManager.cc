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

  
  
}

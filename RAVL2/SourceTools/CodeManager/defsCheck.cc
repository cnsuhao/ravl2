// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id: defsCheck.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlSourceTools
//! file="Ravl/SourceTools/CodeManager/defsCheck.cc"
//! docentry="Ravl.API.Source Tools"
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/Option.hh"
#include "Ravl/SourceTools/DefsFile.hh"
#include "Ravl/SourceTools/SourceCodeManager.hh"
#include "Ravl/OS/Filename.hh"

using namespace RavlN;

bool verb;

static bool CheckDirectory(StringC &dir,DefsMkFileC &defs) {
  if(verb)
    cerr << "Checking '" << dir << "' \n";
  StringListC source = defs.AllSources();
  for(DLIterC<StringC> it(source);it;it++) {
    FilenameC fn(dir + filenameSeperator + *it);
    if(!fn.Exists()) {
      cerr << "ERROR: Source file '" << fn << "' does not exist. \n";
      return false;
    }
    if(!fn.IsReadable()) {
      cerr << "ERROR: Source file '" << fn << "' is not readable \n";
      return false;
    }
  }
  return true;
}

int main(int nargs,char **argv) {
  OptionC option(nargs,argv);
  StringC fn = option.String("i",".","Input filename. ");
  bool all = option.Boolean("a",false,"Go into inactive directories as well. ");
  verb = option.Boolean("v",false,"Verbose mode.");
  option.Check();
  
  SourceCodeManagerC chkit(fn);
  if(verb)
    chkit.SetVerbose(true);  
  chkit.ForAllDirs(CallFunc2C<StringC&,DefsMkFileC&,bool>(&CheckDirectory),all);
  
  return 0;
}

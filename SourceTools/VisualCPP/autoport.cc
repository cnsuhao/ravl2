// This file is part of VCPP, Visual C++ porting tool for QMake projects 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/SourceTools/VisualCPP/autoport.cc"

#include "Ravl/Option.hh"

#include "Ravl/SourceTools/AutoPortSource.hh"
#include "Ravl/SourceTools/AutoPortGenerator.hh"
#include "Ravl/OS/Directory.hh"
#include <fstream.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

using namespace RavlN;

// If PROJECT_OUT isn't defined, make one up.

#ifndef PROJECT_OUT
#define PROJECT_OUT "."
#endif

void BuildTemplates(StringC &templFile,AutoPortSourceC &src,StringC &outFile) {
  if(FilenameC(templFile).IsDirectory()) {
    ONDEBUG(cerr << "Processing templates in :'" << templFile << "'\n");
    DirectoryC dir(templFile);
    DListC<StringC> fl = dir.FiltList("*.tmpl");
    for(DLIterC<StringC> it(fl);it;it++) {
      StringC subDir = dir + filenameSeperator + *it;
      BuildTemplates(subDir,src,outFile);
    }
    return;
  }
  ONDEBUG(cerr << "Processing template file : '" << templFile << "'\n");
  AutoPortGeneratorC fg(src,templFile,outFile);
  fg.BuildFiles();
}

// -----------------------------------------------------------------------------

int main(int nargs,char **argv) {

  OptionC option(nargs,argv,true);

  StringC fn    = option.String("i",".",     "(input)  Directory for unix src tree. ");
  StringC fout  = option.String("o","",      "(output) Directory for VCPP src tree.  ");
  StringC pathtempl= option.String("pt", PROJECT_OUT "/share/RAVL/AutoPort","Where to look for template files.");
  
  //bool rec    = option.Boolean("r",true,    "recurse into subdirectories. ");
  //bool all    = option.Boolean("a",false,   "Go into inactive directories as well. ");
  bool verb   = option.Boolean("v",false,   "Verbose mode.");
  
  option.Check();
  
  AutoPortSourceC portInfo(fn);
  if(verb) 
    portInfo.SetVerbose(verb);
  BuildTemplates(pathtempl,portInfo,fout);
  return 0;
}

// -----------------------------------------------------------------------------

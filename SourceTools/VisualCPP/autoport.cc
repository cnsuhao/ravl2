//////////////////////////////////////////
//! rcsid="$Id$"

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
    DListC<FilenameC> fl = dir.FiltList("*.tmpl");
    for(DLIterC<FilenameC> it(fl);it;it++) {
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
  StringC pathtempl= option.String("pt", PROJECT_OUT "/Tools/AutoPort","Where to look for template files.");
  
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

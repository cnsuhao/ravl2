//////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Option.hh"

//#include "Ravl/SourceTools/VCPP.hh"
#include <fstream.h>

using namespace RavlN;

// If PROJECT_OUT isn't defined, make one up.

#ifndef PROJECT_OUT
#define PROJECT_OUT "."
#endif

// -----------------------------------------------------------------------------

int main(int nargs,char **argv) {

#if 0
  OptionC option(nargs,argv,true);
  StringC fn    = option.String("i",".",     "(input)  Directory for unix src tree. ");
  StringC fout  = option.String("o","",      "(output) Directory for VCPP src tree.  ");
  StringC dosdrive= option.String("d", "h",    "dos drive letter to append to src path");
  StringC dospath = option.String("dp","same", "dos path for project files, "
                                                "no leading or trailing / required, "
                                                "defaults to same as output directory. ");
  StringC dostemp = option.String("dt","c:/temp","dos path for temp files. ");

  StringC libtempl= option.String("lt","lib6.dsp","A template file for a static library");
  StringC contempl= option.String("ct","con6.dsp","A template file for a console application");
  StringC pathtempl= option.String("pt", PROJECT_OUT "/Tools/VCPP","Where to look for template files.");
  
  bool rec    = option.Boolean("r",true,    "recurse into subdirectories. ");
  bool all    = option.Boolean("a",false,   "Go into inactive directories as well. ");
  bool back   = option.Boolean("b",false,   "Put the files back (run in reverse)");
  bool verb   = option.Boolean("v",false,   "Verbose mode.");
  bool one    = option.Boolean("one",false, "Make only one library.");
  bool execs  = option.Boolean("ex",false,  "Do the executables as well.");
  bool ported  = option.Boolean("ported",false,  "Create the RAVL ported workspace");
  
  option.Check();
  
  if (dospath=="same") 
    dospath=fout;
  
  ConvertVCPPC chkit(fn,
		     fout, fout + "/src",                             
		     dosdrive,  dospath, dostemp,
		     back,execs,one);
  
  if(verb) 
    chkit.SetVerbose(verb);

  chkit.LoadNested(rec,all);
  // read the defs files and load info on all the unix src files

  if(!chkit.DoNested(all)) return 1;
  // goes thru all the files and executes DoOp as provided in ConvertVCPP
  // i.e. all the file copying
  
  if(!back) {
    chkit.CreateProjectFiles(pathtempl + '/' + libtempl, pathtempl + '/' +contempl);
    chkit.CreateWorkspaceFile();
    chkit.CreateRAVLported(pathtempl + '/' + libtempl, pathtempl + '/' + "RAVLported");
  }
#endif
  return 0;
}

// -----------------------------------------------------------------------------

// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCxxDoc

#include "Ravl/CxxDoc/Parser.hh"
#include "Ravl/CxxDoc/Document.hh"
#include "Ravl/CxxDoc/DocTree.hh"
#include "Ravl/Option.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/DList.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/OS/Directory.hh"

#ifndef NDEBUG
#define YYDEBUG 1
#else
#define YYDEBUG 0
#endif

using namespace RavlN;
using namespace RavlCxxDocN;

#if YYDEBUG
extern "C" {
  extern int yydebug;
}
#endif

extern bool stopOnError;
extern bool verbose;

void BuildTemplates(FilenameC templFile,RavlCxxDocN::ObjectListC &ol,StringC &outFile,DocTreeC &dt) {
  if(templFile.IsDirectory()) {
    DirectoryC dir(templFile);
    DListC<FilenameC> fl = dir.FiltList("*.tmpl");
    for(DLIterC<FilenameC> it(fl);it;it++) 
      BuildTemplates(dir + filenameSeperator + *it,ol,outFile,dt);
    return;
  }
  
  RavlCxxDocN::DocumentC doc(templFile,outFile,dt);
  doc.Document(ol);
}

int BuildCxx(int argc, char **argv)
{
  // Setup default location for project out.
  const char *prjo = getenv("PROJECT_OUT");
  if(prjo == 0) 
    prjo = PROJECT_OUT; // Hmmm ... where else ?
  
  OptionC opt(argc,argv);
  StringC projName = opt.String("pn","Ravl","Project Name. ");
  StringC localProjOut = opt.String("p",prjo,"Project out. ");
  StringC inFiles = opt.String("i",localProjOut + "/inc" , "Directory containing header files");
  StringC outFile = opt.String("o",localProjOut + "/doc/Auto", "output document");
  StringC ehtFiles = opt.String("eht",localProjOut + "/Tools/AutoDoc/EHT","Location of EHT files. ");
  StringC templFiles = opt.String("tc",PROJECT_OUT "/Tools/CxxDoc/Class", "Directory of template files for class pages, or single template file");

#if 1
  StringC docNodeFiles = opt.String("td",PROJECT_OUT "/Tools/CxxDoc/DocNode", "Directory of template files for doc node page, or single template file");
#else
  StringC docNodeFiles = opt.String("td","", "Directory of template files for doc node page, or single template file");
#endif
  
  stopOnError = opt.Boolean("s",false,"Stop on error. ");
  bool noParse = opt.Boolean("np",false,"Don't do a header parse. ");
  verbose = opt.Boolean("v",false,"Verbose ");
#if YYDEBUG
  yydebug = opt.Boolean("d",false,"Enable parser debuging.");
#endif
  bool dump = opt.Boolean("l",false,"List database contents. ");
  bool doDoc = opt.Boolean("w",true,"Write documentation. ");
  
  opt.Check();
  
  RavlCxxDocN::ParserC pt(true);
  
  if(!noParse)
    pt.ParseTree(inFiles);

  if(verbose)
    cerr << "Resolving refrences.\n";
  pt.Resolve();
  
  DocTreeC docTree(projName);
  if(ehtFiles != "") 
    docTree.ReadEHTSet(ehtFiles);
  
  if(dump)
    pt.Dump(cout); // Dump parse tree.
  
  if(verbose)
    cerr << "Building documentation.\n";
  
  if(doDoc) {
    pt.Data().Append(docTree.Root());
    BuildTemplates(templFiles,pt.Data(),outFile,docTree);
    if(docNodeFiles != "")
      BuildTemplates(docNodeFiles,pt.Data(),outFile,docTree);
  }
  return 0;
}


//: This puts a wrapper around the main program that catches
//: exceptions and turns them into readable error messages.

RAVL_ENTRY_POINT(BuildCxx);

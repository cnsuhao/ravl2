// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCxxDoc
//! file="Ravl/SourceTools/CxxDoc/CxxDoc.cc"

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

#include <stdlib.h>


using namespace RavlN;
using namespace RavlCxxDocN;

#if YYDEBUG
extern "C" {
  extern int yydebug;
}
#endif

extern bool stopOnError;
extern bool verbose;

StringC projName;
StringC projDesc;

void BuildTemplates(FilenameC templFile,RavlCxxDocN::ObjectListC &ol,StringC &outFile,DocTreeC &dt) {
  if(templFile.IsDirectory()) {
    DirectoryC dir(templFile);
    DListC<StringC> fl = dir.FiltList("*.tmpl");
    for(DLIterC<StringC> it(fl);it;it++) 
      BuildTemplates(dir + filenameSeperator + *it,ol,outFile,dt);
    return;
  }
  
  RavlCxxDocN::DocumentC doc(templFile,outFile,dt,projName,projDesc);
  doc.Document(ol);
}

int BuildCxx(int argc, char **argv)
{
  // Setup default location for project out.
  const char *prjo = getenv("PROJECT_OUT");
  if(prjo == 0) 
    prjo = PROJECT_OUT; // Hmmm ... where else ?
  
  OptionC opt(argc,argv);
  projName = opt.String("pn","Ravl","Project Name. ").TopAndTail();
  projDesc = opt.String("pd","RAVL, Recognition And Vision Library","Project description. ").TopAndTail();
  StringC localProjOut = opt.String("p",prjo,"Project out. ");
  StringC inFiles = opt.String("i",localProjOut + "/include" , "Directory containing header files");
  StringC outFile = opt.String("o",localProjOut + "/share/doc/RAVL/Auto", "output document");
  StringC ehtFiles = opt.String("eht",localProjOut + "/share/RAVL/Admin/AutoDoc/EHT","Location of EHT files. ");
  StringC installHome = opt.String("ih",PROJECT_OUT,"Install home.");
  StringC templFiles = opt.String("tc",installHome + "/share/RAVL/CxxDoc/Class", "Directory of template files for class pages, or single template file");
  
  StringC docNodeFiles = opt.String("td",installHome + "/share/RAVL/CxxDoc/DocNode", "Directory of template files for doc node page, or single template file");
  
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
    cerr << "Resolving references.\n";
  pt.Resolve();
  
  DocTreeC docTree(projName);
  if(ehtFiles != "") {
    if(verbose)
      cerr << "Reading EHT files. \n";
    docTree.ReadEHTSet(ehtFiles);
  }
  
  if(dump) {
    cerr << "C++ Tree:\n";
    pt.Dump(cout); // Dump parse tree.
    cerr << "Docnodes:\n";
    docTree.Dump(cout);
  }
  
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

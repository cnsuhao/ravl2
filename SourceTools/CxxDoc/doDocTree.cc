// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCxxDoc

#include "Ravl/Option.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/CxxDoc/Document.hh"
#include "Ravl/DList.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/OS/Directory.hh"
#include "Ravl/CxxDoc/DocNode.hh"
#include "Ravl/CxxDoc/DocTree.hh"
#include <stdlib.h>

using namespace RavlN;
using namespace RavlCxxDocN;

extern bool verbose;

void BuildTemplates(FilenameC templFile,RavlCxxDocN::ObjectListC &ol,StringC &outFile) {
  if(templFile.IsDirectory()) {
    DirectoryC dir(templFile);
    DListC<FilenameC> fl = dir.FiltList("*.tmpl");
    for(DLIterC<FilenameC> it(fl);it;it++) 
      BuildTemplates(dir + filenameSeperator + *it,ol,outFile);
    return;
  }
  
  RavlCxxDocN::DocumentC doc(templFile,outFile);
  doc.Document(ol);
}

int BuildCxxTree(int argc, char **argv) {
 
  const char *prjo = getenv("PROJECT_OUT");
  if(prjo == 0) 
    prjo = PROJECT_OUT; // Hmmm ... where else ?
  
  OptionC opt(argc,argv);
  StringC localProjOut = opt.String("p",prjo,"Project out. ");
  StringC inFiles = opt.String("i",localProjOut + "/inc" , "Directory containing header files");
  StringC outFile = opt.String("o",localProjOut + "/doc/Auto", "output document");
  StringC templFiles = opt.String("tf",PROJECT_OUT "/Tools/CxxDoc/docnode.tmpl", "Directory of template files, or single template file");
  StringC projName = opt.String("n","Ravl","Project name. ");
  StringC ehtFiles = opt.String("eht",localProjOut + "/Tools/AutoDoc/EHT","Location of EHT files. ");
  StringC docEntries = opt.String("d",localProjOut + "/doc/Auto/Index/docentries","Project name. ");
  verbose = opt.Boolean("v",false,"Verbose ");
  bool dump = opt.Boolean("dump",false,"Dump out tree structure to cerr. ");
  bool doDoc = opt.Boolean("w",true,"Write documentation. ");
  
  opt.Check();
  cerr << "Building tree.\n";
  DocTreeC tree(projName);
  if(docEntries != "") 
    tree.ReadDocentries(docEntries);
  if(ehtFiles != "") 
    tree.ReadEHTSet(ehtFiles);
  if(doDoc) {
    cerr << "Writing documentation.\n";
    BuildTemplates(templFiles,tree.Root(),outFile);
  }
  if(dump) 
    tree.Root().Dump(cerr);
  cerr << "Done.\n";
  
  return 1;
}

RAVL_ENTRY_POINT(BuildCxxTree);

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlClassWizard
//! docentry="Ravl.Source Tools.Class Wizard"
//! author="Charles Galambos"

#include "Ravl/SourceTools/ClassWizard.hh"
#include "Ravl/Option.hh"

//: Tool for automaticly generating handle classes and methods
// This program searches for classes with a name ending in BodyC
// and ensure's the corresponding handle class exposes all its
// public functions.

using namespace RavlN;
int main(int nargs,char **argv)
{
  OptionC opts(nargs,argv);
  StringC prefix = opts.String("p","_","Prefix to add to modified files. ");
  bool verbose = opts.Boolean("v",false,"Verbose mode. ");
  StringC fileName=opts.String("",".","Input filename/directory. ");
  bool dryRun = opts.Boolean("d",false,"Dry run, don't write any files. ");
  bool writeStubs = opts.Boolean("s",false,"Write stubs. ");
  bool dumpTree = opts.Boolean("dt",false,"Dump parse tree. ");
  opts.Check();
  
  ClassWizardC classWizard(fileName,fileName,verbose,writeStubs,dryRun);
  if(!prefix.IsEmpty())
    classWizard.SetModifiedPrefix(prefix);
  if(verbose)
    cout << "Processing... \n";
  
  classWizard.ApplyWizard();
  if(dumpTree)
    classWizard.DumpParseTree(cout);
  if(verbose)
    cout << "Done. \n";
  
  return 0;
}
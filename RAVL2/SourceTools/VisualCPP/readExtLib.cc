// This file is part of VCPP, Visual C++ porting tool for QMake projects 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
#include "Ravl/SourceTools/ExtLibTable.hh"
#include "Ravl/Option.hh"
#include "Ravl/IO.hh"
//! rcsid="$Id$"
//! lib=RavlAutoPort
//! file="Ravl/SourceTools/VisualCPP/readExtLib.cc"

using namespace RavlN;

namespace RavlN {
  void InitExtLibFormat();
  void InitExtLibTableFormat();
}

int main(int nargs, char **argv) {
  OptionC opt(nargs, argv, true);
  
  StringC inFile = opt.String("i", "", "input xml file");
  InitExtLibFormat();
  InitExtLibTableFormat();

  ExtLibTableC libs;
  if(!Load(inFile, libs))
    RavlIssueError("Unable to open: " + inFile);

  for(HashIterC<StringC, ExtLibC>it(libs);it;it++) {
    cout << "-------------------" << endl;
    cout << it.Key() << endl;
    cout << it.Data().IncludePaths() << endl;
    cout << it.Data().LibPaths() << endl;
    cout << it.Data().Libs() << endl;
  }

  return 0;
}

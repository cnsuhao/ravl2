// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! author="Charles Galambos"
//! file="Ravl/Core/System/exXMLTree.cc"

#include "Ravl/XMLTree.hh"
#include "Ravl/Option.hh"

using namespace RavlN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC ifn = opt.String("i","test.xml","Input file. ");
  StringC ofn = opt.String("o","-","Output file. ");
  opt.Check();
  
  XMLIStreamC ins(ifn);
  if(!ins) {
    cerr << "Failed to open file '" << ifn << "' \n";
    return 1;
  }

  XMLTreeC tree(true);

  tree.Read(ins);
  
  OStreamC out(ofn);
  tree.Dump(out);
  return 0;
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: vdf.cc 3322 2003-08-22 11:10:02Z ees1wc $"
//! lib=RavlVDF
//! file="Ravl/Applications/VisualDataFlow/vdf.cc"

//: Visual Data Flow
//
// This is work in progress, not of much practical use 

#include "Ravl/Option.hh"
#include "Ravl/DF/GUIEditor.hh"
#include "Ravl/GUI/Manager.hh"

using namespace RavlGUIN;
using namespace RavlN;
using namespace RavlDFN;

int main(int nargs,char **argv) {
  Manager.Init(nargs,argv);
  
  OptionC opts(nargs,argv);
  StringC name = opts.String("n","new","Name of inital system. ");
  opts.Check();
  
  DFEditorC editor(name);
  
  editor.Show();
  
  Manager.Start();
  
  return 0;
}

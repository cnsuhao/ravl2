// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, Omniperception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/exMessageBox.cc"

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/MessageBox.hh"

using namespace RavlGUIN;

bool result2()
{
  cerr << "Alert box finished!" << endl;
  Manager.Quit();
  return true;
}

bool result1(bool& bResult)
{
  cerr << "Question box finished! Result: ";
  if (bResult) {
    cerr << "Yes!" << endl;
  }
  else {
    cerr << "No!" << endl;
  }  
  return true;
}

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  Manager.Execute();

  QuestionBox("Do you want to run a pointless function?",result1);
  AlertBox("This is just a message box");
  AlertBox("This alert box will quit the whole program",result2);
  
  Manager.Wait();
  cerr << "Finished... \n";
}

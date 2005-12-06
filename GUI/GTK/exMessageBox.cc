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
//! author="James Smith"
//! docentry="Ravl.API.GUI.Dialogs"
//! userlevel=Normal

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/MessageBox.hh"
#include "Ravl/GUI/ButtonBox.hh"

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

bool OnButtonClick(UIntT & buttonNo) {
  if(buttonNo == 0) 
    cerr << "Yes" << endl;
  else if(buttonNo ==1) 
    cerr << "No" << endl;
  else if(buttonNo == 2)
    cerr << "Cancel" << endl;
  else {
    cerr << "button no too high" << endl;
    return false;
  }
  return true;
}

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  Manager.Execute();
  cerr << "Opening window 1 \n";
  QuestionBox("Do you want to run a pointless function?",result1);
  cerr << "Opening window 2 \n";
  AlertBox("This is just a message box");
  cerr << "Opening window 3 \n";
  AlertBox("This alert box will quit the whole program",result2);
  
  cerr << "Opening window 4 \n";
  
  //: An example of ButtonBox in action
  SArray1dC<StringC>button(3);
  button[0] = "Yes";
  button[1] = "No";
  button[2] = "Cancel";
  ButtonBox("Do something here?", button,"Action Required", OnButtonClick); 
  
  cerr << "Waiting fox exit... \n";
  
  Manager.Wait();
  cerr << "Finished... \n";
}

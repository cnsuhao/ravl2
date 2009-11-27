// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/exCombo.cc"
//! userlevel=Normal
//! docentry="Ravl.API.Graphics.GTK.Control"
//! author="Lee Gregory"
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/ComboBoxText.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/Option.hh"

using namespace RavlGUIN;

//: A callback to handle seleced items
bool HandleCombo (ComboBoxTextC &  combo, StringC & id)
{
  cerr << "\n id: " << id << "\t" << combo.TextSelected() << "\n"; 
  return true ; 
}

int main(int nargs,char *args[]) 
{
  // Start the GUI manager - pass through any command line options
  Manager.Init(nargs,args);
  
  // Setup a list of things to put inside the combo box. 
  DListC<StringC> comboData ; 
  comboData.InsLast("item A") ; 
  comboData.InsLast("item B") ; 
  comboData.InsLast("item C") ; 
  comboData.InsLast("item D") ; 
  
  // Window creation
  WindowC win(100,100,"Combo Test");
  ComboBoxTextC combo(comboData, true);
  Connect(combo.SigTextSelected(), HandleCombo, combo, StringC(""));
  win.Add(combo);
  win.GUIShow();
  
  // Start the UI
  Manager.Start();
  cerr << "Finished... \n";
}

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
//! docentry="Ravl.API.GUI.Control"
//! author="Lee Gregory"
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Combo.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/Option.hh"

using namespace RavlGUIN;

//: A callback to handle seleced items
bool HandleCombo (ComboC &  combo, StringC & id)
{
  cerr << "\n id: " << id << "\t" << combo.Selected() ; 
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
 
 WindowC win(100,100,"Combo Test");
 win.Add( Combo( comboData, HandleCombo, StringC("combo 1"), true  ) ) ; 
 win.Show() ; 

  Manager.Start();
  cerr << "\n\nFinished... \n";
}

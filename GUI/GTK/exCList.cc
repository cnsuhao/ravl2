// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/CList.hh"


using namespace RavlGUIN;

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  WindowC win(100,100,"Hello");
  
  DListC<StringC> strLst;
  strLst.InsFirst("Hello1");
  strLst.InsFirst("Hello2");
  strLst.InsFirst("Hello3");
  strLst.InsFirst("A longer message");
#if 0
  CListC aList(strLst);
#else  
  const char *titles[] = {"one","two","three",0};
  CListC aList(titles);
#endif
  //aList.Add(StringC("Hi!!!"));
  SArray1dC<StringC> lineInfo(3);
  lineInfo[0] = "x";
  lineInfo[1] = "y";
  lineInfo[2] = "z";
  int val = 0;
  aList.GUIAppendLine(val,lineInfo);
    
  win.Add(aList);
  
  win.Show();
  
  //aList.Add(StringC("Hi2"));
  Manager.Start();
  
}

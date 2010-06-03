// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
// rcsinfo.cc
// $Id: rcsinfo.cc 77 2001-05-10 13:29:16Z craftit $
//! rcsid="$Id: rcsinfo.cc 77 2001-05-10 13:29:16Z craftit $"
//! lib=RavlSourceTools
//! file="Ravl/SourceTools/CodeManager/rcsinfo.cc"

#include "Ravl/DList.hh"
#include "Ravl/String.hh"
#include "Ravl/Option.hh"
#include "Ravl/SourceTools/RCSFile.hh"

#include <stdlib.h>

using namespace RavlN;

int main(int nargs,char **argv) {
  OptionC option(nargs,argv,true);
  DListC<StringC> files = option.List("i","Input files. ");
  bool extInit = option.Boolean("x",false,"Extract inital author info.\n");
  bool headOnly = option.Boolean("h",false,"Extract head version number only.\n");
  option.Check();
  
  for(DLIterC<StringC> it(files);it.IsElm();it.Next()) {
    RCSFileC rcsfile(it.Data());
    cout << it.Data();
    if(it.Data().length() < 8)
      cout << "\t";
    cout << "\t: ";
    if(extInit) {
      StringC author("??"),date("??");
      if(!rcsfile.ExtractInital(author,date)) {
	cerr << "ERROR: Failed to find inital author information. \n";
	exit(1);
      }
      cout <<"Author:'" << author <<"'  Date:'" << date << "'\n";
      continue;
    }
    if(!headOnly) {
      cout << "UsesRCS=" ;
      if(rcsfile.UsesRCS())
	cout << "Yes ";
      else {
	cout << "No \n";
	continue;
      }
    } else {
      if(!rcsfile.UsesRCS()) {
	cout << "Doesn't use RCS. \n";
	continue;
      }
    }
    cout << "Head=" << rcsfile.HeadVersion() << " ";
    if(headOnly) {
      cout << endl;
      continue;
    }
    cout << "IsCheckedOut=";
    if(rcsfile.IsCheckedOut())
      cout << "Yes ";
    else
      cout << "No ";
    
    cout << "IsAvailable=";
    if(rcsfile.IsAvailable())
      cout << "Yes ";
    else
      cout << "No ";
    
    cout << "HasAccess=";
    if(rcsfile.HasAccess(UserInfoC::WhoAmI()))
      cout << "Yes ";
    else
      cout << "No ";
    cout << "\n";
  }
  return 0;
}

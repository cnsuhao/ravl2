// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/DList/exDList.cc"
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Lists"

//: Simple example of DList's.

#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

int main() {

  DListC<int> aList;
  
  // Put the numbers 1,2,3 into the list in a round
  // about way.
  
  aList.InsFirst(2);
  aList.InsFirst(1);
  aList.InsLast(3);
  
  // To prove it go through the list with an iterator 
  // and print out elements.
  
  cout << "List:";
  for(DLIterC<int> it(aList);it;it++)
    cout << " " << *it;
  cout << "\n";
  return 0;
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/Collection.hh"
#include "Ravl/CollectionIter.hh"
#include "Ravl/SArr1Iter.hh"

using namespace RavlN;

int testBasic();

int main()
{
  int err;
  if((err = testBasic()) != 0) {
    cerr << "Test failed line :" << err <<"\n";
  }
  
  cerr << "Collection test passed. \n";
  return 0;
}

int testBasic() {
  
  CollectionC<IntT> c(100);
  
  if(!c.IsEmpty()) return __LINE__;
  int x = 0;
  c.Insert(x);
  if(c.Size() != 1) return __LINE__;
  if(c.IsEmpty()) return __LINE__;
  for(int i= 1;i < 100;i++)
    c.Insert(i);
  if(c.Size() != 100) return __LINE__;
  // Check pick.
  int v = c.Pick();
  if(v < 0 || v > 99) return __LINE__;
  // Check array function works, and the
  // value 'v' has been removed from the set.
  if(c.Size() != 99) return __LINE__;
  SArray1dC<IntT> vs(c.Array());
  for(SArray1dIterC<IntT> it(vs);it;it++)
    if(*it == v) return __LINE__;
  
  return 0;
}

template class CollectionC<IntT>;
template class CollectionIterC<IntT>;

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/Branch/testBranch.cc"

#include "Ravl/Stream.hh"
#include "Ravl/BList.hh"
#include "Ravl/BListIter.hh"
#include "Ravl/BHash.hh"
#include "Ravl/BHashIter.hh"

using namespace RavlN;

int testBList();
int testBListIter();
int testBHash();
int testBHashIter();

int main() {
  int ln;
  if((ln = testBList()) != 0) {
    cerr << "Error at line:" << ln << "\n";
    return 1;
  }
  if((ln = testBListIter()) != 0) {
    cerr << "Error at line:" << ln << "\n";
    return 1;
  }
  if((ln = testBHash()) != 0) {
    cerr << "Error at line:" << ln << "\n";
    return 1;
  }
  if((ln = testBHashIter()) != 0) {
    cerr << "Error at line:" << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int testBList() {
  BListC<int> list;
  if(!list.IsEmpty()) return __LINE__;
  if(list.Size() != 0) return __LINE__;
  list.InsFirst(1);
  if(list.IsEmpty()) return __LINE__;
  if(list.Size() != 1) return __LINE__;
  list.InsFirst(2);
  if(list.Size() != 2) return __LINE__;
  list.Empty();
  if(!list.IsEmpty()) return __LINE__;
  if(list.Size() != 0) return __LINE__;
  return 0;
}

int testBListIter() {
  // Build a test list.
  BListC<int> list;
  int i;
  for(i =0;i < 3;i++)
    list.InsFirst(i);
  // Check the iterator gives the same values as we put in.
  BListIterC<int> it(list);
  if(!it) return __LINE__;
  for(;it;it++) {
    i--;
    if(*it != i) return __LINE__;
  }
  if(i != 0) return __LINE__;
  // Check the iterator deals with an empty list.
  list.Empty();
  BListIterC<int> it2(list);
  if(it2) return __LINE__;
  return 0;
}

int testBHash() {
  BHashC<int,UIntT> table;
  for(int i = 0;i < 10;i++)
    table.Insert(i,(UIntT) i);
  UIntT x;
  for(int i = 0;i < 10;i++) {
    if(!table.Lookup(i,x)) return __LINE__;
    if(x != (UIntT) i) return __LINE__;
  }
  if(table.Lookup(10,x)) return __LINE__;
  return 0;
}

int testBHashIter() {
  BHashC<int,UIntT> table;
  for(int i = 0;i < 10;i++)
    table.Insert(i,(UIntT) i);
  UIntT count = 0;
  HSetC<int> done;
  for(BHashIterC<int,UIntT> it(table);it;it++) {
    if(it.Key() != it.Data()) return __LINE__;
    count++;
    done += it.Key();
  }
  if(done.Size() != count) return __LINE__;
  if(count != 10) return __LINE__;  
  return 0;
}

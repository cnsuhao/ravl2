// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/testCollection.cc"
//! docentry="Ravl.Core.Misc"
//! author="Charles Galambos"

#include "Ravl/Collection.hh"
#include "Ravl/CollectionIter.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/DArray1d.hh"
#include "Ravl/DArray1dIter.hh"
#include "Ravl/DArray1dIter2.hh"
#include "Ravl/DArray1dIter3.hh"
#include "Ravl/DList.hh"

using namespace RavlN;

int testBasic();
int testDArray1d();
int testDArray1dMore();

int main()
{
  int err;
  if((err = testBasic()) != 0) {
    cerr << "Test failed line :" << err <<"\n";
    return 1;
  }
  if((err = testDArray1d()) != 0) {
    cerr << "Test failed line :" << err <<"\n";
    return 1;
  }
  if((err = testDArray1dMore()) != 0) {
    cerr << "Test failed line :" << err <<"\n";
    return 1;
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


template class DArray1dC<IntT>;
template class DArray1dIterC<IntT>;
template class DArray1dIter2C<IntT,RealT>;
template class DArray1dIter3C<IntT,RealT,ByteT>;

const int testSize = 10000;

int testDArray1d() {
  cerr << "testDArray1d(), Called. \n";
  DArray1dC<int> test(10);
  
  if(!test.Contains(2)) return __LINE__;
  if(test.Contains(-1)) return __LINE__;
  if(test.Contains(11)) return __LINE__;
  
  test.Fill(1);
  UIntT count = 0;
  for(DArray1dIterC<int> it(test);it;it++) {
    if(*it != 1) return __LINE__;
    count++;
  }
  if(count != 10) return __LINE__;
  
  int i;
  for(i = 0;i < 10;i++)
    test[i] = i;
  i = 0;
  for(DArray1dIterC<int> it(test);it;it++,i++) 
    if(*it != i) return __LINE__;
  
  DArray1dC<int> test2(5,true);
  for(i = 0;i < testSize;i++) {
    if(test2.Size() != (UIntT) i) {
      cerr << "Test failed at count=" << i << " size=" << test2.Size() << "\n";
      return __LINE__;
    }
    test2.Append(i);
    IntT j = 0;
    for(DArray1dIterC<int> it(test2);it;it++,j++)
      if(*it != j) return __LINE__;
  }
  i = 0;
  for(DArray1dIterC<int> it(test2);it;it++,i++)
    if(*it != i) return __LINE__;
  if(i != testSize) return __LINE__;

  i = 0;
  for(DArray1dIter2C<int,int> it(test,test2);it;it++,i++) {
    if(it.Data1() != it.Data2()) return __LINE__;
    if(it.Index() != i) return __LINE__;
  }
  if(i != 10) return __LINE__;
  return 0;
}

int testDArray1dMore() {
  cerr << "testDArray1dMore(), Called. \n";
  DArray1dC<int> test1;
  DArray1dC<int> test2;
  DArray1dC<int> test3;
  int i;
  for(i = 0;i < 4;i++)
    test2.Append(i);
  for(;i < 8;i++)
    test3.Append(i);
  test1.Append(test2);
  test1.Append(test3);
  if(test1.Size() != 8) return __LINE__;
  for(i = 0;i < 8;i++)
    if(test1[i] != i) return __LINE__;
  return 0;
}

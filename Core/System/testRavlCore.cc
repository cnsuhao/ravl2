// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/testRavlCore.cc"

#include "Ravl/EntryPnt.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/Array1dIter2.hh"
#include "Ravl/Array2d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
//#include "Ravl/VectorN.hh"
//#include "Ravl/MatrixN.hh"
#include "Ravl/DList.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/StringList.hh"
#include "Ravl/InDList.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/HSet.hh"
//#include "Ravl/Graph.hh"
#include <string.h>


#if RAVL_HAVE_ANSICPPHEADERS
#include <iostream>
#include <typeinfo>
#else
#include <iostream.h>
#include <typeinfo.h>
#endif

using namespace RavlN;
using namespace std;

int testArray1();
int testArray2();
int testVectorN();
int testMatrixN();
int testDList();
int testTypeName();
int testStrList();
int testIntrDList();

int testRavlCore(int argc,char **argv) {
  int line = 0;
  if((line = testArray1()) != 0) {
    cerr << "Array1 test failed line :" << line << "\n";
    return 1;
  }
  if((line = testArray2()) != 0) {
    cerr << "Array2 test failed line :" << line << "\n";
    return 1;
  }
#if 0
  if((line = testVectorN()) != 0) {
    cerr << "VectorN test failed line :" << line << "\n";
    return 1;
  }
  if((line = testMatrixN()) != 0) {
    cerr << "MatrixN test failed line :" << line << "\n";
    return 1;
  }
#endif
  if((line = testDList()) != 0) {
    cerr << "DList test failed line :" << line << "\n";
    return 1;
  }
  if((line = testTypeName()) != 0) {
    cerr << "TypeName test failed line :" << line << "\n";
    return 1;
  }
  if((line = testStrList()) != 0) {
    cerr << "StrList test failed line :" << line << "\n";
    return 1;
  }
  if((line = testIntrDList()) != 0) {
    cerr << "IntrDList test failed line :" << line << "\n";
    return 1;
  }
  return 0;
}

int testArray1() {
  cout << "Testing Array1dC \n";  
  Array1dC<int> test(10);
  Array1dC<int> test2(10);
  test[0] = 1;
  test[9] = 0;
  int count = 0;
  for(Array1dIterC<int> it(test);it;it++) {
    *it = 1;
    count++;
  }
  if(count != 10) return __LINE__;
  for(Array1dIter2C<int,int> it(test,test2);it;it++) {
    it.Data1() = it.Data2();
    count++;
  }
  if(count != 20) return __LINE__;
  return 0;
}

int testArray2() {
  cout << "Testing Array2dC \n";  
  Array2dC<int> test(10,10);
  Array2dC<int> test2(10,10);
  test[0][1] = 1;
  test[9][3] = 0;
  int count = 0;
  for(Array2dIterC<int> it(test);it;it++) {
    *it = 1;
    count++;
  }
  if(count != 100) return __LINE__;
  for(Array2dIter2C<int,int> it(test,test2);it;it++) {
    it.Data1() = it.Data2();
    count++;
  }
  return 0;
}

#if 0
int testVectorN() {
  
  VectorNC<RealT> vec(10);
  return 0;
}

int testMatrixN() {
  cout << "Testing MatrixN \n";  
  MatrixNC<RealT> m1(10,10);
  MatrixNC<RealT> m2(10,10);
  for(MatrixNIterC<RealT> it(m1);it;it++)
    *it = 1;
  if(m1.Sum() != 100) return __LINE__;
  for(MatrixNIterNC<RealT,2> it(m1,m2);it;it++)
    *it = it[1];

  MatrixNC<RealT> m3 = m1.Copy();
  for(MatrixNIterNC<RealT,2> it(m2,m3);it;it++)
    if(*it != it[1]) return __LINE__;
  m3.Fill(5);
  for(MatrixNIterNC<RealT,2> it(m1,m3);it;it++)
    if(it[0] == it[1]) return __LINE__;
  m2 = m3;
  for(MatrixNIterNC<RealT,2> it(m2,m3);it;it++)
    if(*it != it[1]) return __LINE__;
  return 0;
}
#endif

static bool IntLessOrEqual(const int &v1,const int &v2)
{ return v1 <= v2; }

int testDList() {
  cout << "Testing DListC \n";
  DListC<IntT> alist;
  if(!alist.IsEmpty()) return __LINE__;
  alist.InsFirst(1);
  if(alist.Size() != 1) return __LINE__;
  if(alist.IsEmpty()) return __LINE__;
  alist.InsLast(-1);
  if(alist.Size() != 2) return __LINE__;
  alist.InsFirst(2);
  if(alist.Size() != 3) return __LINE__;
  IntT sum = 0;
  DLIterC<IntT> it(alist);
  for(;it;it++)
    sum += *it;  
  if(sum != 2) return __LINE__;
  it.First();
  if(*it != 2) return __LINE__;
  it.DelMoveNext();
  if(*it != 1) return __LINE__;
  if(alist.Size() != 2) return __LINE__;
  it.Del();
  if(it) return __LINE__; 
  if(alist.Size() != 1) return __LINE__;
  alist.Empty();
  if(alist.Size() != 0) return __LINE__;
  if(!alist.IsEmpty()) return __LINE__;
  
  // Check the sort function.
  alist.InsFirst(3); 
  alist.InsFirst(1);
  alist.InsFirst(7);
  alist.InsFirst(4);
  alist.InsFirst(2);
  alist.InsFirst(5);
  alist.InsFirst(6);
  alist.MergeSort(IntLessOrEqual);
  // Check it.
  if(alist.Size() != 7) return __LINE__;
  int last = 0;
  for(it.First();it;it++) {
    if(last > *it) return __LINE__;
    last = *it;
  }
  
  return 0;
}

int testTypeName() {
#if RAVL_HAVE_RTTI
  cout << "Testing TypeName() functions" << endl;
  const char *nm = TypeName(typeid(IntT));
  if(strcmp(nm,"IntT") != 0)  return __LINE__;
  nm = TypeName(typeid(RealT));
  if(strcmp(nm,"RealT") != 0)  return __LINE__;
  if(RTypeInfo("RealT") != typeid(RealT)) return __LINE__;
#endif
  return 0;
}


int testStrList()
{
  cout << "Testing StringListC" << endl;
  StringListC alist("one two 3");
  if(alist.Size() != 3) return __LINE__;
  if(alist.First() != "one") return __LINE__;
  if(alist.Last() != "3") return __LINE__;
  alist.PopFirst();
  if(alist.First() != "two") return __LINE__;
  return 0;
}

int testIntrDList() {
  cout << "Testing IntrDList\n";
  IntrDListC<DLinkC> lst;
  if(!lst.IsEmpty()) return __LINE__;
  DLinkC lnk1,lnk2,lnk3;
  lst.InsFirst(lnk1);
  if(lst.IsEmpty()) return __LINE__;
  if(lst.Size() != 1) return __LINE__;
  lst.InsFirst(lnk2);
  if(lst.Size() != 2) return __LINE__;
  if(&lst.First() != &lnk2) return __LINE__;
  if(&lst.Last() != &lnk1) return __LINE__;
  lst.InsLast(lnk3);
  if(&lst.Last() != &lnk3) return __LINE__;
  // What about the iterator ?
  IntrDLIterC<DLinkC> it(lst);
  if(!it.IsValid()) return __LINE__;
  if(!it) return __LINE__;
  if(&it.Data() != &lnk2)  return __LINE__;
  it++;
  if(!it) return __LINE__;
  if(&it.Data() != &lnk1)  return __LINE__;
  it.Next();
  if(!it) return __LINE__;
  if(&it.Data() != &lnk3)  return __LINE__;
  it.Next();
  if(it) return __LINE__;
  it--;
  if(!it) return __LINE__;
  if(&it.Data() != &lst.Last()) return __LINE__;
  return 0;
}

RAVL_ENTRY_POINT(testRavlCore);

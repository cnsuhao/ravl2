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
#include "Ravl/DList.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/StringList.hh"
#include "Ravl/InDList.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/HSet.hh"
#include "Ravl/Option.hh"
#include "Ravl/FunctionRegister.hh"
#include "Ravl/Cache.hh"
#include "Ravl/String.hh"
#include "Ravl/StrStream.hh"

#include <string.h>

#if RAVL_HAVE_ANSICPPHEADERS
#include <iostream>
#include <typeinfo>
#else
#include <iostream.h>
#include <typeinfo.h>
#endif

using namespace RavlN;
#if RAVL_HAVE_STDNAMESPACE
using namespace std;
#endif

int testArray1();
int testArray2();
int testDList();
int testTypeName();
int testStrList();
int testIntrDList();
int testOption();
int testFunctionRegister();
int testCache();
int testStringArrayIO();

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
  if((line = testOption()) != 0) {
    cerr << "Option test failed line :" << line << "\n";
    return 1;
  }
  if((line = testFunctionRegister()) != 0) {
    cerr << "FunctionRegister test failed line :" << line << "\n";
    return 1;
  }
  if((line = testCache()) != 0) {
    cerr << "Cache test failed line :" << line << "\n";
    return 1;
  }
  if((line = testStringArrayIO()) != 0) {
    cerr << "String array io test failed line :" << line << "\n";
    return 1;
  }
  
  cout << "Test passed. \n";
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

int testOption() {
  cout << "Testing OptionC.\n";
  // Do a quick check that OptionC is doing something sensible.
  int nargs = 5;
  char *argv[] = { "arg0","-d","0.3","-i","4",0 };
  OptionC opt(nargs,argv);
  RealT vd= opt.Real("d",0,"Read in a real. ");
  RealT vd2= opt.Real("d2",0.4,"Read in a real. ");
  IntT vi= opt.Int("i",1,"Read in a int. ");
  opt.Check();
  if(vd != 0.3) return __LINE__;
  if(vi != 4) return __LINE__;
  if(vd2 != 0.4) return __LINE__;
  if(!opt.IsOnCommandLine("d")) return __LINE__;
  if(opt.IsOnCommandLine("x")) return __LINE__;
  
  return 0;
}

int testFunctionRegister() {
  cout << "Testing FunctionRegister. \n";
  
  int (*afunc)(int);
  
  if(!LookupFunctionByName("NullFunc(int)",afunc)) return __LINE__;
  if(afunc(2) != 2) return __LINE__;
  return 0;
}

int testCache() {
  cout << "Testing CacheC. \n";
  CacheC<IntT,IntT> cache(5);
  for(int i = 0;i < 10;i++)
    cache.Insert(i,i);
  if(cache.Size() != 5)
    return __LINE__;
  for(CacheIterC<IntT,IntT> it(cache);it;it++) {
    if(it.Key() < 5) return __LINE__;
    if(it.Key() != it.Data()) return __LINE__;
  }  
  IntT v;
  for(int i = 5;i <= 9;i++) {
    if(!cache.Lookup(i,v)) return __LINE__;
    if(v != i) return __LINE__;
  }
    
  return 0;
}

int testStringArrayIO() {
  cout << "Testing SArray1dC<StringC> IO. \n";
 
  // Test SArray1dC...
  SArray1dC<StringC> str(3);
  str[0] = StringC("Hello1");
  str[1] = StringC("Hello2");
  str[2] = StringC("Hello3");
  
  StrOStreamC outs;
  outs << str;
  StringC data = outs.String();
  StrIStreamC ins(data);
  SArray1dC<StringC> tstr;
  ins >> tstr;
  if(str.Size() != tstr.Size()) return __LINE__;
  if(str[0] != tstr[0]) return __LINE__;
  if(str[1] != tstr[1]) return __LINE__;
  if(str[2] != tstr[2]) return __LINE__;

  // Test Array1dC...
  
  Array1dC<StringC> tarr(tstr);
  StrOStreamC xout;
  xout << tarr;
  
  StrIStreamC ins2(xout.String());
  //cerr << "Data='" << data << "'\n";
  Array1dC<StringC> xstr;
  ins2 >> xstr;
  if(str.Size() != (UIntT) xstr.Range().Size()) return __LINE__;
  if(str[0] != xstr[0]) return __LINE__;
  if(str[1] != xstr[1]) return __LINE__;
  if(str[2] != xstr[2]) return __LINE__;
  
  return 0;
}

RAVL_ENTRY_POINT(testRavlCore);

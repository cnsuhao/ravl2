// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/DList/testDList.cc"

#include "Ravl/InDList.hh"
#include "Ravl/InDLIter.hh"
#include "Ravl/DList.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/BinStream.hh"
#include <iostream.h>

using namespace RavlN;

class StuffC
  : public DLinkC
{
public:
  StuffC()
    {}
  //: Default constructor.

  StuffC(int nv)
    : v(nv)
    {}
  //: Constructor.
  
  int v;
};

#ifndef __sgi__
template class DListC<IntT>;
template class DLIterC<IntT>;

template IntrDListC<StuffC>; // Force instanciation of all methods.
template IntrDLIterC<StuffC>; // Force instanciation of all methods.
#endif

int testDListBinIO();
int testIntrDList();

int main(int nargs,char *argv[])
{
  int lineno;
  if((lineno = testIntrDList()) != 0) {
    cerr << "testIntrDListC test failed on line "<< lineno << "\n";
    return 1;
  }
  if((lineno = testDListBinIO()) != 0) {
    cerr << "testDListIO test failed on line "<< lineno << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";	      
  return 0;
}

int testIntrDList() {
  IntrDListC<StuffC> lst;
  if(!lst.IsEmpty()) return __LINE__;
  int i;
  for(i = 0;i < 10;i++)
    lst.InsLast(*new StuffC(i));
  i = 0;
  if(lst.IsEmpty()) return __LINE__;
  for(IntrDLIterC<StuffC> it(lst);it;it++,i++) {
    if(it->v != i)
      return __LINE__;
  }
    
  IntrDListC<StuffC> lstCopy(lst);
  if(lstCopy.IsEmpty()) return __LINE__;
  lst.Empty();
  if(!lst.IsEmpty()) return __LINE__;
  if(lstCopy.IsEmpty()) return __LINE__;
  i = 0;
  for(IntrDLIterC<StuffC> it(lstCopy);it;it++,i++) {
    if(it->v != i)
      return __LINE__;
  }
  IntrDListC<StuffC> lstCopy2;
  lstCopy2 = lstCopy;
  if(!lst.IsEmpty()) return __LINE__;
  if(lstCopy.IsEmpty()) return __LINE__;
  if(lstCopy2.IsEmpty()) return __LINE__;
  i = 0;
  for(IntrDLIterC<StuffC> it(lstCopy2);it;it++,i++) {
    if(it->v != i)
      return __LINE__;
  }
  
  return 0;
}

int testDListBinIO() {
  DListC<IntT> val;
  val.InsLast(1);
  val.InsLast(2);
  
  StrOStreamC out;
  BinOStreamC bo(out);
  
  bo << val;
  StrIStreamC in(out.String());
  BinIStreamC bi(in);
  DListC<IntT> back;
  bi >> back;
  if(back.Size() != val.Size()) return __LINE__;
  if(back.First() != val.First()) return __LINE__;
  if(back.Last() != val.Last()) return __LINE__;
  
  return 0;
}


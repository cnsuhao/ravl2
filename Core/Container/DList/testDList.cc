// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/DList/testDList.cc"

#include "Ravl/IntrDList.hh"
#include "Ravl/IntrDLIter.hh"
#include "Ravl/DList.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/Stream.hh"

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
int testDLIter();

int main(int nargs,char *argv[])
{
  int lineno;
  if((lineno = testIntrDList()) != 0) {
    cerr << "testIntrDListC test failed on line "<< lineno << "\n";
    return 1;
  }
  if((lineno = testDLIter()) != 0) {
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

int testDLIter() {
  DListC<IntT> list;
  for(int i = 0;i < 10;i++)
    list.InsLast(i);
  DLIterC<IntT> it(list);
  if(!it) return __LINE__;
  if((*it) != 0) return __LINE__;
  it++;
  if(!it) return __LINE__;
  if((*it) != 1) return __LINE__;
  DLIterC<IntT> ita = it;
  it++;
  if(!it) return __LINE__;
  if((*it) != 2) return __LINE__;
  it++;
  if(!it) return __LINE__;
  if((*it) != 3) return __LINE__;
  DLIterC<IntT> itb = it;
  it++;
  if(!it) return __LINE__;
  if((*it) != 4) return __LINE__;
  it++;
  if(!it) return __LINE__;
  if((*it) != 5) return __LINE__;
  
  DListC<IntT> incHead = ita.Head();
  DListC<IntT> incTail = itb.InclusiveTail();
#if 0
  cerr << "IncHead=" << incHead << "\n";
  cerr << "IncTail=" << incTail << "\n";
  cerr << "list=" << list << "\n";
#endif
  if(list.Size() != 2) return __LINE__;
  if(incTail.Size() != 7) return __LINE__;
  if(incHead.Size() != 1) return __LINE__;
  
  DLIterC<IntT> itc = list;
  DLIterC<IntT> itd = itc;
  itd++;
  DListC<IntT> xyz = itc.Head();
  if(xyz.Size() != 0) return __LINE__;
  if(list.Size() != 2) return __LINE__;
  DListC<IntT> la = itc.Tail();
  //cerr << "la=" << la << " itc=" << *itc << "\n";
  if(la.Size() != 1) return __LINE__;
  if(la.First() != 2) return __LINE__;
  // Check taking the head and tail of an empty list works.
  
#if 0
  DListC<IntT> emptyList;
  DLIterC<IntT> itz(emptyList);
  itz.Tail();
  itz.Head();
#endif
  return 0;
}

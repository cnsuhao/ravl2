// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/Array/testArray2d.cc"

#include "Ravl/Array3d.hh"
#include "Ravl/Array3dIter.hh"
#include "Ravl/Array3dIter2.hh"
#include "Ravl/Array3dIter3.hh"

using namespace RavlN;

int testBasic();
int testSqr2();
int testSqr3();
int testSqr31();
int testSqr311();

int main()
{
  int ln;
  if((ln = testBasic()) != 0) {
    cerr << "Basic Array2d test failed line:" << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int testBasic() {

  Array3dC<IntT> arr1(1,10,2,10,3,10);
  Index3dC origin = Index3dC(1,2,3);
  arr1[1][2][3] = 0;
  arr1.Fill(1);
  if(arr1[1][2][3] != 1) {
    cerr << "Fill failed. ("  << arr1[1][2][3] << ")\n";
    return __LINE__;
  }
  
  UIntT x = 0;
  {
    Array3dIterC<IntT> it(arr1);
    if(it.Index() != origin) {
      cerr << "Index check 1 failed.  Inital:" << it.Index() << "  \n";
      return __LINE__;
    }
    for(;it;it++)
      x += *it;
  }
  arr1 /= 2;
  arr1 += 1;
  arr1 = arr1 + arr1;
  UIntT count =0;
  UIntT total = 0;
  {
    Array3dIter2C<IntT,IntT> it(arr1,arr1);
    if(it.Index() != origin)  return __LINE__;
    for(;it;it++) {
      total += it.Data1();
      it.Data1() = count;
      if(it.Data2() != (IntT) count) return __LINE__;
      count++;
    }
    if(count != arr1.Size()) return __LINE__;
    cerr << "Total: " << total << "\n";
  }
  {
    Array3dIter3C<IntT,IntT,IntT> it(arr1,arr1,arr1);
    count = 0;
    if(it.Index() != origin) return __LINE__;
    for(;it;it++) {
      it.Data1() = it.Data2();
      count++;
    }
    if(count != arr1.Size()) return __LINE__;
  }
  return 0;
}

template class Array3dC<IntT>;
template class Array3dIterC<IntT>;
template class Array3dIter2C<IntT,RealT>;
template class Array3dIter3C<IntT,RealT,ByteT>;

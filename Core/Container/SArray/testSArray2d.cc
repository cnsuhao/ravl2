// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/SArray/testSArray2d.cc"

#include "Ravl/SArray2d.hh"
#include "Ravl/Slice1d.hh"
#include "Ravl/SArr2Iter.hh"
#include "Ravl/SArr2Iter2.hh"
#include "Ravl/SArr2Iter3.hh"

using namespace RavlN;

int main() {
  cerr << "Starting test of SArray2d.\n";
  SArray2dC<int> testArr(10,10);
  testArr[Index2dC(1,1)] = 2;
  
  int place = 0;
  for(IndexC i = 0;i < 10;i++)
    for(IndexC j = 0;j < 10;j++)
      testArr[i][j] = place++;
  
  Slice1dC<int> slice = testArr.Diagonal();
  int v = 0;
  for(Slice1dIterC<int> its(slice);its;its++,v+=11) {
    if(*its != v) {
      cerr << "Diagonal slice test failed. " << *its << " " << v << "\n";
      return 1;
    }
  }
  v = 0;
  for(SArray2dIterC<int> it(testArr);it;it++,v++) {
    if(*it != v) {
      cerr << "Iterator test failed. " << *it << " " << v << "\n";
      return 1;
    }
    *it = 0;
  }
  testArr /= 2;
  testArr += 1;
  testArr = testArr + testArr;
  
  for(SArray2dIter2C<int,int> it(testArr,testArr);it;it++)
    it.Data1() = 0;
  for(SArray2dIter3C<int,int,int> it(testArr,testArr,testArr);it;it++)
    it.Data1() = 0;
  cerr << "Test passed ok. \n";
  return 0; 
}

template class SArray2dC<UIntT>;
template class SArray2dIterC<UIntT>;
template class SArray2dIter2C<UIntT,RealT>;
template class SArray2dIter3C<UIntT,RealT,ByteT>;

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

#include "Ravl/SArray3d.hh"
#include "Ravl/Slice1d.hh"
#include "Ravl/SArr3Iter.hh"
#include "Ravl/SArr3Iter2.hh"
#include "Ravl/SArr3Iter3.hh"

using namespace RavlN;

int main() {
  cerr << "Starting test of SArray3d.\n";
  SArray3dC<int> testArr(10,10,10);
  testArr[Index3dC(1,1,1)] = 2;
  
  int place = 0;
  for(IndexC i = 0;i < 10;i++)
    for(IndexC j = 0;j < 10;j++)
      for(IndexC k = 0;k < 10;k++)
	testArr[i][j][k] = place++;
  
  int v = 0;
#if 0
  Slice1dC<int> slice = testArr.Diagonal();
  for(Slice1dIterC<int> its(slice);its;its++,v+=11) {
    if(*its != v) {
      cerr << "Diagonal slice test failed. " << *its << " " << v << "\n";
      return 1;
    }
  }
#endif
  v = 0;
  for(SArray3dIterC<int> it(testArr);it;it++,v++) {
    if(*it != v) {
      cerr << "Iterator test failed. " << *it << " " << v << "\n";
      return 1;
    }
    *it = 0;
  }
  testArr /= 2;
  testArr += 1;
  testArr = testArr + testArr;
  
  for(SArray3dIter2C<int,int> it(testArr,testArr);it;it++)
    it.Data1() = 0;
  for(SArray3dIter3C<int,int,int> it(testArr,testArr,testArr);it;it++)
    it.Data1() = 0;
  cerr << "Test passed ok. \n";
  return 0; 
}

template class SArray3dC<UIntT>;
template class SArray3dIterC<UIntT>;
template class SArray3dIter2C<UIntT,RealT>;
template class SArray3dIter3C<UIntT,RealT,ByteT>;

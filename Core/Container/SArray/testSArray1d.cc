// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlCore
//! file="Ravl/Core/Container/SArray/testSArray1d.cc"
//! rcsid="$Id$"

#include "Ravl/Stream.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/SArray1dIterR.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/SArray1dIter4.hh"

using namespace RavlN;

int testBasic();
int testSort();
int testReverse();
int testIO();

int  main()
{
  int ln;
  if((ln = testBasic()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testSort()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testIO()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  return 0;
}

int testBasic() {

  ////////////////////////////////////////////////////
  // Test conversions between SArray1dC and Array1dC.
  
  SArray1dC<IntT> sarr1(2);
  sarr1[0] = 1;
  sarr1[1] = 2;
  
  if(sarr1.Contains(2)) {
    cerr << "Array bounds problem. 1 \n";
    return __LINE__;
  }
  if(sarr1.Contains(2) || sarr1.Contains(-1)) {
    cerr << "Array bounds problem. 2 \n";
    return __LINE__;
  }
  // Check copy.
  SArray1dC<IntT> sarr2(sarr1.Copy());
  sarr1[0]=2;
  if(sarr2[0] != 1 || sarr2[1] != 2) {
    cerr << "SArray Copy failed.\n";
    return __LINE__;
  }
  if(sarr2.Size() != sarr1.Size()) {
    cerr << "SArray copy failed.\n";
    return __LINE__;
  }
  sarr1[0]=1;
  // Check iterators work properly.
  IntT sum = 0;
  IntT count = 0;
  for(SArray1dIterC<IntT> it(sarr2);it;it++,count++)
    sum += *it;
  if(sum != 3 || count != 2) {
    cerr << "Sum failed.\n";
    return __LINE__;
  }
  sum = 0;
  for(SArray1dIterC<IntT> it(sarr2,1);it;it++)
    sum += *it;
  if(sum != 1) {
    cerr << "Sum failed 2.\n";
    return __LINE__;
  }
  sum = 0;
  for(SArray1dIterC<IntT> it(sarr2,2);it;it++)
    sum += *it;
  if(sum != 3) {
    cerr << "Sum failed 3.\n";
    return __LINE__;
  }
  sum = 0;
  for(SArray1dIterC<IntT> it(sarr2,0);it;it++)
    sum += *it;
  if(sum != 0) {
    cerr << "Sum failed 4.\n";
    return __LINE__;
  }
  
  // Check it works on empty arrays.
  SArray1dC<IntT> earr;
  sum = 0;
  for(SArray1dIterC<IntT> it(earr,0);it;it++)
    sum++;
  if(sum != 0) {
    cerr << "Empty array test failed. \n";
    return __LINE__;
  }

  // Numerical opertions...
  
  SArray1dC<IntT> sarrSum = sarr1 + sarr2;
  if(sarrSum.Size() != sarr1.Size()) {
    cerr << "Size check failed. \n";
    return __LINE__;
  }
  if(sarrSum[0] != 2) {
    cerr << "Sum check failed. \n";
    return __LINE__;
  }
  if(sarrSum[1] != 4) {
    cerr << "Sum check failed. \n";
    return __LINE__;
  }
  cerr << "SArray test passed. \n";
  return 0;
}

int testSort() {
  SArray1dC<int> arr(5);
  arr[0] = 1;
  arr[1] = 5;
  arr[2] = 2;
  arr[3] = 4;
  arr[4] = 3;
  
  arr.Sort();
  // cerr << "Out=" << arr << "\n";
  for(int i = 1;i < (int) arr.Size();i++)
    if(arr[i-1] < arr[i]) return __LINE__;

  arr[0] = 1;
  arr[1] = 5;
  arr[2] = 2;
  arr[3] = 4;
  arr[4] = 3;
  BubbleSort(arr);
  for(int i = 1;i < (int) arr.Size();i++)
    if(arr[i-1] < arr[i]) return __LINE__;
  
  return 0;
}

int testIO() {
  SArray1dC<RealT> v(4);
  for(int i = 0;i < 4;i++)
    v[i] = i;
  
  // Test binary IO.
  {
    StrOStreamC os;
    {
      BinOStreamC bin(os);
      bin << v;
    }
    SArray1dC<RealT> v2;
    StrIStreamC ifs(os.String());
    {
      BinIStreamC bin(ifs);
      bin >> v2;
    }
    if((v - v2).SumOfSqr() > 0.000001)
      return __LINE__;
  }

  // Test text IO.
  {
    StrOStreamC os;
    os << v;
    SArray1dC<RealT> v2;
    StrIStreamC ifs(os.String());
    ifs >> v2;
    if((v - v2).SumOfSqr() > 0.000001)
      return __LINE__;
  }
  return 0;
}

int testReverse() {
  cerr << "Reverse test. \n";
  SArray1dC<IntT> arr(3);
  for(IntT i = 0;i < (IntT) arr.Size();i++)
    arr[i] = i;
  SArray1dIterRC<IntT> it(arr);
  if(!it) return __LINE__;
  if(*it != 2) return __LINE__;
  it--;
  if(!it) return __LINE__;
  if(*it != 1) return __LINE__;
  it--;
  if(!it) return __LINE__;
  if(*it != 0) return __LINE__;
  it--;
  if(it) return __LINE__;
  return 0;
}

#include "Ravl/Slice1d.hh"

template class SArray1dC<UIntT>;
template class SArray1dIterC<UIntT>;
template class SArray1dIter2C<UIntT,RealT>;
template class SArray1dIter3C<UIntT,RealT,ByteT>;
template class SArray1dIter4C<UIntT,RealT,ByteT,IntT>;

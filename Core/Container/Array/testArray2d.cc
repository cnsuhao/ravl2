// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/Array/testArray2d.cc"

#include "Ravl/Array2d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/Array2dSqr2Iter.hh"
#include "Ravl/Array2dSqr2Iter2.hh"
#include "Ravl/Array2dSqr3Iter.hh"
#include "Ravl/Array2dSqr31Iter2.hh"
#include "Ravl/Array2dSqr311Iter3.hh"
#include "Ravl/Array2dSqr3111Iter4.hh"
#include "Ravl/Array2dSqr3311Iter4.hh"
#include "Ravl/SArr2Iter.hh"

using namespace RavlN;

int testBasic();
int testSArrayConv();
int testSqr2();
int testSqr3();
int testSqr31();
int testSqr31b();
int testSqr311();
int testSqr3111();

int main()
{
  int ln;
  if((ln = testBasic()) != 0) {
    cerr << "Basic Array2d test failed line:" << ln << "\n";
    return 1;
  }
  if((ln = testSArrayConv()) != 0) {
    cerr << "SArrayConv Array2d test failed line:" << ln << "\n";
    return 1;
  }
  if((ln = testSqr2()) != 0) {
    cerr << "Sqr2Iter Array2d test failed line:" << ln << "\n";
    return 1;
  }
  if((ln = testSqr3()) != 0) {
    cerr << "Sqr3Iter Array2d test failed line:" << ln << "\n";
    return 1;
  }
  if((ln = testSqr31()) != 0) {
    cerr << "Sqr31Iter2 Array2d test failed line:" << ln << "\n";
    return 1;
  }
  if((ln = testSqr31b()) != 0) {
    cerr << "Sqr31Iter2 Array2d test failed line:" << ln << "\n";
    return 1;
  }
  if((ln = testSqr311()) != 0) {
    cerr << "Sqr311Iter3 Array2d test failed line:" << ln << "\n";
    return 1;
  }
  if((ln = testSqr3111()) != 0) {
    cerr << "Sqr3111Iter4 Array2d test failed line:" << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int testBasic() {

  Array2dC<IntT> arr1(1,10,2,10);
  arr1[1][2]  = 0;
  arr1.Fill(1);
  if(arr1[1][2] != 1) {
    cerr << "Fill failed. ("  << arr1[1][2] << ")\n";
    return __LINE__;
  }
  
  UIntT x = 0;
  {
    Array2dIterC<IntT> it(arr1);
    if(it.Index() != arr1.Rectangle().Origin()) {
      cerr << "Index check 1 failed.  Inital:" << it.Index() << "  Origin:" << arr1.Rectangle().Origin() << "\n";
      return __LINE__;
    }
    for(;it;it++)
      x += *it;
  }
  if(x != arr1.Rectangle().Area()) {
    cerr << "Area test failed. \n";
    return __LINE__;
  }
  arr1 /= 2;
  arr1 += 1;
  arr1 = arr1 + arr1;
  
  {
    Array2dIter2C<IntT,IntT> it(arr1,arr1);
    if(it.Index() != arr1.Rectangle().Origin()) {
      cerr << "Index check 2 failed. \n";
      return __LINE__;
    }    
    for(;it;it++)
      it.Data1() = it.Data2();
  }
  {
    Array2dIter3C<IntT,IntT,IntT> it(arr1,arr1,arr1);
    if(it.Index() != arr1.Rectangle().Origin()) {
      cerr << "Index check 3 failed. \n";
      return __LINE__;
    }    
    for(;it;it++)
      it.Data1() = it.Data2();
  }

  return 0;
}

int testSArrayConv() {
  Array2dC<IntT> data(IndexRangeC(1,3),IndexRangeC(2,6));
  int i = 0;
  for(Array2dIterC<IntT> it(data);it;it++,i++)
    *it = i;
  Array2dC<IntT> data2(3,3);  
  i = 0;
  for(Array2dIterC<IntT> it(data2);it;it++,i++)
    *it = i;
  SArray2dC<IntT> d1(data2.SArray2d());
  i = 0;
  for(SArray2dIterC<IntT> it(d1);it;it++,i++)
    if(*it != i) return __LINE__;
  i = 0;
  Array2dC<IntT> a1(d1);
  for(Array2dIterC<IntT> it(a1);it;it++,i++)
    if(*it != i) return __LINE__;
  
  SArray2dC<IntT> d2(data.SArray2d(true));
  i = 0;
  for(SArray2dIterC<IntT> it(d2);it;it++,i++)
    if(*it != i) return __LINE__;
  
  return 0;
}


// Test 2x2 iterators.

int testSqr2() {
  Array2dC<IntT> data(4,4);
  
  IntT count = 1;
  for(Array2dIterC<IntT> ita(data);ita;ita++)
    *ita = count++;
  //cerr <<"Locs:" << count << "\n";
  count = 0;
  IntT sqrs = 0;
  Array2dSqr2IterC<IntT> it(data);
  if(!it.First()) return __LINE__;
  if(!it) return __LINE__;
  for(;it;it++,sqrs++)
    count += it.DataBR() + it.DataBL() + it.DataTR() + it.DataTL();
  if(sqrs != 9) return __LINE__;
  if(count != 306) return __LINE__;
  // Seems ok.

  Array2dC<Int16T> data2(4,4);
  data2.Fill(1);
  Array2dSqr2Iter2C<IntT,Int16T> it2(data,data2);
  if(!it2) return __LINE__;
  if(!it2.First()) return __LINE__;
  sqrs = 0;
  count = 0;
  for(;it2;it2++,sqrs++)
    count += it2.DataBR1() + it2.DataBL1() + it2.DataTR1() + it2.DataTL1() +
      it2.DataBR2() + it2.DataBL2() + it2.DataTR2() + it2.DataTL2();
  if(sqrs != 9) return __LINE__;
  if(count != 342) return __LINE__;
  return 0;
}

// Test 3x3 iterators.

int testSqr3() {
  Array2dC<IntT> data(5,5);
  data.Fill(1);
  IntT count = 1;
  for(Array2dIterC<IntT> ita(data);ita;ita++)
    *ita = count++;
  
  Array2dSqr3IterC<IntT> it(data);
  if(!it) return __LINE__;
  if(!it.First()) return __LINE__;
  IntT sqrs = 0;
  count = 0;
  for(;it;it++,sqrs++)
    count += 
      it.DataBR() + it.DataBM() + it.DataBL() + 
      it.DataMR() + it.DataMM() + it.DataML() + 
      it.DataTR() + it.DataTM() + it.DataTL();
  //cerr << "Count:" << count << "\n";
  if(count != 1053) return __LINE__;
  if(sqrs != 9) return __LINE__;
  return 0;
}

// Test 3x3 iterators.

int testSqr31() {
  Array2dC<IntT> data(5,5);
  data.Fill(1);

  IntT count = 1;
  for(Array2dIterC<IntT> ita(data);ita;ita++)
    *ita = count++;
  
  Array2dSqr31Iter2C<IntT,IntT> it(data,data);
  if(!it) return __LINE__;
  if(!it.First()) return __LINE__;
  IntT sqrs = 0;
  count = 0;
  for(;it;it++,sqrs++)
    count += 
      it.DataBR1() + it.DataBM1() + it.DataBL1() + 
      it.DataMR1() + it.DataMM1() + it.DataML1() + 
      it.DataTR1() + it.DataTM1() + it.DataTL1();
  //cerr << "Count:" << count << "\n";
  if(count != 1053) return __LINE__;
  if(sqrs != 9) return __LINE__;
  return 0;
}

// Test 3x3 iterators.

int testSqr31b() {
  Array2dC<IntT> data(5,4);
  Array2dC<IntT> data2(5,4);
  data.Fill(1);
  data2.Fill(0);
  IntT count = 1;
  for(Array2dIterC<IntT> ita(data);ita;ita++)
    *ita = count++;
  
  Array2dSqr31Iter2C<IntT,IntT> it(data,data2);
  if(!it) return __LINE__;
  if(!it.First()) return __LINE__;
  IntT sqrs = 0;
  count = 0;
  for(;it;it++,sqrs++) {
    count += 
      it.DataBR1() + it.DataBM1() + it.DataBL1() + 
      it.DataMR1() + it.DataMM1() + it.DataML1() + 
      it.DataTR1() + it.DataTM1() + it.DataTL1();
    it.Data2() = count;
  }
  //cerr << data2;
  //cerr << "Count:" << count << " Sqrs:" << sqrs << "\n";
  if(sqrs != 6) return __LINE__;
  if(count != 567) return __LINE__;
  return 0;
}

// Test 3x3 iterators.

int testSqr311() {
  Array2dC<IntT> data(5,5);
  data.Fill(1);

  IntT count = 1;
  for(Array2dIterC<IntT> ita(data);ita;ita++)
    *ita = count++;
  
  Array2dSqr311Iter3C<IntT,IntT,IntT> it(data,data,data);
  if(!it) return __LINE__;
  if(!it.First()) return __LINE__;
  IntT sqrs = 0;
  count = 0;
  for(;it;it++,sqrs++)
    count += 
      it.DataBR1() + it.DataBM1() + it.DataBL1() + 
      it.DataMR1() + it.DataMM1() + it.DataML1() + 
      it.DataTR1() + it.DataTM1() + it.DataTL1();
  //cerr << "Count:" << count << "\n";
  if(count != 1053) return __LINE__;
  if(sqrs != 9) return __LINE__;
  return 0;
}


// Test 3x3 iterators.

int testSqr3111() {
  Array2dC<IntT> data(5,5);
  data.Fill(1);

  IntT count = 1;
  for(Array2dIterC<IntT> ita(data);ita;ita++)
    *ita = count++;
  
  Array2dSqr3111Iter4C<IntT,IntT,IntT,IntT> it(data,data,data,data);
  if(!it) return __LINE__;
  if(!it.First()) return __LINE__;
  IntT sqrs = 0;
  count = 0;
  for(;it;it++,sqrs++)
    count += 
      it.DataBR1() + it.DataBM1() + it.DataBL1() + 
      it.DataMR1() + it.DataMM1() + it.DataML1() + 
      it.DataTR1() + it.DataTM1() + it.DataTL1();
  //cerr << "Count:" << count << "\n";
  if(count != 1053) return __LINE__;
  if(sqrs != 9) return __LINE__;
  return 0;
}


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

#include "Ravl/Array2d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter3.hh"

using namespace RavlN;

int main()
{
  Array2dC<IntT> arr1(1,10,2,10);
  arr1[1][2]  = 0;
  arr1.Fill(1);
  if(arr1[1][2] != 1) {
    cerr << "Fill failed. ("  << arr1[1][2] << ")\n";
    return 1;
  }
  
  UIntT x = 0;
  {
    Array2dIterC<IntT> it(arr1);
    if(it.Index() != arr1.Rectangle().Origin()) {
      cerr << "Index check 1 failed.  Inital:" << it.Index() << "  Origin:" << arr1.Rectangle().Origin() << "\n";
      return 1;
    }
    for(;it;it++)
      x += *it;
  }
  if(x != arr1.Rectangle().Area()) {
    cerr << "Area test failed. \n";
    return 1;
  }
  arr1 /= 2;
  arr1 += 1;
  arr1 = arr1 + arr1;
  
  {
    Array2dIter2C<IntT,IntT> it(arr1,arr1);
    if(it.Index() != arr1.Rectangle().Origin()) {
      cerr << "Index check 2 failed. \n";
      return 1;
    }    
    for(;it;it++)
      it.Data1() = it.Data2();
  }
  {
    Array2dIter3C<IntT,IntT,IntT> it(arr1,arr1,arr1);
    if(it.Index() != arr1.Rectangle().Origin()) {
      cerr << "Index check 3 failed. \n";
      return 1;
    }    
    for(;it;it++)
      it.Data1() = it.Data2();
  }

  cerr << "Test passed ok. \n";
  return 0;
}

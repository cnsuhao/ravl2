// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlCore

////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include <iostream.h>
#include "Ravl/SArray1d.hh"
#include "Ravl/SArr1Iter.hh"

using namespace RavlN;

int  main()
{

  ////////////////////////////////////////////////////
  // Test conversions between SArray1dC and Array1dC.
  
  SArray1dC<IntT> sarr1(2);
  sarr1[0] = 1;
  sarr1[1] = 2;
  
  if(sarr1.Contains(2)) {
    cerr << "Array bounds problem. 1 \n";
    return 1;
  }
  if(sarr1.Contains(2) || sarr1.Contains(-1)) {
    cerr << "Array bounds problem. 2 \n";
    return 1;
  }
  
  SArray1dC<IntT> sarr2(sarr1.Copy());
  if(sarr2[0] != 1 || sarr2[1] != 2) {
    cerr << "SArray Copy failed.\n";
    return 1;
  }
  if(sarr2.Size() != sarr1.Size()) {
    cerr << "SArray copy failed.\n";
    return 1;
  }
  // Check iterators work properly.
  IntT sum = 0;
  IntT count = 0;
  for(SArray1dIterC<IntT> it(sarr2);it;it++,count++)
    sum += *it;
  if(sum != 3 || count != 2) {
    cerr << "Sum failed.\n";
    return 1;
  }
  sum = 0;
  for(SArray1dIterC<IntT> it(sarr2,1);it;it++)
    sum += *it;
  if(sum != 1) {
    cerr << "Sum failed 2.\n";
    return 1;
  }
  sum = 0;
  for(SArray1dIterC<IntT> it(sarr2,2);it;it++)
    sum += *it;
  if(sum != 3) {
    cerr << "Sum failed 3.\n";
    return 1;
  }
  sum = 0;
  for(SArray1dIterC<IntT> it(sarr2,0);it;it++)
    sum += *it;
  if(sum != 0) {
    cerr << "Sum failed 4.\n";
    return 1;
  }

  // Check it works on empty arrays.
  SArray1dC<IntT> earr;
  sum = 0;
  for(SArray1dIterC<IntT> it(earr,0);it;it++)
    sum++;
  if(sum != 0) {
    cerr << "Empty array test failed. \n";
    return 1;
  }
  
  // Numerical opertions...
  
  SArray1dC<IntT> sarrSum = sarr1 + sarr2;
  if(sarrSum.Size() != sarr1.Size()) {
    cerr << "Size check failed. \n";
    return 1;
  }
  if(sarrSum[0] != 2) {
    cerr << "Sum check failed. \n";
    return 1;
  }
  if(sarrSum[1] != 4) {
    cerr << "Sum check failed. \n";
    return 1;
  }
  cerr << "SArray test passed. \n";
  return 0;
}

// IAPS - Image analysis program system.
// End of file exArray.cc

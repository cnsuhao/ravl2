// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/MeanVariance.hh"
#include <iostream.h>

using namespace RavlN;

int testMeanVar();

const RealT small = 0.000000001;

int main() {
  int ln;
  if((ln = testMeanVar()) != 0) {
    cerr << "testMeanVar, failed. Line:" << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok.\n";
  return 0;
}

int testMeanVar() {
  // Do some simple tests...
  MeanVarianceC mvo;
  MeanVarianceC mv1(1,2,3);
  if(mv1.Variance() != 3) return __LINE__;
  if(mv1.Mean() != 2) return __LINE__;
  if(mv1.Number() != 1) return __LINE__;
  MeanVarianceC mv2(2,2,3);
  mvo = mv1;
  mv1 += mv2;
  if(mv1.Number() != 3) return __LINE__;
  // The mean and variance should be the same.
  if(Abs(mv1.Mean() - mvo.Mean()) > small) return __LINE__;
  if(Abs(mv1.Variance() - mvo.Variance()) > small) return __LINE__;
  mv1 -= mv2;
  if(mv1.Number() != 1) return __LINE__;
  // The mean and variance should be the same.
  if(Abs(mv1.Mean() - mvo.Mean()) > small) return __LINE__;
  if(Abs(mv1.Variance() - mvo.Variance()) > small) return __LINE__;
  cerr << mv1 << "\n";
  return 0;
}

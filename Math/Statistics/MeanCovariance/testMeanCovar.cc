// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/MeanCovariance/testMeanCovar.cc"

#include "Ravl/MeanVariance.hh"
#include "Ravl/FMean.hh"
#include "Ravl/FMeanCovariance.hh"
#include "Ravl/MeanCovariance2d.hh"
#include "Ravl/MeanCovariance3d.hh"
#include <iostream.h>

using namespace RavlN;

int testMeanVar();
int testFMean();
int testFMeanCovar();

const RealT small = 0.000000001;

template FMeanC<2>;
template FMeanCovarianceC<2>;

int main() {
  int ln;
  if((ln = testMeanVar()) != 0) {
    cerr << "testMeanVar, failed. Line:" << ln << "\n";
    return 1;
  }
  if((ln = testFMean()) != 0) {
    cerr << "testMeanVar, failed. Line:" << ln << "\n";
    return 1;
  }
  if((ln = testFMeanCovar()) != 0) {
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

int testFMean() {
  FMeanC<2> mean;
  mean += Vector2dC(0,1);
  mean += Vector2dC(2,5);
  if((mean.Mean() - Vector2dC(1,3)).SumSqr() > 0.00001) return __LINE__;
  cout << "Mean=" << mean << "\n";
  return 0;
}

int testFMeanCovar() {
  FMeanCovarianceC<2> meanco;
  meanco += Vector2dC(0,1);
  meanco += Vector2dC(2,5);
  if((meanco.Mean() - Vector2dC(1,3)).SumSqr() > 0.00001) return __LINE__;
  return 0;
}

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
#include "Ravl/MeanCovariance.hh"
#include "Ravl/Matrix2d.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

int testMeanVar();
int testFMean();
int testFMeanCovar();
int testMeanCovar();
int testMeanCovar2d();

const RealT small = 0.000000001;

#if RAVL_HAVE_TEMPLATEINSTANTIATE 
template FMeanC<2>;
template FMeanCovarianceC<2>;
#endif

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
  if((ln = testMeanCovar()) != 0) {
    cerr << "testMeanCovar, failed. Line:" << ln << "\n";
    return 1;
  }
  if((ln = testMeanCovar2d()) != 0) {
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
  //cerr << mv1 << "\n";

  SArray1dC<RealT> data(11);
  RealT var = 0;
  for(int i = 0;i < 11;i++) {
    var += Sqr((RealT) i - 5);
    data[i] = (RealT) i;
  }
  MeanVarianceC mv3(data);
  if(Abs(mv3.Mean() - 5) > 0.00000001) return __LINE__;
  if(Abs(mv3.Variance() - (var/10)) > 0.00000001) return __LINE__;  
  return 0;
}

int testFMean() {
  FMeanC<2> mean;
  mean = Vector2dC(0,1);
  mean += Vector2dC(2,5);
  if((mean.Mean() - Vector2dC(1,3)).SumOfSqr() > 0.00001) return __LINE__;
  if(mean.Number() != 2) return __LINE__;
  //cout << "Mean=" << mean << "\n";  
  return 0;
}

int testFMeanCovar() {
  FMeanCovarianceC<2> meanco;
  meanco = Vector2dC(0,1);
  meanco += Vector2dC(2,5);
  if((meanco.Mean() - Vector2dC(1,3)).SumOfSqr() > 0.00001) return __LINE__;

  SArray1dC<FVectorC<2> > xyz(3);
  FMeanCovarianceC<2> meanco2;
  for(int i = 0;i < 3;i++) {
    Vector2dC test((RealT) i,(RealT) i * 2.0);
    xyz[i] = test;
    meanco2 += test;
  }
  FMeanCovarianceC<2> meanco3(xyz);
#if 0
  cerr << "Covar2=" << meanco2.Covariance() << "\n";
  cerr << "Covar3=" << meanco3.Covariance() << "\n";
#endif
  if((meanco2.Covariance() - meanco3.Covariance()).SumOfSqr() > 0.00001) return __LINE__;  
  return 0;
}


int testMeanCovar2d() {
  // Check product operation.
  MeanCovariance2dC mc1;
  mc1 = Vector2dC(0,0);
  mc1 += Vector2dC(0.5,1);
  mc1 += Vector2dC(-0.5,1);
  mc1 += Vector2dC(0,2);
  MeanCovariance2dC mc2;
  mc2 = Vector2dC(0,0);
  mc2 += Vector2dC(1,0.5);
  mc2 += Vector2dC(1,-0.5);
  mc2 += Vector2dC(2,0);
  
  MeanCovariance2dC mc3 = mc1 * mc2;
  //cerr << "Product=" << mc3 << "\n";
  if((mc3.Mean() - Vector2dC(0.2,0.2)).SumOfSqr() > 0.000001) return __LINE__;
  if((mc3.Covariance() - Matrix2dC(0.1,0,0,0.1)).SumOfSqr() > 0.000001) return __LINE__;

  Vector2dC at(0.5,0.5);
  RealT val = mc1.Gauss(at);
  cerr << "Gauss=" << val << "\n";
  return 0;
}

int testMeanCovar() {
  MeanCovarianceC meancov2(2);
  SArray1dC<VectorC > xyz(3);
  for(int i = 0;i < 3;i++) {
    VectorC test((RealT) i,i * 2.0);;
    xyz[i] = test;
    meancov2 += test;
  }
  MeanCovarianceC meancov(xyz);
#if 0
  cerr << "Mean1=" << meancov.Mean() << " Mean2=" << meancov2.Mean() << "\n";
  cerr << "Covar=" << meancov.Covariance() << "\n";
  cerr << "Covar2=" << meancov2.Covariance() << "\n";
#endif
  if((meancov2.Covariance() - meancov.Covariance()).SumOfSqr() > 0.00001) return __LINE__;
  if(VectorC(meancov2.Mean() - meancov.Mean()).SumOfSqr() > 0.00001) return __LINE__;


  MeanCovarianceC mcn1(2);
  mcn1 += VectorC(0,0);
  mcn1 += VectorC(0.5,1);
  mcn1 += VectorC(-0.5,1);
  mcn1 += VectorC(0,2);
  MeanCovarianceC mcn2(2);
  mcn2 += VectorC(0,0);
  mcn2 += VectorC(1,0.5);
  mcn2 += VectorC(1,-0.5);
  mcn2 += VectorC(2,0);

  MeanCovarianceC mcn3 = mcn1 * mcn2;
  // cerr << "Product=" << mcn3 << "\n";
  if((mcn3.Mean() - VectorC(0.2,0.2)).SumOfSqr() > 0.000001) return __LINE__;
  if((mcn3.Covariance() - MatrixC(0.1,0,0,0.1)).SumOfSqr() > 0.000001) return __LINE__;
  return 0;
}


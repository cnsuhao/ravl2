// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/MeanCovariance/MeanCovarianceNd.cc"

#include "Ravl/MeanNd.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/MeanCovariance.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Stream.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Compute the mean and covariance of an array of vectors.
  
  MeanCovarianceC::MeanCovarianceC(const SArray1dC<VectorC> & data) 
    : m(data)
  {
    //ONDEBUG(cerr << "MeanCovarianceC::MeanCovarianceC(), Called with " << data.Size() << " elements. \n");
    if(data.Size() == 0)
      return;
    m.number = data.Size();
    SArray1dIterC<VectorC> it(data);
    cov = it->OuterProduct();
    m.Mean() = it->Copy();
    it++;
    RealT n = ((RealT) m.number);
    for(;it;it++) {
      m.Mean() += *it;
      cov += it->OuterProduct();
    }
    m.Mean() /= n;
    cov /= n;
    cov -= Mean().OuterProduct();
  }
  
  MeanCovarianceC MeanCovarianceC::Copy() const {
    return MeanCovarianceC(Number(), m.Mean().Copy(), cov.Copy());
  }
  
  
  const MeanCovarianceC & MeanCovarianceC::SetZero() {
    m.Fill(0);
    cov.Fill(0);
    return *this;
  }
  
  const MeanCovarianceC & 
  MeanCovarianceC::operator+=(const VectorC & point) {
    // Update the covariance matrix.
    const RealT number = (RealT) Number();
    const RealT p1 = number / (number+1.0);
    const RealT p2 = p1 / (number+1.0);
    cov *= p1;
    cov += (VectorC(point - Mean()).OuterProduct() *= p2);
    
    // Update the mean.
    m += point;
    
    return *this;
  }
  
  const MeanCovarianceC & 
  MeanCovarianceC::operator-=(const VectorC & point) {
    const RealT number = (RealT) Number();
    const RealT nDen   = number-1.0;
    if (nDen <= 0) {
      SetZero();
    } else {
      // Update the covariance matrix.
      const RealT p1 = number / nDen;
      const RealT p2 = p1 / nDen;
      cov *= p1;
      cov -= (VectorC(point - Mean()).OuterProduct() *= p2);
      
      // Update the mean.
      m -= point;
    }
    return *this;
  }
  
  const MeanCovarianceC & 
  MeanCovarianceC::operator+=(const MeanNdC & mean) {
    // Update the covariance matrix.
    const RealT number1 = (RealT) Number();
    const RealT number2 = (RealT) mean.Number();
    const RealT nDen    = number1 + number2;
    if (nDen <= 0) { // Both set were obviously empty.
      SetZero();
    } else {
      const RealT p1 = number1 / nDen;
      const RealT p2 = number2 / nDen;
      cov *= p1;
      cov += (VectorC(mean.Mean() - Mean()).OuterProduct() *= p1*p2);
      
      // Update the mean.
      m += mean;
    }
    return *this;
  }
  
  const MeanCovarianceC &   
  MeanCovarianceC::operator-=(const MeanNdC & mean) {
    const RealT number1 = (RealT) Number();
    const RealT number2 = (RealT) mean.Number();
    const RealT nDen    = number1 - number2;
    if (nDen <= 0) { 
      SetZero();
    } else  {
      // Update the covariance matrix.
      const RealT p1 = number1 / nDen;
      const RealT p2 = number2 / nDen;
      cov *= p1;
      cov -= (VectorC(mean.Mean() - Mean()).OuterProduct() *= p1*p2);
      
      // Update the mean.
      m -= mean;
    }
    return *this;
  }
  
  const MeanCovarianceC & 
  MeanCovarianceC::operator+=(const MeanCovarianceC & meanCov) {
    // Update the covariance matrix.
    const RealT number1 = (RealT) Number();
    const RealT number2 = (RealT) meanCov.Number();
    const RealT nDen    = number1 + number2;
    if (nDen <= 0) { // Both sets were obviously empty.
      SetZero();
    } else {
      const RealT p1 = number1 / nDen;
      const RealT p2 = number2 / nDen;
      if (&cov != &(meanCov.Covariance())) {
	cov *= p1;
	cov += meanCov.Covariance() * p2;
      }
      cov += (VectorC(meanCov.Mean() - Mean()).OuterProduct() *= p1*p2);
      
      // Update the mean.
      m += meanCov.m;
    }
    return *this;
  }
  
  const MeanCovarianceC &  
  MeanCovarianceC::operator-=(const MeanCovarianceC & meanCov) {
    const RealT number1 = (RealT) Number();
    const RealT number2 = (RealT) meanCov.Number();
    const RealT nDen    = number1 - number2;
    if (nDen <= 0) {
      SetZero();
    } else {
	// Update the covariance matrix.
      const RealT p1 = number1 / nDen;
      const RealT p2 = number2 / nDen;
      if (&cov != &(meanCov.Covariance())) {
	cov *= p1;
	cov -= meanCov.Covariance() * p2;
      }
      cov -= (VectorC(meanCov.Mean() - Mean()).OuterProduct() *= p1*p2);
      
      // Update the mean.
      m -= meanCov.m;
    }
    return *this;
  }
  
  const MeanCovarianceC & 
  MeanCovarianceC::Add(const VectorC & point, const VectorC & var) {
    // Update the covariance matrix.
    const RealT number = (RealT) Number();
    const RealT p1 = number / (number+1.0);
    const RealT p2 = 1.0 / (number+1.0);
    cov *= p1;
    cov.AddDiagonal(var * p2);
    cov += (VectorC(point - Mean()).OuterProduct() *= p1 * p2);
    
    // Update the mean.
    m += point;
    
    return *this;
  }
  
  const MeanCovarianceC & MeanCovarianceC::Remove(const VectorC & point, const VectorC & var) {
    const RealT number = (RealT) Number();
    const RealT nDen   = number-1.0;
    if (nDen <= 0) {
      SetZero();
    } else {
      // Update the covariance matrix.
      const RealT p1 = number / nDen;
      const RealT p2 = 1.0 / nDen;
      cov *= p1;
      cov.AddDiagonal(var * (-p2));
      cov -= (VectorC(point - Mean()).OuterProduct() *= p1*p2);
      
      // Update the mean.
      m -= point;
    }
    return *this;
  }
  
  const MeanCovarianceC & 
  MeanCovarianceC::SetSum(const MeanCovarianceC & meanCov1,
			    const MeanCovarianceC & meanCov2) {
    return *this = (meanCov1.Copy()+=meanCov2);
  }

  //: Calculate the product of the two probability density functions.
  // This assumes the estimates of the distributions are accurate. (The number
  // of samples is ignored) 
  
  MeanCovarianceC MeanCovarianceC::operator*(const MeanCovarianceC &oth) const {
    MatrixC sumCov = Covariance() + oth.Covariance();
    sumCov.InverseIP();
    MatrixC newCov = Covariance() * sumCov * oth.Covariance();
    VectorC mean = oth.Covariance() * sumCov * Mean();
    mean += Covariance() * sumCov * oth.Mean();
    return MeanCovarianceC(Number() + oth.Number(),mean,newCov);
  }
  
  
  ostream & operator<<(ostream & outS, const MeanCovarianceC & meanCov) {
    outS << meanCov.Mean() << '\n' 
	 << meanCov.Covariance() << '\n';
    return outS;
  }
  
  istream & operator>>(istream & inS, MeanCovarianceC & meanCov) {
    inS >> meanCov.m >> meanCov.cov;
    return inS;
  }

  
}




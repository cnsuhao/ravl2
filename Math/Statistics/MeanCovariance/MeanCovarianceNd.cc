// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/MeanNd.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/MeanCovarianceNd.hh"
#include <iostream.h>

namespace RavlN {

  //: Compute the mean and covariance of an array of vectors.
  
  MeanCovarianceNdC::MeanCovarianceNdC(const SArray1dC<VectorC> & data) 
    : m(data)
  {
    if(Number() == 0)
      return ;
    SArray1dIterC<VectorC> it(data);
    cov = it->OuterProduct();
    it++;
    for(;it;it++)
      cov += it->OuterProduct();
    cov -= Mean().OuterProduct();
    cov /= Number()-1;
  }
  
  MeanCovarianceNdC MeanCovarianceNdC::Copy() const {
    return MeanCovarianceNdC(Number(), m.Mean().Copy(), cov.Copy());
  }
  
  
  const MeanCovarianceNdC & MeanCovarianceNdC::SetZero() {
    m.Fill(0);
    cov.Fill(0);
    return *this;
  }
  
  const MeanCovarianceNdC & 
  MeanCovarianceNdC::operator+=(const VectorC & point) {
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
  
  const MeanCovarianceNdC & 
  MeanCovarianceNdC::operator-=(const VectorC & point) {
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
  
  const MeanCovarianceNdC & 
  MeanCovarianceNdC::operator+=(const MeanNdC & mean) {
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
  
  const MeanCovarianceNdC &   
  MeanCovarianceNdC::operator-=(const MeanNdC & mean) {
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
  
  const MeanCovarianceNdC & 
  MeanCovarianceNdC::operator+=(const MeanCovarianceNdC & meanCov) {
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
  
  const MeanCovarianceNdC &  
  MeanCovarianceNdC::operator-=(const MeanCovarianceNdC & meanCov) {
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
  
  const MeanCovarianceNdC & 
  MeanCovarianceNdC::Add(const VectorC & point, const VectorC & var) {
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
  
  const MeanCovarianceNdC & MeanCovarianceNdC::Remove(const VectorC & point, const VectorC & var) {
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
  
  const MeanCovarianceNdC & 
  MeanCovarianceNdC::SetSum(const MeanCovarianceNdC & meanCov1,
			    const MeanCovarianceNdC & meanCov2) {
    return *this = (meanCov1.Copy()+=meanCov2);
  }
  
  ostream & 
  operator<<(ostream & outS, const MeanCovarianceNdC & meanCov) {
    outS << meanCov.Mean()        << '\n' 
	 << meanCov.Covariance()    << '\n';
    return outS;
  }
  
  istream & 
  operator>>(istream & inS, MeanCovarianceNdC & meanCov) {
    inS >> meanCov.m >> meanCov.cov;
    return inS;
  }
  
}




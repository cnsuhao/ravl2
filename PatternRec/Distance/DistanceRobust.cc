// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DistanceRobust.hh"
#include "Ravl/SArr1Iter3.hh"

namespace RavlN {
  
  //: Constructor.
  
  DistanceRobustBodyC::DistanceRobustBodyC(RealT nClipLimit,const DistanceC &nmetric) 
    : clipLimit(nClipLimit),
      metric(nmetric)
  {}
  
  //: Measure the distance from d1 to d2.
  // Each value of d2 is limited to be within 'clipLimit' of d1.
  
  RealT DistanceRobustBodyC::Measure(const VectorC &d1,const VectorC &d2) const {
    VectorC nd2(d2.Size());
    for(SArray1dIter3C<RealT,RealT,RealT> it(nd2,d1,d2);it;it++) {
      if(Abs(it.Data2() - it.Data3()) > clipLimit) {
	if(it.Data2() < it.Data3()) 
	  it.Data1() = it.Data2() + clipLimit;
	else
	  it.Data1() = it.Data2() - clipLimit;
      } else
	it.Data1() = it.Data3();
    }
    return metric.Measure(d1,nd2);
  }
  
  //: Measure the magnitude of d1.
  
  RealT DistanceRobustBodyC::Magnitude(const VectorC &d1) const {
    VectorC vec(d1.Size());
    for(SArray1dIter2C<RealT,RealT> it(vec,d1);it;it++) {
      if(Abs(it.Data2()) > clipLimit)
	it.Data1() = Sign(it.Data2()) * clipLimit;
      else
	it.Data1() = it.Data2(); 
    }
    return metric.Magnitude(d1);
  }
  
  //: Calculates Jacobian matrix at X
  
  MatrixC DistanceRobustBodyC::Jacobian (const VectorC &X) const {
    VectorC vec(X.Size());
    for(SArray1dIter2C<RealT,RealT> it(vec,X);it;it++) {
      if(Abs(it.Data2()) > clipLimit)
	it.Data1() = Sign(it.Data2()) * clipLimit;
      else
	it.Data1() = it.Data2(); 
    }
    MatrixC dSdX = metric.Jacobian (vec);
    for(SArray1dIterC<RealT> it(X);it;it++)
      if(Abs(*it) > clipLimit)
	dSdX[0][it.Index()] = 0.0;    
    return dSdX;
  }

}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/SampleVector.cc"

#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/DArray1dIter.hh"
#include "Ravl/MeanCovariance.hh"

namespace RavlN {

  //: Find the mean vector.
  
  VectorC SampleVectorC::Mean() const {
    DArray1dIterC<VectorC> it(*this);
    if(!it)
      return VectorC();
    VectorC total = *it;
    for(;it;it++)
      total += *it;
    return total/ ((RealT) Size());
  }
  
  //: Find the mean and covariance of the sample
  
  MeanCovarianceC SampleVectorC::MeanCovariance() const {
    UIntT in = Size();
    if(in == 0)
      return MeanCovariance();
    RealT n = (RealT) in;
    DArray1dIterC<VectorC> it(*this);
    MatrixC cov = it->OuterProduct();
    VectorC mean = it->Copy();
    it++;
    for(;it;it++) {
      mean += *it;
      cov += it->OuterProduct();
    }
    mean /= n;
    cov /= n;
    cov -= mean.OuterProduct();
    return MeanCovarianceC(in,mean,cov);
  }
  
}


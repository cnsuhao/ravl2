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
#include "Ravl/DArray1dIter2.hh"
#include "Ravl/MeanCovariance.hh"
#include "Ravl/MatrixRUT.hh"

namespace RavlN {

  //: Get the size of vectors in this sample.
  
  UIntT SampleVectorC::VectorSize() const {
    if(IsEmpty())
      return 0;
    return First().Size();
  }
  
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
    MatrixRUTC cov = OuterProductRUT(*it);
    VectorC mean = it->Copy();
    it++;
    for(;it;it++) {
      mean += *it;
      cov.AddOuterProduct(*it);
    }
    mean /= n;
    cov /= n;
    cov -= OuterProductRUT(mean);
    cov.MakeSymmetric();
    return MeanCovarianceC(in,mean,cov);
  }

  //: Compute the sum of the outerproducts.
  
  MatrixRUTC SampleVectorC::SumOuterProducts() const {
    MatrixRUTC ret;
    DArray1dIterC<VectorC> it(*this);
    if(!it) return ret; // No samples.
    ret = OuterProductRUT(*it);
    for(it++;it;it++)
      ret.AddOuterProduct(*it);
    return ret;
  }
  
  //: Compute the sum of the outerproducts.
  // sam2 must have the same size as this sample vector.
  
  MatrixC SampleVectorC::TMul(const SampleC<VectorC> &sam2) const {
    MatrixC ret;
    DArray1dIter2C<VectorC,VectorC> it(*this,sam2.DArray());
    if(!it) return ret; // No samples.    
    ret = it.Data1().OuterProduct(it.Data2());
    for(it++;it;it++)
      ret.AddOuterProduct(it.Data1(),it.Data2());
    return ret;
  }
  
}


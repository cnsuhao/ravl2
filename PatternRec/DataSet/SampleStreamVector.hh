// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SAMPLESTREAMVECTOR_HEADER
#define RAVL_SAMPLESTREAMVECTOR_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! examples=exSampleStream.cc

#include "Ravl/PatternRec/SampleStream.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  class MeanCovarianceC;
  class MatrixC;
  
  //! userlevel=Normal
  //: Stream of sample vectors
  
  class SampleStreamVectorC 
    : public SampleStreamC<VectorC>
  {
  public:
    SampleStreamVectorC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle
    
    SampleStreamVectorC(const SampleStreamC<VectorC> &stream)
      : DPEntityC(stream)
    {}
    //: Base constructor.
    
    SampleStreamVectorC(const DPISPortC<VectorC> &port)
      : DPEntityC(port)
    {}
    //: Base constructor.

    MeanCovarianceC MeanCovariance();
    //: Find the mean and covariance of the sample
    
    MatrixC SumOuterProducts();
    //: Compute the sum of the outerproducts.
    
    
  };
}


#endif

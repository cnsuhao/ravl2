// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SAMPLEVECTOR_HEADER
#define RAVL_SAMPLEVECTOR_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.API.Pattern Recognition.Data Set"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/SampleVector.hh"

#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Matrix.hh"

namespace RavlN {

  class MatrixRUTC;
  class MeanCovarianceC;  
  
  //! userlevel=Normal
  //: Sample of vectors.
  // This class expects all the vectors in the sample to be of the same
  // size.
  
  class SampleVectorC
    : public SampleC<VectorC>
  {
    
  public:
    SampleVectorC(SizeT maxSize=10)
      : SampleC<VectorC>(maxSize)
    {}
    //: Create a sample of data with a maximum size
    
    SampleVectorC(const SArray1dC<VectorC> & dat)
      : SampleC<VectorC>(dat)
    {}
    //: Create a sample of data from an array
    
    SampleVectorC(const SampleC<VectorC> &svec)
      : SampleC<VectorC>(svec)
    {}
    //: Construct from base class.

    SampleVectorC(const SampleC<VectorC> &svec, const SArray1dC<IndexC> &featureSet);
    //: Construct a sample set with a reduced set of features
    //!param: svec       - a sample of vectors
    //!param: featureSet - the indexes of features to keep
    
    UIntT VectorSize() const;
    //: Get the size of vectors in this sample.
    
    VectorC Mean() const;
    //: Find the mean vector of the sample.
    
    VectorC Mean(const SampleC<RealT> &weights) const;
    //: Find the weighted mean vector of the sample.
    
    MeanCovarianceC MeanCovariance(bool sampleStatistics = true) const;
    //: Find the mean and covariance of the sample
    
    MeanCovarianceC MeanCovariance(const SampleC<RealT> &weights,bool sampleStatistics = true) const;
    //: Find the mean and covariance of a weighted sample
    
    MatrixRUTC SumOuterProducts() const;
    //: Compute the sum of the outerproducts.
    
    MatrixC TMul(const SampleC<VectorC> &sam2) const;
    //: Compute the sum of the outerproducts.
    // sam2 must have the same size as this sample vector.
    
    MatrixRUTC SumOuterProducts(const SampleC<RealT> &w) const;
    //: Compute the sum of the outerproducts weighting each with the corresponding value from 'w'.
    
    MatrixC TMul(const SampleC<VectorC> &sam2,const SampleC<RealT> &w) const;
    //: Compute the sum of the outerproducts weighting each with the corresponding value from 'w'.
    // sam2 must have the same size as this sample vector.
    
    void Normalise(const MeanCovarianceC & stats);
    //: Normalises the input vectors using given stats
    // In order to achieve zero mean and unity variance this function should be
    // called with the return value from MeanCovariance. Subsequent data sets can
    // then be normalised the same way by recording the MeanCovarianceC returned by
    // MeanCovariance.
    
    void UndoNormalisation(const MeanCovarianceC & stats);
    //: Undo the normalisation done by 'Normalise()'.
    
  }; 
  
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASETVECTORLABEL_HEADER
#define RAVL_DATASETVECTORLABEL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/DataSetVectorLabel.hh"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! author="Charles Galambos"

#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleLabel.hh"
#include "Ravl/MeanCovariance.hh"

namespace RavlN {

  class DataSetVectorLabelC;

  //! userlevel=Develop
  //: Data set of labeled vectors.
  
  class DataSetVectorLabelBodyC 
    : public DataSet2BodyC<SampleVectorC,SampleLabelC>
  {
  public:
    DataSetVectorLabelBodyC(const SampleVectorC & vec,
			    const SampleLabelC & lab)
      : DataSet2BodyC<SampleVectorC,SampleLabelC>(vec,lab)
    {}
    //: Constructor
    
    SArray1dC<SampleVectorC> SeperateLabels() const;
    //: Create a seperate sample for each label.

    VectorC GlobalMean() const;
    //: returns mean of the input vectors

    SArray1dC<VectorC> ClassMeans () const;
    //: Returns mean of input vectors for each label value
  
     DataSetVectorLabelC ClassMeansLabels () const;
    //: Returns mean of input vectors for each label along with the label

    SArray1dC<UIntT> ClassNums () const;
    //: Returns array containing the count of each label value

    SArray1dC<MeanCovarianceC> ClassStats () const;
    //: Returns mean and covariance of input vectors for each label value

    MatrixC BetweenClassScatter () const;
    //: Returns between class scatter (covariance) matrix

    MatrixC WithinClassScatter () const;
    //: Returns within class scatter (covariance) matrix
    
    DataSetVectorLabelC ExtractPerLabel(UIntT numSamples) const;
    //: Extracts numSamples samples per label
    
  };
  
  //! userlevel=Normal
  //: Data set of labeled vectors.
  
  class DataSetVectorLabelC 
    : public DataSet2C<SampleVectorC,SampleLabelC>
  {
  public:
    DataSetVectorLabelC()
    {}
    //: Default constructor.

    DataSetVectorLabelC(UIntT sizeEstimate)
      : DataSet2C<SampleVectorC,SampleLabelC>(sizeEstimate)
    {}
    //: Construct from an estimate of the size.
    
    DataSetVectorLabelC(const SampleVectorC & vec,const SampleLabelC & lab)
      : DataSet2C<SampleVectorC,SampleLabelC>(*new DataSetVectorLabelBodyC(vec,lab))
    {}
    //: Constructor
    
  protected:
    DataSetVectorLabelBodyC &Body()
    { return static_cast<DataSetVectorLabelBodyC &>(DataSetBaseC::Body()); }
    //: Access body.
    
    const DataSetVectorLabelBodyC &Body() const
    { return static_cast<const DataSetVectorLabelBodyC &>(DataSetBaseC::Body()); }
    //: Access body.
    
  public:
    SArray1dC<SampleVectorC> SeperateLabels() const
    { return Body().SeperateLabels(); }
    //: Create a seperate sample for each label.

    VectorC GlobalMean() const
    { return Body().GlobalMean(); }     
    //: returns mean of the input vectors

    SArray1dC<VectorC> ClassMeans () const
    { return Body().ClassMeans(); }
    //: Returns mean of input vectors for each label value

    DataSetVectorLabelC ClassMeansLabels () const
    { return Body().ClassMeansLabels(); }
    //: Returns mean of input vectors for each label along with the label

    SArray1dC<UIntT> ClassNums () const
    { return Body().ClassNums(); }
    //: Returns array containing the count of each label value

    SArray1dC<MeanCovarianceC> ClassStats () const
    { return Body().ClassStats(); }
    //: Returns mean and covariance of input vectors for each label value

    MatrixC BetweenClassScatter () const
    { return Body().BetweenClassScatter (); }
    //: Returns between class scatter (covariance) matrix

    MatrixC WithinClassScatter () const
    { return Body().WithinClassScatter (); }
    //: Returns within class scatter (covariance) matrix

    DataSetVectorLabelC ExtractPerLabel(UIntT numSamples) const
      { return Body().ExtractPerLabel(numSamples); }
    //: Extracts numSamples samples per label

    
  };
}


#endif

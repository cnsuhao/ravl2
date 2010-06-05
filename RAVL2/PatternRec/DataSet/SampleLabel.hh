// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SAMPLELABEL_HEADER
#define RAVL_SAMPLELABEL_HEADER 1
//! rcsid="$Id: SampleLabel.hh 5240 2005-12-06 17:16:50Z plugger $"
//! author="Kieron Messer"
//! docentry="Ravl.API.Pattern Recognition.Data Set"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/SampleLabel.hh"

#include "Ravl/PatternRec/SampleDiscrete.hh"

namespace RavlN {
  class VectorC;
  
  //! userlevel=Normal
  //: Sample of labels.
  
  class SampleLabelC 
    : public SampleDiscreteC<UIntT>
  {
  public:
    SampleLabelC(SizeT maxSize=10)
      : SampleDiscreteC<UIntT>(maxSize)
    {}
    //: Create a sample of data with a maximum size
    
    SampleLabelC(const SArray1dC<UIntT> & dat)
      : SampleDiscreteC<UIntT>(dat)
    {}
    //: Create a sample of data from an array

    SampleLabelC(const SampleC<UIntT> &sample)
      : SampleDiscreteC<UIntT>(sample)
    {}
    //: Construct from base class.
    
    UIntT MaxValue() const;
    //: Find the value of the largest label.

    SArray1dC<UIntT> LabelSums() const;
    //: Return the number of samples in each class
    
    SampleC<VectorC> SampleVector(RealT inClass = 1,RealT outClass = 0,IntT maxLabel = -1) const;
    //: Convert a sample of labels to vectors
    // Where the label index is set to 'inClass' and the rest to 'outClass'.
    
  }; 
  
}

#endif

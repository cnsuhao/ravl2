// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SAMPLELABEL_HEADER
#define RAVL_SAMPLELABEL_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/SampleLabel.hh"

#include "Ravl/PatternRec/SampleDiscrete.hh"

namespace RavlN {
  
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
    
    UIntT MaxValue() const;
    //: Find the value of the largest label.
  }; 
  
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/ClassifierFunc1Threshold.hh"

namespace RavlN {
  
  //: Constructor.
  
  ClassifierFunc1ThresholdBodyC::ClassifierFunc1ThresholdBodyC(const Function1C &nfunc,RealT nthreshold)
    : ClassifierBodyC(2),
      func(nfunc),
      threshold(nthreshold)
  {
    if(nfunc.IsValid())
      InputSize(nfunc.InputSize());
  }
  
  //: Classifier vector 'data' return the most likely label.
  
  UIntT ClassifierFunc1ThresholdBodyC::Classify(const VectorC &data) const {
    RealT x = func.Apply1(data);
    return (x > threshold) ? 1 : 0;
  }

}

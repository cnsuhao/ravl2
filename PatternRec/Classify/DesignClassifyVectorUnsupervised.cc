// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Classify/DesignClassifyVector.cc"

#include "Ravl/PatternRec/DesignClassifyVectorUnsupervised.hh"
#include "Ravl/PatternRec/SampleIter.hh"

namespace RavlN {
  
  //: Create a clasifier.
  
  ClassifyVectorC DesignClassifyVectorUnsupervisedBodyC::Apply(const SampleC<VectorC> &in) {
    RavlAssertMsg(0,"DesignClassifyVectorUnsupervisedBodyC::Apply(), Abstract method called. ");
    return ClassifyVectorC();
  }
  
  //: Create a clasifier with weights for the samples.
  
  ClassifyVectorC DesignClassifyVectorUnsupervisedBodyC::Apply(const SampleC<VectorC> &in,const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignClassifyVectorUnsupervisedBodyC::Apply(), Abstract method called. ");
    return ClassifyVectorC();
  }
  
}

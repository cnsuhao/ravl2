// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Classify/DesignClassifyVectorSupervised.cc"

#include "Ravl/PatternRec/DesignClassifyVectorSupervised.hh"
#include "Ravl/PatternRec/SampleIter.hh"

namespace RavlN {
  
  //: Create a clasifier.
  
  ClassifyVectorC DesignClassifyVectorSupervisedBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out) {
    RavlAssertMsg(0,"DesignClassifyVectorSupervisedBodyC::Apply(), Abstract method called. ");
    return ClassifyVectorC();
  }
  
  //: Create a clasifier with weights for the samples.
  
  ClassifyVectorC DesignClassifyVectorSupervisedBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignClassifyVectorSupervisedBodyC::Apply(), Abstract method called. ");
    return ClassifyVectorC();
  }
  
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classifier/DesignDiscriminantFunction.cc"

#include "Ravl/PatternRec/DesignDiscriminantFunction.hh"
#include "Ravl/PatternRec/ClassifierDiscriminantFunction.hh"
#include "Ravl/PatternRec/SampleLabel.hh"

namespace RavlN {
  
  //: Default constructor.
  
  DesignDiscriminantFunctionBodyC::DesignDiscriminantFunctionBodyC(const DesignFunctionSupervisedC &dfunc) 
    : designFunc(dfunc)
  {}

  //: Create a clasifier.
    
  ClassifierC DesignDiscriminantFunctionBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out) {
    // FIXME :- Find a way of caching 'vout' for labels.
    SampleC<VectorC> vout = SampleLabelC(out).SampleVector();
    return ClassifierDiscriminantFunctionC(designFunc.Apply(in,vout));
  }
					 
  //: Create a clasifier with weights for the samples.
  
  ClassifierC DesignDiscriminantFunctionBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight) {
    // FIXME :- Find a way of caching 'vout' for labels.
    SampleC<VectorC> vout = SampleLabelC(out).SampleVector();
    return ClassifierDiscriminantFunctionC(designFunc.Apply(in,vout,weight));
  }

}

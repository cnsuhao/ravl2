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
#include "Ravl/VirtualConstructor.hh"
#if RAVL_COMPILER_VISUALCPP
#include "Ravl/BinStream.hh"
#endif

namespace RavlN {
  
  //: Load from stream.
  
  DesignDiscriminantFunctionBodyC::DesignDiscriminantFunctionBodyC(istream &strm)
    : DesignClassifierSupervisedBodyC(strm)
  { strm >> designFunc; }
  
  //: Load from binary stream.
  
  DesignDiscriminantFunctionBodyC::DesignDiscriminantFunctionBodyC(BinIStreamC &strm)
    : DesignClassifierSupervisedBodyC(strm)
  { strm >> designFunc; }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignDiscriminantFunctionBodyC::Save (ostream &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    out << ' ' << designFunc;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignDiscriminantFunctionBodyC::Save (BinOStreamC &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    out << designFunc;
    return true;
  }
  
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
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignDiscriminantFunctionBodyC,DesignDiscriminantFunctionC,DesignClassifierSupervisedC);
  
}

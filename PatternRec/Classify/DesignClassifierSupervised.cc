// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Classifier/DesignClassifierSupervised.cc"

#include "Ravl/PatternRec/DesignClassifierSupervised.hh"
#include "Ravl/PatternRec/SampleIter.hh"

namespace RavlN {
  
  //: Load from stream.
  
  DesignClassifierSupervisedBodyC::DesignClassifierSupervisedBodyC(istream &strm)
    : DesignFunctionSupervisedBodyC(strm)
  {}
  
  //: Load from binary stream.
  
  DesignClassifierSupervisedBodyC::DesignClassifierSupervisedBodyC(BinIStreamC &strm)
    : DesignFunctionSupervisedBodyC(strm)
  {}
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignClassifierSupervisedBodyC::Save (ostream &out) const 
  { return DesignFunctionSupervisedBodyC::Save(out); }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignClassifierSupervisedBodyC::Save (BinOStreamC &out) const
  { return DesignFunctionSupervisedBodyC::Save(out); }
  
  //: Create a clasifier.
  
  ClassifierC DesignClassifierSupervisedBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out) {
    RavlAssertMsg(0,"DesignClassifierSupervisedBodyC::Apply(), Abstract method called. ");
    return ClassifierC();
  }
  
  //: Create a clasifier with weights for the samples.
  
  ClassifierC DesignClassifierSupervisedBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignClassifierSupervisedBodyC::Apply(), Abstract method called. ");
    return ClassifierC();
  }

  
  //: Load from stream.
  
  DesignClassifierSupervisedC::DesignClassifierSupervisedC(istream &strm)
    : DesignFunctionSupervisedC(RAVL_VIRTUALCONSTRUCTOR(strm,DesignClassifierSupervisedBodyC))    
  {}
  
  //: Load from binary stream.
  
  DesignClassifierSupervisedC::DesignClassifierSupervisedC(BinIStreamC &strm)
    : DesignFunctionSupervisedC(RAVL_VIRTUALCONSTRUCTOR(strm,DesignClassifierSupervisedBodyC))
  {}


}

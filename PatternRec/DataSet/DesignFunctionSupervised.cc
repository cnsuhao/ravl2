// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DesignFunctionSupervised.hh"

namespace RavlN {
  
  //: Create function from the given data.
  
  FunctionC DesignFunctionSupervisedBodyC::Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out) {
    RavlAssertMsg(0,"DesignSupervisedFunctionBodyC::Apply(const SampleC<VectorC> &,const SampleC<VectorC> &), Abstract method called. \n");
    return FunctionC();
  }
  
  //: Create function from the given data.
  
  FunctionC DesignFunctionSupervisedBodyC::Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weights) {
    RavlAssertMsg(0,"DesignFunctionSupervisedBodyC::Apply(const SampleC<VectorC> &,const SampleC<VectorC> &out,const SampleC<RealT> &), Abstract method called. \n");
    return FunctionC();
  }
  
}

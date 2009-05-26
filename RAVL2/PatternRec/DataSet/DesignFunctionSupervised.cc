// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/DesignFunctionSupervised.cc"

#include "Ravl/PatternRec/DesignFunctionSupervised.hh"

namespace RavlN {

  //: Load from stream.
  
  DesignFunctionSupervisedBodyC::DesignFunctionSupervisedBodyC(istream &strm)
    : DesignerBodyC(strm)
  {}
  
  //: Load from binary stream.
  
  DesignFunctionSupervisedBodyC::DesignFunctionSupervisedBodyC(BinIStreamC &strm) 
    : DesignerBodyC(strm)
  {}
  
  //: Writes object to stream.
  
  bool DesignFunctionSupervisedBodyC::Save (ostream &out) const {
    return DesignerBodyC::Save(out);
  }
  
  //: Writes object to binary stream.
  
  bool DesignFunctionSupervisedBodyC::Save (BinOStreamC &out) const {
    return DesignerBodyC::Save(out);
  }
  
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
  
  //: Create function from the given data.
  
  FunctionC DesignFunctionSupervisedBodyC::Apply(SampleStream2C<VectorC,VectorC > &in) {
    RavlAssertMsg(0,"DesignFunctionSupervisedBodyC::Apply(const SampleStream2C<VectorC,VectorC> &), Abstract method called. \n");
    return FunctionC();
    
  }
  
  //: Create function from the given data, and sample weights.
  
  FunctionC DesignFunctionSupervisedBodyC::Apply(SampleStream3C<VectorC,VectorC,RealT> &in) {
    RavlAssertMsg(0,"DesignFunctionSupervisedBodyC::Apply(const SampleStream2C<VectorC,VectorC,RealT> &), Abstract method called. \n");
    return FunctionC();
  }
  
  ////////////////////////////////////////////////////////////////////
  
  //: Load from stream.
  
  DesignFunctionSupervisedC::DesignFunctionSupervisedC(istream &strm)
    : DesignerC(RAVL_VIRTUALCONSTRUCTOR(strm,DesignFunctionSupervisedBodyC))
  {}
  
  //: Load from binary stream.
  
  DesignFunctionSupervisedC::DesignFunctionSupervisedC(BinIStreamC &strm)
    : DesignerC(RAVL_VIRTUALCONSTRUCTOR(strm,DesignFunctionSupervisedBodyC))
  {}

}

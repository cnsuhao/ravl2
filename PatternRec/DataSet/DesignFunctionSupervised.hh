// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNFUNCTIONUNSUPERVISED_HEADER
#define RAVL_DESIGNFUNCTIONUNSUPERVISED_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Functions"

#include "Ravl/PatternRec/Function.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/PatternRec/Designer.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Supervised function designer.
  
  class DesignFunctionSupervisedBodyC
    : public DesignerBodyC
  {
  public:
    DesignFunctionSupervisedBodyC()
    {}
    //: Default constructor.
    
    virtual FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out);
    //: Create function from the given data.
    
    virtual FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weight);
    //: Create function from the given data, and sample weights.
    
  };
  
  //! userlevel=Normal
  //: Supervised function designer.
  
  class DesignFunctionSupervisedC
    : public DesignerC
  {
  public:
    DesignFunctionSupervisedC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DesignFunctionSupervisedC(DesignFunctionSupervisedBodyC &bod)
      : DesignerC(bod)
    {}
    //: Body constructor.
    
    DesignFunctionSupervisedBodyC &Body()
    { return static_cast<DesignFunctionSupervisedBodyC &>(DesignerC::Body()); }
    //: Access body.
    
    const DesignFunctionSupervisedBodyC &Body() const
    { return static_cast<const DesignFunctionSupervisedBodyC &>(DesignerC::Body()); }
    //: Access body.
    
  public:
    FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out)
    { return Body().Apply(in,out); }
    //: Create function from the given data.
    
    FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weight)
    { return Body().Apply(in,out,weight); }
    //: Create function from the given data, and sample weights.
    
  };

}


#endif

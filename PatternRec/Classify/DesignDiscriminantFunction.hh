// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNDISCRIMINANTFUNCTION_HEADER
#define RAVL_DESIGNDISCRIMINANTFUNCTION_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Classifier"
//! file="Ravl/PatternRec/Classifier/DesignDiscriminantFunction.hh"

#include "Ravl/PatternRec/DesignClassifierSupervised.hh"
#include "Ravl/PatternRec/DesignFunctionSupervised.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a discriminat function classifier.
  
  class DesignDiscriminantFunctionBodyC
    : public DesignClassifierSupervisedBodyC
  {
  public:
    DesignDiscriminantFunctionBodyC(const DesignFunctionSupervisedC &func);
    //: Default constructor.
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Create a clasifier.
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.
    
    const DesignFunctionSupervisedC &FunctionDesigner() const
    { return designFunc; }
    //: Access the current function designer being used.
    
  protected:
    DesignFunctionSupervisedC designFunc;
  };

  //! userlevel=Normal
  //: Design a discriminat function classifier.
  
  class DesignDiscriminantFunctionC
    : public DesignClassifierSupervisedC
  {
  public:
    DesignDiscriminantFunctionC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    DesignDiscriminantFunctionC(const DesignFunctionSupervisedC &designFunc)
      : DesignClassifierSupervisedC(*new DesignDiscriminantFunctionBodyC(designFunc))
    {}
    //: Create a new designer.
    
  protected:
    DesignDiscriminantFunctionC(DesignDiscriminantFunctionBodyC &bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body constructor.
    
    DesignDiscriminantFunctionBodyC &Body()
    { return static_cast<DesignDiscriminantFunctionBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.

    const DesignDiscriminantFunctionBodyC &Body() const
    { return static_cast<const DesignDiscriminantFunctionBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.
    
  public:
    
    const DesignFunctionSupervisedC &FunctionDesigner() const
    { return Body().FunctionDesigner(); }
    //: Access the current function designer being used.
  };

}


#endif

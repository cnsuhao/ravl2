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
  //: Unsupervised function designer.
  
  class DesignFunctionUnsupervisedBodyC
    : public DesignerBodyC
  {
  public:
    DesignFunctionUnsupervisedBodyC()
    {}
    //: Default constructor.
    
    virtual FunctionC Apply(const SampleC<VectorC> &in);
    //: Create function from the given data.
    
    virtual FunctionC Apply(const SampleC<VectorC> &in,const SampleC<RealT> &weight);
    //: Create function from the given data, and sample weights.
    
  };
  
  //! userlevel=Normal
  //: Unsupervised function designer.
  
  class DesignFunctionUnsupervisedC
    : public DesignerC
  {
  public:
    DesignFunctionUnsupervisedC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DesignFunctionUnsupervisedC(DesignFunctionUnsupervisedBodyC &bod)
      : DesignerC(bod)
    {}
    //: Body constructor.
    
    DesignFunctionUnsupervisedBodyC &Body()
    { return static_cast<DesignFunctionUnsupervisedBodyC &>(DesignerC::Body()); }
    //: Access body.

    const DesignFunctionUnsupervisedBodyC &Body() const
    { return static_cast<const DesignFunctionUnsupervisedBodyC &>(DesignerC::Body()); }
    //: Access body.
    
  public:
    FunctionC Apply(const SampleC<VectorC> &in)
    { return Body().Apply(in); }
    //: Create function from the given data.
    
    FunctionC Apply(const SampleC<VectorC> &in,const SampleC<RealT> &weight)
    { return Body().Apply(in,weight); }
    //: Create function from the given data, and sample weights.
    
  };

}


#endif

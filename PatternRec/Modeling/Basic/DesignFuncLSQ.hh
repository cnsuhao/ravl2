#ifndef RAVL_DESIGNFUNCLSQ_HEADER
#define RAVL_DESIGNFUNCLSQ_HEADER 1

#include "Ravl/PatternRec/DesignFunctionSupervised.hh"
#include "Ravl/PatternRec/FuncLinearCoeff.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Design function with Least Squares Fitting.
  
  class DesignFuncLSQBodyC
    : public DesignFunctionSupervisedBodyC
  {
  public:
    DesignFuncLSQBodyC()
    {}
    //: Default constructor.
    
    DesignFuncLSQBodyC(UIntT norder,bool northogonal);
    //: Create least squares designer.
    
    virtual FuncLinearCoeffC CreateFunc(UIntT nin,UIntT nout);
    //: Create new function.
    
    virtual FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out);
    //: Create function from the given data.
    
    virtual FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weight);
    //: Create function from the given data, and sample weights.
    
    static bool IsMarginal (const MatrixC &m, SArray1dC<int> invalid,bool verbose = false);
    //: Tests whether matrix is singular.
    // IsMarginal is used to determine whether or not the matrix m is singular 
    // and would therefore be impossible to invert. It is used by
    // LeastSquaresModelC to detemine which parameters or model weights to
    // incorporate.
    
  protected:
    UIntT order;
    bool orthogonal;
  };

  //! userlevel=Normal
  //: Design function with Least Squares Fitting.
  
  class DesignFuncLSQC
    : public DesignFunctionSupervisedC
  {
  public:
    DesignFuncLSQC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignFuncLSQC(UIntT order,bool orthogonal)
      : DesignFunctionSupervisedC(*new DesignFuncLSQBodyC(order,orthogonal))
    {}
    //: Create designer.
    
  protected:
    
  };
  
}


#endif

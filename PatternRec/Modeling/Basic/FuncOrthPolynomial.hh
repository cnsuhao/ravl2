#ifndef RAVL_ORTHPOLYNOMIAL_HEADER
#define RAVL_ORTHPOLYNOMIAL_HEADER 1
//! date="21/4/1998"
//! author="Robert Crida and Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Functions"

#include "Ravl/PatternRec/FuncLinearCoeff.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Orthogonal Polynomial function.
  // See handle for more information.
  
  class FuncOrthPolynomialBodyC 
    : public FuncLinearCoeffBodyC
  {
  public:
    FuncOrthPolynomialBodyC(UIntT order);
    //: Construct an orthogonal polynomial of given 'order'.
    
    virtual VectorC MakeInput (const VectorC &X) const;
    //: Expand vector to linear coefficients.
    
    virtual VectorC MakeJacobianInput (const VectorC &X, IntT i) const;
    //: Expand vector to linear coefficients.
    
    virtual UIntT NumberCoeffs(UIntT inputSize) const;
    //: Calculate the number of coefficents for a given input size.
    
  protected:    
    UIntT noCoeffs; // Number of coefficents.
    UIntT order;    // Order of polynomial
  };
  
  //! userlevel=Normal
  //: Orthogonal Polynomial function.
  
  // It provides a class implementation functions of the form Y=f(X)
  // where each element of Y is an k'th polynomial of the elements of X.<p>
  //
  // For example, when a second order polynomial is selected and X and Y have
  // 2 and 3 elements respectively and A is the matrix of model weights then:<p>
  // <pre>
  // Y[0] = A[0][0] + A[0][1]X[0] + A[0][2]X[0]^2 + A[0][3]X[1] + A[0][4]X[1]^2
  // Y[1] = A[1][0] + A[1][1]X[0] + A[1][2]X[0]^2 + A[1][3]X[1] + A[1][4]X[1]^2
  // Y[2] = A[2][0] + A[2][1]X[0] + A[2][2]X[0]^2 + A[2][3]X[1] + A[2][4]X[1]^2
  // </pre>
  // Note that in this model there are no cross parameter terms regardless of
  // the model order selected, ie each term is only a power of an individual
  // element of X.
  
  class FuncOrthPolynomialC
    : public FuncLinearCoeffC
  {
  public:
    FuncOrthPolynomialC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    FuncOrthPolynomialC(UIntT order)
      : FuncLinearCoeffC(*new FuncOrthPolynomialBodyC(order))
    {}
    //: Construct an orthogonal polynomial of given 'order'.
    
  protected:
    FuncOrthPolynomialC(FuncOrthPolynomialBodyC &bod)
      : FuncLinearCoeffC(bod)
    {}
    //: Body constructor.
    
    FuncOrthPolynomialBodyC &Body()
    { return static_cast<FuncOrthPolynomialBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const FuncOrthPolynomialBodyC &Body() const
    { return static_cast<const FuncOrthPolynomialBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    
  };
}


#endif



#include "Ravl/PatternRec/FuncOrthPolynomial.hh"

namespace RavlN {
  
  //: Construct an orthogonal polynomial of given 'order'.
  
  FuncOrthPolynomialBodyC::FuncOrthPolynomialBodyC(int inSize,int outSize,UIntT norder)
    : FuncLinearCoeffBodyC(inSize,outSize),
      order(norder)
  {
    noCoeffs = NumberCoeffs(inSize);
  }
  
  //: Calculate the number of coefficents for a given input size.
  
  UIntT FuncOrthPolynomialBodyC::NumberCoeffs(UIntT inputSize) const {
    return 1 + inputSize * order;
  }
  
  //: Expand vector to linear coefficients.
  
  VectorC FuncOrthPolynomialBodyC::MakeInput(const VectorC &X) const {
    VectorC ret(noCoeffs);
    SArray1dIterC<RealT> it(ret);
    *it = 1.0;
    it++;
    for (UIntT i = 1; i <= order; i++) {
      for(SArray1dIterC<RealT> it2(X);it2;it2++,it++)
	*it = Pow(*it2,(IntT) i);
    }
    return ret;
  }
  
  //: Expand vector to linear coefficients.
  
  VectorC FuncOrthPolynomialBodyC::MakeJacobianInput(const VectorC &X, IntT index) const {
    VectorC ret(noCoeffs);
    ret.Fill(0);
    double val = X[index];
    for (UIntT i = 0; i < order; i++) 
      ret[1+InputSize()*i+index] = (i+1) * Pow (val,(IntT) i);
    return ret;
  }

}

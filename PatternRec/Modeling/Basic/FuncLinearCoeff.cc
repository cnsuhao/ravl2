// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/FuncLinearCoeff.hh"

namespace RavlN {
  
  //: Default constructor.
  
  FuncLinearCoeffBodyC::FuncLinearCoeffBodyC()
  {}
  
  //: Apply function to 'data'
  
  VectorC FuncLinearCoeffBodyC::Apply(const VectorC &data) const 
  { return a*MakeInput(data); }
  
  //: Calculate Jacobian matrix at X
  
  MatrixC FuncLinearCoeffBodyC::Jacobian (const VectorC &X) const {
    MatrixC ret(OutputSize(),InputSize());
    for(UIntT i = 0;i < X.Size();i++)
      ret.SetColumn(i,a*MakeJacobianInput(X,i));
    return ret;
  }
  
  //: Expand vector to linear coefficients.
  
  VectorC FuncLinearCoeffBodyC::MakeInput(const VectorC &X) const {
    RavlAssertMsg(0,"FuncLinearCoeffBodyC::MakeInput(), Abstract method called. ");
    return VectorC();
  }
  
  //: Expand vector to linear coefficients.
  
  VectorC FuncLinearCoeffBodyC::MakeJacobianInput (const VectorC &X, IntT i) const {
    RavlAssertMsg(0,"FuncLinearCoeffBodyC::MakeJacobianInput(), Abstract method called. ");
    return VectorC();
  }
  
  //: Calculate the number of coefficents for a given input size.
  
  UIntT FuncLinearCoeffBodyC::NumberCoeffs(UIntT inputSize) const {
    RavlAssertMsg(0,"FuncLinearCoeffBodyC::NumberCoeffs(), Abstract method called. ");
    return 0;
  }

}

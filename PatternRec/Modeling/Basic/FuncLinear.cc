// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/FuncLinear.hh"

namespace RavlN {

  //: Construct from a transform matrix.
  
  FuncLinearBodyC::FuncLinearBodyC() 
  {}
  
  //: Expand vector to linear coefficients.
  
  VectorC FuncLinearBodyC::MakeInput(const VectorC &X) const {
    VectorC ret(X.Size() + 1);
    for(SArray1dIter2C<RealT,RealT> it(ret,X);it;it++)
      it.Data1() = it.Data2();
    ret[X.Size()] = 1;
    return ret;
  }
  
  //: Expand vector to linear coefficients.
  
  VectorC FuncLinearBodyC::MakeJacobianInput(const VectorC &X, IntT i) const {
    VectorC ret(1+X.Size());
    ret.Fill(0);
    ret[i] = 1.0;
    return ret;
  }

  //: Calculate the number of coefficents for a given input size.
  
  UIntT FuncLinearBodyC::NumberCoeffs(UIntT inputSize) const {
    return inputSize + 1;
  }
  
}

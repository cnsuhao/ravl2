// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCQUADRATIC_HEADER
#define RAVL_FUNCQUADRATIC_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Robert Crida and Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Numerical Modeling"

#include "Ravl/PatternRec/FuncLinearCoeff.hh"
#include "Ravl/Matrix.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Quadratic function.
  
  class FuncQuadraticBodyC 
    : public FuncLinearCoeffBodyC
  {
  public:
    FuncQuadraticBodyC(int inSize,int outSize)
      : FuncLinearCoeffBodyC(inSize,outSize)
    {
      noCoeffs = NumberCoeffs(inSize);
    }
    //: Constructor.
    
    virtual VectorC MakeInput (const VectorC &X) const;
    //: Expand vector to linear coefficients.
    
    virtual VectorC MakeJacobianInput (const VectorC &X, IntT i) const;
    //: Expand vector to linear coefficients.
    
    virtual UIntT NumberCoeffs(UIntT inputSize) const;
    //: Calculate the number of coefficents for a given input size.
    
  protected:
    
    UIntT noCoeffs; // Number of coefficents.
  };
  
  //! userlevel=Normal
  //: Quadratic function.
  //
  // It provides a concrete class implementation for functions of the
  // form Y=f(X) where each element of Y is an 2nd polynomial of the elements
  // of X including all the cross parameter terms.
  
  class FuncQuadraticC
    : public FuncLinearCoeffC
  {
  public:    
    FuncQuadraticC(int inSize,int outSize)
      : FuncLinearCoeffC(*new FuncQuadraticBodyC(inSize,outSize))
    {}
    //: Constructor.
    
  protected:
    FuncQuadraticC(FuncQuadraticBodyC &bod)
      : FuncLinearCoeffC(bod)
    {}
    //: Body constructor.
    
    FuncQuadraticBodyC &Body()
    { return static_cast<FuncQuadraticBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const FuncQuadraticBodyC &Body() const
    { return static_cast<const FuncQuadraticBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}

#endif

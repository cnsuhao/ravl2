// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCLINEAR_HEADER
#define RAVL_FUNCLINEAR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! date="21/4/1998"
//! author="Robert Crida and Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Functions"

#include "Ravl/PatternRec/FuncLinearCoeff.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Linear function.
  
  class FuncLinearBodyC 
    : public FuncLinearCoeffBodyC
  {
  public:
    FuncLinearBodyC();
    //: Construct from a transform matrix.
    
    FuncLinearBodyC(UIntT inSize,UIntT outSize)
      : FuncLinearCoeffBodyC(inSize,outSize)
    {}
    //: Construct with an input and output size.
    
    virtual VectorC MakeInput (const VectorC &X) const;
    //: Expand vector to linear coefficients.
    
    virtual VectorC MakeJacobianInput (const VectorC &X, IntT i) const;
    //: Expand vector to linear coefficients.
    
    virtual UIntT NumberCoeffs(UIntT inputSize) const;
    //: Calculate the number of coefficents for a given input size.
    
  };
  
  
  //! userlevel=Normal
  //: Linear function.
  
  class FuncLinearC 
    : public FuncLinearCoeffC
  {
  public:
    FuncLinearC()
    {}
    //: Default constructor.
    
    FuncLinearC(UIntT inSize,UIntT outSize)
      : FuncLinearCoeffC(*new FuncLinearBodyC(inSize,outSize))
    {}
    //: Construct a linear function with given input and output size.
    // The transform itsself is left undefined.
    
  protected:
    FuncLinearC(FuncLinearBodyC &bod)
      : FuncLinearCoeffC(bod)
    {}
    //: Body constructor.
    
    FuncLinearBodyC &Body()
    { return static_cast<FuncLinearBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const FuncLinearBodyC &Body() const
    { return static_cast<const FuncLinearBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:    
  };
  
}


#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CLASSIFYDISCRIMINANTFUNCTION_HEADER
#define RAVL_CLASSIFYDISCRIMINANTFUNCTION_HEADER 1
///////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Classify"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classify/ClassifyDiscriminantFunction.hh"

#include "Ravl/PatternRec/ClassifyVector.hh"
#include "Ravl/PatternRec/Function.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Create a classifier based on a descriminant function.
  //  This classifier returns the label with the highest value.
  
  class ClassifyDiscriminantFunctionBodyC 
    : public ClassifyVectorBodyC
  {
  public:
    ClassifyDiscriminantFunctionBodyC(const FunctionC &nfunc);
    //: Create classifier from a discriminant function.
    
    virtual UIntT Classify(const VectorC &data) const;
    //: Classify vector 'data' return the most likely label.
    
    virtual VectorC Confidence(const VectorC &data) const;
    //: Estimate the confidence for each label.
    // The meaning of the confidence assigned to each label depends
    // on the function used. The higher the confidence the more likely
    // it is the label is correct. The sum of the vector has been normalised
    // to 1.
    
    const FunctionC &Discriminant() const
    { return func; }
    //: Access discriminant function.
    
  protected:
    FunctionC func;
  };
  
  //! userlevel=Develop
  //: Create a classifier based on a descriminant function.
  //  This classifier returns the label with the highest value.
  
  class ClassifyDiscriminantFunctionC 
    : public ClassifyVectorC
  {
  public:
    ClassifyDiscriminantFunctionC(const FunctionC &nfunc)
      : ClassifyVectorC(*new ClassifyDiscriminantFunctionBodyC(nfunc))
    {}
    //: Create classifier from a discriminant function.

  protected:
    ClassifyDiscriminantFunctionC(ClassifyDiscriminantFunctionBodyC &bod)
      : ClassifyVectorC(bod)
    {}
    //: Body constructor.
    
    ClassifyDiscriminantFunctionBodyC &Body()
    { return static_cast<ClassifyDiscriminantFunctionBodyC &>(ClassifyVectorC::Body()); }
    //: Access body.

    const ClassifyDiscriminantFunctionBodyC &Body() const
    { return static_cast<const ClassifyDiscriminantFunctionBodyC &>(ClassifyVectorC::Body()); }
    //: Access body.
    
  public:
    const FunctionC &Discriminant() const
    { return Body().Discriminant(); }
    //: Access discriminant function.
    
  };
  
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/ClassifyDiscriminantFunction.hh"

namespace RavlN {
  
  //: Create classifier from function.
  
  ClassifyDiscriminantFunctionBodyC::ClassifyDiscriminantFunctionBodyC(const FunctionC &nfunc)
    : ClassifyVectorBodyC(nfunc.OutputSize()),
      func(nfunc)
  {}
  
  //: Classify vector 'data' return the most likely label.
  
  UIntT ClassifyDiscriminantFunctionBodyC::Classify(const VectorC &data) const {
    VectorC vec = func(data);
    return vec.MaxIndex().V();
  }
  
  //: Estimate the confidence for each label.
  // The meaning of the confidence assigned to each label depends
  // on the classifier used. The higher the confidence the more likely
  // it is the label is correct.
  
  VectorC ClassifyDiscriminantFunctionBodyC::Confidence(const VectorC &data) const {
    VectorC vec = func(data);
    return vec.MakeUnit();
  }
  
  
}

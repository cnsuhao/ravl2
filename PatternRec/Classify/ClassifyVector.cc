// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classify/ClassifyVector.cc"

#include "Ravl/PatternRec/ClassifyVector.hh"

namespace RavlN {

  //: Default constructor.
  
  ClassifyVectorBodyC::ClassifyVectorBodyC(UIntT maxLabels)
    : labels(maxLabels)
  {}
  
  //: Classify vector 'data' return the most likely label.
  
  UIntT ClassifyVectorBodyC::Classify(const VectorC &data) const {
    return 0;
  }
    
  //: Generate a probability for each label.
  // Note: Not all classifiers return a true probablility vector.
  
  VectorC ClassifyVectorBodyC::Confidence(const VectorC &data) const {
    VectorC ret(labels);
    ret.Fill(0);
    UIntT res = Classify(data);
    RavlAssert(res < labels);
    ret[res] = 1;
    return ret;
  }
  
}

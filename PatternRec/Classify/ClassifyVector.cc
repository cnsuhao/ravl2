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
    : FunctionBodyC(0,maxLabels)
  {}
  
  //: Load from stream.
  
  ClassifyVectorBodyC::ClassifyVectorBodyC(istream &strm) 
    : FunctionBodyC(strm)
  {}
  
  //: Load from binary stream.
  
  ClassifyVectorBodyC::ClassifyVectorBodyC(BinIStreamC &strm) 
    : FunctionBodyC(strm)
  {}
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifyVectorBodyC::Save (ostream &out) const {
    return FunctionBodyC::Save(out);
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifyVectorBodyC::Save (BinOStreamC &out) const {
    return FunctionBodyC::Save(out);
  }
  
  //: Classify vector 'data' return the most likely label.
  
  UIntT ClassifyVectorBodyC::Classify(const VectorC &data) const {
    RavlAssertMsg(0,"ClassifyVectorBodyC::Classify(), Abstract method called. ");
    return 0;
  }
  
  //: Generate a probability for each label.
  // Note: Not all classifiers return a true probablility vector.
  
  VectorC ClassifyVectorBodyC::Apply(const VectorC &data) const {
    VectorC ret(NoLabels());
    ret.Fill(0);
    UIntT res = Classify(data);
    RavlAssert(res < NoLabels());
    ret[res] = 1;
    return ret;
  }
  
  
  ///////////////////////////////////////////////////////////
  
  //: Load from stream.
  
  ClassifyVectorC::ClassifyVectorC(istream &strm)
    : FunctionC(RAVL_VIRTUALCONSTRUCTOR(strm,ClassifyVectorBodyC))    
  {}
  
  //: Load from binary stream.
  
  ClassifyVectorC::ClassifyVectorC(BinIStreamC &strm)
    : FunctionC(RAVL_VIRTUALCONSTRUCTOR(strm,ClassifyVectorBodyC))
  {}

}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classifier/Classifier.cc"

#include "Ravl/PatternRec/Classifier.hh"

namespace RavlN {

  //: Default constructor.
  
  ClassifierBodyC::ClassifierBodyC(UIntT maxLabels)
    : FunctionBodyC(0,maxLabels)
  {}
  
  //: Load from stream.
  
  ClassifierBodyC::ClassifierBodyC(istream &strm) 
    : FunctionBodyC(strm)
  {}
  
  //: Load from binary stream.
  
  ClassifierBodyC::ClassifierBodyC(BinIStreamC &strm) 
    : FunctionBodyC(strm)
  {}
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifierBodyC::Save (ostream &out) const {
    return FunctionBodyC::Save(out);
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifierBodyC::Save (BinOStreamC &out) const {
    return FunctionBodyC::Save(out);
  }
  
  //: Classifier vector 'data' return the most likely label.
  
  UIntT ClassifierBodyC::Classifier(const VectorC &data) const {
    RavlAssertMsg(0,"ClassifierBodyC::Classifier(), Abstract method called. ");
    return 0;
  }
  
  //: Generate a probability for each label.
  // Note: Not all classifiers return a true probablility vector.
  
  VectorC ClassifierBodyC::Apply(const VectorC &data) const {
    VectorC ret(NoLabels());
    ret.Fill(0);
    UIntT res = Classifier(data);
    RavlAssert(res < NoLabels());
    ret[res] = 1;
    return ret;
  }
  
  
  ///////////////////////////////////////////////////////////
  
  //: Load from stream.
  
  ClassifierC::ClassifierC(istream &strm)
    : FunctionC(RAVL_VIRTUALCONSTRUCTOR(strm,ClassifierBodyC))    
  {}
  
  //: Load from binary stream.
  
  ClassifierC::ClassifierC(BinIStreamC &strm)
    : FunctionC(RAVL_VIRTUALCONSTRUCTOR(strm,ClassifierBodyC))
  {}

}

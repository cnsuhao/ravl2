// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: Error.cc 7592 2010-02-24 00:00:22Z kier $"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Performance/Error.cc"

#include "Ravl/PatternRec/Error.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/PatternRec/DataSet2Iter.hh"
namespace RavlN {

  //: Load from stream.
  
  ErrorBodyC::ErrorBodyC(istream &strm)
    : RCBodyVC(strm)
  {}
  
  //: Load from binary stream.
  
  ErrorBodyC::ErrorBodyC(BinIStreamC &strm)
    : RCBodyVC(strm)
  {}
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ErrorBodyC::Save (ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ErrorBodyC::Save (BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    return true;
  }
  
  RealT ErrorBodyC::Error(const ClassifierC & classifier, const SampleVectorC & x, const SampleLabelC & labels) {
    return Error(classifier, DataSetVectorLabelC(x, labels));
  }

  RealT ErrorBodyC::Error(const ClassifierC & classifier, const DataSetVectorLabelC & dset) {
    UIntT correct = 0;
    UIntT wrong = 0;    
    for(DataSet2IterC<SampleVectorC, SampleLabelC>it(dset);it;it++) {
      UIntT label = classifier.Classify(it.Data1());
      if(label==it.Data2()) correct++;
      else wrong++;
    }
    RealT pmc = (RealT)wrong/(RealT)dset.Sample1().Size();
    return pmc;
  }

  
  RealT ErrorBodyC::Error(const Classifier2C & classifier, const DataSetVectorLabelC & dset, UIntT label, RealT threshold) {
    UIntT correct = 0;
    UIntT wrong = 0;    
    
    for(DataSet2IterC<SampleVectorC, SampleLabelC>it(dset);it;it++) {
      RealT score = classifier.Classify2(it.Data1());
      if(it.Data2() == label && score <= threshold) 
        correct++;
      else if(it.Data2() != label && score > threshold)
        correct++;
      else wrong++;
    }
    RealT pmc = (RealT)wrong/(RealT)dset.Sample1().Size();
    return pmc;
  }

  
  
  //: Load from stream.
  
  ErrorC::ErrorC(istream &strm) 
    : RCHandleVC<ErrorBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,ErrorBodyC))
  {}
    
  //: Load from binary stream.
  
  ErrorC::ErrorC(BinIStreamC &strm) 
    : RCHandleVC<ErrorBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,ErrorBodyC))    
  {}

  //: Setup virtual constructor.
  // As this is an abstract class its not really needed, but its usefull to
  // have an example of how it should work here.
  
  //RAVL_INITVIRTUALCONSTRUCTOR(ErrorBodyC);
  
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CLASSIFYFUNC1THRESHOLD_HEADER
#define RAVL_CLASSIFYFUNC1THRESHOLD_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Classifier"
//! date="9/3/2003"

#include "Ravl/PatternRec/Classifier.hh"
#include "Ravl/PatternRec/Function1.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Binary Classifier, threshold a function.
  
  class ClassifierFunc1ThresholdBodyC 
    : public ClassifierBodyC
  {
  public:
    ClassifierFunc1ThresholdBodyC(const Function1C &nfunc,RealT nthreshold);
    //: Constructor.
    
    virtual UIntT Classify(const VectorC &data) const;
    //: Classifier vector 'data' return the most likely label.
    
  protected:
    Function1C func;
    RealT threshold;
  };
  
  //! userlevel=Normal
  //: Binary Classifier, threshold a function.
  
  class ClassifierFunc1ThresholdC
    : public ClassifierC
  {
  public:
    ClassifierFunc1ThresholdC()
    {}
    //: Default constructor.
    
    ClassifierFunc1ThresholdC(const Function1C &nfunc,RealT nthreshold)
      : ClassifierC(*new ClassifierFunc1ThresholdBodyC(nfunc,nthreshold))
    {}
    //: Constructor.
    
  };
}



#endif

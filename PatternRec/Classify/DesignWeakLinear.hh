// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNWEAKLINEAR_HEADER
#define RAVL_DESIGNWEAKLINEAR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Classifier"
//! file="Ravl/PatternRec/Classifier/DesignWeakLinear.hh"

#include "Ravl/PatternRec/DesignClassifierSupervised.hh"
#include "Ravl/PatternRec/DesignFunctionSupervised.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a weak linear classifier.
  
  class DesignWeakLinearBodyC
    : public DesignClassifierSupervisedBodyC
  {
  public:
    DesignWeakLinearBodyC(IndexC feature, RealT falseNegative)
      :m_feature(feature),
       m_falseNegative(falseNegative)
    {}
    //: Constructor.
    
    DesignWeakLinearBodyC(istream &strm);
    //: Load from stream.
    
    DesignWeakLinearBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor

    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Create a clasifier.
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.
    
  protected:
    IndexC m_feature;
    RealT m_falseNegative;
  };
  
  //! userlevel=Normal
  //: Design a weak linear classifier.
  
  class DesignWeakLinearC
    : public DesignClassifierSupervisedC
  {
  public:
    DesignWeakLinearC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignWeakLinearC(IndexC feature, RealT falseNegative)
      : DesignClassifierSupervisedC(*new DesignWeakLinearBodyC(feature,falseNegative))
    {}
    //: Create a new designer.
    //!param: feature       - which feature number to use for the classifier
    //!param: falseNegative - acceptable level of false negatives on class 0
    
    DesignWeakLinearC(istream &strm);
    //: Load from stream.
    
    DesignWeakLinearC(BinIStreamC &strm);
    //: Load from binary stream.

  protected:
    DesignWeakLinearC(DesignWeakLinearBodyC &bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body constructor.

    DesignWeakLinearC(DesignWeakLinearBodyC *bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body ptr constructor.
    
  };
  
}

#endif

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
#include "Ravl/MeanVariance.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a weak linear classifier.
  
  class DesignWeakLinearBodyC
    : public DesignClassifierSupervisedBodyC
  {
  public:
    DesignWeakLinearBodyC(RealT weight)
      :m_weight(weight)
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
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SArray1dC<IndexC> &featureSet);
    //: Create a clasifier
    
  private:
    RealT BestThreshold(RealT start);
    RealT Difference(RealT x);
  protected:
    RealT m_weight;
    MeanVarianceC m_dist0;
    MeanVarianceC m_dist1;
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
    
    DesignWeakLinearC(RealT weight)
      : DesignClassifierSupervisedC(*new DesignWeakLinearBodyC(weight))
    {}
    //: Create a new designer.
    //!param: weight - A priori probability for labels. Greater than 0.5 favours label1, less than 0.5 favours label0. 0 < weight < 1.
    
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

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNLINEARCOMBINATION_HEADER
#define RAVL_DESIGNLINEARCOMBINATION_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Classifier"
//! file="Ravl/PatternRec/Classifier/DesignLinearCombination.hh"

#include "Ravl/PatternRec/DesignClassifierSupervised.hh"
#include "Ravl/PatternRec/DesignFunctionSupervised.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a linear combination classifier.
  
  class DesignLinearCombinationBodyC
    : public DesignClassifierSupervisedBodyC
  {
  public:
    DesignLinearCombinationBodyC(RealT maxFalsePos, RealT minTruePos, UIntT numFeatures)
      :m_maxFalsePos(maxFalsePos),
       m_minTruePos(minTruePos),
       m_numFeatures(numFeatures)
    {}
    //: Constructor.
    
    DesignLinearCombinationBodyC(istream &strm);
    //: Load from stream.
    
    DesignLinearCombinationBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor

    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Create a clasifier.
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.
    
  private:
    VectorC NormaliseWeights(const VectorC &weights);
    
  protected:
    RealT m_maxFalsePos;
    RealT m_minTruePos;
    UIntT m_numFeatures;
  };
  
  //! userlevel=Normal
  //: Design a weak linear classifier.
  
  class DesignLinearCombinationC
    : public DesignClassifierSupervisedC
  {
  public:
    DesignLinearCombinationC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignLinearCombinationC(RealT maxFalsePos, RealT minTruePos, UIntT numFeatures)
      : DesignClassifierSupervisedC(*new DesignLinearCombinationBodyC(maxFalsePos,minTruePos,numFeatures))
    {}
    //: Create a new designer.
    
    DesignLinearCombinationC(istream &strm);
    //: Load from stream.
    
    DesignLinearCombinationC(BinIStreamC &strm);
    //: Load from binary stream.

  protected:
    DesignLinearCombinationC(DesignLinearCombinationBodyC &bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body constructor.

    DesignLinearCombinationC(DesignLinearCombinationBodyC *bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body ptr constructor.
    
  };
  
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_LINEARCOMBINATION_HEADER
#define RAVL_LINEARCOMBINATION_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Robert Crida"
//! userlevel=Normal
//! docentry="Ravl.Pattern Recognition.Classifier"
//! file="Ravl/PatternRec/Classify/ClassifierLinearCombination.hh"

#include "Ravl/PatternRec/Classifier.hh"
#include "Ravl/SArray1dIter2.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Linear combination classifier
  // Classifier which uses a weighted set of weak classifiers to classify into
  // one of two classes.
  
  class ClassifierLinearCombinationBodyC 
    : public ClassifierBodyC
  {
  public:
    ClassifierLinearCombinationBodyC(SArray1dC<ClassifierC> weakClassifiers, SArray1dC<RealT> weights, RealT threshold)
      :m_weakClassifiers(weakClassifiers),
       m_weights(weights),
       m_sumWeights(0.0),
       m_featureSet(weakClassifiers.Size())
    {
      RavlAssert(weakClassifiers.Size() == weights.Size());
      for(SArray1dIter2C<RealT,IndexC> it(weights,m_featureSet); it; it++) {
	m_sumWeights += it.Data1();
	it.Data2() = it.Index();
      }
      m_sumWeights *= threshold;
    }
    //: Constructor.
    //!param: weakClassifiers - a set of classifiers to be combined
    //!param: weights         - relative weights for each classifier
    // Classification is label 1 if sum(weight[i]*classify[i](x)) >= 0.5sum(weight[i])
    
    ClassifierLinearCombinationBodyC(istream &strm);
    //: Load from stream.
    
    ClassifierLinearCombinationBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual UIntT Classify(const VectorC &data) const;
    //: Classifier vector 'data' return the most likely label.

    virtual UIntT Classify(const VectorC &data,const SArray1dC<IndexC> &featureSet) const;
    //: Classify vector 'data' using only the given subset of features
    
  protected:
    SArray1dC<ClassifierC> m_weakClassifiers;
    SArray1dC<RealT> m_weights;
    RealT m_sumWeights;
    SArray1dC<IndexC> m_featureSet;
  };
  
  //! userlevel=Normal
  //: Linear combination classifier
  // Classifier which uses a weighted set of weak classifiers to classify into
  // one of two classes.

  class ClassifierLinearCombinationC 
    : public ClassifierC
  {
  public:
    ClassifierLinearCombinationC()
    {}
    //: Default constructor 
    // Creates an invalid handle.

    ClassifierLinearCombinationC(SArray1dC<ClassifierC> weakClassifiers, SArray1dC<RealT> weights, RealT threshold)
      : ClassifierC(*new ClassifierLinearCombinationBodyC(weakClassifiers,weights,threshold))
    {}
    //: Constructor.
    
    ClassifierLinearCombinationC(istream &strm);
    //: Load from stream.
    
    ClassifierLinearCombinationC(BinIStreamC &strm);
    //: Load from binary stream.
    
  protected:
    ClassifierLinearCombinationC(ClassifierLinearCombinationBodyC &bod)
      : ClassifierC(bod)
    {}
    //: Body constructor.

    ClassifierLinearCombinationC(ClassifierLinearCombinationBodyC *bod)
      : ClassifierC(bod)
    {}
    //: Body ptr constructor.
  };

  void InitRavlClassifierLinearCombinationIO();
      
}
#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classifier/DesignLinearCombination.cc"

#include "Ravl/PatternRec/DesignLinearCombination.hh"
#include "Ravl/PatternRec/ClassifierLinearCombination.hh"
#include "Ravl/PatternRec/DesignWeakLinear.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/SArray1dIter2.hh"

namespace RavlN {
  
  //: Load from stream.
  
  DesignLinearCombinationBodyC::DesignLinearCombinationBodyC(istream &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignWeakLinearBodyC::DesignWeakLinearBodyC(istream &), Unrecognised version number in stream. ");
    strm >> m_maxFalsePos >> m_minTruePos >> m_numFeatures;
  }
  
  //: Load from binary stream.
  
  DesignLinearCombinationBodyC::DesignLinearCombinationBodyC(BinIStreamC &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignWeakLinearBodyC::DesignWeakLinearBodyC(BinIStreamC &), Unrecognised version number in stream. ");
    strm >> m_maxFalsePos >> m_minTruePos >> m_numFeatures;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignLinearCombinationBodyC::Save (ostream &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    int version = 0;
    out << version << ' ' << m_maxFalsePos << ' ' << m_minTruePos << ' ' << m_numFeatures;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignLinearCombinationBodyC::Save (BinOStreamC &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    int version = 0;
    out << version << m_maxFalsePos << m_minTruePos << m_numFeatures;
    return true;
  }
  
  //: Create a clasifier.
  
  ClassifierC DesignLinearCombinationBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out) {
    RavlAssertMsg(in.Size() == out.Size(),"DesignLinearCombinationBodyC::Apply(), Sample of vector and labels should be the same size.");
    SArray1dC<ClassifierC> weakClassifiers(0);
    SArray1dC<RealT> classifierWeights(0);
    SArray1dC<ClassifierC> oneClassifier(1);
    SArray1dC<RealT> oneWeight(1);
    ClassifierLinearCombinationC strongClassifier;
    // initialise the weights
    VectorC weights(in.Size());
    Vector2dC sampleCount;
    sampleCount.Fill(0.0);
    for(SampleIterC<UIntT> it1(out); it1; it1++)
      sampleCount[*it1]++;
    for(SampleIterC<UIntT> it2(out); it2; it2++)
      weights[*it2] = 1.0/(2.0*sampleCount[*it2]);
    // for each feature that is added
    for(UIntT t = 0; t < m_numFeatures; t++) {
      weights = NormaliseWeights(weights);
      IndexC totalFeatures = in[0].Size();
      // for each feature, train a classifier and evaluate error
      ClassifierC bestClassifier;
      RealT lowestError = 1e30;
      for (IndexC j = 0; j < totalFeatures; j++) {
	DesignWeakLinearC designer(j, 1e-5);
	ClassifierC weakClassifier = designer.Apply(in,out);
	RealT error = 0.0;
	for (IndexC i = 0; i < in.Size(); i++)
	  error += weights[i] * Abs(weakClassifier.Classify(in[i]) - out[i]);
	if (lowestError > error) {
	  lowestError = error;
	  bestClassifier = weakClassifier;
	}
      }
      // update the strong classifier by adding the newest weak classifier
      RealT betaT = lowestError / (1.0-lowestError);
      RealT alphaT = log(1.0/betaT);
      oneClassifier[0] = bestClassifier;
      oneWeight[0] = alphaT;
      weakClassifiers.Append(oneClassifier);
      classifierWeights.Append(oneWeight);
      strongClassifier = ClassifierLinearCombinationC(weakClassifiers,classifierWeights);
      // update the weights
      for(IndexC i = 0; i < in.Size(); i++) {
	RealT ei = strongClassifier.Classify(in[i]) == out[i];
	weights[i] = weights[i] * Pow(betaT,1.0-ei);
      }
    }
    return strongClassifier;
  }

  VectorC DesignLinearCombinationBodyC::NormaliseWeights(const VectorC &weights) {
    VectorC out (weights.Size());
    RealT sum = weights.Sum();
    for(SArray1dIter2C<RealT,RealT> it(weights,out); it; it++)
      it.Data2() = it.Data1() / sum;
    return out;
  }
  
  //: Create a clasifier with weights for the samples.
  
  ClassifierC DesignLinearCombinationBodyC::Apply(const SampleC<VectorC> &in,
						  const SampleC<UIntT> &out,
						  const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignLinearCombinationBodyC::Apply(in,out,weight), Not implemented. Send a feature request! ");
    return ClassifierC();
  }
 
  //////////////////////////////////////////////////////////
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignLinearCombinationBodyC,DesignLinearCombinationC,DesignClassifierSupervisedC);

}

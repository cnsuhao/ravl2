// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classifier/DesignWeakLinear.cc"

#include "Ravl/PatternRec/DesignWeakLinear.hh"
#include "Ravl/PatternRec/ClassifierWeakLinear.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/MeanVariance.hh"

namespace RavlN {
  
  //: Load from stream.
  
  DesignWeakLinearBodyC::DesignWeakLinearBodyC(istream &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignWeakLinearBodyC::DesignWeakLinearBodyC(istream &), Unrecognised version number in stream. ");
    strm >> m_weight;
  }
  
  //: Load from binary stream.
  
  DesignWeakLinearBodyC::DesignWeakLinearBodyC(BinIStreamC &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignWeakLinearBodyC::DesignWeakLinearBodyC(BinIStreamC &), Unrecognised version number in stream. ");
    strm >> m_weight;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignWeakLinearBodyC::Save (ostream &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    int version = 0;
    out << ' ' << version << ' ' << m_weight;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignWeakLinearBodyC::Save (BinOStreamC &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    int version = 0;
    out << version << m_weight;
    return true;
  }
  
  //: Create a clasifier.
  
  ClassifierC DesignWeakLinearBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out) {
    RavlAssertMsg(in[0].Size() == 1,"DesignWeakLinearBodyC::Apply(), Feature vectors can only have 1 element.");
    SArray1dC<IndexC> featureSet(1);
    featureSet[0] = 0;
    // use the other apply method to do the work
    return Apply(in,out,featureSet);
  }
  
  //: Create a clasifier with weights for the samples.
  
  ClassifierC DesignWeakLinearBodyC::Apply(const SampleC<VectorC> &in,
					   const SampleC<UIntT> &out,
					   const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignWeakLinearBodyC::Apply(in,out,weight), Not implemented. Send a feature request! ");
    return ClassifierC();
  }
 
  ClassifierC DesignWeakLinearBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SArray1dC<IndexC> &featureSet) {
    RavlAssertMsg(in.Size() == out.Size(),"DesignWeakLinearBodyC::Apply(), Sample of vector and labels should be the same size.");
    RavlAssertMsg(featureSet.Size() == 1,"DesignWeakLinearBodyC::Apply(), Reduced feature set may only contain a single feature.");
    IndexC feature = featureSet[0];
    Vector2dC sumX;
    Vector2dC sumX2;
    Vector2dC sampleCount;
    sumX.Fill(0.0);
    sumX2.Fill(0.0);
    sampleCount.Fill(0.0);
    SampleIterC<VectorC> it1(in);
    SampleIterC<UIntT> it2(out);
    for (; it1; it1++,it2++) {
      RealT val = (*it1)[feature];
      sumX[*it2] += val;
      sumX2[*it2] += val * val;
      sampleCount[*it2]++;
    }
    RealT threshold;
    RealT parity;
    if (sampleCount[0] != 0 && sampleCount[1] != 0) {
      RealT mean1 = sumX[1] / sampleCount[1];
      RealT var1 = sumX2[1] / sampleCount[1] - mean1*mean1;
      if (var1 < 0.0) var1 = 0.0;
      RealT mean0 = sumX[0] / sampleCount[0];
      RealT var0 = sumX2[0] / sampleCount[0] - mean0*mean0;
      if (var0 < 0.0) var0 = 0.0;
      m_dist1 = MeanVarianceC((UIntT)sampleCount[1], mean1, var1); 
      m_dist0 = MeanVarianceC((UIntT)sampleCount[0], mean0, var0);
      if (mean1 > mean0) {
	parity = -1.0;
	threshold = BestThreshold((mean1+mean0)/2);//mean1 - 2.5 * Sqrt(var1);
      }
      else {
	parity = 1.0;
	threshold = BestThreshold((mean1+mean0)/2);//mean1 + 2.5 * Sqrt(var1);
      }
    }
    else {
      //cout << "Empty label count in one class!\n";
      cout << "E";
      parity = 1;
      threshold = 1e6;
    }
    return ClassifierWeakLinearC (threshold, parity);
  }

  RealT DesignWeakLinearBodyC::BestThreshold(RealT start) {
    RealT x = start;
    RealT v = Difference(x);
    IntT count = 10;
    while (Abs(v) > 1e-6 && count--) {
      RealT derivative = (Difference(x+1e-6) - Difference(x-1e-6)) / 2e-6;
      x = x - v / derivative;
      v = Difference(x);
    }
    return x;
  }

  RealT DesignWeakLinearBodyC::Difference(RealT x) {
    return m_weight * m_dist1.Gauss(x) - (1.0 - m_weight) * m_dist0.Gauss(x);
  }
  
  //////////////////////////////////////////////////////////
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignWeakLinearBodyC,DesignWeakLinearC,DesignClassifierSupervisedC);

}

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

namespace RavlN {
  
  //: Load from stream.
  
  DesignWeakLinearBodyC::DesignWeakLinearBodyC(istream &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignWeakLinearBodyC::DesignWeakLinearBodyC(istream &), Unrecognised version number in stream. ");
    strm >> m_feature >> m_falseNegative;
  }
  
  //: Load from binary stream.
  
  DesignWeakLinearBodyC::DesignWeakLinearBodyC(BinIStreamC &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignWeakLinearBodyC::DesignWeakLinearBodyC(BinIStreamC &), Unrecognised version number in stream. ");
    strm >> m_feature >> m_falseNegative;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignWeakLinearBodyC::Save (ostream &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    int version = 0;
    out << ' ' << version << ' ' << m_feature << ' ' << m_falseNegative;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignWeakLinearBodyC::Save (BinOStreamC &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    int version = 0;
    out << version << m_feature << m_falseNegative;
    return true;
  }
  
  //: Create a clasifier.
  
  ClassifierC DesignWeakLinearBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out) {
    RavlAssertMsg(in.Size() == out.Size(),"DesignWeakLinearBodyC::Apply(), Sample of vector and labels should be the same size.");
    Vector2dC sumX;
    Vector2dC sumX2;
    Vector2dC sampleCount;
    sumX.Fill(0.0);
    sumX2.Fill(0.0);
    sampleCount.Fill(0.0);
    SampleIterC<VectorC> it1(in);
    SampleIterC<UIntT> it2(out);
    for (; it1; it1++,it2++) {
      RealT val = (*it1)[m_feature];
      sumX[*it2] += val;
      sumX2[*it2] += val * val;
      sampleCount[*it2]++;
    }
    RealT threshold;
    RealT parity;
    RealT mean = sumX[0] / sampleCount[0];
    RealT var = mean*mean - sumX2[0]*sumX2[0] / sampleCount[0];
    if (sumX[0] > sumX[1]) {
      parity = -1.0;
      threshold = mean - 3.0 * Sqrt(var);
    }
    else {
      parity = 1.0;
      threshold = mean + 3.0 * Sqrt(var);
    }
    return ClassifierWeakLinearC (m_feature, threshold, parity);
  }
  
  //: Create a clasifier with weights for the samples.
  
  ClassifierC DesignWeakLinearBodyC::Apply(const SampleC<VectorC> &in,
					   const SampleC<UIntT> &out,
					   const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignWeakLinearBodyC::Apply(in,out,weight), Not implemented. Send a feature request! ");
    return ClassifierC();
  }
 
  //////////////////////////////////////////////////////////
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignWeakLinearBodyC,DesignWeakLinearC,DesignClassifierSupervisedC);

}

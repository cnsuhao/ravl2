// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classifier/ClassifierLinearCombination.cc"

#include "Ravl/PatternRec/ClassifierLinearCombination.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/SArray1dIter3.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Load from stream.
  
  ClassifierLinearCombinationBodyC::ClassifierLinearCombinationBodyC(istream &strm) 
    : ClassifierBodyC(strm)
  {
    IntT version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("ClassifierLinearCombinationBodyC(istream &), Unrecognised version number in stream. ");
    strm >> m_weakClassifiers >> m_weights >> m_sumWeights >> m_featureSet;
  }
  
  //: Load from binary stream.
  
  ClassifierLinearCombinationBodyC::ClassifierLinearCombinationBodyC(BinIStreamC &strm) 
    : ClassifierBodyC(strm)
  {
    IntT version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("ClassifierWeakLinearBodyC(BinIStreamC &), Unrecognised version number in stream. ");
    strm >> m_weakClassifiers >> m_weights >> m_sumWeights >> m_featureSet;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifierLinearCombinationBodyC::Save (ostream &out) const {
    if(!ClassifierBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << m_weakClassifiers << ' ' << m_weights << ' ' << m_sumWeights << ' ' << m_featureSet;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifierLinearCombinationBodyC::Save (BinOStreamC &out) const {
    if(!ClassifierBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version << m_weakClassifiers << m_weights << m_sumWeights << m_featureSet;
    return true;
  }

  UIntT ClassifierLinearCombinationBodyC::Classify(const VectorC &data) const {
    return Classify(data,m_featureSet);
  }

  UIntT ClassifierLinearCombinationBodyC::Classify(const VectorC &data,const SArray1dC<IndexC> &featureSet) const {
    RealT weightedSumLabels = 0.0;
    SArray1dC<IndexC> oneFeature(1);
    for(SArray1dIter3C<ClassifierC,RealT,IndexC> it(m_weakClassifiers,m_weights,featureSet); it; it++) {
      oneFeature[0] = it.Data3();
      weightedSumLabels += it.Data2() * it.Data1().Classify(data,oneFeature);
    }
    return weightedSumLabels >= m_sumWeights; // threshold is included in sum weights
  }
      
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(ClassifierLinearCombinationBodyC,ClassifierLinearCombinationC,ClassifierC);

  void InitRavlClassifierLinearCombinationIO() {
  }

}

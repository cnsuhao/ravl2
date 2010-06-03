// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: ClassifierWeakLinear.cc 3073 2003-06-13 07:18:32Z craftit $"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classify/ClassifierWeakLinear.cc"

#include "Ravl/PatternRec/ClassifierWeakLinear.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/BinStream.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Constructor

  ClassifierWeakLinearBodyC::ClassifierWeakLinearBodyC(RealT threshold1, RealT parity1, RealT threshold2, RealT parity2)
    :m_featureSet(1),
     m_parityThreshold1(parity1*threshold1),
     m_parity1(parity1),
     m_parityThreshold2(parity2*threshold2),
     m_parity2(parity2)
  {
    RavlAssert(parity1 == 1.0 || parity1 == -1.0);
    RavlAssert(parity2 == 1.0 || parity2 == -1.0);
    m_featureSet[0] = 0;
  }

  //: Load from stream.
  
  ClassifierWeakLinearBodyC::ClassifierWeakLinearBodyC(istream &strm) 
    : ClassifierBodyC(strm)
  {
    IntT version;
    strm >> version;
    if(version != 1)
      throw ExceptionOutOfRangeC("ClassifierWeakLinearBodyC(istream &), Unrecognised version number in stream. ");
    strm >> m_featureSet >> m_parityThreshold1 >> m_parity1 >> m_parityThreshold2 >> m_parity2;
  }
  
  //: Load from binary stream.
  
  ClassifierWeakLinearBodyC::ClassifierWeakLinearBodyC(BinIStreamC &strm) 
    : ClassifierBodyC(strm)
  {
    IntT version;
    strm >> version;
    if(version != 1)
      throw ExceptionOutOfRangeC("ClassifierWeakLinearBodyC(BinIStreamC &), Unrecognised version number in stream. ");
    strm >> m_featureSet >> m_parityThreshold1 >> m_parity1 >> m_parityThreshold2 >> m_parity2;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifierWeakLinearBodyC::Save (ostream &out) const {
    if(!ClassifierBodyC::Save(out))
      return false;
    IntT version = 1;
    out << ' ' << version << ' ' << m_featureSet << ' ' << m_parityThreshold1 << ' ' << m_parity1 << ' ' << m_parityThreshold2 << ' ' << m_parity2;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifierWeakLinearBodyC::Save (BinOStreamC &out) const {
    if(!ClassifierBodyC::Save(out))
      return false;
    IntT version = 1;
    out << version << m_featureSet << m_parityThreshold1 << m_parity1 << m_parityThreshold2 << m_parity2;
    return true;
  }
      
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(ClassifierWeakLinearBodyC,ClassifierWeakLinearC,ClassifierC);

  void InitRavlClassifierWeakLinearIO() {
  }

}

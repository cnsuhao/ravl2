// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classifier/ClassifierWeakLinear.cc"

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

  ClassifierWeakLinearBodyC::ClassifierWeakLinearBodyC(RealT threshold, RealT parity)
    :m_featureSet(1),
     m_parityThreshold(parity*threshold),
     m_parity(parity)
  {
    RavlAssert(parity == 1.0 || parity == -1.0);
    m_featureSet[0] = 0;
  }

  //: Load from stream.
  
  ClassifierWeakLinearBodyC::ClassifierWeakLinearBodyC(istream &strm) 
    : ClassifierBodyC(strm)
  {
    IntT version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("ClassifierWeakLinearBodyC(istream &), Unrecognised version number in stream. ");
    strm >> m_featureSet >> m_parityThreshold >> m_parity;
  }
  
  //: Load from binary stream.
  
  ClassifierWeakLinearBodyC::ClassifierWeakLinearBodyC(BinIStreamC &strm) 
    : ClassifierBodyC(strm)
  {
    IntT version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("ClassifierWeakLinearBodyC(BinIStreamC &), Unrecognised version number in stream. ");
    strm >> m_featureSet >> m_parityThreshold >> m_parity;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifierWeakLinearBodyC::Save (ostream &out) const {
    if(!ClassifierBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << m_featureSet << ' ' << m_parityThreshold << ' ' << m_parity;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ClassifierWeakLinearBodyC::Save (BinOStreamC &out) const {
    if(!ClassifierBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version << m_featureSet << m_parityThreshold << m_parity;
    return true;
  }
      
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(ClassifierWeakLinearBodyC,ClassifierWeakLinearC,ClassifierC);

}

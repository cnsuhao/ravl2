// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/Lottery.hh"
#include "Ravl/HashIter.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  LotteryBodyC::LotteryBodyC(const StringC& type, const RCHashC<StringC,RealT>& outcomes) {
    SetType(type);
    SetOutcomes(outcomes);
  }

  LotteryBodyC::~LotteryBodyC() {
  }

  const StringC& LotteryBodyC::Type() const {
    return m_type;
  }

  LotteryBodyC& LotteryBodyC::operator*=(const LotteryBodyC& other) {
  	if (Type() != other.Type())
  		throw ExceptionC("LotteryBodyC::operator*=(), other must be same type");
  	for (HashIterC<StringC,RealT> ht(m_outcomes); ht; ht++) {
  		ht.Data() *= other.m_outcomes[ht.Key()];
  	}
  	Normalize();
  	return *this;
  }
  
  void LotteryBodyC::SetType(const StringC& type) {
    m_type = type;
  }

  const RCHashC<StringC,RealT>& LotteryBodyC::Outcomes() const {
    return m_outcomes;
  }

  void LotteryBodyC::SetOutcomes(const RCHashC<StringC,RealT>& outcomes) {
    m_outcomes = outcomes;
    Normalize();
  }

  StringC LotteryBodyC::ToString() const {
    StringC string = Type() + "=[";
    if (Outcomes().Size() > 0) {
      HashIterC<StringC,RealT> it(Outcomes());
      string += "(";
      string += StringC(it.Data());
      string += ",";
      string += it.Key();
      string += ")";
      for (it++; it; it++) {
        string += ",(";
        string += StringC(it.Data());
        string += ",";
        string += it.Key();
        string += ")";
      }
    }
    string += "]";
    return string;
  }

  void LotteryBodyC::Normalize() {
    RealT sum = 0;
    for (HashIterC<StringC,RealT> it(Outcomes()); it; it++)
      sum += it.Data();
    RealT invSum = 1.0 / sum;
    for (HashIterC<StringC,RealT> it(Outcomes()); it; it++)
      it.Data() *= invSum;
  }

}

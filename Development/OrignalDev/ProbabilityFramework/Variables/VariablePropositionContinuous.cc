// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/VariablePropositionContinuous.hh"
#include "Ravl/StdHash.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  VariablePropositionContinuousBodyC::VariablePropositionContinuousBodyC(const VariableContinuousC& variable, RealRangeC valueRange)
    : VariablePropositionBodyC(variable)
  {
    SetValueRange(valueRange);
  }

  VariablePropositionContinuousBodyC::VariablePropositionContinuousBodyC(istream &in)
    : VariablePropositionBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariablePropositionContinuousBodyC(istream &), Unrecognised version number in stream.");
    RealRangeC valueRange;
    in >> valueRange;
    SetValueRange(valueRange);
  }

  VariablePropositionContinuousBodyC::VariablePropositionContinuousBodyC(BinIStreamC &in)
    : VariablePropositionBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariablePropositionContinuousBodyC(BinIStream &), Unrecognised version number in stream.");
    RealRangeC valueRange;
    in >> valueRange;
    SetValueRange(valueRange);
  }
  
  bool VariablePropositionContinuousBodyC::Save (ostream &out) const {
    if(!VariablePropositionBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << ValueRange();
    return true;
  }
  
  bool VariablePropositionContinuousBodyC::Save (BinOStreamC &out) const {
    if(!VariablePropositionBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version << ValueRange();
    return true;
  }

  VariablePropositionContinuousBodyC::~VariablePropositionContinuousBodyC() {
  }
  
  StringC VariablePropositionContinuousBodyC::ToString() const {
    return StringC("[")+ValueRange().Min()+","+ValueRange().Max()+"]";
  }

  RealRangeC VariablePropositionContinuousBodyC::ValueRange() const {
    return m_valueRange;
  }

  void VariablePropositionContinuousBodyC::SetValueRange(RealRangeC valueRange) {
    if (!VariableContinuous().Interval().Contains(valueRange))
      throw ExceptionC("VariablePropositionContinuousBodyC::SetValueRange(), illegal value range (must be contained by variable interval)");
    m_valueRange = valueRange;
  }

  bool VariablePropositionContinuousBodyC::operator==(const VariablePropositionC& other) const {
    if (!VariablePropositionBodyC::operator==(other))
      return false;
    VariablePropositionContinuousC otherContinuous(other);
    if (!otherContinuous.IsValid())
      return false;
    return ValueRange() == otherContinuous.ValueRange();
  }

  UIntT VariablePropositionContinuousBodyC::Hash() const {
	Int64T bitwiseIntMin = *((Int64T*)&ValueRange().Min());
    Int64T bitwiseIntMax = *((Int64T*)&ValueRange().Max());
    return VariablePropositionBodyC::Hash() + StdHash(bitwiseIntMin) + StdHash(bitwiseIntMax);
  }

  VariableContinuousC VariablePropositionContinuousBodyC::VariableContinuous() const {
    return VariableContinuousC(Variable());
  }

  static TypeNameC type1(typeid(VariablePropositionContinuousC),"RavlProbN::VariablePropositionContinuousC");
    
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(VariablePropositionContinuousBodyC,VariablePropositionContinuousC,VariablePropositionC);
  
}

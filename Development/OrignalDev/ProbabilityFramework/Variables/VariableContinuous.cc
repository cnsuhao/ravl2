// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/VariableContinuous.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  VariableContinuousBodyC::VariableContinuousBodyC(const StringC& name, const RealRangeC& interval)
    : VariableBodyC(name)
  {
    SetInterval(interval);
  }

  VariableContinuousBodyC::VariableContinuousBodyC(istream &in)
    : VariableBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableContinuousBodyC(istream &), Unrecognised version number in stream.");
    RealRangeC interval;
    in >> interval;
    SetInterval(interval);
  }

  VariableContinuousBodyC::VariableContinuousBodyC(BinIStreamC &in)
    : VariableBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableContinuousBodyC(BinIStream &), Unrecognised version number in stream.");
    RealRangeC interval;
    in >> interval;
    SetInterval(interval);
  }
  
  bool VariableContinuousBodyC::Save (ostream &out) const {
    if(!VariableBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << Interval();
    return true;
  }
  
  bool VariableContinuousBodyC::Save (BinOStreamC &out) const {
    if(!VariableBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version << Interval();
    return true;
  }

  VariableContinuousBodyC::~VariableContinuousBodyC() {
  }
  
  StringC VariableContinuousBodyC::ToString() const {
    StringC values = Name() + "=[";
    values += StringC(m_interval.Min());
    values += ",";
    values += StringC(m_interval.Max());
    values += "]";
    return values;
  }

  const RealRangeC& VariableContinuousBodyC::Interval() const {
    return m_interval;
  }

  void VariableContinuousBodyC::SetInterval(const RealRangeC& interval) {
    m_interval = interval;
  }

  static TypeNameC type1(typeid(VariableContinuousC),"RavlProbN::VariableContinuousC");
    
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(VariableContinuousBodyC,VariableContinuousC,VariableC);
  
}

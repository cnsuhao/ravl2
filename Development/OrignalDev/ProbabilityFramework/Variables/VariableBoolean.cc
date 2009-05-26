// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/VariableBoolean.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  VariableBooleanBodyC::VariableBooleanBodyC(const StringC& name)
    : VariableDiscreteBodyC(name)
  {
    SetValueNames();
    DomainDiscreteC domain;
    domain.Insert(m_trueValue);
    domain.Insert(m_falseValue);
    SetDomain(domain);
  }

  VariableBooleanBodyC::VariableBooleanBodyC(istream &in)
    : VariableDiscreteBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableBooleanBodyC(istream &), Unrecognised version number in stream.");
    SetValueNames();
  }

  VariableBooleanBodyC::VariableBooleanBodyC(BinIStreamC &in)
    : VariableDiscreteBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableBooleanBodyC(BinIStream &), Unrecognised version number in stream.");
    SetValueNames();
  }
  
  bool VariableBooleanBodyC::Save (ostream &out) const {
    if(!VariableDiscreteBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version;
    return true;
  }
  
  bool VariableBooleanBodyC::Save (BinOStreamC &out) const {
    if(!VariableDiscreteBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version;
    return true;
  }

  VariableBooleanBodyC::~VariableBooleanBodyC() {
  }

  const StringC& VariableBooleanBodyC::Value(bool value) const {
    return value? m_trueValue: m_falseValue;
  }
  
  void VariableBooleanBodyC::SetValueNames() {
    m_trueValue = downcase(Name());
    m_falseValue = StringC("¬")+downcase(Name());
  }

  static TypeNameC type1(typeid(VariableBooleanC),"RavlProbN::VariableBooleanC");
    
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(VariableBooleanBodyC,VariableBooleanC,VariableDiscreteC);
  
}

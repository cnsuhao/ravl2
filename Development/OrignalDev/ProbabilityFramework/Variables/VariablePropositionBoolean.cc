// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/VariablePropositionBoolean.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  VariablePropositionBooleanBodyC::VariablePropositionBooleanBodyC(const VariableBooleanC& variable, bool value)
    : VariablePropositionDiscreteBodyC(variable)
  {
    SetBooleanValue(value);
  }

  VariablePropositionBooleanBodyC::VariablePropositionBooleanBodyC(istream &in)
    : VariablePropositionDiscreteBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariablePropositionBooleanBodyC(istream &), Unrecognised version number in stream.");
    bool value;
    in >> value;
    SetBooleanValue(value);
  }

  VariablePropositionBooleanBodyC::VariablePropositionBooleanBodyC(BinIStreamC &in)
    : VariablePropositionDiscreteBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariablePropositionBooleanBodyC(BinIStream &), Unrecognised version number in stream.");
    bool value;
    in >> value;
    SetBooleanValue(value);
  }
  
  bool VariablePropositionBooleanBodyC::Save (ostream &out) const {
    if(!VariablePropositionDiscreteBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << BooleanValue();
    return true;
  }
  
  bool VariablePropositionBooleanBodyC::Save (BinOStreamC &out) const {
    if(!VariablePropositionDiscreteBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version << BooleanValue();
    return true;
  }

  VariablePropositionBooleanBodyC::~VariablePropositionBooleanBodyC() {
  }
  
  bool VariablePropositionBooleanBodyC::BooleanValue() const {
    return m_booleanValue;
  }

  void VariablePropositionBooleanBodyC::SetBooleanValue(bool value) {
    m_booleanValue = value;
    VariablePropositionDiscreteBodyC::SetValue(VariableBoolean().Value(value));
  }

  void VariablePropositionBooleanBodyC::SetValue(const StringC& value) {
    SetBooleanValue(VariableBoolean().Value(true) == value);
  }

  VariableBooleanC VariablePropositionBooleanBodyC::VariableBoolean() const {
    return VariableBooleanC(Variable());
  }

  static TypeNameC type1(typeid(VariablePropositionBooleanC),"RavlProbN::VariablePropositionBooleanC");
    
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(VariablePropositionBooleanBodyC,VariablePropositionBooleanC,VariablePropositionDiscreteC);
  
}

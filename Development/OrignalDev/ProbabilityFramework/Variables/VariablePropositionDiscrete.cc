// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/VariablePropositionDiscrete.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  VariablePropositionDiscreteBodyC::VariablePropositionDiscreteBodyC(const VariableDiscreteC& variable, const StringC& value)
    : VariablePropositionBodyC(variable)
  {
    SetValue(value);
  }

  VariablePropositionDiscreteBodyC::VariablePropositionDiscreteBodyC(const VariableDiscreteC& variable)
    : VariablePropositionBodyC(variable)
  {
    //: NOTE that the value hasn't been initialized, you better know what you are doing!
  }

  VariablePropositionDiscreteBodyC::VariablePropositionDiscreteBodyC(istream &in)
    : VariablePropositionBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariablePropositionDiscreteBodyC(istream &), Unrecognised version number in stream.");
    StringC value;
    in >> value;
    SetValue(value);
  }

  VariablePropositionDiscreteBodyC::VariablePropositionDiscreteBodyC(BinIStreamC &in)
    : VariablePropositionBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariablePropositionDiscreteBodyC(BinIStream &), Unrecognised version number in stream.");
    StringC value;
    in >> value;
    SetValue(value);
  }
  
  bool VariablePropositionDiscreteBodyC::Save (ostream &out) const {
    if(!VariablePropositionBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << Value();
    return true;
  }
  
  bool VariablePropositionDiscreteBodyC::Save (BinOStreamC &out) const {
    if(!VariablePropositionBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version << Value();
    return true;
  }

  VariablePropositionDiscreteBodyC::~VariablePropositionDiscreteBodyC() {
  }
  
  StringC VariablePropositionDiscreteBodyC::ToString() const {
    return Value();
  }

  const StringC& VariablePropositionDiscreteBodyC::Value() const {
    return m_value;
  }

  void VariablePropositionDiscreteBodyC::SetValue(const StringC& value) {
    if (!VariableDiscrete().Domain().Contains(value))
      throw ExceptionC("VariablePropositionDiscreteBodyC::SetValue(), illegal value");
    m_value = value;
  }

  IndexC VariablePropositionDiscreteBodyC::Index() const {
    return VariableDiscrete().Index(Value());
  }

  bool VariablePropositionDiscreteBodyC::operator==(const VariablePropositionC& other) const {
    if (!VariablePropositionBodyC::operator==(other))
      return false;
    VariablePropositionDiscreteC otherDiscrete(other);
    if (!otherDiscrete.IsValid())
      return false;
    return Value() == otherDiscrete.Value();
  }

  UIntT VariablePropositionDiscreteBodyC::Hash() const {
    return VariablePropositionBodyC::Hash() + Value().Hash();
  }

  VariableDiscreteC VariablePropositionDiscreteBodyC::VariableDiscrete() const {
    return VariableDiscreteC(Variable());
  }

  static TypeNameC type1(typeid(VariablePropositionDiscreteC),"RavlProbN::VariablePropositionDiscreteC");
    
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(VariablePropositionDiscreteBodyC,VariablePropositionDiscreteC,VariablePropositionC);
  
}

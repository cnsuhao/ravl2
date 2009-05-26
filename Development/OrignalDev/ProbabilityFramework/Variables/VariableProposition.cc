// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/VariableProposition.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  VariablePropositionBodyC::VariablePropositionBodyC(const VariableC& variable) {
    SetVariable(variable);
  }

  VariablePropositionBodyC::VariablePropositionBodyC(istream &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariablePropositionBodyC(istream &), Unrecognised version number in stream.");
    VariableC variable(in);
    SetVariable(variable);
  }

  VariablePropositionBodyC::VariablePropositionBodyC(BinIStreamC &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariablePropositionBodyC(BinIStream &), Unrecognised version number in stream.");
    VariableC variable(in);
    SetVariable(variable);
  }
  
  bool VariablePropositionBodyC::Save (ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << Variable();
    return true;
  }
  
  bool VariablePropositionBodyC::Save (BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << version << Variable();
    return true;
  }

  VariablePropositionBodyC::~VariablePropositionBodyC() {
  }

  const VariableC& VariablePropositionBodyC::Variable() const {
    return m_variable;
  }

  void VariablePropositionBodyC::SetVariable(const VariableC& variable) {
    if (!variable.IsValid())
      throw ExceptionC("VariablePropositionBodyC::SetVariable() with invalid variable");
    m_variable = variable;
  }

  bool VariablePropositionBodyC::operator==(const VariablePropositionC& other) const {
    return Variable() == other.Variable();
  }

  UIntT VariablePropositionBodyC::Hash() const {
    return Variable().Hash();
  }

  ostream &operator<<(ostream &s,const VariablePropositionC &obj) {
    obj.Save(s);
    return s;
  }
  
  istream &operator>>(istream &s,VariablePropositionC &obj) {
    obj = VariablePropositionC(s);
    return s;
  }

  BinOStreamC &operator<<(BinOStreamC &s,const VariablePropositionC &obj) {
    obj.Save(s);
    return s;
  }
    
  BinIStreamC &operator>>(BinIStreamC &s,VariablePropositionC &obj) {
    obj = VariablePropositionC(s);
    return s;
  }
 
  static TypeNameC type1(typeid(VariablePropositionC),"RavlProbN::VariablePropositionC");
    
  RAVL_VIRTUALCONSTRUCTOR_HANDLE(VariablePropositionBodyC,VariablePropositionC,RCHandleVC<VariablePropositionBodyC>);
  
}

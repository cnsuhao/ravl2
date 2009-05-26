// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/Variable.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  VariableBodyC::VariableBodyC(const StringC& name) {
    SetName(name);
  }

  VariableBodyC::VariableBodyC(istream &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableBodyC(istream &), Unrecognised version number in stream.");
    StringC name(in);
    SetName(name);
  }

  VariableBodyC::VariableBodyC(BinIStreamC &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableBodyC(BinIStream &), Unrecognised version number in stream.");
    StringC name;
    in >> name;
    SetName(name);
  }
  
  bool VariableBodyC::Save (ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << Name();
    return true;
  }
  
  bool VariableBodyC::Save (BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << version << Name();
    return true;
  }

  VariableBodyC::~VariableBodyC() {
  }

  const StringC& VariableBodyC::Name() const {
    return m_name;
  }

  void VariableBodyC::SetName(const StringC& name) {
    m_name = downcase(name);
    m_name[0] = toupper(m_name[0]);
  }

  bool VariableBodyC::operator==(const VariableC& other) const {
    return Name() == other.Name();
  }

  UIntT VariableBodyC::Hash() const {
    return Name().Hash();
  }

  ostream &operator<<(ostream &s,const VariableC &obj) {
    obj.Save(s);
    return s;
  }
  
  istream &operator>>(istream &s,VariableC &obj) {
    obj = VariableC(s);
    return s;
  }

  BinOStreamC &operator<<(BinOStreamC &s,const VariableC &obj) {
    obj.Save(s);
    return s;
  }
    
  BinIStreamC &operator>>(BinIStreamC &s,VariableC &obj) {
    obj = VariableC(s);
    return s;
  }
 
  static TypeNameC type1(typeid(VariableC),"RavlProbN::VariableC");

  RAVL_VIRTUALCONSTRUCTOR_HANDLE(VariableBodyC,VariableC,RCHandleVC<VariableBodyC>);
  
}

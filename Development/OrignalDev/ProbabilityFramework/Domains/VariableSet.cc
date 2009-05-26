// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/VariableSet.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  VariableSetBodyC::VariableSetBodyC(const HSetC<VariableC>& variables) {
    SetVariables(variables);
  }

  VariableSetBodyC::VariableSetBodyC(const VariableC& variable) {
    SetSingleVariable(variable);
  }

  VariableSetBodyC::VariableSetBodyC(istream &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableSetBodyC(istream &), Unrecognised version number in stream.");
    HSetC<VariableC> variables;
    in >> variables;
    SetVariables(variables);
  }

  VariableSetBodyC::VariableSetBodyC(BinIStreamC &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableSetBodyC(BinIStream &), Unrecognised version number in stream.");
    HSetC<VariableC> variables;
    in >> variables;
    SetVariables(variables);
  }
  
  bool VariableSetBodyC::Save (ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << Variables();
    return true;
  }
  
  bool VariableSetBodyC::Save (BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << version << Variables();
    return true;
  }

  VariableSetBodyC::~VariableSetBodyC() {
  }

  bool VariableSetBodyC::operator==(const VariableSetBodyC& other) const {
    if (this == &other)
      return true;
    if (Size() != other.Size())
      return false;
    for (HSetIterC<VariableC> ht(Variables()); ht; ht++)
      if (!other.Variables().Contains(*ht))
        return false;
    return true;
  }

  bool VariableSetBodyC::Contains(const VariableC& variable) const {
    //:FIXME- depends on choice of collection
    if (!variable.IsValid())
    	return false;
    return Variables().Contains(variable);
  }

  SizeT VariableSetBodyC::Size() const {
    return Variables().Size();
  }

  const HSetC<VariableC>& VariableSetBodyC::Variables() const {
    return m_variables;
  }

  const VariableC& VariableSetBodyC::Variable(IndexC index) const {
    if (index < 0 || index >= Size())
      throw ExceptionC("VariableSetBodyC::Variable(), index too big");
    HSetIterC<VariableC> it(Variables());
    while(index--)
      it++;
    return *it;
  }

  void VariableSetBodyC::SetVariables(const HSetC<VariableC>& variables) {
    //:FIXME- what collection for efficiency?
    m_variables = variables.Copy();
  }
  
  void VariableSetBodyC::SetSingleVariable(const VariableC& variable) {
  	HSetC<VariableC> variables;
  	variables.Insert(variable);
  	SetVariables(variables);
  }

  IndexC VariableSetBodyC::Index(const VariableC& variable) const {
  	if (!variable.IsValid())
  		throw ExceptionC("VariableSetBodyC::Index(), invalid variable");
    //:FIXME- this should probably be implemented using hash table
    IndexC index(0);
    for (HSetIterC<VariableC> it(Variables()); it; it++, index++)
      if (*it == variable)
        return index;
    throw ExceptionC("VariableSetBodyC::Index(), couldn't find variable");
  }

  StringC VariableSetBodyC::ToString() const {
  	if (Size() == 0)
  		return "{}";
    HSetIterC<VariableC> it(Variables());
    StringC string = StringC("{") + it->Name();
    for (it++; it; it++) {
      string += ",";
      string += it->Name();
    }
    string += "}";
    return string;
  }

  UIntT VariableSetBodyC::Hash() const {
    UIntT hash = 0;
    for (HSetIterC<VariableC> it(Variables()); it; it++)
      hash += it->Hash();
    return hash;
  }

  ostream &operator<<(ostream &s,const VariableSetC &obj) {
    obj.Save(s);
    return s;
  }
  
  istream &operator>>(istream &s,VariableSetC &obj) {
    obj = VariableSetC(s);
    return s;
  }

  BinOStreamC &operator<<(BinOStreamC &s,const VariableSetC &obj) {
    obj.Save(s);
    return s;
  }
    
  BinIStreamC &operator>>(BinIStreamC &s,VariableSetC &obj) {
    obj = VariableSetC(s);
    return s;
  }
 
  static TypeNameC type1(typeid(VariableSetC),"RavlProbN::VariableSetC");
    
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(VariableSetBodyC,VariableSetC,RCHandleVC<VariableSetBodyC>);
  
}

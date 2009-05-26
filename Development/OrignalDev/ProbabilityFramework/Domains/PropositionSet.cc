// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PropositionSet.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PropositionSetBodyC::PropositionSetBodyC(const VariableSetC& variableSet, const HSetC<VariablePropositionC>& values) {
    SetVariableSet(variableSet);
    SetValues(values);
  }

  PropositionSetBodyC::PropositionSetBodyC(const VariableSetC& variableSet, const RCHashC<VariableC,VariablePropositionC>& values)
    : m_variableSet(variableSet),
      m_values(values)
  {}
  
  PropositionSetBodyC::PropositionSetBodyC(const VariableSetC& variableSet, const VariablePropositionC& value) {
    SetVariableSet(variableSet);
    SetSingleValue(value);
  }

  PropositionSetBodyC::PropositionSetBodyC(const VariablePropositionC& value) {
    HSetC<VariableC> var;
    var += value.Variable();
    SetVariableSet(var);
    SetSingleValue(value);
  }
  
  PropositionSetBodyC::PropositionSetBodyC(const PropositionSetBodyC& other, const VariablePropositionC& value) 
    : m_variableSet(other.VariableSet().Variables().Copy()),
      m_values(other.Values().Copy())
  {
    m_values[value.Variable()] = value;
  }
  
  PropositionSetBodyC::PropositionSetBodyC(istream &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("PropositionSetBodyC(istream &), Unrecognised version number in stream.");
    VariableSetC variableSet(in);
    SetVariableSet(variableSet);
    HSetC<VariablePropositionC> values;
    in >> values;
    SetValues(values);
  }

  PropositionSetBodyC::PropositionSetBodyC(BinIStreamC &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("PropositionSetBodyC(BinIStream &), Unrecognised version number in stream.");
    VariableSetC variableSet(in);
    SetVariableSet(variableSet);
    HSetC<VariablePropositionC> values;
    in >> values;
    SetValues(values);
  }
  
  bool PropositionSetBodyC::Save (ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << VariableSet() << ' ' << Values();
    return true;
  }
  
  bool PropositionSetBodyC::Save (BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << version << VariableSet() << Values();
    return true;
  }

  PropositionSetBodyC::~PropositionSetBodyC() 
  {}
  

  const VariablePropositionC& PropositionSetBodyC::Value(IndexC index) const {
    if (index < 0 || index >= Size())
      throw ExceptionC("PropositionSetBodyC::Value(), index out of range");
    HashIterC<VariableC,VariablePropositionC> it(Values());
    while(index--)
      it++;
    return *it;
  }

  StringC PropositionSetBodyC::ToString() const {
    if (Size() == 0)
      return "{}";
    HashIterC<VariableC,VariablePropositionC> it(Values());
    StringC string = StringC("{") + it.Key().Name() + "=" + it.Data().ToString();
    for (it++; it; it++) {
      string += ",";
      string += it.Key().Name() + "=" + it.Data().ToString();
    }
    string += "}";
    return string;
  }
  
  StringC PropositionSetBodyC::LotteryName() const {
    StringC name = VariableSet().ToString(); // show all variables
    name += "->(";
    bool first = true;
    for (HSetIterC<VariableC> it(VariableSet().Variables()); it; it++) {
      if(m_values.IsElm(*it))
        continue;
      if(!first)
        name += ",";
      else
        first = false;
      name += it->Name();
    }
    name += ")";
    return name;
  }
  
  PropositionSetC PropositionSetBodyC::SubPropositionSet(const VariableSetC& subVariableSet) const {
    // Check that all variables are in current variableSet!
    RCHashC<VariableC,VariablePropositionC> newValues;
    for (HSetIterC<VariableC> dt(subVariableSet.Variables()); dt; dt++) {
      if (!VariableSet().Contains(*dt))
        throw ExceptionC("PropositionSetBodyC::SubPropositionSet(), invalid new variableSet variable");
      const VariablePropositionC *prop;
      if((prop = m_values.Lookup(*dt)) != 0)
        newValues[*dt] = *prop;
    }
    return PropositionSetC(subVariableSet, newValues);
  }

  void PropositionSetBodyC::SetVariableSet(const VariableSetC& variableSet) {
    m_variableSet = variableSet;
  }

  void PropositionSetBodyC::SetValues(const HSetC<VariablePropositionC>& values) {
    //:FIXME- what collection for efficiency?
    m_values.Empty();
    for (HSetIterC<VariablePropositionC> it(values); it; it++) {
      if (!VariableSet().Contains(it->Variable()))
        throw ExceptionC("PropositionSetBodyC::SetValues(), value not in variableSet");
      m_values[it->Variable()] = *it;
    }
  }

  void PropositionSetBodyC::SetSingleValue(const VariablePropositionC& value) {
    HSetC<VariablePropositionC> values;
    values.Insert(value);
    SetValues(values);
  }
  
  bool PropositionSetBodyC::operator==(const PropositionSetBodyC& other) const {
    if (this == &other)
      return true;
    if (VariableSet() != other.VariableSet())
      return false;
    //cerr << "m_values=" << ToString() << " " << "other.Values()=" << other.ToString() << " Equality=" << (m_values == other.Values()) << "\n";
    return (m_values == other.Values());
  }

  UIntT PropositionSetBodyC::Hash() const {
    return VariableSet().Hash() + m_values.Hash();
  }

  ostream &operator<<(ostream &s,const PropositionSetC &obj) {
    obj.Save(s);
    return s;
  }
  
  istream &operator>>(istream &s,PropositionSetC &obj) {
    obj = PropositionSetC(s);
    return s;
  }

  BinOStreamC &operator<<(BinOStreamC &s,const PropositionSetC &obj) {
    obj.Save(s);
    return s;
  }
    
  BinIStreamC &operator>>(BinIStreamC &s,PropositionSetC &obj) {
    obj = PropositionSetC(s);
    return s;
  }
 
  static TypeNameC type1(typeid(PropositionSetC),"RavlProbN::PropositionSetC");
    
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(PropositionSetBodyC,PropositionSetC,RCHandleVC<PropositionSetBodyC>);
  
}

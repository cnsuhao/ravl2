// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/DomainDiscrete.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  DomainDiscreteBodyC::DomainDiscreteBodyC() {
  }

  DomainDiscreteBodyC::DomainDiscreteBodyC(istream &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("DomainDiscreteBodyC(istream &), Unrecognised version number in stream.");
    in >> m_valueArray;
    CreateValueHash();
  }

  DomainDiscreteBodyC::DomainDiscreteBodyC(BinIStreamC &in)
    : RCBodyVC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("DomainDiscreteBodyC(BinIStream &), Unrecognised version number in stream.");
    in >> m_valueArray;
    CreateValueHash();
  }
  
  bool DomainDiscreteBodyC::Save (ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << m_valueArray;
    return true;
  }
  
  bool DomainDiscreteBodyC::Save (BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    IntT version = 0;
    out << version << m_valueArray;
    return true;
  }

  DomainDiscreteBodyC::~DomainDiscreteBodyC() {
  }

  void DomainDiscreteBodyC::Insert(const StringC& value) {
    StringC downcaseValue = downcase(value);
    if (Contains(downcaseValue))
  		throw ExceptionC("DomainDiscreteBodyC::Insert(), value already in domain");
  	SArray1dC<StringC> values(1);
  	values[0] = downcaseValue;
  	m_valueArray.Append(values);
  	CreateValueHash();
  }

  void DomainDiscreteBodyC::Remove(const StringC& value) {
  	IndexC index = Index(value);
  	SArray1dC<StringC> newArray(m_valueArray.From(0, index.V()));
  	newArray.Append(m_valueArray.After(index.V()));
  	m_valueArray = newArray;
  	CreateValueHash();
  }

  bool DomainDiscreteBodyC::Contains(const StringC& value) const {
  	IndexC index;
  	return m_valueHash.Lookup(downcase(value), index);
  }

  IndexC DomainDiscreteBodyC::Index(const StringC& value) const {
  	IndexC index;
  	if (m_valueHash.Lookup(downcase(value), index) == true)
  		return index;
  	throw ExceptionC("DomainDiscreteBodyC::Index(), value isn't in domain");
  }

  const StringC& DomainDiscreteBodyC::Value(IndexC index) const {
  	if (index < 0 || index >= Size())
  		throw ExceptionC("DomainDiscreteBodyC::Value(), index out of range");
  	return m_valueArray[index];
  }

  SizeT DomainDiscreteBodyC::Size() const {
  	return m_valueArray.Size();
  }

  SArray1dIterC<StringC> DomainDiscreteBodyC::Iterator() const {
  	return SArray1dIterC<StringC>(m_valueArray);
  }

  bool DomainDiscreteBodyC::operator==(const DomainDiscreteBodyC& other) const {
    return m_valueArray == other.m_valueArray;
  }
  
  StringC DomainDiscreteBodyC::ToString() const {
    StringC values("<");
    SArray1dIterC<StringC> it = Iterator();
    values += *it;
    for (it++ ; it; it++) {
      values += ",";
      values += *it;
    }
    values += ">";
    return values;
  }

  UIntT DomainDiscreteBodyC::Hash() const {
    return m_valueArray.Hash();
  }
  
  void DomainDiscreteBodyC::CreateValueHash() {
  	m_valueHash = HashC<StringC,IndexC>();
  	IndexC index = 0;
  	for (SArray1dIterC<StringC> it = Iterator(); it; it++, index++) {
  		m_valueHash.Insert(*it, index);
  	}
  }

  ostream &operator<<(ostream &s,const DomainDiscreteC &obj) {
    obj.Save(s);
    return s;
  }
  
  istream &operator>>(istream &s,DomainDiscreteC &obj) {
    obj = DomainDiscreteC(s);
    return s;
  }

  BinOStreamC &operator<<(BinOStreamC &s,const DomainDiscreteC &obj) {
    obj.Save(s);
    return s;
  }
    
  BinIStreamC &operator>>(BinIStreamC &s,DomainDiscreteC &obj) {
    obj = DomainDiscreteC(s);
    return s;
  }
 
  static TypeNameC type1(typeid(DomainDiscreteC),"RavlProbN::DomainDiscreteC");

  RAVL_VIRTUALCONSTRUCTOR_HANDLE(DomainDiscreteBodyC,DomainDiscreteC,RCHandleVC<DomainDiscreteBodyC>);
  
}

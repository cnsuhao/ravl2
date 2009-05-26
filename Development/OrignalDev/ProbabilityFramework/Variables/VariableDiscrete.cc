// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/VariableDiscrete.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  VariableDiscreteBodyC::VariableDiscreteBodyC(const StringC& name, const DomainDiscreteC& domain)
    : VariableBodyC(name)
  {
    SetDomain(domain);
  }

  VariableDiscreteBodyC::VariableDiscreteBodyC(const StringC& name)
    : VariableBodyC(name)
  {
  }

  VariableDiscreteBodyC::VariableDiscreteBodyC(istream &in)
    : VariableBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableDiscreteBodyC(istream &), Unrecognised version number in stream.");
    DomainDiscreteC domain(in);
    SetDomain(domain);
  }

  VariableDiscreteBodyC::VariableDiscreteBodyC(BinIStreamC &in)
    : VariableBodyC(in)
  {
    IntT version;
    in >> version;
    if (version < 0 || version > 0)
      throw ExceptionOutOfRangeC("VariableDiscreteBodyC(BinIStream &), Unrecognised version number in stream.");
    DomainDiscreteC domain(in);
    SetDomain(domain);
  }
  
  bool VariableDiscreteBodyC::Save (ostream &out) const {
    if(!VariableBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << Domain();
    return true;
  }
  
  bool VariableDiscreteBodyC::Save (BinOStreamC &out) const {
    if(!VariableBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version << Domain();
    return true;
  }

  VariableDiscreteBodyC::~VariableDiscreteBodyC() {
  }
  
  StringC VariableDiscreteBodyC::ToString() const {
    return Name() + "=" + Domain().ToString();
  }

  SizeT VariableDiscreteBodyC::DomainSize() const {
    return Domain().Size();
  }

  const DomainDiscreteC& VariableDiscreteBodyC::Domain() const {
    return m_domain;
  }

  const StringC& VariableDiscreteBodyC::Value(IndexC index) const {
  	return Domain().Value(index);
  }

  IndexC VariableDiscreteBodyC::Index(const StringC& value) const {
  	return Domain().Index(value);
  }

  void VariableDiscreteBodyC::SetDomain(const DomainDiscreteC& domain) {
	//!FIXME:- Need to use domain.Copy()!
  	m_domain = domain;
  }

  static TypeNameC type1(typeid(VariableDiscreteC),"RavlProbN::VariableDiscreteC");
    
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(VariableDiscreteBodyC,VariableDiscreteC,VariableC);
  
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2009, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlXMLFactory
//! author="Charles Galambos"
//! docentry=Ravl.API.Core.IO.XMLFactory

#include "Ravl/XMLFactoryRegister.hh"
#include "Ravl/Threads/Signal.hh"
#include "Ravl/Threads/Signal1.hh"

namespace RavlN {
  
  XMLFactoryRegisterC<XMLFactoryC> g_xmlFactoryRegisterXMLFactory("RavlN::XMLFactoryC");
  
  static RavlN::RCWrapAbstractC StdStringFactoryFunc(const XMLFactoryContextC &node)
  { return RavlN::RCWrapC<std::string>(node.AttributeString("value","").data()); }

  static RavlN::RCWrapAbstractC StringFactoryFunc(const XMLFactoryContextC &node)
  { return RavlN::RCWrapC<StringC>(node.AttributeString("value","")); }

  static RavlN::RCWrapAbstractC Signal0FactoryFunc(const XMLFactoryContextC &node)
  { return RavlN::RCWrapC<Signal0C>(Signal0C(true)); }

  static RavlN::RCWrapAbstractC Signal1BoolFactoryFunc(const XMLFactoryContextC &node)
  { return RavlN::RCWrapC<Signal1C<bool> >(Signal1C<bool>(node.AttributeBool("value",false))); }

  static RavlN::RCWrapAbstractC Signal1StringFactoryFunc(const XMLFactoryContextC &node)
  { return RavlN::RCWrapC<Signal1C<StringC> >(Signal1C<StringC>(node.AttributeString("value",""))); }

  static int InitStringFactory() {
    RavlN::AddTypeName(typeid(std::string),"std::string");
    RavlN::AddTypeName(typeid(Signal0C),"RavlN::Signal0C");
    RavlN::AddTypeName(typeid(Signal1C<bool>),"RavlN::Signal1C<bool>");
    RavlN::AddTypeName(typeid(Signal1C<StringC>),"RavlN::Signal1C<RavlN::StringC>");
    XMLFactoryC::RegisterTypeFactory(typeid(std::string),&StdStringFactoryFunc);
    XMLFactoryC::RegisterTypeFactory(typeid(StringC),&StringFactoryFunc);
    XMLFactoryC::RegisterTypeFactory(typeid(Signal0C),&Signal0FactoryFunc);
    XMLFactoryC::RegisterTypeFactory(typeid(Signal1C<bool>),&Signal1BoolFactoryFunc);
    XMLFactoryC::RegisterTypeFactory(typeid(Signal1C<StringC>),&Signal1StringFactoryFunc);
    return 0;
  }

  int g_initStringFactory = InitStringFactory();

  void linkXMLFactoryRegister()
  {}

}

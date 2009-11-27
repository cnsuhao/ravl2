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

namespace RavlN {
  
  XMLFactoryRegisterC<XMLFactoryC> g_xmlFactoryRegisterXMLFactory("RavlN::XMLFactoryC");
  
  static RavlN::RCWrapAbstractC StdStringFactoryFunc(const XMLFactoryContextC &node)
  { return RavlN::RCWrapC<std::string>(node.AttributeString("value","").data()); }

  static RavlN::RCWrapAbstractC StringFactoryFunc(const XMLFactoryContextC &node)
  { return RavlN::RCWrapC<StringC>(node.AttributeString("value","")); }

  static int InitStringFactory() {
    RavlN::AddTypeName(typeid(std::string),"std::string");
    //RavlN::AddTypeName(typeid(StringC),"RavlN::StringC");
    XMLFactoryC::RegisterTypeFactory(typeid(std::string),&StdStringFactoryFunc);
    XMLFactoryC::RegisterTypeFactory(typeid(StringC),&StringFactoryFunc);
    return 0;
  }

  int g_initStringFactory = InitStringFactory();

  void linkXMLFactoryRegister()
  {}

}

# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2009, OmniPerception Ltd
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! author=Charles Galambos
#! docentry=Ravl.API.Core.IO.XMLFactory

PACKAGE=Ravl

HEADERS=XMLFactory.hh XMLFactoryRegister.hh XMLFactoryAutoStart.hh ConfigParameter.hh

SOURCES=XMLFactory.cc XMLFactoryRegister.cc XMLFactoryAutoStart.cc ConfigParameter.cc

MUSTLINK=LinkXMLFactory.cc

PLIB=RavlXMLFactory

USESLIBS=RavlCore RavlIO RavlThreads RavlOS

PROGLIBS=

EXAMPLES= exXMLFactory.cc

TESTEXES= testXMLFactory.cc

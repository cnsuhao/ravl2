# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Core/System/defs.mk"

PACKAGE=Ravl

HEADERS=StringList.hh Option.hh TypeName.hh BufStream.hh \
 SubStringList.hh XMLStream.hh XMLTree.hh \
 Collection.hh CollectionIter.hh IO.hh

SOURCES=StringList.cc Option.cc TypeName.cc BufStream.cc \
 SubStringList.cc XMLStream.cc XMLTree.cc StreamParse.cc

PLIB=RavlCore

LIBDEPS=RavlSys.def

USESLIBS=RavlCore

EXAMPLES=exOption.cc exXMLTree.cc

EHT=Ravl.Core.XML.html

TESTEXES=testRavlCore.cc testXMLStream.cc testCollection.cc

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
 Collection.hh CollectionIter.hh IO.hh \
 DArray1d.hh DArray1dIter.hh DArray1dIter2.hh DArray1dIter3.hh \
 VirtualConstructor.hh FunctionRegister.hh IndexNd.hh Cache.hh \
 DListExtra.hh VariableLengthCode.hh IndexRange2dSet.hh Base64.hh

SOURCES=StringList.cc Option.cc TypeName.cc BufStream.cc \
 SubStringList.cc XMLStream.cc XMLTree.cc StreamParse.cc \
 VirtualConstructor.cc FunctionRegister.cc IndexNd.cc \
 VariableLengthCode.cc IndexRange2dSet.cc Base64.cc

PLIB=RavlCore

LIBDEPS=RavlSys.def

USESLIBS=RavlCore

EXAMPLES=exOption.cc exXMLTree.cc exVariableLengthCode.cc exXMLStream.cc

EHT=Ravl.Core.XML.html Ravl.Core.IO.Type_Name.html Ravl.Core.IO.Function_Register.html

TESTEXES=testRavlCore.cc testXMLStream.cc testCollection.cc

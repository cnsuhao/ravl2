# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Logic/Index/defs.mk"

PACKAGE=Ravl/Logic

HEADERS=LiteralIndexBase.hh LiteralIndexElement.hh LiteralIndexLeaf.hh \
 LiteralIndexNode.hh LiteralIndex.hh LiteralIndexIter.hh \
 LiteralIndexFilterBase.hh LiteralIndexFilter.hh LiteralIndexLeafIter.hh \
 BLiteralIndex.hh BMinTermIndex.hh BMinTermIndexIter.hh BMinTermListIndex.hh \
 LiteralIndexLeafVarIter.hh StateIndexed.hh LiteralIndexFilterRaw.hh

SOURCES=LiteralIndexBase.cc LiteralIndexElement.cc LiteralIndexLeaf.cc \
 LiteralIndexNode.cc LiteralIndexIter.cc LiteralIndexFilterBase.cc \
 LiteralIndexLeafIter.cc LiteralIndexLeafVarIter.cc StateIndexed.cc \
 LiteralIndexFilterRaw.cc

PLIB=RavlLogic

LIBDEPS=RavlLogicIndex.def

USESLIBS=RavlLogic

TESTEXES=testLiteralIndex.cc testBLiteralIndex.cc

EHT=Ravl.API.Logic.Index.html

# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"
#! file="Ravl/Core/Base/defs.mk"

DESCRIPTION= RAVL core functionality

PACKAGE=Ravl

HEADERS=Types.hh config.h Pair.hh \
 Assert.hh Exception.hh EntryPnt.hh Index.hh String.hh \
 RefCounter.hh HandleRefCounter.hh Trigger.hh Calls.hh \
 MTLocks.hh StreamType.hh Stream.hh StrStream.hh BinStream.hh \
 BitStream.hh IndexRange1d.hh Index2d.hh IndexRange2d.hh \
 Index3d.hh RCWrap.hh Empty.hh IntC.hh TFVector.hh FIndex.hh \
 StdConst.hh RCAbstract.hh Math.hh CallMethods.hh CallMethodRefs.hh \
 DeepCopy.hh StdHash.hh Const.hh IndexRange3d.hh

SOURCES=Assert.cc Exception.cc EntryPnt.cc Index.cc String.cc \
 RefCounter.cc HandleRefCounter.cc Trigger.cc Calls.cc \
 MTLocks.cc StreamType.cc Stream.cc StrStream.cc BinStream.cc \
 BitStream.cc IndexRange1d.cc IndexRange2d.cc \
 Index2d.cc Index3d.cc IntC.cc StdConst.cc RCAbstract.cc \
 BinString.cc RCWrap.cc IndexRange3d.cc Math.cc

PLIB=RavlCore

USESLIBS=Math

TESTEXES= testRavlBase.cc testCalls.cc testString.cc testStream.cc testTFVector.cc

EXAMPLES = exIndex.cc

EHT=Ravl.Core.Indexing.eht Ravl.Core.Error_Handling.eht Ravl.Core.Misc.eht Ravl.Core.Reference_Counting.eht \
 Ravl.Core.Strings.html



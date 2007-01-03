# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Core/Base/defs.mk"

DESCRIPTION= RAVL core functionality

PACKAGE=Ravl

HEADERS=Types.hh config.h Pair.hh Resource.hh \
 Assert.hh Exception.hh EntryPnt.hh Index.hh String.hh \
 RefCounter.hh HandleRefCounter.hh Trigger.hh Calls.hh \
 MTLocks.hh StreamType.hh Stream.hh StrStream.hh BinStream.hh \
 BitStream.hh IndexRange1d.hh Index2d.hh IndexRange2d.hh \
 Index3d.hh RCWrap.hh Empty.hh IntC.hh TFVector.hh FIndex.hh \
 StdConst.hh RCAbstract.hh Math.hh CallMethods.hh CallMethodRefs.hh \
 DeepCopy.hh StdHash.hh Const.hh IndexRange3d.hh Average.hh RealC.hh \
 SmartPtr.hh SubIndexRange2dIter.hh SubIndexRange3dIter.hh \
 RealRange1d.hh RealRange2d.hh RealRange3d.hh \
 RCBodyV.hh RCHandleV.hh IndexRange2dIter.hh IndexRange3dIter.hh fdstreambuf.hh \
 fdstream.hh GenBinStream.hh Traits.hh FPNumber.hh QInt.hh CompilerHints.hh \
 stdio_fdstream.hh AMutex.hh RCLayer.hh SmartLayerPtr.hh CallMethodPtrs.hh CPUID.hh

SOURCES=Assert.cc Exception.cc EntryPnt.cc Index.cc String.cc \
 RefCounter.cc HandleRefCounter.cc Trigger.cc Calls.cc \
 MTLocks.cc StreamType.cc Stream.cc StrStream.cc BinStream.cc \
 BitStream.cc IndexRange1d.cc IndexRange2d.cc \
 Index2d.cc Index3d.cc IntC.cc StdConst.cc RCAbstract.cc \
 BinString.cc RCWrap.cc IndexRange3d.cc Math.cc RealC.cc \
 RealRange1d.cc RealRange2d.cc RealRange3d.cc \
 RCBodyV.cc URLMapper.cc GenBinStream.cc Resource.cc \
 AMutex.cc RCLayer.cc CPUID.cc

PLIB=RavlCore

MUSTLINK=atexit.cc

USESLIBS=Math

TESTEXES= testRavlBase.cc testCalls.cc testString.cc testStream.cc testTFVector.cc testRCLayer.cc

EXAMPLES = exIndex.cc exRefCounter.cc exRefCounterInherit.cc exQInt.cc exTrigger.cc testRCLayer.cc exCPUID.cc

EHT=Ravl.API.Core.Indexing.eht Ravl.API.Core.Error_Handling.eht Ravl.API.Core.Misc.eht Ravl.API.Core.Reference_Counting.eht \
 Ravl.API.Core.Strings.html Ravl.API.Core.IO.Streams.html Ravl.API.Core.Calls.html Ravl.API.Math.QInt.html \
 Ravl.API.Core.Locks.html Ravl.API.Core.Resource.html Ravl.API.Core.Typedefs.html




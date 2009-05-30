# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Core/Container/Buffer/defs.mk"

PACKAGE=Ravl

HEADERS=Buffer.hh CompositeBuffer.hh RangeBufferAccess.hh SizeBufferAccess.hh BufferAccess.hh \
 BufferAccessIter.hh BfAccIter2.hh BfAccIter3.hh BfAccIter4.hh BfAccIter5.hh BfAccIter6.hh BfAccIter7.hh \
 BfAcc2Iter.hh BfAcc2Iter2.hh BfAcc2Iter3.hh BfAcc2Iter4.hh BfAcc2Iter5.hh BfAcc2Iter6.hh BfAcc2Iter7.hh \
 Buffer2d.hh SizeBufferAccess2d.hh RangeBufferAccess2d.hh Slice1d.hh Slice1dIter.hh \
 Slice1dIter2.hh Slice1dIter3.hh \
 Buffer3d.hh BfAcc3Iter.hh BfAcc3Iter2.hh BfAcc3Iter3.hh \
 SizeBufferAccess3d.hh RangeBufferAccess3d.hh BufferAccessIterR.hh SingleBuffer.hh

SOURCES=RangeBufferAccess2d.cc SizeBufferAccess2d.cc RangeBufferAccess.cc SizeBufferAccess.cc

PLIB= RavlCore

LIBDEPS=RavlBuff.def

USESLIBS=RavlCore

EHT=Ravl.API.Core.Arrays.Buffer.html

TESTEXES=testBuffer2d.cc testBuffer3d.cc testSlice.cc

EXAMPLES=exSizeBufferAccess.cc exRangeBufferAccess.cc


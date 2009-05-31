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
 BufferAccessIter.hh BufferAccessIter2.hh BufferAccessIter3.hh BufferAccessIter4.hh BufferAccessIter5.hh BufferAccessIter6.hh BufferAccessIter7.hh \
 BufferAccess2dIter.hh BufferAccess2dIter2.hh BufferAccess2dIter3.hh BufferAccess2dIter4.hh BufferAccess2dIter5.hh BufferAccess2dIter6.hh BufferAccess2dIter7.hh \
 Buffer2d.hh SizeBufferAccess2d.hh RangeBufferAccess2d.hh Slice1d.hh Slice1dIter.hh \
 Slice1dIter2.hh Slice1dIter3.hh \
 Buffer3d.hh BufferAccess3dIter.hh BufferAccess3dIter2.hh BufferAccess3dIter3.hh \
 SizeBufferAccess3d.hh RangeBufferAccess3d.hh BufferAccessIterR.hh SingleBuffer.hh \
 BufferAccess2dIterBase.hh \
 AttachedBuffer2d.hh AttachedBuffer3d.hh

SOURCES=RangeBufferAccess2d.cc SizeBufferAccess2d.cc RangeBufferAccess.cc SizeBufferAccess.cc

PLIB= RavlCore

LIBDEPS=RavlBuff.def

USESLIBS=RavlCore

EHT=Ravl.API.Core.Arrays.Buffer.html

TESTEXES=testBuffer2d.cc testBuffer3d.cc testSlice.cc

EXAMPLES=exSizeBufferAccess.cc exRangeBufferAccess.cc


# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Core/Container/Buffer/defs.mk"

PACKAGE=Ravl

HEADERS=Buffer.hh CompositeBuffer.hh RBfAcc.hh SBfAcc.hh BufferAccess.hh \
 BfAccIter.hh BfAccIter2.hh BfAccIter3.hh BfAccIter4.hh \
 BfAcc2Iter.hh BfAcc2Iter2.hh BfAcc2Iter3.hh BfAcc2Iter4.hh \
 Buffer2d.hh SBfAcc2d.hh RBfAcc2d.hh Slice1d.hh Slice1dIter.hh \
 Slice1dIter2.hh Slice1dIter3.hh \
 Buffer3d.hh BfAcc3Iter.hh BfAcc3Iter2.hh BfAcc3Iter3.hh \
 SBfAcc3d.hh RBfAcc3d.hh BufferAccessIterR.hh

#BfAcc3Iter.hh

SOURCES=

PLIB= RavlCore

LIBDEPS=RavlBuff.def

USESLIBS=RavlCore

EHT=Ravl.Core.Arrays.Buffer.html

TESTEXES=testBuffer2d.cc testBuffer3d.cc testSlice.cc

EXAMPLES=exSBfAcc.cc exRBfAcc.cc


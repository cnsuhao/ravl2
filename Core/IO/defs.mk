# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Core/IO/defs.mk"


PACKAGE=Ravl/DP

HEADERS=Entity.hh Process.hh Port.hh SPort.hh SPortAttach.hh \
 StreamOp.hh IOJoin.hh ProcOStream.hh ProcIStream.hh Func2Proc.hh \
 FileIO.hh BinFileIO.hh FuncP2Proc.hh ProcCompose.hh ProcInfo.hh \
 Converter.hh DataConv.hh TypeInfo.hh Pipes.hh FileFormat.hh \
 FileFormDesc.hh FileFormatStream.hh FileFormatBinStream.hh \
 FileFormatGen.hh FileFormatIO.hh TypeConverter.hh FileFormatRegistry.hh

SOURCES=Entity.cc Process.cc Port.cc SPort.cc SPortAttach.cc ProcInfo.cc \
 Converter.cc TypeInfo.cc Pipes.cc FileFormat.cc FileFormDesc.cc \
 FileFormatStream.cc FileFormatBinStream.cc FileFormatGen.cc \
 FileFormatIO.cc TypeConverter.cc FileFormatRegistry.cc

# ProcInfo.cc

PLIB=RavlIO

USESLIBS=RavlCore

TESTEXES=testFunc2Proc.cc

EHT=Ravl.Core.IO.eht Ravl.Core.Data_Processing.eht

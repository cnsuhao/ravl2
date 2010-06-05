# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 7367 2009-11-10 18:12:56Z craftit $"
#! file="Ravl/Core/IO/defs.mk"

PACKAGE=Ravl/DP

NESTED=doc.r

HEADERS=Entity.hh Process.hh Port.hh SPort.hh SPortAttach.hh \
 StreamOp.hh IOJoin.hh ProcOStream.hh ProcIStream.hh Func2Proc.hh \
 FileIO.hh BinFileIO.hh FuncP2Proc.hh ProcCompose.hh ProcInfo.hh \
 Converter.hh DataConv.hh TypeInfo.hh Pipes.hh FileFormat.hh \
 FileFormatDesc.hh FileFormatStream.hh FileFormatBinStream.hh \
 FileFormatGen.hh FileFormatIO.hh TypeConverter.hh FileFormatRegistry.hh \
 CoreIO.hh ComposeSingle.hh Compose.hh Func2Stream.hh IOConnect.hh \
 IFailOver.hh  IOTap.hh  Multiplex.hh SplitO.hh Event.hh EventSet.hh \
 Method2Proc.hh MethodIO.hh ContainerIO.hh Plug.hh Tap.hh StreamProcess.hh \
 Process21.hh Process31.hh Method2Proc21.hh Method2Proc31.hh StreamOp21.hh \
 StreamOp31.hh Func2Proc21.hh Func2Proc31.hh OffsetScale.hh RunningAverage.hh \
 IOPort.hh XMLFileIO.hh FileFormatXMLStream.hh ListIO.hh AttributeType.hh \
 AttributeCtrl.hh AttributeValueTypes.hh AttributeSet.hh  AttributeCtrlInternal.hh \
 ByteFileIO.hh SampleStream.hh CacheIStream.hh ByteStream.hh SByteStream.hh \
 MemIO.hh AttributeCtrlUpdateSignal.hh PrintIOInfo.hh MethodPtrIO.hh \
 FileFormatByteFile.hh MethodPtr2Proc.hh

SOURCES=Entity.cc Process.cc Port.cc SPort.cc SPortAttach.cc ProcInfo.cc \
 Converter.cc TypeInfo.cc Pipes.cc FileFormat.cc FileFormatDesc.cc \
 FileFormatStream.cc FileFormatBinStream.cc FileFormatGen.cc \
 FileFormatIO.cc TypeConverter.cc FileFormatRegistry.cc IndexIO.cc \
 Event.cc EventSet.cc Plug.cc StreamOp.cc StreamProcess.cc IOConnect.cc \
 FileFormatXMLStream.cc DataConv.cc AttributeCtrl.cc AttributeType.cc \
 AttributeValueTypes.cc AttributeCtrlXML.cc AttributeSet.cc \
 ByteFileIO.cc ByteStream.cc SByteStream.cc AttributeCtrlInternal.cc \
 AttributeCtrlUpdateSignal.cc PrintIOInfo.cc FileFormatByteFile.cc

MUSTLINK= CoreIO.cc
# ProcInfo.cc

PLIB=RavlIO

USESLIBS=RavlCore

TESTEXES= testDataProc.cc

EXAMPLES = exComposeSingle.cc exDataProc.cc exFileFormat.cc

EHT=Ravl.API.Core.IO.eht IOHacks.html \
    Ravl.API.Core.IO.Formats.html \
    Ravl.API.Core.IO.Type_Converter.html \
    Ravl.API.Core.IO.Virtual_Files.html

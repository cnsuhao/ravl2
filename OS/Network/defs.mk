# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/OS/Network/defs.mk"
DONOT_SUPPORT=cygwin

PACKAGE=Ravl/OS

HEADERS = SktError.hh Socket.hh NetStream.hh Packet.hh \
 NetMessage.hh NetEndPoint.hh NetMsgCall.hh NetIPort.hh \
 NetIPortServer.hh NetPortManager.hh NetPortClient.hh \
 NetPortFormat.hh NetOPort.hh NetOPortServer.hh NetPort.hh \
 NetAttributeCtrl.hh NetRequestManager.hh NetAttributeCtrlServer.hh \
 NetByteStream.hh NetMsgOPortData.hh WinSocket.hh

SOURCES = Socket.cc NetStream.cc SocketStrm.cc Packet.cc \
 NetMessage.cc NetEndPoint.cc NetMsgCall.cc NetIPort.cc \
 NetIPortServer.cc NetPortManager.cc NetPortClient.cc \
 NetPortFormat.cc NetOPort.cc NetOPortServer.cc NetPort.cc \
 NetAttributeCtrl.cc NetRequestManager.cc NetAttributeCtrlServer.cc \
 NetByteStream.cc NetMsgOPortData.cc WinSocket.cc

MUSTLINK = RavlSysNetworkML.cc

PLIB = RavlNet

EHT=Ravl.API.OS.Network.html Ravl.API.OS.Network.NetPort.html

EXAMPLES = exSocket.cc exEndPoint.cc exNetPort.cc

TESTEXES=testNetPort.cc testSocket.cc

USESLIBS = RavlOS RavlCore Socket RavlThreads RavlIO

PROGLIBS= RavlThreads

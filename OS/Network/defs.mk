# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/OS/Network/defs.mk"

PACKAGE=Ravl/OS

HEADERS = SktError.hh Socket.hh NetStream.hh Packet.hh \
 NetMessage.hh NetEndPoint.hh NetMsgCall.hh

SOURCES = Socket.cc NetStream.cc SocketStrm.cc Packet.cc \
 NetMessage.cc    NetEndPoint.cc NetMsgCall.cc

MUSTLINK = RavlSysNetworkML.cc

LIBDEPS = RavlNet.def

PLIB = RavlOS

EHT=Ravl.OS.Network.html

EXAMPLES = exSocket.cc exEndPoint.cc

USESLIBS = RavlOS RavlCore Socket RavlThreads


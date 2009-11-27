# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2005, OmniPerception Ltd
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

ORGANISATION=OmniPerception Ltd

PACKAGE=Ravl/DataServer

HEADERS=DataServer.hh DataServerControlInterface.hh DataServerControlMessages.hh \
 DataServerVFSNode.hh DataServerVFSRealFile.hh DataServerVFSRealDir.hh \
 DataServerControlServer.hh DataServerControlConnection.hh DataServerControlClient.hh DataServerControlNetClient.hh

SOURCES=DataServer.cc DataServerControlInterface.cc \
 DataServerVFSNode.cc DataServerVFSRealFile.cc DataServerVFSRealDir.cc \
 DataServerControlServer.cc DataServerControlConnection.cc DataServerControlClient.cc DataServerControlNetClient.cc

PLIB=RavlDataServer

MAINS= dsd.cc

USESLIBS= RavlNet RavlOSIO 

PROGLIBS= RavlIO RavlImageIO RavlVideoIO RavlExtImgIO RavlImage RavlImgIOV4L2.opt

# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2005, OmniPerception Ltd
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

ORGANISATION=OmniPerception Ltd

PACKAGE=Ravl/DataServer

HEADERS=DataServer.hh DataServerVFSNode.hh DataServerVFSRealFile.hh DataServerVFSRealDir.hh

SOURCES=DataServer.cc DataServerVFSNode.cc DataServerVFSRealFile.cc DataServerVFSRealDir.cc

MAINS= dsd.cc

USESLIBS= RavlNet RavlOSIO 

PROGLIBS= RavlImageIO RavlVideoIO RavlExtImgIO RavlImage

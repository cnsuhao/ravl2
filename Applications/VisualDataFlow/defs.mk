# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

DESCRIPTION=Visual data flow programming tool.

PACKAGE=Ravl/DF

HEADERS=DFObject.hh DFSystem.hh ViewElement.hh GUIView.hh GUIEditor.hh \
 DFData.hh DFProcess.hh DFStreamOp.hh DFPort.hh DFLink.hh Factory.hh \
 FactorySet.hh GUIFactory.hh

SOURCES=DFObject.cc DFSystem.cc ViewElement.cc GUIView.cc GUIEditor.cc \
 DFData.cc DFProcess.cc DFStreamOp.cc DFPort.cc DFLink.cc Factory.cc \
 FactorySet.cc GUIFactory.cc

PLIB= RavlVDF

MAINS=vdf.cc

USESLIBS=RavlGUI RavlIO RavlImageIO RavlDPDisplay RavlOSIO RavlImgIOV4L

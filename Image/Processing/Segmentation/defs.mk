# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Segmentation/defs.mk"

PACKAGE=Ravl/Image

HEADERS=ChromaThreshold.hh  Segmentation.hh ConnectedComponents.hh \
 BlueScreen.hh

SOURCES=ChromaThreshold.cc Segmentation.cc ConnectedComponents.cc \
 BlueScreen.cc

PLIB=RavlImageProc

LIBDEPS=RavlImageSegmentation.def

TESTEXES=testConnectedComponents.cc 

USESLIBS=RavlImageProc  

EHT=Ravl.Images.Segmentation.html

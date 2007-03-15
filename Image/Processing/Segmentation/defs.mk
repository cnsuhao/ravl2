# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Segmentation/defs.mk"

PACKAGE=Ravl/Image

HEADERS=Segmentation.hh RegionSet.hh ConnectedComponents.hh \
 ChromaThreshold.hh BlueScreen.hh SegmentExtrema.hh FloodRegion.hh SegmentRegion.hh \
 RegionGrow.hh RegionGrowSteal.hh PixelSelectStack.hh \
 PixelClassifyGrey.hh PixelClassifyColour.hh PixelClassifyMotion.hh 

SOURCES=ChromaThreshold.cc Segmentation.cc ConnectedComponents.cc \
 BlueScreen.cc SegmentExtrema.cc PixelSelectStack.cc 

CCPPFLAGS += -g
LDFLAGS += -g
MAINS=extrema.cc

PLIB=RavlImageProc

LIBDEPS=RavlImageSegmentation.def

TESTEXES=testConnectedComponents.cc 

USESLIBS=RavlImageProc  

PROGLIBS=RavlImageIO RavlVideoIO RavlMathIO RavlDPDisplay.opt RavlImgIOV4L.opt RavlExtImgIO.opt RavlLibFFmpeg.opt

EXAMPLES=extrema.cc exSegmentation.cc exConnectedComponents.cc 

EHT=Ravl.API.Images.Segmentation.html

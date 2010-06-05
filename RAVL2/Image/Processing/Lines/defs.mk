# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5240 2005-12-06 17:16:50Z plugger $"
#! file="Ravl/Image/Processing/Lines/defs.mk"

PACKAGE = Ravl/Image

MAINS = doPPHT.cc doArcs.cc
#genSobelImg.cc

HEADERS= PixelMap.hh PixelMapSearch.hh PCPixel.hh PCPixelList.hh \
 PCMapping.hh PPHT.hh ArcDetector.hh

SOURCES= PixelMap.cc PixelMapSearch.cc PCPixel.cc PCPixelList.cc \
 PCMapping.cc PPHT.cc ArcDetector.cc

PLIB=RavlImageProc

LIBDEPS=RavlImageProcHT.def

USESLIBS=RavlImageProc 

PROGLIBS=RavlIO RavlOS RavlOSIO RavlImageIO RavlMathIO RavlImgIOV4L.opt RavlDPDisplay.opt RavlExtImgIO

EHT = Ravl.API.Images.Lines.html 

EXAMPLES=doPPHT.cc doArcs.cc 

TESTEXES=testLineDet.cc
#exedoPPHT.eht

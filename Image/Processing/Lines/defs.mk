# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Lines/defs.mk"

PACKAGE = Ravl/Image

MAINS = doPPHT.cc 
#genSobelImg.cc

HEADERS= PixelMap.hh PixelMapSearch.hh PCPixel.hh PCPixelList.hh \
 PCMapping.hh PPHT.hh

SOURCES= PixelMap.cc PixelMapSearch.cc PCPixel.cc PCPixelList.cc \
 PCMapping.cc PPHT.cc

PLIB=RavlImageProc

LIBDEPS=RavlImageProcHT.def

USESLIBS=RavlImageProc RavlIO RavlOS RavlOSIO RavlMath

PROGLIBS=

EHT = Ravl.Images.Lines.html 
#exedoPPHT.eht

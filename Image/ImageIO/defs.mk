# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/ImageIO/defs.mk"

PACKAGE = Ravl/Image

DESCRIPTION =  File IO methods.

HEADERS = ImgIOPNMB.hh ImgIOPNM.hh PNMFormat.hh ImgIO.hh

SOURCES = ImgIOPNM.cc PNMFormat.cc ImgIOInt.cc ImgIOByte.cc \
 ImgIOUInt16.cc ImgIOByteRGB.cc ImgIOByteYUV.cc ImgIOReal.cc \
 ImgIORealRGB.cc ImgIOByteRGBA.cc ImgIORealYUV.cc ImgIOUInt16RGB.cc \
 ImgIOByteYUVA.cc ImgCnvRGB.cc ImgCnvYUV.cc \
 ImgTypeCnv.cc ImgTypeCnv2.cc ImgTypeCnv3.cc \
 ImgIOByteYUV422.cc ImgIOByteVYU.cc

# ImgIOPixel.cc  PixelIO.cc 

MUSTLINK = RavlImgIO.cc 

PLIB = RavlImageIO

EXAMPLES = exImgIO.cc

TESTEXES = testImgIO.cc

USESLIBS = RavlCore RavlIO RavlImage

PROGLIBS = RavlOS

EHT = Ravl.Images.IO.html

AUXDIR = share/RAVL/pixmaps
AUXFILES = monkey.ppm

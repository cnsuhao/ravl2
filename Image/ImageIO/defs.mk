# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/ImageIO/defs.mk"

PACKAGE = Ravl/Image

DESCRIPTION =  File IO stuff.

HEADERS = ImgIOPNMB.hh ImgIOPNM.hh PNMFormat.hh ImgIO.hh
#  \
# ImageConv.hh 

SOURCES = ImgIOPNM.cc PNMFormat.cc ImgIOInt.cc ImgIOByte.cc \
 ImgIOUInt16.cc ImgIOByteRGB.cc ImgIOByteYUV.cc ImgIOReal.cc \
 ImgIORealRGB.cc ImgIOByteRGBA.cc ImgIORealYUV.cc ImgIOUInt16RGB.cc

#  \
# ImgTypeCnv.cc ImgTypeCnv2.cc ImgCnvRGB.cc  \
# ImgIOPixel.cc \
#   \
#  ImgIOU16RGB.cc ImgCnvRGB16.cc\
#   \
# PixelIO.cc ImgFrameCnv.cc ImgIOByteVYU.cc \
# ImgIOCompatRGB.cc ImgIOCompatYUV.cc ImgIOCompatY.cc

#NumImageCnv.cc

MUSTLINK = RavlImgIO.cc 

LIBDEPS= RavlImageIO.def

PLIB = RavlImage

EXAMPLES = 
#exImgIO.cc

TESTEXES = testImgIO.cc

USESLIBS = RavlCore RavlIO

#EHT = Image.Image_IO.eht

# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Base/defs.mk"

PACKAGE=Ravl/Image

HEADERS=ImageRectangle.hh Image.hh RGBValue.hh RGBAValue.hh YUVValue.hh \
 ByteRGBValue.hh ByteYUVValue.hh ByteRGBAValue.hh IAValue.hh ByteIAValue.hh \
 RealRGBValue.hh RealYUVValue.hh UInt16RGBValue.hh RGBcYUV.hh YUVAValue.hh \
 ByteYUVAValue.hh BGRAValue.hh ByteBGRAValue.hh YUV422Value.hh ByteYUV422Value.hh \
 ByteRGBMedian.hh RealRGBAverage.hh \
 Deinterlace.hh VYUValue.hh ByteVYUValue.hh DrawFrame.hh DrawCross.hh \
 Font.hh PSFFont.h DrawLine.hh DrawCircle.hh

SOURCES=ImageRectangle.cc Image.cc ByteRGBValue.cc ByteYUVValue.cc RealRGBValue.cc \
 RealYUVValue.cc RGBcYUV.cc Font.cc

PLIB=RavlImage

USESLIBS=RavlCore

PROGLIBS=RavlImageIO RavlOS RavlMath

MAINS=imgdiff.cc

TESTEXES=testImage.cc

EXAMPLES= exImage.cc imgdiff.cc

EHT=Ravl.Images.Pixel_Types.html

AUXDIR=share/RAVL/Fonts

AUXFILES=default8x16.psf

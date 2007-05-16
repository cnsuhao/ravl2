# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Base/defs.mk"

PACKAGE=Ravl/Image

HEADERS=ImageRectangle.hh Image.hh \
 RGBValue.hh ByteRGBValue.hh UInt16RGBValue.hh RealRGBValue.hh \
 RGBAValue.hh ByteRGBAValue.hh \
 BGRValue.hh ByteBGRValue.hh RealBGRValue.hh BGRAValue.hh ByteBGRAValue.hh \
 YUVValue.hh ByteYUVValue.hh RealYUVValue.hh \
 YUVAValue.hh ByteYUVAValue.hh \
 YUV422Value.hh ByteYUV422Value.hh \
 VYUValue.hh ByteVYUValue.hh \
 RealHSVValue.hh FixedPointHSVValue.hh \
 IAValue.hh ByteIAValue.hh \
 ByteRGBMedian.hh RealRGBAverage.hh \
 ScaleValues.hh Reflect.hh \
 RGBcYUV.hh ImageConv.hh \
 Font.hh PSFFont.h \
 DrawFrame.hh DrawCross.hh DrawMask.hh \
 DrawLine.hh DrawCircle.hh DrawPolygon.hh  DrawEllipse.hh\
 Deinterlace.hh BilinearInterpolation.hh \
 RealDVSRGBValue.hh RealDVSYUVValue.hh dvsRGBcdvsYUV422.hh 

SOURCES=ImageRectangle.cc Image.cc ByteRGBValue.cc ByteYUVValue.cc RealRGBValue.cc \
 RealYUVValue.cc RGBcYUV.cc Font.cc ImageConv.cc ImageConv2.cc ImageConv3.cc ImageConv4.cc \
 ByteRGBAValue.cc ByteVYUValue.cc ByteYUV422Value.cc ByteYUVAValue.cc \
 RealDVSRGBValue.cc RealDVSYUVValue.cc dvsRGBcdvsYUV422.cc

PLIB=RavlImage

USESLIBS=RavlCore RavlMath

PROGLIBS=RavlImageIO RavlOS RavlMath RavlDPDisplay.opt

MAINS=imgdiff.cc

TESTEXES=testImage.cc testHSVValue.cc test_imgdiff.cc

EXAMPLES= exImage.cc imgdiff.cc exDraw.cc exFont.cc

EHT=Ravl.API.Images.Pixel_Types.html Drawing.html

AUXDIR=share/RAVL/Fonts

AUXFILES=default8x16.psf

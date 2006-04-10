# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! file="Ravl/Image/ExternalImageIO/defs.mk"
#! rcsid="$Id$"
#
# This directory contains software which interfaces Ravl to external
# image IO libraries.  Edit ExtImgIO.hh to specify which libraries
# are available.

DONOT_SUPPORT=cygwin arm
DESCRIPTION = External Image IO routines... like jpeg,gif,tiff

PACKAGE=Ravl/Image

MAINS= 
#exExtImgIO.cc

PLIB = RavlExtImgIO

HEADERS = ImgIOJPeg.hh ImgIOJPegB.hh JPEGFormat.hh \
 ImgIOPNG.hh ImgIOPNGB.hh PNGFormat.hh \
 ImgIOTiff.hh ImgIOTiffB.hh TiffFormat.hh \
 ExtImgIO.hh  CompressedImageJPEG.hh

SOURCES = ImgIOJPeg.cc JPEGFormat.cc \
 ImgIOPNG.cc PNGFormat.cc \
 ImgIOTiff.cc TiffFormat.cc  CompressedImageJPEG.cc

MUSTLINK =  ExtImgIO.cc

EXAMPLES = exExtImgIO.cc exImgMemIO.cc

USESLIBS = RavlImage RavlIO LibJPEG LibPNG LibTIFF RavlImageIO

PROGLIBS = RavlDPDisplay.opt

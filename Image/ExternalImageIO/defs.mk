# $Id$
#
# This directory contains software which interfaces Ravl to external
# image IO libraries.  Edit ExtImgIO.hh to specify which libraries
# are available.


DESCRIPTION = External Image IO routines... like jpeg,gif,tiff

PACKAGE=Ravl/Image

MAINS= exExtImgIO.cc

PLIB = ExtImgIO

HEADERS = ImgIOJPeg.hh ImgIOJPegB.hh JPEGFormat.hh ImgIOPNG.hh \
 ImgIOPNGB.hh PNGFormat.hh ExtImgIO.hh ImgIOTiff.hh ImgIOTiffB.hh \
 TiffFormat.hh

SOURCES = ImgIOJPeg.cc  JPEGFormat.cc ImgIOPNG.cc  PNGFormat.cc ImgIOTiff.cc \
 TiffFormat.cc

MUSTLINK = ExtImgIO.cc

USESLIBS = DPImageIO LibJPEG LibPNG LibTIFF

PROGLIBS = Mopt

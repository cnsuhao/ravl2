# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5240 2005-12-06 17:16:50Z plugger $"
#! file="cvsspSoftware/GrabFileFormat/defs.mk"

PACKAGE = Ravl/Image

DESCRIPTION = Raw video IO classes.

HEADERS = ImgIOdvsyuv.hh ImgIOdvsrgb.hh GrabfileCommon.hh GrabfileReader.hh GrabfileReaderV1.hh GrabfileWriter.hh GrabfileWriterV1.hh LegacyGrabfileReader.hh NewGrabfileReader.hh NewGrabfileWriter.hh dvsFormat.hh Utilities.hh

SOURCES = ImgIOdvsyuv.cc ImgIOdvsrgb.cc dvsFormat.cc GrabfileReader.cc GrabfileReaderV1.cc GrabfileWriterV1.cc LegacyGrabfileReader.cc NewGrabfileReader.cc NewGrabfileWriter.cc Utilities.cc

PLIB = RavlRawVidIO

#LIBDEBS=DVSFileFormat

#EXAMPLES =

USESLIBS = RavlImageIO RavlOSIO RavlImage RavlExtImgIO

MUSTLINK=RavlRawVidIO.cc
#MAINS= readgrab.cc

EHT=RawVid.html

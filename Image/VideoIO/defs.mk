# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
###########################################
# $Id$
#! rcsid="$Id$"
#! file="Ravl/Image/VideoIO/defs.mk"

PACKAGE = Ravl/Image

DESCRIPTION = Video IO classes.

HEADERS = ImgIOCif.hh CifFormat.hh \
          ImgIOyuv.hh yuvFormat.hh syuvFormat.hh \
          ImgIOrgb.hh rgbFormat.hh rawFormat.hh \
	  MultiVidIO.hh

#          VidIO.hh SubSamp2Intl.hh SubSample.hh 

SOURCES = ImgIOCif.cc CifFormat.cc \
          ImgIOyuv.cc yuvFormat.cc syuvFormat.cc \
          ImgIOrgb.cc rgbFormat.cc rawFormat.cc \
	  MultiVidIO.cc

#              SubSamp2Intl.cc  ImgComposites.cc


MUSTLINK = RavlVidIO.cc

PLIB = RavlVideoIO

EXAMPLES = exImgSeq.cc

USESLIBS = RavlImageIO RavlOSIO RavlImage

EHT=Ravl.Images.Video.html Ravl.Images.Video.Formats.html
#PROGLIBS = Mopt

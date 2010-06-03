# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 7068 2009-01-15 10:41:26Z alexkostin $"
#! file="Ravl/Contrib/V4L/defs.mk"
#! author="Charles Galambos"

PACKAGE=Ravl/Image

SUPPORT_ONLY=linux linux64

REQUIRES=devVideo4Linux

MAINS=testV4LIO.cc

HEADERS=ImgIOV4L.hh V4LFormat.hh

SOURCES=ImgIOV4L.cc ImgIOV4L1.cc V4LFormat.cc ImgIOV4LAux.cc

LOCALHEADERS=

MUSTLINK=InitV4L.cc

PLIB=RavlImgIOV4L

USESLIBS=RavlImageIO RavlVideoIO

EHT=Ravl.API.Images.Video.Video_IO.Video4Linux.html

PROGLIBS=RavlOSIO RavlDPDisplay.opt RavlExtImgIO.opt

ANSIFLAG =


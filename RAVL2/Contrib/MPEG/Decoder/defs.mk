# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5518 2006-06-05 18:44:47Z craftit $"
#! file="Ravl/Image/VideoIO/defs.mk"

PACKAGE = Ravl/Image

DONOTSUPPORT=VCPP

DESCRIPTION = MPEG video IO classes.

HEADERS = ImgIMPEG.hh MPEGIFormat.hh
#ImgIOMpeg.hh ImgIOMpegB.hh MpegFormat.hh \
 #         ExtVidIO.hh

SOURCES = ImgIMPEG.cc MPEGIFormat.cc
#ImgIOMpeg.cc MpegFormat.cc

MUSTLINK = RAVLVidIMPEG.cc

PLIB = RavlMPEG

EXAMPLES = exMPEGI.cc

USESLIBS = RavlImageIO RavlImage RavlOSIO LibMPEG 

PROGLIBS = RavlDPDisplay.opt

AUXDIR=lib/RAVL/libdep

AUXFILES=LibMPEG.def
#USERCFLAGS = -g
#PROGLIBS = Mopt

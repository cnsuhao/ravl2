# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Contrib/DV/defs.mk"

PACKAGE = Ravl/Image

DESCRIPTION = Digital Video Classes

SUPPORT_ONLY = linux  linux64

REQUIRES = libDV

MAINS=doDvDisplay.cc 

HEADERS=ImgIODv.hh DvDecode.hh DvIFormat.hh 

SOURCES=ImgIODv.cc DvDecode.cc DvIFormat.cc DvFrameConvert.cc

PLIB=RavlDV

AUXDIR=lib/RAVL/libdep

AUXFILES= LibDV.def

USESLIBS=system RavlCore RavlImage RavlIO RavlOS RavlOSIO RavlDPDisplay glib GTK LibDV  RavlVideoIO RavlAV

PROGLIBS= RavlDPDisplay.opt RavlDPDisplay RavlDevAudio

MUSTLINK = RAVLVidIDV.cc

EHT = DV.html


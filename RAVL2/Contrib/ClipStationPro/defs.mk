# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Contrib/ClipStationPro/defs.mk"

PACKAGE=Ravl/Image

DONOT_SUPPORT=VCPP

REQUIRES = libClipStationPro

#MAINS = testCSP.cc  testCSP2.cc

EXAMPLES = exCSPControl.cc exImgIOCSP.cc

HEADERS= CSPControl.hh ImgIOCSP.hh CSPFormat.hh

SOURCES= CSPControl.cc ImgIOCSP.cc CSPFormat.cc 

MUSTLINK=ClipStationPro.cc

PLIB= CSPDriver

USESLIBS=ClipStationPro RavlCore RavlImage RavlImageIO RavlThreads  

PROGLIBS= RavlOSIO RavlImage RavlMath

AUXFILES= ClipStationPro.def

AUXDIR=lib/RAVL/libdep

EHT=Ravl.API.Images.Video.Video_IO.ClipStationPro.html

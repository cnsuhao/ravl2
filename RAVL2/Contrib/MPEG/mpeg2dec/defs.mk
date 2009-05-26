# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Contrib/MPEG/mpeg2dec/defs.mk"

PACKAGE=Ravl/Image

HEADERS=ImgIOmpeg2dec.hh MPEG2Format.hh

SOURCES=ImgIOmpeg2dec.cc MPEG2Format.cc

PLIB=RavlMPEG2

USESLIBS=RavlVideoIO RavlOS

PROGLIBS=RavlDPDisplay.opt

MUSTLINK= MustLinkMPEG2.cc



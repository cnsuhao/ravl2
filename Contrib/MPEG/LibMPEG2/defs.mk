# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU
# General Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5518 2006-06-05 18:44:47Z craftit $"
#! file="Ravl/Contrib/MPEG/LibMPEG2/defs.mk"

REQUIRES = libmpeg2

DONOT_SUPPORT=VCPP

PACKAGE = Ravl/Image

HEADERS = ImgIOMPEG2.hh LibMPEG2Format.hh MPEG2Demux.hh

SOURCES = ImgIOMPEG2.cc LibMPEG2Format.cc MPEG2Demux.cc

PLIB = RavlLibMPEG2

MUSTLINK = MustLinkLibMPEG2.cc

USESLIBS = RavlImage RavlIO LibMPEG2 RavlDPDisplay

PROGLIBS = RavlGUI

EXAMPLES = exMPEG2.cc exMPEG2Seek.cc

AUXDIR = lib/RAVL/libdep

AUXFILES = LibMPEG2.def

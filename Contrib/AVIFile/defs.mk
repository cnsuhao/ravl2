# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5518 2006-06-05 18:44:47Z craftit $"
#! file="Ravl/Contrib/AVIFile/defs.mk"

REQUIRES=avifile

DONOT_SUPPORT=VCPP

PACKAGE=Ravl/Image

HEADERS= AVIFileIO.hh AVIFileFormat.hh

SOURCES= AVIFileIO.cc AVIFileFormat.cc

PLIB=RavlAVIFile

MUSTLINK= MustLinkAVIFile.cc

USESLIBS= RavlImage RavlIO AVIFile

PROGLIBS= RavlVideoIO

EXAMPLES=testAVIFile.cc

AUXDIR=lib/RAVL/libdep

AUXFILES=AVIFile.def

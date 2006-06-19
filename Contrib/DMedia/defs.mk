# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Contrib/DMedia/defs.mk"

SUPPORT_ONLY=sgi

REQUIRES = libDMedia

PACKAGE = Ravl/DMedia

HEADERS = Server.hh NodePath.hh RingMemory.hh Video.hh RingData.hh Memory.hh \
 Buffer.hh DIVO.hh DIVOFormat.hh

SOURCES = Server.cc NodePath.cc RingMemory.cc Video.cc RingData.cc Memory.cc \
 DIVO.cc DIVOFormat.cc

MUSTLINK = RavlInitDMediaIO.cc

MAINS = exDMediaIO.cc

EXAMPLES = exDMedia.cc

PLIB = RavlDMedia

USESLIBS= RavlCore RavlOSIO  RavlOS RavlThreads SGIVL

PROGLIBS=RavlVideoIO RavlImageIO RavlDPDisplay.opt

EHT = SGI_DMedia.html

AUXDIR=libdep

AUXFILES=SGIVL.def

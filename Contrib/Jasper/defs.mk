# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2005, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

ORGANISATION=OmniPerception Ltd.

DONOT_SUPPORT=VCPP

REQUIRES=LibJasper

PACKAGE=Ravl/Image

HEADERS=ImgIOJasper.hh JasperFormat.hh CompressedImageJ2k.hh

SOURCES=ImgIOJasper.cc JasperFormat.cc CompressedImageJ2k.cc

MUSTLINK=JasperImgIO.cc

PLIB=RavlImgIOJasper

USESLIBS=RavlImage LibJasper RavlIO

PROGLIBS=RavlDPDisplay

AUXDIR=lib/RAVL/libdep

AUXFILES=LibJasper.def

TESTEXES=testImgIOJasper.cc

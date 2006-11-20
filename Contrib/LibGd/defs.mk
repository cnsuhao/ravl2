# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2005, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5178 2005-10-24 10:14:58Z plugger $"

ORGANISATION=OmniPerception Ltd.

REQUIRES=LibGd

DONOT_SUPPORT=VCPP

PACKAGE=Ravl/Image

HEADERS=Gd.hh

SOURCES=Gd.cc

PLIB=RavlImgGd

USESLIBS=RavlImage LibGd RavlIO

PROGLIBS=RavlDPDisplay

AUXDIR=lib/RAVL/libdep

AUXFILES=LibGd.def

TESTEXES=testGd.cc

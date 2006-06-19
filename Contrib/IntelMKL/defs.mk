# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 4777 2005-01-18 14:28:18Z ees1wc $"
#! file="Ravl/Contrib/IntelMKL/defs.mk"

REQUIRES=libmkl

PACKAGE=Ravl

HEADERS=IntelFFT2d.hh

SOURCES=IntelFFT2d.cc

TESTEXES= testIntelFFT2d.cc

PLIB=RavlIntelMKL

USESLIBS=IntelMKL RavlMath

AUXFILES=IntelMKL.def

AUXDIR=lib/RAVL/libdep

# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 6513 2008-01-22 11:09:32Z alexkostin $"
#! file="Ravl/Math/Signals/2D/defs.mk"

PACKAGE=Ravl

HEADERS=FFT2d.hh

SOURCES=FFT2d.cc

LIBDEPS=RavlSignal2.def

TESTEXES=testFFT2d.cc

PLIB=RavlMath

USESLIBS= RavlMath

PROGLIBS=RavlOS


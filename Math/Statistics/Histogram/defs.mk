# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/Statistics/Histogram/defs.mk"


PACKAGE=Ravl

HEADERS=Histogram.hh RealHistogram1d.hh RealHistogram2d.hh RealHistogram3d.hh Parzen.hh

SOURCES=RealHistogram1d.cc RealHistogram2d.cc RealHistogram3d.cc \
 RealHist1dBinaryIO.cc RealHist2dBinaryIO.cc RealHist3dBinaryIO.cc

PLIB=RavlMath

LIBDEPS=RavlMathHistogram.def

USESLIBS=RavlMath

TESTEXES=testHistogram.cc

EXAMPLES=exHistogram.cc

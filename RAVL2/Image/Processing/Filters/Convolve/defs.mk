# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Filters/defs.mk"

PACKAGE=Ravl/Image

MAINS=doConvolve.cc 

HEADERS= Convolve2d.hh ConvolveSeparable2d.hh ConvolveHorz2d.hh \
 ConvolveVert2d.hh GaussConvolve2d.hh GaussConvolve.hh Averaging2d.hh \
 SpatialDifference.hh SumRectangles.hh 

TESTEXES= testConvolve.cc

LIBDEPS=RavlImageConvolve.def

EXAMPLES = exGaussConvolve.cc 

PLIB=RavlImageProc

USESLIBS=RavlImageProc

PROGLIBS=RavlIO RavlImageIO RavlExtImgIO RavlOSIO RavlOptimise  RavlDPDisplay.opt



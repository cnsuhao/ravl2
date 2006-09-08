# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Filters/defs.mk"

PACKAGE=Ravl/Image

MAINS=doConvolve.cc doHomomorphicFilter.cc unDistort.cc doThinPlateWarp.cc 

HEADERS= Convolve2d.hh ConvolveSeparable2d.hh ConvolveHorz2d.hh \
 ConvolveVert2d.hh GaussConvolve2d.hh GaussConvolve.hh Averaging2d.hh \
  Correlate2d.hh NormalisedCorrelation.hh GaborFilter2d.hh GabourFilter2d.hh HomomorphicFilter.hh HistogramEqualise.hh \
 Matching.hh WarpScale.hh WarpAffine.hh WarpProjective.hh \
 PixelMixer.hh RemoveDistortion.hh WarpThinPlateSpline.hh \
 SpatialDifference.hh SpecificFilters.hh  SumRectangles.hh DeinterlaceStream.hh \
 DCT2d.hh ImageExtend.hh ImagePyramid.hh WarpMesh2d.hh

SOURCES= HomomorphicFilter.cc Correlate2d.cc Matching.cc WarpThinPlateSpline.cc \
 GaborFilter2d.cc DCT2d.cc DeinterlaceStream.cc WarpMesh2d.cc

TESTEXES= testConvolve.cc

LIBDEPS=RavlImageFilter.def

EXAMPLES = exGaussConvolve.cc exGaborFilter.cc

PLIB=RavlImageProc

USESLIBS=RavlImageProc RavlMath

PROGLIBS=RavlIO RavlImageIO RavlOSIO RavlOptimise  RavlDPDisplay.opt

EHT= Ravl.API.Images.Filtering.html Ravl.API.Images.Warping.html

AUXFILES = antialias.png
AUXDIR = share/doc/RAVL/Images

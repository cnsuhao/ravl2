# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/Statistics/MeanCovariance/defs.mk"

PACKAGE=Ravl

HEADERS= MeanVariance.hh MeanNd.hh MeanCovariance.hh Statistics.hh \
 Mean.hh FMean.hh FMeanCovariance.hh MeanCovariance2d.hh MeanCovariance3d.hh

SOURCES= MeanVariance.cc MeanNd.cc MeanCovariance.cc Statistics.cc \
 Mean.cc

TESTEXES=testMeanCovar.cc

PLIB=RavlMath

LIBDEPS=RavlMathMeanCov.def

USESLIBS=RavlMath

# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

DESCRIPTION = Pattern Recognition Toolbox

PACKAGE = Ravl/PatternRec

HEADERS=Distance.hh DistanceEuclidean.hh DistanceMax.hh DistanceCityBlock.hh \
 DistanceMahalanobis.hh

SOURCES=Distance.cc DistanceEuclidean.cc DistanceMax.cc DistanceCityBlock.cc \
 DistanceMahalanobis.cc

LIBDEPS=RavlPatternRecDistance.def

PLIB=RavlPatternRec

USESLIBS=RavlPatternRec RavlMath

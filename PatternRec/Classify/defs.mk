# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/Classify/defs.mk"

DESCRIPTION = Pattern Recognition Classifiers

PACKAGE = Ravl/PatternRec

HEADERS=ClassifyVector.hh DesignClassifyVector.hh \
 DesignDiscriminantFunction.hh DesignKNearestNeighbour.hh \
 ClassifyKNearestNeighbour.hh ClassifyAverageNearestNeighbour.hh \
 ClassifyDiscriminantFunction.hh

SOURCES=ClassifyVector.cc DesignClassifyVector.cc \
 DesignDiscriminantFunction.cc DesignKNearestNeighbour.cc \
 ClassifyKNearestNeighbour.cc ClassifyAverageNearestNeighbour.cc \
 ClassifyDiscriminantFunction.cc

PLIB = RavlPatternRec

TESTEXES=testClassify.cc

LIBDEPS = RavlPatternRecClassify.def 

USESLIBS=RavlPatternRec

EHT = Ravl.Pattern_Recognition.Classify.html

# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

DESCRIPTION = Pattern Recognition Classifiers

PACKAGE = Ravl/PatternRec

HEADERS=ClassifyVector.hh KNearestNeighbour.hh AverageNearestNeighbour.hh

SOURCES=ClassifyVector.cc KNearestNeighbour.cc AverageNearestNeighbour.cc

PLIB = RavlPatternRec

TESTEXES=testClassify.cc

LIBDEPS = RavlPatternRecClassify.def 

USESLIBS=RavlPatternRec

EHT = Ravl.Pattern_Recognition.Classify.html
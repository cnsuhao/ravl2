# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/Classifier/defs.mk"

DESCRIPTION = Pattern Recognition Classifiers

PACKAGE = Ravl/PatternRec

HEADERS=Classifier.hh DesignClassifierSupervised.hh  DesignClassifierUnsupervised.hh \
 DesignDiscriminantFunction.hh DesignKNearestNeighbour.hh \
 ClassifierKNearestNeighbour.hh ClassifierNearestNeighbour.hh ClassifierAverageNearestNeighbour.hh \
 ClassifierDiscriminantFunction.hh DesignKMeans.hh DesignMeanShiftCluster.hh

SOURCES=Classifier.cc DesignClassifierSupervised.cc DesignClassifierUnsupervised.cc \
 DesignDiscriminantFunction.cc DesignKNearestNeighbour.cc \
 ClassifierKNearestNeighbour.cc ClassifierNearestNeighbour.cc ClassifierAverageNearestNeighbour.cc \
 ClassifierDiscriminantFunction.cc DesignKMeans.cc DesignMeanShiftCluster.cc

PLIB = RavlPatternRec

TESTEXES=testClassifier.cc

LIBDEPS = RavlPatternRecClassifier.def 

USESLIBS=RavlPatternRec

EHT = Ravl.Pattern_Recognition.Classify.html

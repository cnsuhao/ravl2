# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/Cluster/defs.mk"

DESCRIPTION = Pattern Recognition Classifiers

PACKAGE=Ravl/PatternRec

HEADERS=Classifier.hh DesignClassifierUnsupervised.hh ClassifierNearestNeighbour.hh \
 DesignKMeans.hh DesignMeanShiftCluster.hh DesignCluster.hh

SOURCES=Classifier.cc DesignClassifierUnsupervised.cc ClassifierNearestNeighbour.cc \
 DesignKMeans.cc DesignMeanShiftCluster.cc DesignCluster.cc

PLIB=RavlPatternRec

LIBDEPS=RavlPatternRecCluster.def

USESLIBS=RavlPatternRec

EXAMPLES=exKMeansCluster.cc

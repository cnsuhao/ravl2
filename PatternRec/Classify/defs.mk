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

HEADERS= DesignClassifierSupervised.hh  \
 DesignDiscriminantFunction.hh DesignKNearestNeighbour.hh \
 ClassifierKNearestNeighbour.hh ClassifierAverageNearestNeighbour.hh \
 ClassifierDiscriminantFunction.hh \
 ClassifierGaussianMixture.hh DesignClassifierGaussianMixture.hh \
 ClassifierPreprocess.hh ClassifierFunc1Threshold.hh \
 ClassifierWeakLinear.hh ClassifierLinearCombination.hh \
 DesignWeakLinear.hh \
ClassifierBayesNormalLinear.hh DesignBayesNormalLinear.hh DesignBayesNormalQuadratic.hh ClassifierBayesNormalQuadratic.hh ClassifierNeuralNetwork.hh DesignClassifierNeuralNetwork.hh

SOURCES= DesignClassifierSupervised.cc \
 DesignDiscriminantFunction.cc DesignKNearestNeighbour.cc \
 ClassifierKNearestNeighbour.cc ClassifierAverageNearestNeighbour.cc \
 ClassifierDiscriminantFunction.cc ClassifierGaussianMixture.cc DesignClassifierGaussianMixture.cc \
 ClassifierPreprocess.cc ClassifierFunc1Threshold.cc \
 ClassifierWeakLinear.cc ClassifierLinearCombination.cc \
 DesignWeakLinear.cc \
ClassifierBayesNormalLinear.cc DesignBayesNormalLinear.cc DesignBayesNormalQuadratic.cc ClassifierBayesNormalQuadratic.cc ClassifierNeuralNetwork.cc DesignClassifierNeuralNetwork.cc 

PLIB = RavlPatternRec

TESTEXES=testClassifier.cc exNeuralNetwork.cc

LIBDEPS = RavlPatternRecClassifier.def 

USESLIBS=RavlCore RavlOS RavlIO RavlMath RavlPatternRec fann

EHT = Ravl.API.Pattern_Recognition.Classifier.html

EXAMPLES=  exKNearestNeighbour.cc


DESCRIPTION = Pattern Recognition Classifiers

PACKAGE=Ravl/PatternRec

HEADERS=Classifier.hh DesignClassifierUnsupervised.hh ClassifierNearestNeighbour.hh \
 DesignKMeans.hh DesignCluster.hh

SOURCES=Classifier.cc DesignClassifierUnsupervised.cc ClassifierNearestNeighbour.cc \
 DesignKMeans.cc DesignCluster.cc

PLIB=RavlPatternRec

LIBDEPS=RavlPatternRecCluster.def

USESLIBS=RavlPatternRec

EXAMPLES=exKMeansCluster.cc

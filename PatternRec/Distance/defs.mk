
DESCRIPTION = Pattern Recognition Toolbox

PACKAGE = Ravl/PatternRec

HEADERS=Distance.hh DistanceEuclidean.hh DistanceMax.hh DistanceCityBlock.hh \
 DistanceMahalanobis.hh

SOURCES=Distance.cc DistanceEuclidean.cc DistanceMax.cc DistanceCityBlock.cc \
 DistanceMahalanobis.cc

LIBDEPS=RavlPatternRecDistance.def

PLIB=RavlPatternRec

USESLIBS=RavlPatternRec RavlMath

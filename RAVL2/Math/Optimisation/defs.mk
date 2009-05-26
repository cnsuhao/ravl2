# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/Optimisation/defs.mk"

PACKAGE=Ravl

NESTED= DocLevenbergMarquardt.r

PLIB = RavlOptimise

SOURCES = ObsVector.cc ObsVectorBiGaussian.cc ObsVectorPoint2dPair.cc \
	  StateVector.cc StateVectorLine2d.cc StateVectorQuadratic.cc \
	  StateVectorHomog2d.cc StateVectorRot3d.cc \
	  Observation.cc ObservationExplicit.cc ObservationQuadraticPoint.cc \
	  ObservationImplicit.cc ObservationLine2dPoint.cc \
	  ObservationImpQuadraticPoint.cc \
	  ObservationHomog2dPoint.cc ObservationImpHomog2dPoint.cc \
	  StoredState.cc LevenbergMarquardt.cc \
	  Ransac.cc ObservationManager.cc FitToSample.cc EvaluateSolution.cc \
	  EvaluateNumInliers.cc EvaluateLikelihood.cc \
	  FitLine2dPoints.cc FitQuadraticPoints.cc FitHomog2dPoints.cc \
	  ObservationAffine2dPoint.cc StateVectorAffine2d.cc FitAffine2dPoints.cc \
	  OptimiseQuadraticCurve.cc OptimiseOrthogonalRegression.cc \
	  Optimise2dHomography.cc Optimise2dAffineHomography.cc

HEADERS = ObsVector.hh ObsVectorBiGaussian.hh ObsVectorPoint2dPair.hh \
	  StateVector.hh StateVectorLine2d.hh StateVectorQuadratic.hh \
	  StateVectorHomog2d.hh StateVectorRot3d.hh \
	  Observation.hh ObservationExplicit.hh ObservationQuadraticPoint.hh \
	  ObservationImplicit.hh ObservationLine2dPoint.hh \
	  ObservationImpQuadraticPoint.hh \
	  ObservationHomog2dPoint.hh ObservationImpHomog2dPoint.hh \
	  StoredState.hh LevenbergMarquardt.hh \
	  Ransac.hh ObservationManager.hh FitToSample.hh EvaluateSolution.hh \
	  EvaluateNumInliers.hh EvaluateLikelihood.hh \
	  FitLine2dPoints.hh FitQuadraticPoints.hh FitHomog2dPoints.hh  \
	  ObservationAffine2dPoint.hh StateVectorAffine2d.hh FitAffine2dPoints.hh \
	  OptimiseQuadraticCurve.hh OptimiseOrthogonalRegression.hh \
	  Optimise2dHomography.hh Optimise2dAffineHomography.hh \
	  Point2dObs.hh Point2dPairObs.hh

MAINS=

EHT=Ravl.API.Math.Optimisation.html Ravl.API.Math.Optimisation.Examples.html

TESTEXES= OrthogonalRegressionTest.cc QuadraticFitTest.cc Homography2dFitTest.cc Affine2dFitTest.cc

EXAMPLES= OrthogonalRegressionTest.cc QuadraticFitTest.cc Homography2dFitTest.cc

USESLIBS=RavlCore RavlMath

PROGLIBS=

HTML = Optimisation.pdf

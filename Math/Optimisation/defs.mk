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
	  FitLine2dPoints.cc FitQuadraticPoints.cc FitHomog2dPoints.cc

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
	  FitLine2dPoints.hh FitQuadraticPoints.hh FitHomog2dPoints.hh

MAINS=OrthogonalRegressionTest.cc QuadraticFitTest.cc Homography2dFitTest.cc

EHT=Ravl.Math.Optimisation.html Ravl.Math.Optimisation.Examples.html

TESTEXES= OrthogonalRegressionTest.cc QuadraticFitTest.cc Homography2dFitTest.cc

EXAMPLES= OrthogonalRegressionTest.cc QuadraticFitTest.cc Homography2dFitTest.cc

USESLIBS=RavlCore RavlMath



#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlOptimise
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlOptimise
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/ObsVector.obj $(OPTOBJDIR)/ObsVectorBiGaussian.obj $(OPTOBJDIR)/ObsVectorPoint2dPair.obj $(OPTOBJDIR)/StateVector.obj $(OPTOBJDIR)/StateVectorLine2d.obj $(OPTOBJDIR)/StateVectorQuadratic.obj $(OPTOBJDIR)/StateVectorHomog2d.obj $(OPTOBJDIR)/StateVectorRot3d.obj $(OPTOBJDIR)/Observation.obj $(OPTOBJDIR)/ObservationExplicit.obj $(OPTOBJDIR)/ObservationQuadraticPoint.obj $(OPTOBJDIR)/ObservationImplicit.obj $(OPTOBJDIR)/ObservationLine2dPoint.obj $(OPTOBJDIR)/ObservationImpQuadraticPoint.obj $(OPTOBJDIR)/ObservationHomog2dPoint.obj $(OPTOBJDIR)/ObservationImpHomog2dPoint.obj $(OPTOBJDIR)/StoredState.obj $(OPTOBJDIR)/LevenbergMarquardt.obj $(OPTOBJDIR)/Ransac.obj $(OPTOBJDIR)/ObservationManager.obj $(OPTOBJDIR)/FitToSample.obj $(OPTOBJDIR)/EvaluateSolution.obj $(OPTOBJDIR)/EvaluateNumInliers.obj $(OPTOBJDIR)/EvaluateLikelihood.obj $(OPTOBJDIR)/FitLine2dPoints.obj $(OPTOBJDIR)/FitQuadraticPoints.obj $(OPTOBJDIR)/FitHomog2dPoints.obj $(OPTOBJDIR)/ObservationAffine2dPoint.obj $(OPTOBJDIR)/StateVectorAffine2d.obj $(OPTOBJDIR)/FitAffine2dPoints.obj $(OPTOBJDIR)/OptimiseQuadraticCurve.obj $(OPTOBJDIR)/OptimiseOrthogonalRegression.obj $(OPTOBJDIR)/Optimise2dHomography.obj $(OPTOBJDIR)/Optimise2dAffineHomography.obj
	@echo -- making $(OPTLIBDIR)/RavlOptimise.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlOptimise.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/ObsVector.obj $(DEBUGOBJDIR)/ObsVectorBiGaussian.obj $(DEBUGOBJDIR)/ObsVectorPoint2dPair.obj $(DEBUGOBJDIR)/StateVector.obj $(DEBUGOBJDIR)/StateVectorLine2d.obj $(DEBUGOBJDIR)/StateVectorQuadratic.obj $(DEBUGOBJDIR)/StateVectorHomog2d.obj $(DEBUGOBJDIR)/StateVectorRot3d.obj $(DEBUGOBJDIR)/Observation.obj $(DEBUGOBJDIR)/ObservationExplicit.obj $(DEBUGOBJDIR)/ObservationQuadraticPoint.obj $(DEBUGOBJDIR)/ObservationImplicit.obj $(DEBUGOBJDIR)/ObservationLine2dPoint.obj $(DEBUGOBJDIR)/ObservationImpQuadraticPoint.obj $(DEBUGOBJDIR)/ObservationHomog2dPoint.obj $(DEBUGOBJDIR)/ObservationImpHomog2dPoint.obj $(DEBUGOBJDIR)/StoredState.obj $(DEBUGOBJDIR)/LevenbergMarquardt.obj $(DEBUGOBJDIR)/Ransac.obj $(DEBUGOBJDIR)/ObservationManager.obj $(DEBUGOBJDIR)/FitToSample.obj $(DEBUGOBJDIR)/EvaluateSolution.obj $(DEBUGOBJDIR)/EvaluateNumInliers.obj $(DEBUGOBJDIR)/EvaluateLikelihood.obj $(DEBUGOBJDIR)/FitLine2dPoints.obj $(DEBUGOBJDIR)/FitQuadraticPoints.obj $(DEBUGOBJDIR)/FitHomog2dPoints.obj $(DEBUGOBJDIR)/ObservationAffine2dPoint.obj $(DEBUGOBJDIR)/StateVectorAffine2d.obj $(DEBUGOBJDIR)/FitAffine2dPoints.obj $(DEBUGOBJDIR)/OptimiseQuadraticCurve.obj $(DEBUGOBJDIR)/OptimiseOrthogonalRegression.obj $(DEBUGOBJDIR)/Optimise2dHomography.obj $(DEBUGOBJDIR)/Optimise2dAffineHomography.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlOptimise.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlOptimise.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlOptimise
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ObsVector.obj: .././Math/Optimisation/ObsVector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObsVector.obj .././Math/Optimisation/ObsVector.cc

$(DEBUGOBJDIR)/ObsVector.obj: .././Math/Optimisation/ObsVector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObsVector.obj .././Math/Optimisation/ObsVector.cc

$(OPTOBJDIR)/ObsVectorBiGaussian.obj: .././Math/Optimisation/ObsVectorBiGaussian.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObsVectorBiGaussian.obj .././Math/Optimisation/ObsVectorBiGaussian.cc

$(DEBUGOBJDIR)/ObsVectorBiGaussian.obj: .././Math/Optimisation/ObsVectorBiGaussian.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObsVectorBiGaussian.obj .././Math/Optimisation/ObsVectorBiGaussian.cc

$(OPTOBJDIR)/ObsVectorPoint2dPair.obj: .././Math/Optimisation/ObsVectorPoint2dPair.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObsVectorPoint2dPair.obj .././Math/Optimisation/ObsVectorPoint2dPair.cc

$(DEBUGOBJDIR)/ObsVectorPoint2dPair.obj: .././Math/Optimisation/ObsVectorPoint2dPair.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObsVectorPoint2dPair.obj .././Math/Optimisation/ObsVectorPoint2dPair.cc

$(OPTOBJDIR)/StateVector.obj: .././Math/Optimisation/StateVector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateVector.obj .././Math/Optimisation/StateVector.cc

$(DEBUGOBJDIR)/StateVector.obj: .././Math/Optimisation/StateVector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateVector.obj .././Math/Optimisation/StateVector.cc

$(OPTOBJDIR)/StateVectorLine2d.obj: .././Math/Optimisation/StateVectorLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateVectorLine2d.obj .././Math/Optimisation/StateVectorLine2d.cc

$(DEBUGOBJDIR)/StateVectorLine2d.obj: .././Math/Optimisation/StateVectorLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateVectorLine2d.obj .././Math/Optimisation/StateVectorLine2d.cc

$(OPTOBJDIR)/StateVectorQuadratic.obj: .././Math/Optimisation/StateVectorQuadratic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateVectorQuadratic.obj .././Math/Optimisation/StateVectorQuadratic.cc

$(DEBUGOBJDIR)/StateVectorQuadratic.obj: .././Math/Optimisation/StateVectorQuadratic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateVectorQuadratic.obj .././Math/Optimisation/StateVectorQuadratic.cc

$(OPTOBJDIR)/StateVectorHomog2d.obj: .././Math/Optimisation/StateVectorHomog2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateVectorHomog2d.obj .././Math/Optimisation/StateVectorHomog2d.cc

$(DEBUGOBJDIR)/StateVectorHomog2d.obj: .././Math/Optimisation/StateVectorHomog2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateVectorHomog2d.obj .././Math/Optimisation/StateVectorHomog2d.cc

$(OPTOBJDIR)/StateVectorRot3d.obj: .././Math/Optimisation/StateVectorRot3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateVectorRot3d.obj .././Math/Optimisation/StateVectorRot3d.cc

$(DEBUGOBJDIR)/StateVectorRot3d.obj: .././Math/Optimisation/StateVectorRot3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateVectorRot3d.obj .././Math/Optimisation/StateVectorRot3d.cc

$(OPTOBJDIR)/Observation.obj: .././Math/Optimisation/Observation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Observation.obj .././Math/Optimisation/Observation.cc

$(DEBUGOBJDIR)/Observation.obj: .././Math/Optimisation/Observation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Observation.obj .././Math/Optimisation/Observation.cc

$(OPTOBJDIR)/ObservationExplicit.obj: .././Math/Optimisation/ObservationExplicit.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObservationExplicit.obj .././Math/Optimisation/ObservationExplicit.cc

$(DEBUGOBJDIR)/ObservationExplicit.obj: .././Math/Optimisation/ObservationExplicit.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObservationExplicit.obj .././Math/Optimisation/ObservationExplicit.cc

$(OPTOBJDIR)/ObservationQuadraticPoint.obj: .././Math/Optimisation/ObservationQuadraticPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObservationQuadraticPoint.obj .././Math/Optimisation/ObservationQuadraticPoint.cc

$(DEBUGOBJDIR)/ObservationQuadraticPoint.obj: .././Math/Optimisation/ObservationQuadraticPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObservationQuadraticPoint.obj .././Math/Optimisation/ObservationQuadraticPoint.cc

$(OPTOBJDIR)/ObservationImplicit.obj: .././Math/Optimisation/ObservationImplicit.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObservationImplicit.obj .././Math/Optimisation/ObservationImplicit.cc

$(DEBUGOBJDIR)/ObservationImplicit.obj: .././Math/Optimisation/ObservationImplicit.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObservationImplicit.obj .././Math/Optimisation/ObservationImplicit.cc

$(OPTOBJDIR)/ObservationLine2dPoint.obj: .././Math/Optimisation/ObservationLine2dPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObservationLine2dPoint.obj .././Math/Optimisation/ObservationLine2dPoint.cc

$(DEBUGOBJDIR)/ObservationLine2dPoint.obj: .././Math/Optimisation/ObservationLine2dPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObservationLine2dPoint.obj .././Math/Optimisation/ObservationLine2dPoint.cc

$(OPTOBJDIR)/ObservationImpQuadraticPoint.obj: .././Math/Optimisation/ObservationImpQuadraticPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObservationImpQuadraticPoint.obj .././Math/Optimisation/ObservationImpQuadraticPoint.cc

$(DEBUGOBJDIR)/ObservationImpQuadraticPoint.obj: .././Math/Optimisation/ObservationImpQuadraticPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObservationImpQuadraticPoint.obj .././Math/Optimisation/ObservationImpQuadraticPoint.cc

$(OPTOBJDIR)/ObservationHomog2dPoint.obj: .././Math/Optimisation/ObservationHomog2dPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObservationHomog2dPoint.obj .././Math/Optimisation/ObservationHomog2dPoint.cc

$(DEBUGOBJDIR)/ObservationHomog2dPoint.obj: .././Math/Optimisation/ObservationHomog2dPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObservationHomog2dPoint.obj .././Math/Optimisation/ObservationHomog2dPoint.cc

$(OPTOBJDIR)/ObservationImpHomog2dPoint.obj: .././Math/Optimisation/ObservationImpHomog2dPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObservationImpHomog2dPoint.obj .././Math/Optimisation/ObservationImpHomog2dPoint.cc

$(DEBUGOBJDIR)/ObservationImpHomog2dPoint.obj: .././Math/Optimisation/ObservationImpHomog2dPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObservationImpHomog2dPoint.obj .././Math/Optimisation/ObservationImpHomog2dPoint.cc

$(OPTOBJDIR)/StoredState.obj: .././Math/Optimisation/StoredState.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StoredState.obj .././Math/Optimisation/StoredState.cc

$(DEBUGOBJDIR)/StoredState.obj: .././Math/Optimisation/StoredState.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StoredState.obj .././Math/Optimisation/StoredState.cc

$(OPTOBJDIR)/LevenbergMarquardt.obj: .././Math/Optimisation/LevenbergMarquardt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LevenbergMarquardt.obj .././Math/Optimisation/LevenbergMarquardt.cc

$(DEBUGOBJDIR)/LevenbergMarquardt.obj: .././Math/Optimisation/LevenbergMarquardt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LevenbergMarquardt.obj .././Math/Optimisation/LevenbergMarquardt.cc

$(OPTOBJDIR)/Ransac.obj: .././Math/Optimisation/Ransac.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Ransac.obj .././Math/Optimisation/Ransac.cc

$(DEBUGOBJDIR)/Ransac.obj: .././Math/Optimisation/Ransac.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Ransac.obj .././Math/Optimisation/Ransac.cc

$(OPTOBJDIR)/ObservationManager.obj: .././Math/Optimisation/ObservationManager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObservationManager.obj .././Math/Optimisation/ObservationManager.cc

$(DEBUGOBJDIR)/ObservationManager.obj: .././Math/Optimisation/ObservationManager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObservationManager.obj .././Math/Optimisation/ObservationManager.cc

$(OPTOBJDIR)/FitToSample.obj: .././Math/Optimisation/FitToSample.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitToSample.obj .././Math/Optimisation/FitToSample.cc

$(DEBUGOBJDIR)/FitToSample.obj: .././Math/Optimisation/FitToSample.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitToSample.obj .././Math/Optimisation/FitToSample.cc

$(OPTOBJDIR)/EvaluateSolution.obj: .././Math/Optimisation/EvaluateSolution.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EvaluateSolution.obj .././Math/Optimisation/EvaluateSolution.cc

$(DEBUGOBJDIR)/EvaluateSolution.obj: .././Math/Optimisation/EvaluateSolution.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EvaluateSolution.obj .././Math/Optimisation/EvaluateSolution.cc

$(OPTOBJDIR)/EvaluateNumInliers.obj: .././Math/Optimisation/EvaluateNumInliers.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EvaluateNumInliers.obj .././Math/Optimisation/EvaluateNumInliers.cc

$(DEBUGOBJDIR)/EvaluateNumInliers.obj: .././Math/Optimisation/EvaluateNumInliers.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EvaluateNumInliers.obj .././Math/Optimisation/EvaluateNumInliers.cc

$(OPTOBJDIR)/EvaluateLikelihood.obj: .././Math/Optimisation/EvaluateLikelihood.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EvaluateLikelihood.obj .././Math/Optimisation/EvaluateLikelihood.cc

$(DEBUGOBJDIR)/EvaluateLikelihood.obj: .././Math/Optimisation/EvaluateLikelihood.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EvaluateLikelihood.obj .././Math/Optimisation/EvaluateLikelihood.cc

$(OPTOBJDIR)/FitLine2dPoints.obj: .././Math/Optimisation/FitLine2dPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitLine2dPoints.obj .././Math/Optimisation/FitLine2dPoints.cc

$(DEBUGOBJDIR)/FitLine2dPoints.obj: .././Math/Optimisation/FitLine2dPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitLine2dPoints.obj .././Math/Optimisation/FitLine2dPoints.cc

$(OPTOBJDIR)/FitQuadraticPoints.obj: .././Math/Optimisation/FitQuadraticPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitQuadraticPoints.obj .././Math/Optimisation/FitQuadraticPoints.cc

$(DEBUGOBJDIR)/FitQuadraticPoints.obj: .././Math/Optimisation/FitQuadraticPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitQuadraticPoints.obj .././Math/Optimisation/FitQuadraticPoints.cc

$(OPTOBJDIR)/FitHomog2dPoints.obj: .././Math/Optimisation/FitHomog2dPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitHomog2dPoints.obj .././Math/Optimisation/FitHomog2dPoints.cc

$(DEBUGOBJDIR)/FitHomog2dPoints.obj: .././Math/Optimisation/FitHomog2dPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitHomog2dPoints.obj .././Math/Optimisation/FitHomog2dPoints.cc

$(OPTOBJDIR)/ObservationAffine2dPoint.obj: .././Math/Optimisation/ObservationAffine2dPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ObservationAffine2dPoint.obj .././Math/Optimisation/ObservationAffine2dPoint.cc

$(DEBUGOBJDIR)/ObservationAffine2dPoint.obj: .././Math/Optimisation/ObservationAffine2dPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ObservationAffine2dPoint.obj .././Math/Optimisation/ObservationAffine2dPoint.cc

$(OPTOBJDIR)/StateVectorAffine2d.obj: .././Math/Optimisation/StateVectorAffine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateVectorAffine2d.obj .././Math/Optimisation/StateVectorAffine2d.cc

$(DEBUGOBJDIR)/StateVectorAffine2d.obj: .././Math/Optimisation/StateVectorAffine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateVectorAffine2d.obj .././Math/Optimisation/StateVectorAffine2d.cc

$(OPTOBJDIR)/FitAffine2dPoints.obj: .././Math/Optimisation/FitAffine2dPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitAffine2dPoints.obj .././Math/Optimisation/FitAffine2dPoints.cc

$(DEBUGOBJDIR)/FitAffine2dPoints.obj: .././Math/Optimisation/FitAffine2dPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitAffine2dPoints.obj .././Math/Optimisation/FitAffine2dPoints.cc

$(OPTOBJDIR)/OptimiseQuadraticCurve.obj: .././Math/Optimisation/OptimiseQuadraticCurve.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimiseQuadraticCurve.obj .././Math/Optimisation/OptimiseQuadraticCurve.cc

$(DEBUGOBJDIR)/OptimiseQuadraticCurve.obj: .././Math/Optimisation/OptimiseQuadraticCurve.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimiseQuadraticCurve.obj .././Math/Optimisation/OptimiseQuadraticCurve.cc

$(OPTOBJDIR)/OptimiseOrthogonalRegression.obj: .././Math/Optimisation/OptimiseOrthogonalRegression.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimiseOrthogonalRegression.obj .././Math/Optimisation/OptimiseOrthogonalRegression.cc

$(DEBUGOBJDIR)/OptimiseOrthogonalRegression.obj: .././Math/Optimisation/OptimiseOrthogonalRegression.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimiseOrthogonalRegression.obj .././Math/Optimisation/OptimiseOrthogonalRegression.cc

$(OPTOBJDIR)/Optimise2dHomography.obj: .././Math/Optimisation/Optimise2dHomography.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Optimise2dHomography.obj .././Math/Optimisation/Optimise2dHomography.cc

$(DEBUGOBJDIR)/Optimise2dHomography.obj: .././Math/Optimisation/Optimise2dHomography.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Optimise2dHomography.obj .././Math/Optimisation/Optimise2dHomography.cc

$(OPTOBJDIR)/Optimise2dAffineHomography.obj: .././Math/Optimisation/Optimise2dAffineHomography.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Optimise2dAffineHomography.obj .././Math/Optimisation/Optimise2dAffineHomography.cc

$(DEBUGOBJDIR)/Optimise2dAffineHomography.obj: .././Math/Optimisation/Optimise2dAffineHomography.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Optimise2dAffineHomography.obj .././Math/Optimisation/Optimise2dAffineHomography.cc



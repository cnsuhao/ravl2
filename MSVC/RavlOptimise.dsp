# Microsoft Developer Studio Project File - Name="RavlOptimise" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlOptimise - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlOptimise.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlOptimise.mak" CFG="RavlOptimise - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlOptimise - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlOptimise - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlOptimise"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlOptimise"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /MDd  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "_DEBUG" /D "VISUAL_CPP" /D "_LIB" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /GZ /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "RavlOptimise - Win32 Release"
# Name "RavlOptimise - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Math\Optimisation\ObsVector.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObsVectorBiGaussian.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObsVectorPoint2dPair.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVector.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorLine2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorQuadratic.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorHomog2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorRot3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Observation.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationExplicit.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationQuadraticPoint.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationImplicit.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationLine2dPoint.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationImpQuadraticPoint.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationHomog2dPoint.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationImpHomog2dPoint.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StoredState.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\LevenbergMarquardt.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Ransac.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationManager.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitToSample.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\EvaluateSolution.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\EvaluateNumInliers.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\EvaluateLikelihood.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitLine2dPoints.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitQuadraticPoints.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitHomog2dPoints.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationAffine2dPoint.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorAffine2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitAffine2dPoints.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\OptimiseQuadraticCurve.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\OptimiseOrthogonalRegression.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Optimise2dHomography.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Optimise2dAffineHomography.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Math\Optimisation\ObsVector.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObsVector.hh

"C:\Build\inc\Ravl\ObsVector.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObsVector.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObsVector.hh

"C:\Build\inc\Ravl\ObsVector.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObsVector.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObsVectorBiGaussian.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObsVectorBiGaussian.hh

"C:\Build\inc\Ravl\ObsVectorBiGaussian.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObsVectorBiGaussian.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObsVectorBiGaussian.hh

"C:\Build\inc\Ravl\ObsVectorBiGaussian.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObsVectorBiGaussian.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObsVectorPoint2dPair.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObsVectorPoint2dPair.hh

"C:\Build\inc\Ravl\ObsVectorPoint2dPair.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObsVectorPoint2dPair.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObsVectorPoint2dPair.hh

"C:\Build\inc\Ravl\ObsVectorPoint2dPair.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObsVectorPoint2dPair.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVector.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header StateVector.hh

"C:\Build\inc\Ravl\StateVector.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVector.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header StateVector.hh

"C:\Build\inc\Ravl\StateVector.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVector.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorLine2d.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header StateVectorLine2d.hh

"C:\Build\inc\Ravl\StateVectorLine2d.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorLine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header StateVectorLine2d.hh

"C:\Build\inc\Ravl\StateVectorLine2d.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorLine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorQuadratic.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header StateVectorQuadratic.hh

"C:\Build\inc\Ravl\StateVectorQuadratic.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorQuadratic.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header StateVectorQuadratic.hh

"C:\Build\inc\Ravl\StateVectorQuadratic.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorQuadratic.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorHomog2d.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header StateVectorHomog2d.hh

"C:\Build\inc\Ravl\StateVectorHomog2d.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorHomog2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header StateVectorHomog2d.hh

"C:\Build\inc\Ravl\StateVectorHomog2d.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorHomog2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorRot3d.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header StateVectorRot3d.hh

"C:\Build\inc\Ravl\StateVectorRot3d.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorRot3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header StateVectorRot3d.hh

"C:\Build\inc\Ravl\StateVectorRot3d.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorRot3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Observation.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header Observation.hh

"C:\Build\inc\Ravl\Observation.hh" :  "" ""
	copy ..\.\Math\Optimisation\Observation.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header Observation.hh

"C:\Build\inc\Ravl\Observation.hh" :  "" ""
	copy ..\.\Math\Optimisation\Observation.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationExplicit.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObservationExplicit.hh

"C:\Build\inc\Ravl\ObservationExplicit.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationExplicit.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObservationExplicit.hh

"C:\Build\inc\Ravl\ObservationExplicit.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationExplicit.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationQuadraticPoint.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObservationQuadraticPoint.hh

"C:\Build\inc\Ravl\ObservationQuadraticPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationQuadraticPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObservationQuadraticPoint.hh

"C:\Build\inc\Ravl\ObservationQuadraticPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationQuadraticPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationImplicit.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObservationImplicit.hh

"C:\Build\inc\Ravl\ObservationImplicit.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationImplicit.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObservationImplicit.hh

"C:\Build\inc\Ravl\ObservationImplicit.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationImplicit.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationLine2dPoint.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObservationLine2dPoint.hh

"C:\Build\inc\Ravl\ObservationLine2dPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationLine2dPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObservationLine2dPoint.hh

"C:\Build\inc\Ravl\ObservationLine2dPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationLine2dPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationImpQuadraticPoint.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObservationImpQuadraticPoint.hh

"C:\Build\inc\Ravl\ObservationImpQuadraticPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationImpQuadraticPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObservationImpQuadraticPoint.hh

"C:\Build\inc\Ravl\ObservationImpQuadraticPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationImpQuadraticPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationHomog2dPoint.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObservationHomog2dPoint.hh

"C:\Build\inc\Ravl\ObservationHomog2dPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationHomog2dPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObservationHomog2dPoint.hh

"C:\Build\inc\Ravl\ObservationHomog2dPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationHomog2dPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationImpHomog2dPoint.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObservationImpHomog2dPoint.hh

"C:\Build\inc\Ravl\ObservationImpHomog2dPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationImpHomog2dPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObservationImpHomog2dPoint.hh

"C:\Build\inc\Ravl\ObservationImpHomog2dPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationImpHomog2dPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StoredState.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header StoredState.hh

"C:\Build\inc\Ravl\StoredState.hh" :  "" ""
	copy ..\.\Math\Optimisation\StoredState.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header StoredState.hh

"C:\Build\inc\Ravl\StoredState.hh" :  "" ""
	copy ..\.\Math\Optimisation\StoredState.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\LevenbergMarquardt.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header LevenbergMarquardt.hh

"C:\Build\inc\Ravl\LevenbergMarquardt.hh" :  "" ""
	copy ..\.\Math\Optimisation\LevenbergMarquardt.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header LevenbergMarquardt.hh

"C:\Build\inc\Ravl\LevenbergMarquardt.hh" :  "" ""
	copy ..\.\Math\Optimisation\LevenbergMarquardt.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Ransac.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header Ransac.hh

"C:\Build\inc\Ravl\Ransac.hh" :  "" ""
	copy ..\.\Math\Optimisation\Ransac.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header Ransac.hh

"C:\Build\inc\Ravl\Ransac.hh" :  "" ""
	copy ..\.\Math\Optimisation\Ransac.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationManager.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObservationManager.hh

"C:\Build\inc\Ravl\ObservationManager.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationManager.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObservationManager.hh

"C:\Build\inc\Ravl\ObservationManager.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationManager.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitToSample.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header FitToSample.hh

"C:\Build\inc\Ravl\FitToSample.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitToSample.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header FitToSample.hh

"C:\Build\inc\Ravl\FitToSample.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitToSample.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\EvaluateSolution.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header EvaluateSolution.hh

"C:\Build\inc\Ravl\EvaluateSolution.hh" :  "" ""
	copy ..\.\Math\Optimisation\EvaluateSolution.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header EvaluateSolution.hh

"C:\Build\inc\Ravl\EvaluateSolution.hh" :  "" ""
	copy ..\.\Math\Optimisation\EvaluateSolution.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\EvaluateNumInliers.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header EvaluateNumInliers.hh

"C:\Build\inc\Ravl\EvaluateNumInliers.hh" :  "" ""
	copy ..\.\Math\Optimisation\EvaluateNumInliers.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header EvaluateNumInliers.hh

"C:\Build\inc\Ravl\EvaluateNumInliers.hh" :  "" ""
	copy ..\.\Math\Optimisation\EvaluateNumInliers.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\EvaluateLikelihood.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header EvaluateLikelihood.hh

"C:\Build\inc\Ravl\EvaluateLikelihood.hh" :  "" ""
	copy ..\.\Math\Optimisation\EvaluateLikelihood.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header EvaluateLikelihood.hh

"C:\Build\inc\Ravl\EvaluateLikelihood.hh" :  "" ""
	copy ..\.\Math\Optimisation\EvaluateLikelihood.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitLine2dPoints.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header FitLine2dPoints.hh

"C:\Build\inc\Ravl\FitLine2dPoints.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitLine2dPoints.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header FitLine2dPoints.hh

"C:\Build\inc\Ravl\FitLine2dPoints.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitLine2dPoints.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitQuadraticPoints.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header FitQuadraticPoints.hh

"C:\Build\inc\Ravl\FitQuadraticPoints.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitQuadraticPoints.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header FitQuadraticPoints.hh

"C:\Build\inc\Ravl\FitQuadraticPoints.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitQuadraticPoints.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitHomog2dPoints.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header FitHomog2dPoints.hh

"C:\Build\inc\Ravl\FitHomog2dPoints.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitHomog2dPoints.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header FitHomog2dPoints.hh

"C:\Build\inc\Ravl\FitHomog2dPoints.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitHomog2dPoints.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\ObservationAffine2dPoint.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header ObservationAffine2dPoint.hh

"C:\Build\inc\Ravl\ObservationAffine2dPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationAffine2dPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header ObservationAffine2dPoint.hh

"C:\Build\inc\Ravl\ObservationAffine2dPoint.hh" :  "" ""
	copy ..\.\Math\Optimisation\ObservationAffine2dPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\StateVectorAffine2d.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header StateVectorAffine2d.hh

"C:\Build\inc\Ravl\StateVectorAffine2d.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorAffine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header StateVectorAffine2d.hh

"C:\Build\inc\Ravl\StateVectorAffine2d.hh" :  "" ""
	copy ..\.\Math\Optimisation\StateVectorAffine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\FitAffine2dPoints.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header FitAffine2dPoints.hh

"C:\Build\inc\Ravl\FitAffine2dPoints.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitAffine2dPoints.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header FitAffine2dPoints.hh

"C:\Build\inc\Ravl\FitAffine2dPoints.hh" :  "" ""
	copy ..\.\Math\Optimisation\FitAffine2dPoints.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\OptimiseQuadraticCurve.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header OptimiseQuadraticCurve.hh

"C:\Build\inc\Ravl\OptimiseQuadraticCurve.hh" :  "" ""
	copy ..\.\Math\Optimisation\OptimiseQuadraticCurve.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header OptimiseQuadraticCurve.hh

"C:\Build\inc\Ravl\OptimiseQuadraticCurve.hh" :  "" ""
	copy ..\.\Math\Optimisation\OptimiseQuadraticCurve.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\OptimiseOrthogonalRegression.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header OptimiseOrthogonalRegression.hh

"C:\Build\inc\Ravl\OptimiseOrthogonalRegression.hh" :  "" ""
	copy ..\.\Math\Optimisation\OptimiseOrthogonalRegression.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header OptimiseOrthogonalRegression.hh

"C:\Build\inc\Ravl\OptimiseOrthogonalRegression.hh" :  "" ""
	copy ..\.\Math\Optimisation\OptimiseOrthogonalRegression.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Optimise2dHomography.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header Optimise2dHomography.hh

"C:\Build\inc\Ravl\Optimise2dHomography.hh" :  "" ""
	copy ..\.\Math\Optimisation\Optimise2dHomography.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header Optimise2dHomography.hh

"C:\Build\inc\Ravl\Optimise2dHomography.hh" :  "" ""
	copy ..\.\Math\Optimisation\Optimise2dHomography.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Optimise2dAffineHomography.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header Optimise2dAffineHomography.hh

"C:\Build\inc\Ravl\Optimise2dAffineHomography.hh" :  "" ""
	copy ..\.\Math\Optimisation\Optimise2dAffineHomography.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header Optimise2dAffineHomography.hh

"C:\Build\inc\Ravl\Optimise2dAffineHomography.hh" :  "" ""
	copy ..\.\Math\Optimisation\Optimise2dAffineHomography.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Point2dObs.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header Point2dObs.hh

"C:\Build\inc\Ravl\Point2dObs.hh" :  "" ""
	copy ..\.\Math\Optimisation\Point2dObs.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header Point2dObs.hh

"C:\Build\inc\Ravl\Point2dObs.hh" :  "" ""
	copy ..\.\Math\Optimisation\Point2dObs.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Optimisation\Point2dPairObs.hh

!IF  "$(CFG)" == "RavlOptimise - Win32 Release"

# Begin Custom Build - Install Header Point2dPairObs.hh

"C:\Build\inc\Ravl\Point2dPairObs.hh" :  "" ""
	copy ..\.\Math\Optimisation\Point2dPairObs.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOptimise - Win32 Debug"

# Begin Custom Build - Install Header Point2dPairObs.hh

"C:\Build\inc\Ravl\Point2dPairObs.hh" :  "" ""
	copy ..\.\Math\Optimisation\Point2dPairObs.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project

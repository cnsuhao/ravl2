# Microsoft Developer Studio Project File - Name="RavlPatternRec" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlPatternRec - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlPatternRec.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlPatternRec.mak" CFG="RavlPatternRec - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlPatternRec - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlPatternRec - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlPatternRec"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlPatternRec"
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

# Name "RavlPatternRec - Win32 Release"
# Name "RavlPatternRec - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleVector.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleLabel.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSetBase.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\Function.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\Function1.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\Designer.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DesignFunctionUnsupervised.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DesignFunctionSupervised.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\VectorLabelIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSetVectorLabel.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleStreamVector.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSetVectorLabelWeight.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\Distance.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceEuclidean.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceMax.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceCityBlock.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceMahalanobis.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceSqrEuclidean.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceRobust.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\Classifier.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignClassifierUnsupervised.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\ClassifierNearestNeighbour.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignKMeans.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignMeanShiftCluster.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignCluster.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignKohonenNet.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\ClassifierFuzzyCMeans.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignFuzzyCMeansCluster.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncLinearCoeff.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncLinear.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncQuadratic.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncOrthPolynomial.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\DesignFuncLSQ.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncPDF.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncPDFNormal.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncMeanProjection.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\DimensionReduction\FuncSubset.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\DimensionReduction\DesignFuncReduce.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\DimensionReduction\DesignFuncPCA.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\DimensionReduction\DesignFuncLDA.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\GaussianMixture\GaussianMixture.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\GaussianMixture\DesignGaussianMixture.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignClassifierSupervised.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignDiscriminantFunction.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignKNearestNeighbour.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierKNearestNeighbour.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierAverageNearestNeighbour.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierDiscriminantFunction.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierGaussianMixture.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignClassifierGaussianMixture.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierPreprocess.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierFunc1Threshold.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierWeakLinear.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierLinearCombination.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignWeakLinear.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierBayesNormalLinear.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignBayesNormalLinear.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignBayesNormalQuadratic.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierBayesNormalQuadratic.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierNeuralNetwork.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignClassifierNeuralNetwork.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\FeatureSelection\FeatureSelector.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\FeatureSelection\FeatureSelectAsymmetricAdaBoost.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Performance\Error.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\PatternRec\DataSet\Sample.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header Sample.hh

"C:\Build\inc\Ravl\PatternRec\Sample.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\Sample.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header Sample.hh

"C:\Build\inc\Ravl\PatternRec\Sample.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\Sample.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleIter.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header SampleIter.hh

"C:\Build\inc\Ravl\PatternRec\SampleIter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleIter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header SampleIter.hh

"C:\Build\inc\Ravl\PatternRec\SampleIter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleIter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleVector.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header SampleVector.hh

"C:\Build\inc\Ravl\PatternRec\SampleVector.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleVector.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header SampleVector.hh

"C:\Build\inc\Ravl\PatternRec\SampleVector.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleVector.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleLabel.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header SampleLabel.hh

"C:\Build\inc\Ravl\PatternRec\SampleLabel.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleLabel.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header SampleLabel.hh

"C:\Build\inc\Ravl\PatternRec\SampleLabel.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleLabel.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleDiscrete.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header SampleDiscrete.hh

"C:\Build\inc\Ravl\PatternRec\SampleDiscrete.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleDiscrete.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header SampleDiscrete.hh

"C:\Build\inc\Ravl\PatternRec\SampleDiscrete.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleDiscrete.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSetBase.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSetBase.hh

"C:\Build\inc\Ravl\PatternRec\DataSetBase.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSetBase.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSetBase.hh

"C:\Build\inc\Ravl\PatternRec\DataSetBase.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSetBase.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSet1.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSet1.hh

"C:\Build\inc\Ravl\PatternRec\DataSet1.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet1.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSet1.hh

"C:\Build\inc\Ravl\PatternRec\DataSet1.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet1.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSet1Iter.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSet1Iter.hh

"C:\Build\inc\Ravl\PatternRec\DataSet1Iter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet1Iter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSet1Iter.hh

"C:\Build\inc\Ravl\PatternRec\DataSet1Iter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet1Iter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSet2.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSet2.hh

"C:\Build\inc\Ravl\PatternRec\DataSet2.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet2.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSet2.hh

"C:\Build\inc\Ravl\PatternRec\DataSet2.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet2.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSet2Iter.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSet2Iter.hh

"C:\Build\inc\Ravl\PatternRec\DataSet2Iter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet2Iter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSet2Iter.hh

"C:\Build\inc\Ravl\PatternRec\DataSet2Iter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet2Iter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSet3.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSet3.hh

"C:\Build\inc\Ravl\PatternRec\DataSet3.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet3.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSet3.hh

"C:\Build\inc\Ravl\PatternRec\DataSet3.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet3.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSet3Iter.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSet3Iter.hh

"C:\Build\inc\Ravl\PatternRec\DataSet3Iter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet3Iter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSet3Iter.hh

"C:\Build\inc\Ravl\PatternRec\DataSet3Iter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet3Iter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSet4.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSet4.hh

"C:\Build\inc\Ravl\PatternRec\DataSet4.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet4.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSet4.hh

"C:\Build\inc\Ravl\PatternRec\DataSet4.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet4.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSet4Iter.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSet4Iter.hh

"C:\Build\inc\Ravl\PatternRec\DataSet4Iter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet4Iter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSet4Iter.hh

"C:\Build\inc\Ravl\PatternRec\DataSet4Iter.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSet4Iter.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleIO.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header SampleIO.hh

"C:\Build\inc\Ravl\PatternRec\SampleIO.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleIO.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header SampleIO.hh

"C:\Build\inc\Ravl\PatternRec\SampleIO.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleIO.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\Function.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header Function.hh

"C:\Build\inc\Ravl\PatternRec\Function.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\Function.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header Function.hh

"C:\Build\inc\Ravl\PatternRec\Function.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\Function.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\Function1.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header Function1.hh

"C:\Build\inc\Ravl\PatternRec\Function1.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\Function1.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header Function1.hh

"C:\Build\inc\Ravl\PatternRec\Function1.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\Function1.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\Designer.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header Designer.hh

"C:\Build\inc\Ravl\PatternRec\Designer.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\Designer.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header Designer.hh

"C:\Build\inc\Ravl\PatternRec\Designer.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\Designer.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DesignFunctionUnsupervised.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignFunctionUnsupervised.hh

"C:\Build\inc\Ravl\PatternRec\DesignFunctionUnsupervised.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DesignFunctionUnsupervised.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignFunctionUnsupervised.hh

"C:\Build\inc\Ravl\PatternRec\DesignFunctionUnsupervised.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DesignFunctionUnsupervised.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DesignFunctionSupervised.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignFunctionSupervised.hh

"C:\Build\inc\Ravl\PatternRec\DesignFunctionSupervised.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DesignFunctionSupervised.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignFunctionSupervised.hh

"C:\Build\inc\Ravl\PatternRec\DesignFunctionSupervised.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DesignFunctionSupervised.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\VectorLabelIO.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header VectorLabelIO.hh

"C:\Build\inc\Ravl\PatternRec\VectorLabelIO.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\VectorLabelIO.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header VectorLabelIO.hh

"C:\Build\inc\Ravl\PatternRec\VectorLabelIO.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\VectorLabelIO.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSetVectorLabel.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSetVectorLabel.hh

"C:\Build\inc\Ravl\PatternRec\DataSetVectorLabel.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSetVectorLabel.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSetVectorLabel.hh

"C:\Build\inc\Ravl\PatternRec\DataSetVectorLabel.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSetVectorLabel.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\DataSetVectorLabelWeight.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DataSetVectorLabelWeight.hh

"C:\Build\inc\Ravl\PatternRec\DataSetVectorLabelWeight.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSetVectorLabelWeight.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DataSetVectorLabelWeight.hh

"C:\Build\inc\Ravl\PatternRec\DataSetVectorLabelWeight.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\DataSetVectorLabelWeight.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleStream.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header SampleStream.hh

"C:\Build\inc\Ravl\PatternRec\SampleStream.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleStream.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header SampleStream.hh

"C:\Build\inc\Ravl\PatternRec\SampleStream.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleStream.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\DataSet\SampleStreamVector.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header SampleStreamVector.hh

"C:\Build\inc\Ravl\PatternRec\SampleStreamVector.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleStreamVector.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header SampleStreamVector.hh

"C:\Build\inc\Ravl\PatternRec\SampleStreamVector.hh" :  "" ""
	copy ..\.\PatternRec\DataSet\SampleStreamVector.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\Distance.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header Distance.hh

"C:\Build\inc\Ravl\PatternRec\Distance.hh" :  "" ""
	copy ..\.\PatternRec\Distance\Distance.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header Distance.hh

"C:\Build\inc\Ravl\PatternRec\Distance.hh" :  "" ""
	copy ..\.\PatternRec\Distance\Distance.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceEuclidean.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DistanceEuclidean.hh

"C:\Build\inc\Ravl\PatternRec\DistanceEuclidean.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceEuclidean.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DistanceEuclidean.hh

"C:\Build\inc\Ravl\PatternRec\DistanceEuclidean.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceEuclidean.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceMax.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DistanceMax.hh

"C:\Build\inc\Ravl\PatternRec\DistanceMax.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceMax.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DistanceMax.hh

"C:\Build\inc\Ravl\PatternRec\DistanceMax.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceMax.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceCityBlock.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DistanceCityBlock.hh

"C:\Build\inc\Ravl\PatternRec\DistanceCityBlock.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceCityBlock.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DistanceCityBlock.hh

"C:\Build\inc\Ravl\PatternRec\DistanceCityBlock.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceCityBlock.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceMahalanobis.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DistanceMahalanobis.hh

"C:\Build\inc\Ravl\PatternRec\DistanceMahalanobis.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceMahalanobis.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DistanceMahalanobis.hh

"C:\Build\inc\Ravl\PatternRec\DistanceMahalanobis.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceMahalanobis.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceSqrEuclidean.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DistanceSqrEuclidean.hh

"C:\Build\inc\Ravl\PatternRec\DistanceSqrEuclidean.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceSqrEuclidean.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DistanceSqrEuclidean.hh

"C:\Build\inc\Ravl\PatternRec\DistanceSqrEuclidean.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceSqrEuclidean.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Distance\DistanceRobust.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DistanceRobust.hh

"C:\Build\inc\Ravl\PatternRec\DistanceRobust.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceRobust.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DistanceRobust.hh

"C:\Build\inc\Ravl\PatternRec\DistanceRobust.hh" :  "" ""
	copy ..\.\PatternRec\Distance\DistanceRobust.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\Classifier.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header Classifier.hh

"C:\Build\inc\Ravl\PatternRec\Classifier.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\Classifier.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header Classifier.hh

"C:\Build\inc\Ravl\PatternRec\Classifier.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\Classifier.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignClassifierUnsupervised.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignClassifierUnsupervised.hh

"C:\Build\inc\Ravl\PatternRec\DesignClassifierUnsupervised.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignClassifierUnsupervised.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignClassifierUnsupervised.hh

"C:\Build\inc\Ravl\PatternRec\DesignClassifierUnsupervised.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignClassifierUnsupervised.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\ClassifierNearestNeighbour.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierNearestNeighbour.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierNearestNeighbour.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\ClassifierNearestNeighbour.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierNearestNeighbour.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierNearestNeighbour.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\ClassifierNearestNeighbour.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignKMeans.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignKMeans.hh

"C:\Build\inc\Ravl\PatternRec\DesignKMeans.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignKMeans.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignKMeans.hh

"C:\Build\inc\Ravl\PatternRec\DesignKMeans.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignKMeans.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignMeanShiftCluster.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignMeanShiftCluster.hh

"C:\Build\inc\Ravl\PatternRec\DesignMeanShiftCluster.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignMeanShiftCluster.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignMeanShiftCluster.hh

"C:\Build\inc\Ravl\PatternRec\DesignMeanShiftCluster.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignMeanShiftCluster.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignCluster.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignCluster.hh

"C:\Build\inc\Ravl\PatternRec\DesignCluster.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignCluster.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignCluster.hh

"C:\Build\inc\Ravl\PatternRec\DesignCluster.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignCluster.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignKohonenNet.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignKohonenNet.hh

"C:\Build\inc\Ravl\PatternRec\DesignKohonenNet.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignKohonenNet.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignKohonenNet.hh

"C:\Build\inc\Ravl\PatternRec\DesignKohonenNet.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignKohonenNet.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\ClassifierFuzzyCMeans.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierFuzzyCMeans.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierFuzzyCMeans.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\ClassifierFuzzyCMeans.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierFuzzyCMeans.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierFuzzyCMeans.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\ClassifierFuzzyCMeans.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Cluster\DesignFuzzyCMeansCluster.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignFuzzyCMeansCluster.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuzzyCMeansCluster.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignFuzzyCMeansCluster.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignFuzzyCMeansCluster.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuzzyCMeansCluster.hh" :  "" ""
	copy ..\.\PatternRec\Cluster\DesignFuzzyCMeansCluster.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncLinearCoeff.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FuncLinearCoeff.hh

"C:\Build\inc\Ravl\PatternRec\FuncLinearCoeff.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncLinearCoeff.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FuncLinearCoeff.hh

"C:\Build\inc\Ravl\PatternRec\FuncLinearCoeff.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncLinearCoeff.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncLinear.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FuncLinear.hh

"C:\Build\inc\Ravl\PatternRec\FuncLinear.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FuncLinear.hh

"C:\Build\inc\Ravl\PatternRec\FuncLinear.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncQuadratic.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FuncQuadratic.hh

"C:\Build\inc\Ravl\PatternRec\FuncQuadratic.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncQuadratic.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FuncQuadratic.hh

"C:\Build\inc\Ravl\PatternRec\FuncQuadratic.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncQuadratic.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncOrthPolynomial.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FuncOrthPolynomial.hh

"C:\Build\inc\Ravl\PatternRec\FuncOrthPolynomial.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncOrthPolynomial.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FuncOrthPolynomial.hh

"C:\Build\inc\Ravl\PatternRec\FuncOrthPolynomial.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncOrthPolynomial.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\DesignFuncLSQ.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignFuncLSQ.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuncLSQ.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\DesignFuncLSQ.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignFuncLSQ.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuncLSQ.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\DesignFuncLSQ.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncPDF.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FuncPDF.hh

"C:\Build\inc\Ravl\PatternRec\FuncPDF.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncPDF.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FuncPDF.hh

"C:\Build\inc\Ravl\PatternRec\FuncPDF.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncPDF.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncPDFNormal.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FuncPDFNormal.hh

"C:\Build\inc\Ravl\PatternRec\FuncPDFNormal.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncPDFNormal.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FuncPDFNormal.hh

"C:\Build\inc\Ravl\PatternRec\FuncPDFNormal.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncPDFNormal.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\Basic\FuncMeanProjection.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FuncMeanProjection.hh

"C:\Build\inc\Ravl\PatternRec\FuncMeanProjection.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncMeanProjection.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FuncMeanProjection.hh

"C:\Build\inc\Ravl\PatternRec\FuncMeanProjection.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\Basic\FuncMeanProjection.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\DimensionReduction\FuncSubset.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FuncSubset.hh

"C:\Build\inc\Ravl\PatternRec\FuncSubset.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\DimensionReduction\FuncSubset.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FuncSubset.hh

"C:\Build\inc\Ravl\PatternRec\FuncSubset.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\DimensionReduction\FuncSubset.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\DimensionReduction\DesignFuncReduce.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignFuncReduce.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuncReduce.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\DimensionReduction\DesignFuncReduce.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignFuncReduce.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuncReduce.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\DimensionReduction\DesignFuncReduce.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\DimensionReduction\DesignFuncPCA.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignFuncPCA.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuncPCA.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\DimensionReduction\DesignFuncPCA.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignFuncPCA.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuncPCA.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\DimensionReduction\DesignFuncPCA.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\DimensionReduction\DesignFuncLDA.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignFuncLDA.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuncLDA.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\DimensionReduction\DesignFuncLDA.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignFuncLDA.hh

"C:\Build\inc\Ravl\PatternRec\DesignFuncLDA.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\DimensionReduction\DesignFuncLDA.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\GaussianMixture\GaussianMixture.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header GaussianMixture.hh

"C:\Build\inc\Ravl\PatternRec\GaussianMixture.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\GaussianMixture\GaussianMixture.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header GaussianMixture.hh

"C:\Build\inc\Ravl\PatternRec\GaussianMixture.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\GaussianMixture\GaussianMixture.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Modeling\GaussianMixture\DesignGaussianMixture.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignGaussianMixture.hh

"C:\Build\inc\Ravl\PatternRec\DesignGaussianMixture.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\GaussianMixture\DesignGaussianMixture.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignGaussianMixture.hh

"C:\Build\inc\Ravl\PatternRec\DesignGaussianMixture.hh" :  "" ""
	copy ..\.\PatternRec\Modeling\GaussianMixture\DesignGaussianMixture.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignClassifierSupervised.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignClassifierSupervised.hh

"C:\Build\inc\Ravl\PatternRec\DesignClassifierSupervised.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignClassifierSupervised.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignClassifierSupervised.hh

"C:\Build\inc\Ravl\PatternRec\DesignClassifierSupervised.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignClassifierSupervised.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignDiscriminantFunction.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignDiscriminantFunction.hh

"C:\Build\inc\Ravl\PatternRec\DesignDiscriminantFunction.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignDiscriminantFunction.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignDiscriminantFunction.hh

"C:\Build\inc\Ravl\PatternRec\DesignDiscriminantFunction.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignDiscriminantFunction.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignKNearestNeighbour.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignKNearestNeighbour.hh

"C:\Build\inc\Ravl\PatternRec\DesignKNearestNeighbour.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignKNearestNeighbour.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignKNearestNeighbour.hh

"C:\Build\inc\Ravl\PatternRec\DesignKNearestNeighbour.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignKNearestNeighbour.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierKNearestNeighbour.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierKNearestNeighbour.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierKNearestNeighbour.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierKNearestNeighbour.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierKNearestNeighbour.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierKNearestNeighbour.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierKNearestNeighbour.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierAverageNearestNeighbour.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierAverageNearestNeighbour.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierAverageNearestNeighbour.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierAverageNearestNeighbour.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierAverageNearestNeighbour.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierAverageNearestNeighbour.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierAverageNearestNeighbour.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierDiscriminantFunction.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierDiscriminantFunction.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierDiscriminantFunction.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierDiscriminantFunction.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierDiscriminantFunction.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierDiscriminantFunction.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierDiscriminantFunction.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierGaussianMixture.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierGaussianMixture.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierGaussianMixture.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierGaussianMixture.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierGaussianMixture.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierGaussianMixture.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierGaussianMixture.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignClassifierGaussianMixture.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignClassifierGaussianMixture.hh

"C:\Build\inc\Ravl\PatternRec\DesignClassifierGaussianMixture.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignClassifierGaussianMixture.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignClassifierGaussianMixture.hh

"C:\Build\inc\Ravl\PatternRec\DesignClassifierGaussianMixture.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignClassifierGaussianMixture.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierPreprocess.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierPreprocess.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierPreprocess.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierPreprocess.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierPreprocess.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierPreprocess.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierPreprocess.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierFunc1Threshold.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierFunc1Threshold.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierFunc1Threshold.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierFunc1Threshold.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierFunc1Threshold.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierFunc1Threshold.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierFunc1Threshold.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierWeakLinear.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierWeakLinear.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierWeakLinear.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierWeakLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierWeakLinear.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierWeakLinear.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierWeakLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierLinearCombination.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierLinearCombination.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierLinearCombination.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierLinearCombination.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierLinearCombination.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierLinearCombination.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierLinearCombination.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignWeakLinear.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignWeakLinear.hh

"C:\Build\inc\Ravl\PatternRec\DesignWeakLinear.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignWeakLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignWeakLinear.hh

"C:\Build\inc\Ravl\PatternRec\DesignWeakLinear.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignWeakLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierBayesNormalLinear.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierBayesNormalLinear.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierBayesNormalLinear.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierBayesNormalLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierBayesNormalLinear.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierBayesNormalLinear.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierBayesNormalLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignBayesNormalLinear.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignBayesNormalLinear.hh

"C:\Build\inc\Ravl\PatternRec\DesignBayesNormalLinear.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignBayesNormalLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignBayesNormalLinear.hh

"C:\Build\inc\Ravl\PatternRec\DesignBayesNormalLinear.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignBayesNormalLinear.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignBayesNormalQuadratic.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignBayesNormalQuadratic.hh

"C:\Build\inc\Ravl\PatternRec\DesignBayesNormalQuadratic.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignBayesNormalQuadratic.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignBayesNormalQuadratic.hh

"C:\Build\inc\Ravl\PatternRec\DesignBayesNormalQuadratic.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignBayesNormalQuadratic.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierBayesNormalQuadratic.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierBayesNormalQuadratic.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierBayesNormalQuadratic.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierBayesNormalQuadratic.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierBayesNormalQuadratic.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierBayesNormalQuadratic.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierBayesNormalQuadratic.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\ClassifierNeuralNetwork.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header ClassifierNeuralNetwork.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierNeuralNetwork.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierNeuralNetwork.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header ClassifierNeuralNetwork.hh

"C:\Build\inc\Ravl\PatternRec\ClassifierNeuralNetwork.hh" :  "" ""
	copy ..\.\PatternRec\Classify\ClassifierNeuralNetwork.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Classify\DesignClassifierNeuralNetwork.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header DesignClassifierNeuralNetwork.hh

"C:\Build\inc\Ravl\PatternRec\DesignClassifierNeuralNetwork.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignClassifierNeuralNetwork.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header DesignClassifierNeuralNetwork.hh

"C:\Build\inc\Ravl\PatternRec\DesignClassifierNeuralNetwork.hh" :  "" ""
	copy ..\.\PatternRec\Classify\DesignClassifierNeuralNetwork.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\FeatureSelection\FeatureSelector.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FeatureSelector.hh

"C:\Build\inc\Ravl\PatternRec\FeatureSelector.hh" :  "" ""
	copy ..\.\PatternRec\FeatureSelection\FeatureSelector.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FeatureSelector.hh

"C:\Build\inc\Ravl\PatternRec\FeatureSelector.hh" :  "" ""
	copy ..\.\PatternRec\FeatureSelection\FeatureSelector.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\FeatureSelection\FeatureSelectAsymmetricAdaBoost.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header FeatureSelectAsymmetricAdaBoost.hh

"C:\Build\inc\Ravl\PatternRec\FeatureSelectAsymmetricAdaBoost.hh" :  "" ""
	copy ..\.\PatternRec\FeatureSelection\FeatureSelectAsymmetricAdaBoost.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header FeatureSelectAsymmetricAdaBoost.hh

"C:\Build\inc\Ravl\PatternRec\FeatureSelectAsymmetricAdaBoost.hh" :  "" ""
	copy ..\.\PatternRec\FeatureSelection\FeatureSelectAsymmetricAdaBoost.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Performance\Error.hh

!IF  "$(CFG)" == "RavlPatternRec - Win32 Release"

# Begin Custom Build - Install Header Error.hh

"C:\Build\inc\Ravl\PatternRec\Error.hh" :  "" ""
	copy ..\.\PatternRec\Performance\Error.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlPatternRec - Win32 Debug"

# Begin Custom Build - Install Header Error.hh

"C:\Build\inc\Ravl\PatternRec\Error.hh" :  "" ""
	copy ..\.\PatternRec\Performance\Error.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project

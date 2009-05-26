


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlPatternRec
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlPatternRec
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlPatternRec  $(OPTOBJDIR)/SampleVector.obj $(OPTOBJDIR)/SampleLabel.obj $(OPTOBJDIR)/DataSetBase.obj $(OPTOBJDIR)/Function.obj $(OPTOBJDIR)/Function1.obj $(OPTOBJDIR)/Designer.obj $(OPTOBJDIR)/DesignFunctionUnsupervised.obj $(OPTOBJDIR)/DesignFunctionSupervised.obj $(OPTOBJDIR)/VectorLabelIO.obj $(OPTOBJDIR)/DataSetVectorLabel.obj $(OPTOBJDIR)/SampleStreamVector.obj $(OPTOBJDIR)/DataSetVectorLabelWeight.obj $(OPTOBJDIR)/Distance.obj $(OPTOBJDIR)/DistanceEuclidean.obj $(OPTOBJDIR)/DistanceMax.obj $(OPTOBJDIR)/DistanceCityBlock.obj $(OPTOBJDIR)/DistanceMahalanobis.obj $(OPTOBJDIR)/DistanceSqrEuclidean.obj $(OPTOBJDIR)/DistanceRobust.obj $(OPTOBJDIR)/Classifier.obj $(OPTOBJDIR)/DesignClassifierUnsupervised.obj $(OPTOBJDIR)/ClassifierNearestNeighbour.obj $(OPTOBJDIR)/DesignKMeans.obj $(OPTOBJDIR)/DesignMeanShiftCluster.obj $(OPTOBJDIR)/DesignCluster.obj $(OPTOBJDIR)/DesignKohonenNet.obj $(OPTOBJDIR)/ClassifierFuzzyCMeans.obj $(OPTOBJDIR)/DesignFuzzyCMeansCluster.obj $(OPTOBJDIR)/FuncLinearCoeff.obj $(OPTOBJDIR)/FuncLinear.obj $(OPTOBJDIR)/FuncQuadratic.obj $(OPTOBJDIR)/FuncOrthPolynomial.obj $(OPTOBJDIR)/DesignFuncLSQ.obj $(OPTOBJDIR)/FuncPDF.obj $(OPTOBJDIR)/FuncPDFNormal.obj $(OPTOBJDIR)/FuncMeanProjection.obj $(OPTOBJDIR)/FuncSubset.obj $(OPTOBJDIR)/DesignFuncReduce.obj $(OPTOBJDIR)/DesignFuncPCA.obj $(OPTOBJDIR)/DesignFuncLDA.obj $(OPTOBJDIR)/GaussianMixture.obj $(OPTOBJDIR)/DesignGaussianMixture.obj $(OPTOBJDIR)/DesignClassifierSupervised.obj $(OPTOBJDIR)/DesignDiscriminantFunction.obj $(OPTOBJDIR)/DesignKNearestNeighbour.obj $(OPTOBJDIR)/ClassifierKNearestNeighbour.obj $(OPTOBJDIR)/ClassifierAverageNearestNeighbour.obj $(OPTOBJDIR)/ClassifierDiscriminantFunction.obj $(OPTOBJDIR)/ClassifierGaussianMixture.obj $(OPTOBJDIR)/DesignClassifierGaussianMixture.obj $(OPTOBJDIR)/ClassifierPreprocess.obj $(OPTOBJDIR)/ClassifierFunc1Threshold.obj $(OPTOBJDIR)/ClassifierWeakLinear.obj $(OPTOBJDIR)/ClassifierLinearCombination.obj $(OPTOBJDIR)/DesignWeakLinear.obj $(OPTOBJDIR)/ClassifierBayesNormalLinear.obj $(OPTOBJDIR)/DesignBayesNormalLinear.obj $(OPTOBJDIR)/DesignBayesNormalQuadratic.obj $(OPTOBJDIR)/ClassifierBayesNormalQuadratic.obj $(OPTOBJDIR)/ClassifierNeuralNetwork.obj $(OPTOBJDIR)/DesignClassifierNeuralNetwork.obj $(OPTOBJDIR)/FeatureSelector.obj $(OPTOBJDIR)/FeatureSelectAsymmetricAdaBoost.obj $(OPTOBJDIR)/Error.obj
	@echo -- making $(OPTLIBDIR)/RavlPatternRec.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlPatternRec.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlPatternRec  $(DEBUGOBJDIR)/SampleVector.obj $(DEBUGOBJDIR)/SampleLabel.obj $(DEBUGOBJDIR)/DataSetBase.obj $(DEBUGOBJDIR)/Function.obj $(DEBUGOBJDIR)/Function1.obj $(DEBUGOBJDIR)/Designer.obj $(DEBUGOBJDIR)/DesignFunctionUnsupervised.obj $(DEBUGOBJDIR)/DesignFunctionSupervised.obj $(DEBUGOBJDIR)/VectorLabelIO.obj $(DEBUGOBJDIR)/DataSetVectorLabel.obj $(DEBUGOBJDIR)/SampleStreamVector.obj $(DEBUGOBJDIR)/DataSetVectorLabelWeight.obj $(DEBUGOBJDIR)/Distance.obj $(DEBUGOBJDIR)/DistanceEuclidean.obj $(DEBUGOBJDIR)/DistanceMax.obj $(DEBUGOBJDIR)/DistanceCityBlock.obj $(DEBUGOBJDIR)/DistanceMahalanobis.obj $(DEBUGOBJDIR)/DistanceSqrEuclidean.obj $(DEBUGOBJDIR)/DistanceRobust.obj $(DEBUGOBJDIR)/Classifier.obj $(DEBUGOBJDIR)/DesignClassifierUnsupervised.obj $(DEBUGOBJDIR)/ClassifierNearestNeighbour.obj $(DEBUGOBJDIR)/DesignKMeans.obj $(DEBUGOBJDIR)/DesignMeanShiftCluster.obj $(DEBUGOBJDIR)/DesignCluster.obj $(DEBUGOBJDIR)/DesignKohonenNet.obj $(DEBUGOBJDIR)/ClassifierFuzzyCMeans.obj $(DEBUGOBJDIR)/DesignFuzzyCMeansCluster.obj $(DEBUGOBJDIR)/FuncLinearCoeff.obj $(DEBUGOBJDIR)/FuncLinear.obj $(DEBUGOBJDIR)/FuncQuadratic.obj $(DEBUGOBJDIR)/FuncOrthPolynomial.obj $(DEBUGOBJDIR)/DesignFuncLSQ.obj $(DEBUGOBJDIR)/FuncPDF.obj $(DEBUGOBJDIR)/FuncPDFNormal.obj $(DEBUGOBJDIR)/FuncMeanProjection.obj $(DEBUGOBJDIR)/FuncSubset.obj $(DEBUGOBJDIR)/DesignFuncReduce.obj $(DEBUGOBJDIR)/DesignFuncPCA.obj $(DEBUGOBJDIR)/DesignFuncLDA.obj $(DEBUGOBJDIR)/GaussianMixture.obj $(DEBUGOBJDIR)/DesignGaussianMixture.obj $(DEBUGOBJDIR)/DesignClassifierSupervised.obj $(DEBUGOBJDIR)/DesignDiscriminantFunction.obj $(DEBUGOBJDIR)/DesignKNearestNeighbour.obj $(DEBUGOBJDIR)/ClassifierKNearestNeighbour.obj $(DEBUGOBJDIR)/ClassifierAverageNearestNeighbour.obj $(DEBUGOBJDIR)/ClassifierDiscriminantFunction.obj $(DEBUGOBJDIR)/ClassifierGaussianMixture.obj $(DEBUGOBJDIR)/DesignClassifierGaussianMixture.obj $(DEBUGOBJDIR)/ClassifierPreprocess.obj $(DEBUGOBJDIR)/ClassifierFunc1Threshold.obj $(DEBUGOBJDIR)/ClassifierWeakLinear.obj $(DEBUGOBJDIR)/ClassifierLinearCombination.obj $(DEBUGOBJDIR)/DesignWeakLinear.obj $(DEBUGOBJDIR)/ClassifierBayesNormalLinear.obj $(DEBUGOBJDIR)/DesignBayesNormalLinear.obj $(DEBUGOBJDIR)/DesignBayesNormalQuadratic.obj $(DEBUGOBJDIR)/ClassifierBayesNormalQuadratic.obj $(DEBUGOBJDIR)/ClassifierNeuralNetwork.obj $(DEBUGOBJDIR)/DesignClassifierNeuralNetwork.obj $(DEBUGOBJDIR)/FeatureSelector.obj $(DEBUGOBJDIR)/FeatureSelectAsymmetricAdaBoost.obj $(DEBUGOBJDIR)/Error.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlPatternRec.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlPatternRec.lib $(DEBUGOBJDIR)/*.obj

setupRavlPatternRec::
        echo --- creating dir for RavlPatternRec
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/SampleVector.obj: .././PatternRec/DataSet/SampleVector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SampleVector.obj .././PatternRec/DataSet/SampleVector.cc

$(DEBUGOBJDIR)/SampleVector.obj: .././PatternRec/DataSet/SampleVector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SampleVector.obj .././PatternRec/DataSet/SampleVector.cc

$(OPTOBJDIR)/SampleLabel.obj: .././PatternRec/DataSet/SampleLabel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SampleLabel.obj .././PatternRec/DataSet/SampleLabel.cc

$(DEBUGOBJDIR)/SampleLabel.obj: .././PatternRec/DataSet/SampleLabel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SampleLabel.obj .././PatternRec/DataSet/SampleLabel.cc

$(OPTOBJDIR)/DataSetBase.obj: .././PatternRec/DataSet/DataSetBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DataSetBase.obj .././PatternRec/DataSet/DataSetBase.cc

$(DEBUGOBJDIR)/DataSetBase.obj: .././PatternRec/DataSet/DataSetBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DataSetBase.obj .././PatternRec/DataSet/DataSetBase.cc

$(OPTOBJDIR)/Function.obj: .././PatternRec/DataSet/Function.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Function.obj .././PatternRec/DataSet/Function.cc

$(DEBUGOBJDIR)/Function.obj: .././PatternRec/DataSet/Function.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Function.obj .././PatternRec/DataSet/Function.cc

$(OPTOBJDIR)/Function1.obj: .././PatternRec/DataSet/Function1.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Function1.obj .././PatternRec/DataSet/Function1.cc

$(DEBUGOBJDIR)/Function1.obj: .././PatternRec/DataSet/Function1.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Function1.obj .././PatternRec/DataSet/Function1.cc

$(OPTOBJDIR)/Designer.obj: .././PatternRec/DataSet/Designer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Designer.obj .././PatternRec/DataSet/Designer.cc

$(DEBUGOBJDIR)/Designer.obj: .././PatternRec/DataSet/Designer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Designer.obj .././PatternRec/DataSet/Designer.cc

$(OPTOBJDIR)/DesignFunctionUnsupervised.obj: .././PatternRec/DataSet/DesignFunctionUnsupervised.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignFunctionUnsupervised.obj .././PatternRec/DataSet/DesignFunctionUnsupervised.cc

$(DEBUGOBJDIR)/DesignFunctionUnsupervised.obj: .././PatternRec/DataSet/DesignFunctionUnsupervised.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignFunctionUnsupervised.obj .././PatternRec/DataSet/DesignFunctionUnsupervised.cc

$(OPTOBJDIR)/DesignFunctionSupervised.obj: .././PatternRec/DataSet/DesignFunctionSupervised.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignFunctionSupervised.obj .././PatternRec/DataSet/DesignFunctionSupervised.cc

$(DEBUGOBJDIR)/DesignFunctionSupervised.obj: .././PatternRec/DataSet/DesignFunctionSupervised.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignFunctionSupervised.obj .././PatternRec/DataSet/DesignFunctionSupervised.cc

$(OPTOBJDIR)/VectorLabelIO.obj: .././PatternRec/DataSet/VectorLabelIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VectorLabelIO.obj .././PatternRec/DataSet/VectorLabelIO.cc

$(DEBUGOBJDIR)/VectorLabelIO.obj: .././PatternRec/DataSet/VectorLabelIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VectorLabelIO.obj .././PatternRec/DataSet/VectorLabelIO.cc

$(OPTOBJDIR)/DataSetVectorLabel.obj: .././PatternRec/DataSet/DataSetVectorLabel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DataSetVectorLabel.obj .././PatternRec/DataSet/DataSetVectorLabel.cc

$(DEBUGOBJDIR)/DataSetVectorLabel.obj: .././PatternRec/DataSet/DataSetVectorLabel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DataSetVectorLabel.obj .././PatternRec/DataSet/DataSetVectorLabel.cc

$(OPTOBJDIR)/SampleStreamVector.obj: .././PatternRec/DataSet/SampleStreamVector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SampleStreamVector.obj .././PatternRec/DataSet/SampleStreamVector.cc

$(DEBUGOBJDIR)/SampleStreamVector.obj: .././PatternRec/DataSet/SampleStreamVector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SampleStreamVector.obj .././PatternRec/DataSet/SampleStreamVector.cc

$(OPTOBJDIR)/DataSetVectorLabelWeight.obj: .././PatternRec/DataSet/DataSetVectorLabelWeight.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DataSetVectorLabelWeight.obj .././PatternRec/DataSet/DataSetVectorLabelWeight.cc

$(DEBUGOBJDIR)/DataSetVectorLabelWeight.obj: .././PatternRec/DataSet/DataSetVectorLabelWeight.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DataSetVectorLabelWeight.obj .././PatternRec/DataSet/DataSetVectorLabelWeight.cc

$(OPTOBJDIR)/Distance.obj: .././PatternRec/Distance/Distance.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Distance.obj .././PatternRec/Distance/Distance.cc

$(DEBUGOBJDIR)/Distance.obj: .././PatternRec/Distance/Distance.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Distance.obj .././PatternRec/Distance/Distance.cc

$(OPTOBJDIR)/DistanceEuclidean.obj: .././PatternRec/Distance/DistanceEuclidean.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DistanceEuclidean.obj .././PatternRec/Distance/DistanceEuclidean.cc

$(DEBUGOBJDIR)/DistanceEuclidean.obj: .././PatternRec/Distance/DistanceEuclidean.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DistanceEuclidean.obj .././PatternRec/Distance/DistanceEuclidean.cc

$(OPTOBJDIR)/DistanceMax.obj: .././PatternRec/Distance/DistanceMax.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DistanceMax.obj .././PatternRec/Distance/DistanceMax.cc

$(DEBUGOBJDIR)/DistanceMax.obj: .././PatternRec/Distance/DistanceMax.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DistanceMax.obj .././PatternRec/Distance/DistanceMax.cc

$(OPTOBJDIR)/DistanceCityBlock.obj: .././PatternRec/Distance/DistanceCityBlock.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DistanceCityBlock.obj .././PatternRec/Distance/DistanceCityBlock.cc

$(DEBUGOBJDIR)/DistanceCityBlock.obj: .././PatternRec/Distance/DistanceCityBlock.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DistanceCityBlock.obj .././PatternRec/Distance/DistanceCityBlock.cc

$(OPTOBJDIR)/DistanceMahalanobis.obj: .././PatternRec/Distance/DistanceMahalanobis.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DistanceMahalanobis.obj .././PatternRec/Distance/DistanceMahalanobis.cc

$(DEBUGOBJDIR)/DistanceMahalanobis.obj: .././PatternRec/Distance/DistanceMahalanobis.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DistanceMahalanobis.obj .././PatternRec/Distance/DistanceMahalanobis.cc

$(OPTOBJDIR)/DistanceSqrEuclidean.obj: .././PatternRec/Distance/DistanceSqrEuclidean.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DistanceSqrEuclidean.obj .././PatternRec/Distance/DistanceSqrEuclidean.cc

$(DEBUGOBJDIR)/DistanceSqrEuclidean.obj: .././PatternRec/Distance/DistanceSqrEuclidean.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DistanceSqrEuclidean.obj .././PatternRec/Distance/DistanceSqrEuclidean.cc

$(OPTOBJDIR)/DistanceRobust.obj: .././PatternRec/Distance/DistanceRobust.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DistanceRobust.obj .././PatternRec/Distance/DistanceRobust.cc

$(DEBUGOBJDIR)/DistanceRobust.obj: .././PatternRec/Distance/DistanceRobust.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DistanceRobust.obj .././PatternRec/Distance/DistanceRobust.cc

$(OPTOBJDIR)/Classifier.obj: .././PatternRec/Cluster/Classifier.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Classifier.obj .././PatternRec/Cluster/Classifier.cc

$(DEBUGOBJDIR)/Classifier.obj: .././PatternRec/Cluster/Classifier.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Classifier.obj .././PatternRec/Cluster/Classifier.cc

$(OPTOBJDIR)/DesignClassifierUnsupervised.obj: .././PatternRec/Cluster/DesignClassifierUnsupervised.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignClassifierUnsupervised.obj .././PatternRec/Cluster/DesignClassifierUnsupervised.cc

$(DEBUGOBJDIR)/DesignClassifierUnsupervised.obj: .././PatternRec/Cluster/DesignClassifierUnsupervised.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignClassifierUnsupervised.obj .././PatternRec/Cluster/DesignClassifierUnsupervised.cc

$(OPTOBJDIR)/ClassifierNearestNeighbour.obj: .././PatternRec/Cluster/ClassifierNearestNeighbour.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierNearestNeighbour.obj .././PatternRec/Cluster/ClassifierNearestNeighbour.cc

$(DEBUGOBJDIR)/ClassifierNearestNeighbour.obj: .././PatternRec/Cluster/ClassifierNearestNeighbour.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierNearestNeighbour.obj .././PatternRec/Cluster/ClassifierNearestNeighbour.cc

$(OPTOBJDIR)/DesignKMeans.obj: .././PatternRec/Cluster/DesignKMeans.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignKMeans.obj .././PatternRec/Cluster/DesignKMeans.cc

$(DEBUGOBJDIR)/DesignKMeans.obj: .././PatternRec/Cluster/DesignKMeans.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignKMeans.obj .././PatternRec/Cluster/DesignKMeans.cc

$(OPTOBJDIR)/DesignMeanShiftCluster.obj: .././PatternRec/Cluster/DesignMeanShiftCluster.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignMeanShiftCluster.obj .././PatternRec/Cluster/DesignMeanShiftCluster.cc

$(DEBUGOBJDIR)/DesignMeanShiftCluster.obj: .././PatternRec/Cluster/DesignMeanShiftCluster.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignMeanShiftCluster.obj .././PatternRec/Cluster/DesignMeanShiftCluster.cc

$(OPTOBJDIR)/DesignCluster.obj: .././PatternRec/Cluster/DesignCluster.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignCluster.obj .././PatternRec/Cluster/DesignCluster.cc

$(DEBUGOBJDIR)/DesignCluster.obj: .././PatternRec/Cluster/DesignCluster.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignCluster.obj .././PatternRec/Cluster/DesignCluster.cc

$(OPTOBJDIR)/DesignKohonenNet.obj: .././PatternRec/Cluster/DesignKohonenNet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignKohonenNet.obj .././PatternRec/Cluster/DesignKohonenNet.cc

$(DEBUGOBJDIR)/DesignKohonenNet.obj: .././PatternRec/Cluster/DesignKohonenNet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignKohonenNet.obj .././PatternRec/Cluster/DesignKohonenNet.cc

$(OPTOBJDIR)/ClassifierFuzzyCMeans.obj: .././PatternRec/Cluster/ClassifierFuzzyCMeans.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierFuzzyCMeans.obj .././PatternRec/Cluster/ClassifierFuzzyCMeans.cc

$(DEBUGOBJDIR)/ClassifierFuzzyCMeans.obj: .././PatternRec/Cluster/ClassifierFuzzyCMeans.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierFuzzyCMeans.obj .././PatternRec/Cluster/ClassifierFuzzyCMeans.cc

$(OPTOBJDIR)/DesignFuzzyCMeansCluster.obj: .././PatternRec/Cluster/DesignFuzzyCMeansCluster.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignFuzzyCMeansCluster.obj .././PatternRec/Cluster/DesignFuzzyCMeansCluster.cc

$(DEBUGOBJDIR)/DesignFuzzyCMeansCluster.obj: .././PatternRec/Cluster/DesignFuzzyCMeansCluster.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignFuzzyCMeansCluster.obj .././PatternRec/Cluster/DesignFuzzyCMeansCluster.cc

$(OPTOBJDIR)/FuncLinearCoeff.obj: .././PatternRec/Modeling/Basic/FuncLinearCoeff.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FuncLinearCoeff.obj .././PatternRec/Modeling/Basic/FuncLinearCoeff.cc

$(DEBUGOBJDIR)/FuncLinearCoeff.obj: .././PatternRec/Modeling/Basic/FuncLinearCoeff.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FuncLinearCoeff.obj .././PatternRec/Modeling/Basic/FuncLinearCoeff.cc

$(OPTOBJDIR)/FuncLinear.obj: .././PatternRec/Modeling/Basic/FuncLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FuncLinear.obj .././PatternRec/Modeling/Basic/FuncLinear.cc

$(DEBUGOBJDIR)/FuncLinear.obj: .././PatternRec/Modeling/Basic/FuncLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FuncLinear.obj .././PatternRec/Modeling/Basic/FuncLinear.cc

$(OPTOBJDIR)/FuncQuadratic.obj: .././PatternRec/Modeling/Basic/FuncQuadratic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FuncQuadratic.obj .././PatternRec/Modeling/Basic/FuncQuadratic.cc

$(DEBUGOBJDIR)/FuncQuadratic.obj: .././PatternRec/Modeling/Basic/FuncQuadratic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FuncQuadratic.obj .././PatternRec/Modeling/Basic/FuncQuadratic.cc

$(OPTOBJDIR)/FuncOrthPolynomial.obj: .././PatternRec/Modeling/Basic/FuncOrthPolynomial.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FuncOrthPolynomial.obj .././PatternRec/Modeling/Basic/FuncOrthPolynomial.cc

$(DEBUGOBJDIR)/FuncOrthPolynomial.obj: .././PatternRec/Modeling/Basic/FuncOrthPolynomial.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FuncOrthPolynomial.obj .././PatternRec/Modeling/Basic/FuncOrthPolynomial.cc

$(OPTOBJDIR)/DesignFuncLSQ.obj: .././PatternRec/Modeling/Basic/DesignFuncLSQ.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignFuncLSQ.obj .././PatternRec/Modeling/Basic/DesignFuncLSQ.cc

$(DEBUGOBJDIR)/DesignFuncLSQ.obj: .././PatternRec/Modeling/Basic/DesignFuncLSQ.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignFuncLSQ.obj .././PatternRec/Modeling/Basic/DesignFuncLSQ.cc

$(OPTOBJDIR)/FuncPDF.obj: .././PatternRec/Modeling/Basic/FuncPDF.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FuncPDF.obj .././PatternRec/Modeling/Basic/FuncPDF.cc

$(DEBUGOBJDIR)/FuncPDF.obj: .././PatternRec/Modeling/Basic/FuncPDF.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FuncPDF.obj .././PatternRec/Modeling/Basic/FuncPDF.cc

$(OPTOBJDIR)/FuncPDFNormal.obj: .././PatternRec/Modeling/Basic/FuncPDFNormal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FuncPDFNormal.obj .././PatternRec/Modeling/Basic/FuncPDFNormal.cc

$(DEBUGOBJDIR)/FuncPDFNormal.obj: .././PatternRec/Modeling/Basic/FuncPDFNormal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FuncPDFNormal.obj .././PatternRec/Modeling/Basic/FuncPDFNormal.cc

$(OPTOBJDIR)/FuncMeanProjection.obj: .././PatternRec/Modeling/Basic/FuncMeanProjection.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FuncMeanProjection.obj .././PatternRec/Modeling/Basic/FuncMeanProjection.cc

$(DEBUGOBJDIR)/FuncMeanProjection.obj: .././PatternRec/Modeling/Basic/FuncMeanProjection.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FuncMeanProjection.obj .././PatternRec/Modeling/Basic/FuncMeanProjection.cc

$(OPTOBJDIR)/FuncSubset.obj: .././PatternRec/Modeling/DimensionReduction/FuncSubset.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FuncSubset.obj .././PatternRec/Modeling/DimensionReduction/FuncSubset.cc

$(DEBUGOBJDIR)/FuncSubset.obj: .././PatternRec/Modeling/DimensionReduction/FuncSubset.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FuncSubset.obj .././PatternRec/Modeling/DimensionReduction/FuncSubset.cc

$(OPTOBJDIR)/DesignFuncReduce.obj: .././PatternRec/Modeling/DimensionReduction/DesignFuncReduce.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignFuncReduce.obj .././PatternRec/Modeling/DimensionReduction/DesignFuncReduce.cc

$(DEBUGOBJDIR)/DesignFuncReduce.obj: .././PatternRec/Modeling/DimensionReduction/DesignFuncReduce.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignFuncReduce.obj .././PatternRec/Modeling/DimensionReduction/DesignFuncReduce.cc

$(OPTOBJDIR)/DesignFuncPCA.obj: .././PatternRec/Modeling/DimensionReduction/DesignFuncPCA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignFuncPCA.obj .././PatternRec/Modeling/DimensionReduction/DesignFuncPCA.cc

$(DEBUGOBJDIR)/DesignFuncPCA.obj: .././PatternRec/Modeling/DimensionReduction/DesignFuncPCA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignFuncPCA.obj .././PatternRec/Modeling/DimensionReduction/DesignFuncPCA.cc

$(OPTOBJDIR)/DesignFuncLDA.obj: .././PatternRec/Modeling/DimensionReduction/DesignFuncLDA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignFuncLDA.obj .././PatternRec/Modeling/DimensionReduction/DesignFuncLDA.cc

$(DEBUGOBJDIR)/DesignFuncLDA.obj: .././PatternRec/Modeling/DimensionReduction/DesignFuncLDA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignFuncLDA.obj .././PatternRec/Modeling/DimensionReduction/DesignFuncLDA.cc

$(OPTOBJDIR)/GaussianMixture.obj: .././PatternRec/Modeling/GaussianMixture/GaussianMixture.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GaussianMixture.obj .././PatternRec/Modeling/GaussianMixture/GaussianMixture.cc

$(DEBUGOBJDIR)/GaussianMixture.obj: .././PatternRec/Modeling/GaussianMixture/GaussianMixture.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GaussianMixture.obj .././PatternRec/Modeling/GaussianMixture/GaussianMixture.cc

$(OPTOBJDIR)/DesignGaussianMixture.obj: .././PatternRec/Modeling/GaussianMixture/DesignGaussianMixture.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignGaussianMixture.obj .././PatternRec/Modeling/GaussianMixture/DesignGaussianMixture.cc

$(DEBUGOBJDIR)/DesignGaussianMixture.obj: .././PatternRec/Modeling/GaussianMixture/DesignGaussianMixture.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignGaussianMixture.obj .././PatternRec/Modeling/GaussianMixture/DesignGaussianMixture.cc

$(OPTOBJDIR)/DesignClassifierSupervised.obj: .././PatternRec/Classify/DesignClassifierSupervised.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignClassifierSupervised.obj .././PatternRec/Classify/DesignClassifierSupervised.cc

$(DEBUGOBJDIR)/DesignClassifierSupervised.obj: .././PatternRec/Classify/DesignClassifierSupervised.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignClassifierSupervised.obj .././PatternRec/Classify/DesignClassifierSupervised.cc

$(OPTOBJDIR)/DesignDiscriminantFunction.obj: .././PatternRec/Classify/DesignDiscriminantFunction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignDiscriminantFunction.obj .././PatternRec/Classify/DesignDiscriminantFunction.cc

$(DEBUGOBJDIR)/DesignDiscriminantFunction.obj: .././PatternRec/Classify/DesignDiscriminantFunction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignDiscriminantFunction.obj .././PatternRec/Classify/DesignDiscriminantFunction.cc

$(OPTOBJDIR)/DesignKNearestNeighbour.obj: .././PatternRec/Classify/DesignKNearestNeighbour.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignKNearestNeighbour.obj .././PatternRec/Classify/DesignKNearestNeighbour.cc

$(DEBUGOBJDIR)/DesignKNearestNeighbour.obj: .././PatternRec/Classify/DesignKNearestNeighbour.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignKNearestNeighbour.obj .././PatternRec/Classify/DesignKNearestNeighbour.cc

$(OPTOBJDIR)/ClassifierKNearestNeighbour.obj: .././PatternRec/Classify/ClassifierKNearestNeighbour.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierKNearestNeighbour.obj .././PatternRec/Classify/ClassifierKNearestNeighbour.cc

$(DEBUGOBJDIR)/ClassifierKNearestNeighbour.obj: .././PatternRec/Classify/ClassifierKNearestNeighbour.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierKNearestNeighbour.obj .././PatternRec/Classify/ClassifierKNearestNeighbour.cc

$(OPTOBJDIR)/ClassifierAverageNearestNeighbour.obj: .././PatternRec/Classify/ClassifierAverageNearestNeighbour.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierAverageNearestNeighbour.obj .././PatternRec/Classify/ClassifierAverageNearestNeighbour.cc

$(DEBUGOBJDIR)/ClassifierAverageNearestNeighbour.obj: .././PatternRec/Classify/ClassifierAverageNearestNeighbour.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierAverageNearestNeighbour.obj .././PatternRec/Classify/ClassifierAverageNearestNeighbour.cc

$(OPTOBJDIR)/ClassifierDiscriminantFunction.obj: .././PatternRec/Classify/ClassifierDiscriminantFunction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierDiscriminantFunction.obj .././PatternRec/Classify/ClassifierDiscriminantFunction.cc

$(DEBUGOBJDIR)/ClassifierDiscriminantFunction.obj: .././PatternRec/Classify/ClassifierDiscriminantFunction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierDiscriminantFunction.obj .././PatternRec/Classify/ClassifierDiscriminantFunction.cc

$(OPTOBJDIR)/ClassifierGaussianMixture.obj: .././PatternRec/Classify/ClassifierGaussianMixture.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierGaussianMixture.obj .././PatternRec/Classify/ClassifierGaussianMixture.cc

$(DEBUGOBJDIR)/ClassifierGaussianMixture.obj: .././PatternRec/Classify/ClassifierGaussianMixture.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierGaussianMixture.obj .././PatternRec/Classify/ClassifierGaussianMixture.cc

$(OPTOBJDIR)/DesignClassifierGaussianMixture.obj: .././PatternRec/Classify/DesignClassifierGaussianMixture.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignClassifierGaussianMixture.obj .././PatternRec/Classify/DesignClassifierGaussianMixture.cc

$(DEBUGOBJDIR)/DesignClassifierGaussianMixture.obj: .././PatternRec/Classify/DesignClassifierGaussianMixture.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignClassifierGaussianMixture.obj .././PatternRec/Classify/DesignClassifierGaussianMixture.cc

$(OPTOBJDIR)/ClassifierPreprocess.obj: .././PatternRec/Classify/ClassifierPreprocess.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierPreprocess.obj .././PatternRec/Classify/ClassifierPreprocess.cc

$(DEBUGOBJDIR)/ClassifierPreprocess.obj: .././PatternRec/Classify/ClassifierPreprocess.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierPreprocess.obj .././PatternRec/Classify/ClassifierPreprocess.cc

$(OPTOBJDIR)/ClassifierFunc1Threshold.obj: .././PatternRec/Classify/ClassifierFunc1Threshold.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierFunc1Threshold.obj .././PatternRec/Classify/ClassifierFunc1Threshold.cc

$(DEBUGOBJDIR)/ClassifierFunc1Threshold.obj: .././PatternRec/Classify/ClassifierFunc1Threshold.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierFunc1Threshold.obj .././PatternRec/Classify/ClassifierFunc1Threshold.cc

$(OPTOBJDIR)/ClassifierWeakLinear.obj: .././PatternRec/Classify/ClassifierWeakLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierWeakLinear.obj .././PatternRec/Classify/ClassifierWeakLinear.cc

$(DEBUGOBJDIR)/ClassifierWeakLinear.obj: .././PatternRec/Classify/ClassifierWeakLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierWeakLinear.obj .././PatternRec/Classify/ClassifierWeakLinear.cc

$(OPTOBJDIR)/ClassifierLinearCombination.obj: .././PatternRec/Classify/ClassifierLinearCombination.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierLinearCombination.obj .././PatternRec/Classify/ClassifierLinearCombination.cc

$(DEBUGOBJDIR)/ClassifierLinearCombination.obj: .././PatternRec/Classify/ClassifierLinearCombination.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierLinearCombination.obj .././PatternRec/Classify/ClassifierLinearCombination.cc

$(OPTOBJDIR)/DesignWeakLinear.obj: .././PatternRec/Classify/DesignWeakLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignWeakLinear.obj .././PatternRec/Classify/DesignWeakLinear.cc

$(DEBUGOBJDIR)/DesignWeakLinear.obj: .././PatternRec/Classify/DesignWeakLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignWeakLinear.obj .././PatternRec/Classify/DesignWeakLinear.cc

$(OPTOBJDIR)/ClassifierBayesNormalLinear.obj: .././PatternRec/Classify/ClassifierBayesNormalLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierBayesNormalLinear.obj .././PatternRec/Classify/ClassifierBayesNormalLinear.cc

$(DEBUGOBJDIR)/ClassifierBayesNormalLinear.obj: .././PatternRec/Classify/ClassifierBayesNormalLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierBayesNormalLinear.obj .././PatternRec/Classify/ClassifierBayesNormalLinear.cc

$(OPTOBJDIR)/DesignBayesNormalLinear.obj: .././PatternRec/Classify/DesignBayesNormalLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignBayesNormalLinear.obj .././PatternRec/Classify/DesignBayesNormalLinear.cc

$(DEBUGOBJDIR)/DesignBayesNormalLinear.obj: .././PatternRec/Classify/DesignBayesNormalLinear.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignBayesNormalLinear.obj .././PatternRec/Classify/DesignBayesNormalLinear.cc

$(OPTOBJDIR)/DesignBayesNormalQuadratic.obj: .././PatternRec/Classify/DesignBayesNormalQuadratic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignBayesNormalQuadratic.obj .././PatternRec/Classify/DesignBayesNormalQuadratic.cc

$(DEBUGOBJDIR)/DesignBayesNormalQuadratic.obj: .././PatternRec/Classify/DesignBayesNormalQuadratic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignBayesNormalQuadratic.obj .././PatternRec/Classify/DesignBayesNormalQuadratic.cc

$(OPTOBJDIR)/ClassifierBayesNormalQuadratic.obj: .././PatternRec/Classify/ClassifierBayesNormalQuadratic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierBayesNormalQuadratic.obj .././PatternRec/Classify/ClassifierBayesNormalQuadratic.cc

$(DEBUGOBJDIR)/ClassifierBayesNormalQuadratic.obj: .././PatternRec/Classify/ClassifierBayesNormalQuadratic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierBayesNormalQuadratic.obj .././PatternRec/Classify/ClassifierBayesNormalQuadratic.cc

$(OPTOBJDIR)/ClassifierNeuralNetwork.obj: .././PatternRec/Classify/ClassifierNeuralNetwork.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierNeuralNetwork.obj .././PatternRec/Classify/ClassifierNeuralNetwork.cc

$(DEBUGOBJDIR)/ClassifierNeuralNetwork.obj: .././PatternRec/Classify/ClassifierNeuralNetwork.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierNeuralNetwork.obj .././PatternRec/Classify/ClassifierNeuralNetwork.cc

$(OPTOBJDIR)/DesignClassifierNeuralNetwork.obj: .././PatternRec/Classify/DesignClassifierNeuralNetwork.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DesignClassifierNeuralNetwork.obj .././PatternRec/Classify/DesignClassifierNeuralNetwork.cc

$(DEBUGOBJDIR)/DesignClassifierNeuralNetwork.obj: .././PatternRec/Classify/DesignClassifierNeuralNetwork.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DesignClassifierNeuralNetwork.obj .././PatternRec/Classify/DesignClassifierNeuralNetwork.cc

$(OPTOBJDIR)/FeatureSelector.obj: .././PatternRec/FeatureSelection/FeatureSelector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FeatureSelector.obj .././PatternRec/FeatureSelection/FeatureSelector.cc

$(DEBUGOBJDIR)/FeatureSelector.obj: .././PatternRec/FeatureSelection/FeatureSelector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FeatureSelector.obj .././PatternRec/FeatureSelection/FeatureSelector.cc

$(OPTOBJDIR)/FeatureSelectAsymmetricAdaBoost.obj: .././PatternRec/FeatureSelection/FeatureSelectAsymmetricAdaBoost.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FeatureSelectAsymmetricAdaBoost.obj .././PatternRec/FeatureSelection/FeatureSelectAsymmetricAdaBoost.cc

$(DEBUGOBJDIR)/FeatureSelectAsymmetricAdaBoost.obj: .././PatternRec/FeatureSelection/FeatureSelectAsymmetricAdaBoost.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FeatureSelectAsymmetricAdaBoost.obj .././PatternRec/FeatureSelection/FeatureSelectAsymmetricAdaBoost.cc

$(OPTOBJDIR)/Error.obj: .././PatternRec/Performance/Error.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Error.obj .././PatternRec/Performance/Error.cc

$(DEBUGOBJDIR)/Error.obj: .././PatternRec/Performance/Error.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Error.obj .././PatternRec/Performance/Error.cc



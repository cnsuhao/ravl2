PACKAGE = Ravl/PatternRec

#PACKAGENAME = SVM

MAINS    = oneClassTest.cc \
           oneClassLargeTest.cc \
	   createClassifier.cc \
	   classifyArff.cc \
	   cutArff.cc \
           glueArff.cc \
	   svmTest.cc \
           svmTest2.cc \
	   svmTest3.cc \
	   svmTest4.cc \
	   svmTest5.cc \
	   classifyList.cc \
	   #buildSVM.cc

SOURCES  = virtualConstr.cc \
           DesignSvm.cc \
           Classifier2.cc \
           SvmClassifier.cc \
           SvmLinearClassifier.cc \
           SvmQuadraticClassifier.cc \
           KernelFunc.cc \
           CommonKernels.cc \
           DesignClassifierSvmSmo.cc \
           DesignSvmSmoLarge.cc \
	   ArffIO.cc \
	   OneClass.cc \
	   DesignOneClass.cc \
	   OneClassLinear.cc \
	   DesignOneClassLarge.cc \
           AuxVector.cc

#MUSTLINK = virtualConstr.cc

HEADERS  = DesignSvm.hh \
           Classifier2.hh \
           SvmClassifier.hh \
           SvmLinearClassifier.hh \
           SvmQuadraticClassifier.hh \
           KernelFunc.hh \
           CommonKernels.hh \
           DesignClassifierSvmSmo.hh \
           DesignSvmSmoLarge.hh \
	   ArffIO.hh \
	   OneClass.hh \
	   DesignOneClass.hh \
	   OneClassLinear.hh \
	   DesignOneClassLarge.hh \
           AuxVector.hh

PLIB     = RavlSVM

USESLIBS = RavlCore \
           RavlPatternRec \
	   #RavlSVMAuxVector \
	   #RavlSVMAuxVectorSSE.opt

AUXFILES = testClsSL32.abs testClsSL64.abs

AUXDIR   = share/RAVL/testData/svm

#TESTEXES = testVirtualConstr.cc

EHT      = Ravl.API.Pattern_Recognition.Classifier.SVM.eht


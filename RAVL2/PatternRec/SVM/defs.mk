PACKAGE = Ravl/PatternRec

#PACKAGENAME = SVM

MAINS    = oneClassTest.cc \
           oneClassLargeTest.cc \
           createClassifier.cc \
           classifyArff.cc \
           svmTest.cc \
           svmTest2.cc \
           svmTest3.cc \
           svmTest4.cc \
           svmTest5.cc \
           classifyList.cc \
           #buildSVM.cc

SOURCES  = DesignSvm.cc \
           SvmClassifier.cc \
           SvmLinearClassifier.cc \
           SvmQuadraticClassifier.cc \
           KernelFunc.cc \
           CommonKernels.cc \
           DesignClassifierSvmSmo.cc \
           DesignSvmSmoLarge.cc \
           OneClass.cc \
           DesignOneClass.cc \
           OneClassLinear.cc \
           DesignOneClassLarge.cc \
           SvmVirtualConstr.cc \
           SvmVirtualConstr2.cc

HEADERS  = DesignSvm.hh \
           SvmClassifier.hh \
           SvmLinearClassifier.hh \
           SvmQuadraticClassifier.hh \
           KernelFunc.hh \
           CommonKernels.hh \
           DesignClassifierSvmSmo.hh \
           DesignSvmSmoLarge.hh \
           OneClass.hh \
           DesignOneClass.hh \
           OneClassLinear.hh \
           DesignOneClassLarge.hh \

PLIB     = RavlSVM

USESLIBS = RavlCore \
           RavlPatternRec 

PROGLIBS = ArffIO

AUXFILES = testClsSL32.abs testClsSL64.abs

AUXDIR   = share/RAVL/testData/svm

MUSTLINK= linkRavlSVM.cc

TESTEXES = testSvmXMLFactory.cc

EHT      = Ravl.API.Pattern_Recognition.Classifier.SVM.eht


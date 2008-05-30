PACKAGE = Ravl/PatternRec

#PACKAGENAME = SVM

REQUIRES = USE_SSE2

SOURCES  = AuxVectorSSE.cc

HEADERS  = AuxVectorSSE.hh 

MUSTLINK  = InitAuxVectorSSE.cc

PLIB     = RavlSVMAuxVectorSSE

USESLIBS = RavlCore RavlSVMAuxVector

USERCPPFLAGS=-msse2

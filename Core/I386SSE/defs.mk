PACKAGE = Ravl

DESCRIPTION= SSE2 versions of core operations

#REQUIRES = USE_SSE2

HEADERS = VectorUtilsI386SSE.hh

SOURCES = VectorUtilsI386SSE.cc

MUSTLINK = linkVectorUtilsI386SSE.cc


USERCPPFLAGS=-msse2

PLIB=RavlCore

USESLIBS = RavlCore 

PROGLIBS= RavlMath RavlOS

LIBDEPS = RavlI386SSE.def

TESTEXES= testI386SSE.cc

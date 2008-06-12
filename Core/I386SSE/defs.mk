PACKAGE = Ravl

DESCRIPTION= SSE2 versions of core operations

#REQUIRES = USE_SSE2

HEADERS = VectorUtilsI386SSE.hh

MUSTLINK = VectorUtilsI386SSE.cc

SOURCES = VectorUtilsI386SSEInit.cc

USERCPPFLAGS=-msse2

PLIB=RavlCore
USESLIBS = RavlCore
LIBDEPS = RavlI386SSE.def

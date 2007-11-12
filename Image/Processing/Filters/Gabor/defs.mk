PACKAGE = Ravl/Image

SOURCES = GaborComplex.cc GaborFilter2d.cc 

HEADERS = GaborComplex.hh GaborFilter2d.hh

PLIB = RavlImageProc

LIBDEPS = RavlImageGabor.def

USESLIBS=  RavlCore RavlImage  RavlMath

PROGLIBS = RavlDPDisplay RavlExtImgIO

EXAMPLES = exGaborFilter.cc exGaborComplex.cc

HTML = Gabor.pdf



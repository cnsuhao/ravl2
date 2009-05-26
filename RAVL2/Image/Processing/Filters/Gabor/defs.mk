PACKAGE = Ravl/Image

SOURCES = GaborComplex.cc GaborFilter2d.cc 

HEADERS = GaborComplex.hh GaborFilter2d.hh

LIBDEPS = RavlImageGabor.def

PLIB = RavlImageProc

USESLIBS=  RavlImageProc

PROGLIBS = RavlDPDisplay.opt RavlExtImgIO

EXAMPLES = exGaborFilter.cc exGaborComplex.cc

HTML = Gabor.pdf



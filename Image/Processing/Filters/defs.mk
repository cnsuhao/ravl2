
PACKAGE=Ravl/Image

HEADERS= Convolve2d.hh ConvolveSeparable2d.hh ConvolveHorz2d.hh ConvolveVert2d.hh

SOURCES= Convolve2d.cc

TESTEXES= testConvolve.cc

LIBDEPS=RavlImageFilter.def

PLIB=RavlImage

USESLIBS=RavlImage

PACKAGE=Ravl/MacOSX

REQUIRES=MacOSX

HEADERS=InitAutoReleasepool.hh

SOURCES=MainRunLoop.mm

PLIB=RavlMacOSXRunLoop

MUSTLINK=linkRavlMacOSXRunLoop.cc

USESLIBS=RavlCore RavlOS OSXFoundation
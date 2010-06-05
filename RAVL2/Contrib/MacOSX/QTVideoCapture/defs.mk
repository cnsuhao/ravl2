
REQUIRES=MacOSX

PACKAGE=Ravl/MacOSX

HEADERS=BufferCVImage.hh QTFormat.hh QTVideoCaptureThread.h QTImageIPort.hh

SOURCES=BufferCVImage.cc QTFormat.cc QTVideoCaptureThread.mm  QTImageIPort.mm

PLIB=RavlMacOSXVideoCapture

MAINS=exQTCapture.cc

USESLIBS=RavlCore RavlOSIO RavlImageIO RavlDPDisplay ObjC OSXFoundation OSXQTKit OSXQuartzCore RavlMacOSXRunLoop

MUSTLINK=LinkQTVideoCapture.cc

PACKAGE=Omni/Image

HEADERS= GLIPContext.hh GLIPProgram.hh GLIPBuffer.hh

SOURCES= GLIPContext.cc GLIPProgram.cc GLIPBuffer.cc

PLIB= OmniGLIP

MAINS=  
#testGLIP.cc

USESLIBS=GLUT RavlCore RavlOS RavlImageIO OmniImageProc

PROGLIBS= RavlDPDisplay RavlExtImgIO 

EXTERNALLIBS=GLUT.def

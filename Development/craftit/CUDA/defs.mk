
PACKAGE=Ravl/CUDA

HEADERS=CUDAContext.hh CUDAArray.hh CUDAMemory.hh

SOURCES=CUDAContext.cc CUDAArray.cc CUDAMemory.cc


PLIB= RavlCUDA 

USESLIBS=RavlCore CUDA RLog RavlOS RavlThreads 

PROGLIBS= CUDA RavlOS RavlDPDisplay RavlImageIO RavlExtImgIO

#USERCPPFLAGS += -msse2

CCPPFLAGS += -DRLOG_COMPONENT=RavlCUDA


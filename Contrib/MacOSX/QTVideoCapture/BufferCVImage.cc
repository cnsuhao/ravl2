
#include "Ravl/MacOSX/BufferCVImage.hh"

namespace RavlImageN {

  BufferCVImageBaseC::BufferCVImageBaseC(CVImageBufferRef &aBuffer)
    : m_imageBuffer(aBuffer)
  {
    CVBufferRetain(m_imageBuffer);
    CVPixelBufferLockBaseAddress(m_imageBuffer,0);
  }
  
  // Destructor
  BufferCVImageBaseC::~BufferCVImageBaseC()
  {
    CVPixelBufferUnlockBaseAddress(m_imageBuffer,0);
    CVBufferRelease(m_imageBuffer);  
  }

  // Access start address of buffer.
  void *BufferCVImageBaseC::StartAddress() {
    return CVPixelBufferGetBaseAddress(m_imageBuffer);
  }

  
}

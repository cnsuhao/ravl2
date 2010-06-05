#ifndef RAVL_BUFFER2DCVIMAGE_HEADER
#define RAVL_BUFFER2DCVIMAGE_HEADER 1

#include "Ravl/Buffer2d.hh"
#include <QuartzCore/QuartzCore.h>

namespace RavlImageN {

  //: Base class for handling image buffers.
  class BufferCVImageBaseC
  {
  public:
    BufferCVImageBaseC(CVImageBufferRef &aBuffer);
    //: Constructor.

    ~BufferCVImageBaseC();
    //: Destructor

    // Access start address of buffer.
    void *StartAddress();
  protected:
    CVPixelBufferRef  m_imageBuffer;
  };


  template<class DataT>
  class BufferCVImageBodyC
   : public RavlN::BufferBodyC<DataT>,
     public BufferCVImageBaseC
  {
  public:
    BufferCVImageBodyC(CVPixelBufferRef &aBuffer)
     : BufferCVImageBaseC(aBuffer)
    {
      // Should check the pixel type here.
      this->buff = reinterpret_cast<DataT *>(StartAddress());
    }

  };

  template<class DataT>
  class BufferCVImageC
    : public RavlN::BufferC<DataT>
  {
  public:
    BufferCVImageC(CVPixelBufferRef &aBuffer)
     : RavlN::BufferC<DataT>(new BufferCVImageBodyC<DataT>(aBuffer))
    {}


  };

}
#endif

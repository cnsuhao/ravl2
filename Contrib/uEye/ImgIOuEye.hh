// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the MIT
// License. See http://www.opensource.org/licenses/mit-license.html
// file-header-ends-here
#ifndef RAVL_IMGIOUEYE_HEADER
#define RAVL_IMGIOUEYE_HEADER 1
//! author = "Charles Galambos"

#include <uEye.h>
#include "Ravl/DP/Port.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

namespace RavlImageN {
  
  //! userlevel=Develop
  //: Base class for running uEye camera's
  
  class ImgIOuEyeBaseC {
  public:
    ImgIOuEyeBaseC(const std::type_info &pixelType,UIntT cameraId = 0);    
    //: Constructor.
    
    ~ImgIOuEyeBaseC();
    //: Destructor.
    
    bool Open(UIntT cameraId);
    //: Open camera.
    
    bool SetPixelType(const std::type_info &pixelType);
    //: Set pixel type
    
    bool CaptureImage(char *buffer);
    //: Capture a single image into the given buffer.
    
  protected:
    bool AllocateImages();
    //: Allocate image buffers.
    
    SizeT ImageBufferSize() const
    { return m_sensorInfo.nMaxWidth * m_sensorInfo.nMaxHeight * (m_bitsPerPixel / 8); }
    //: Get size of image in bytes.
    
    enum { UE_NotReady, UE_Ready, UE_Running } m_state;
    
    HIDS m_phf; // Handle to camera.
    SENSORINFO m_sensorInfo;
    
    IndexRange2dC m_captureSize;
    UIntT m_bitsPerPixel;
    
    static const int m_NumBuffers = 4;
    char *m_buffers[m_NumBuffers];
    int m_imgId[m_NumBuffers];
  };
  

  //! userlevel=Develop
  //: Body for uEye
  
  template <class PixelT>
  class ImgIOuEyeBodyC 
    : public RavlN::DPIPortBodyC< ImageC<PixelT> >,
      public ImgIOuEyeBaseC
  {
  public:
    ImgIOuEyeBodyC(UIntT cameraId = 0)
      : ImgIOuEyeBaseC(typeid(PixelT),cameraId)
    {}
    //: Constructor
    
    virtual ImageC<PixelT> Get() {
      ImageC<PixelT> img;
      if (!Get(img))
        throw DataNotReadyC("Failed to get next frame.");
      return img;
    }
    //: Get next frame.
    
    virtual bool Get(ImageC<PixelT> &img) { 
      // Check the device is open
      if (m_state == UE_NotReady)
        return false;
      if(img.Frame() != m_captureSize)
        img = ImageC<PixelT>(m_captureSize);
      return CaptureImage(reinterpret_cast<char *>(&(img[img.Frame().Origin()])));
    }
    //: Get next image.
    
    virtual bool IsGetReady() const 
    { return (m_state != UE_NotReady); }
    //: Are we ready to aquire images ?
    
    virtual bool IsGetEOS() const 
    { return (m_state == UE_NotReady); }
    //: Has the end of stream been reached ?
    
  protected:
    
  };

  //! userlevel=Normal
  //: Handle for connection to uEye camera's
  
  template <class PixelT>
  class ImgIOuEyeC 
    : public RavlN::DPIPortC< ImageC<PixelT> > 
  {
  public:
    ImgIOuEyeC()
      :  RavlN::DPEntityC(true)
    {}
    //: Default constructor.
    
    ImgIOuEyeC(UIntT cameraId)
      : RavlN::DPEntityC(*new ImgIOuEyeBodyC<PixelT>(cameraId))
    {}
    //: Constructor
    
  protected:
    
  };
 
}



#endif

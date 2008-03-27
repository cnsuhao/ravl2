// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the MIT
// License. See http://www.opensource.org/licenses/mit-license.html
// file-header-ends-here
//! author = "Charles Galambos"

#include "Ravl/Image/ImgIOuEye.hh"
#include "Ravl/Exception.hh"
#include "Ravl/OS/SysLog.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  
  //: Constructor.
  
  ImgIOuEyeBaseC::ImgIOuEyeBaseC(const std::type_info &pixelType,UIntT cameraId)
    : m_state(UE_NotReady)
  {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "Open uEye. ");
    for(int i = 0;i < m_NumBuffers;i++)
      m_buffers[i] = 0;
    
    if(!Open(cameraId)) {
      throw ExceptionOperationFailedC("Failed to open camera ");
    }
    if(!SetPixelType(pixelType)) {
      SysLog(SYSLOG_ERR) << "Failed to set pixel type. ";
      m_state = UE_NotReady;
    }
  }
  

  //: Destructor.
  
  ImgIOuEyeBaseC::~ImgIOuEyeBaseC()
  {
    if(m_state == UE_Running) {
      // Need to stop anything ?
      if(is_StopLiveVideo( m_phf, IS_WAIT ) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to stop video. ";        
      }
      m_state = UE_Ready;
    }
    
    // Free buffers.
    for(int i = 0;i < m_NumBuffers;i++) {      
      if(m_buffers[i] == 0)
        continue;
      
      if(is_FreeImageMem(m_phf,m_buffers[i],m_imgId[i]) != IS_SUCCESS) {
        SysLog(SYSLOG_WARNING) << "Failed to free memory. ";
      }
    }
    
    is_ExitCamera(m_phf);
  }

  //: Open camera.
  
  bool ImgIOuEyeBaseC::Open(UIntT cameraId) {
    if(m_state != UE_NotReady) {
      SysLog(SYSLOG_WARNING) << "Camera already open. \n";
      return false;
    }
    m_phf = (HIDS) cameraId;
    int ret;
    if((ret = is_InitCamera(&m_phf,0)) != IS_SUCCESS) {
      SysLog(SYSLOG_ERR) << "Failed to open camera id " << cameraId << ". Return code=" << ret << " ";
      return false;
    }
    if((ret = is_GetSensorInfo(m_phf, &m_sensorInfo)) != IS_SUCCESS) {
      SysLog(SYSLOG_ERR) << "Failed to retrieve sensor infor for camera " << cameraId << " Return code=" << ret << " ";
      return false;
    }
    if(is_SetImageSize(m_phf, m_sensorInfo.nMaxWidth, m_sensorInfo.nMaxHeight) != IS_SUCCESS) {
      SysLog(SYSLOG_ERR) << "Failed to set image size for camera " << cameraId << " Return code=" << ret << " ";
      return false;
    }
    m_captureSize = IndexRange2dC(0,m_sensorInfo.nMaxHeight-1,
                                  0,m_sensorInfo.nMaxWidth-1);
    
    m_state = UE_Ready;
    if(is_EnableEvent( m_phf, IS_SET_EVENT_FRAME) != IS_SUCCESS) {
      SysLog(SYSLOG_ERR) << "Failed to enable event. ";
    }
    
    return true;
  }

  //: Allocate image buffers.
  
  bool ImgIOuEyeBaseC::AllocateImages() {
    
    // Allocate images.
    for(int i = 0;i < m_NumBuffers;i++) {
      // Free buffer is it exists.
      if(m_buffers[i] != 0) 
        is_FreeImageMem(m_phf,m_buffers[i],m_imgId[i]);
      
      // Allocate new entry of the correct size.
      if(is_AllocImageMem (m_phf, m_sensorInfo.nMaxWidth,m_sensorInfo.nMaxHeight,m_bitsPerPixel, &m_buffers[i],&m_imgId[i]) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to allocate image memory. ";
        return false;
      }
      
      // Add to ring buffer.
      if (is_AddToSequence( m_phf,m_buffers[i],m_imgId[i]) != IS_SUCCESS)
        return false;
    }
    return true;
  }
  
  //: Set pixel type
  
  bool ImgIOuEyeBaseC::SetPixelType(const std::type_info &pixelType) {
    if(m_state == UE_Running) {
      // Need to stop anything ?
      if(is_StopLiveVideo( m_phf, IS_WAIT ) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to stop video. ";        
      }
      m_state = UE_Ready;
    }
    
    if(pixelType == typeid(ByteT)) {
      m_bitsPerPixel = 8;
      return (is_SetColorMode(m_phf,IS_SET_CM_Y8) == IS_SUCCESS);
    } else if(pixelType == typeid(ByteRGBValueC)) {
      m_bitsPerPixel = 24;
      return (is_SetColorMode(m_phf,IS_SET_CM_RGB24) == IS_SUCCESS);
    }
    return false;
  }
  
  //: Capture a single image into the given buffer.
  
  bool ImgIOuEyeBaseC::CaptureImage(char *buffer) {
    RavlAssert(buffer != 0);
    if(m_state == UE_NotReady) 
      return false;
    int ret = 0;
    
    // Start video capture if needed.
    if(m_state == UE_Ready) {
      
      // Allocate ring buffer.
      AllocateImages();
      
      if((ret = is_CaptureVideo(m_phf,IS_DONT_WAIT)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to capture video. Status:" << ret << " \n";
        return false;
      }
      m_state = UE_Running;
    }
    
    // Wait for frame to arrive.
    if(is_WaitEvent(m_phf,IS_SET_EVENT_FRAME,200) != IS_SUCCESS) {
      SysLog(SYSLOG_ERR) << "Failed to wait for event. ";
      return false;
    }
    // Find the last full frame to arrive.
    int dummy = 0;
    char *pMem,*pLast;
    if(is_GetActSeqBuf(m_phf, &dummy, &pMem, &pLast ) != IS_SUCCESS) {
      SysLog(SYSLOG_ERR) << "Failed to get active buffer. ";
      return false;
    }
    
    // Copy that buffer.
    UIntT imgId = 0;
    for(int i = 0;i < m_NumBuffers;i++) {
      if(m_buffers[i] == pLast) {
        imgId = m_imgId[i];
        break;
      }
    }
    
    if(is_LockSeqBuf(m_phf,imgId,pLast) != IS_SUCCESS) {
      SysLog(SYSLOG_ERR) << "Failed to lock sequence buffer. ";
      return false;
    }
    memcpy(buffer,pLast,ImageBufferSize());
    RavlAssert(buffer != 0);
    if(is_UnlockSeqBuf(m_phf,imgId,pLast) != IS_SUCCESS) {
      SysLog(SYSLOG_ERR) << "Failed to unlock sequence buffer. ";
    }
    
    return true;
  }
  

}

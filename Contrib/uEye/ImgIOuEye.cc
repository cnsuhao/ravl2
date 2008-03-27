// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the MIT
// License. See http://www.opensource.org/licenses/mit-license.html
// file-header-ends-here
//! author = "Charles Galambos"

#include "Ravl/Image/ImgIOuEye.hh"
#include "Ravl/Exception.hh"
#include "Ravl/OS/SysLog.hh"
#include "Ravl/DP/AttributeValueTypes.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  
  static const char *g_triggerModeNames[] = { "OFF","HI_LO","LO_HI","SOFTWARE",0 };
  
  
  //: Constructor.
  
  ImgIOuEyeBaseC::ImgIOuEyeBaseC(const std::type_info &pixelType,UIntT cameraId)
    : m_triggerMode(TRIG_OFF),
      m_state(UE_NotReady),
      m_snapshot(false)
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
    if(m_snapshot) {
      // Note: Maximum wait is 1 second at the moment.
      if((ret = is_FreezeVideo(m_phf,1000)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to freeze video. ErrorCode:" << ret << " ";
        return false;
      }
    } else {
      // Wait for frame to arrive.
      if(is_WaitEvent(m_phf,IS_SET_EVENT_FRAME,200) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to wait for event. ";
        return false;
      }
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
  

  bool ImgIOuEyeBaseC::HandleGetAttr(const StringC &attrName, StringC &attrValue)
  {
    // Process the int attributes
    if (attrName == "width" || attrName == "height")
    {
      IntT val;
      bool ret = HandleGetAttr(attrName, val);
      attrValue = StringC(val);
      return ret;
    }
    if(attrName == "trigger") {
      attrValue = g_triggerModeNames[m_triggerMode];
      return true;
    }
    
    
    return false;
  }
  
  
  
  bool ImgIOuEyeBaseC::HandleSetAttr(const StringC &attrName, const StringC &attrValue)
  {
    // Process the int attributes
    if(attrName == "width" || attrName == "height")
      return HandleSetAttr(attrName, attrValue.IntValue());
    if(attrValue == "trigger") {
      for(IntT i = 0;g_triggerModeNames[i] != 0;i++) {
        if(attrValue == g_triggerModeNames[i])
          return HandleSetAttr(attrName,i);
      }
      SysLog(SYSLOG_ERR) << "Failed to set unrecognised trigger mode '" << attrValue << "'. ";
      return false;
    }
    return false;
  }
  
  
  
  bool ImgIOuEyeBaseC::HandleGetAttr(const StringC &attrName, IntT &attrValue)
  {
    // Width
    if (attrName == "width") {
      attrValue = m_captureSize.Cols();
      return true;
    }
    
    // Height
    if (attrName == "height") {
      attrValue = m_captureSize.Rows();
      return true;
    }
    if(attrName == "trigger") {
      attrValue = static_cast<IntT>(m_triggerMode);
      return true;
    }
    
    
    return false;
  }
  
  
  
  bool ImgIOuEyeBaseC::HandleSetAttr(const StringC &attrName, const IntT &attrValue)
  {
    // Width
    if (attrName == "width")
    {
      SysLog(SYSLOG_DEBUG) << "Setting width not implemented. ";
      return false;
    }
    
    // Height
    if (attrName == "height")
    {
      SysLog(SYSLOG_DEBUG) << "Setting height not implemented. ";
      return false;
    }
    
    if(attrName == "trigger") {
      uEyeTrigT newTrig = static_cast<uEyeTrigT>(attrValue);
      // Anything to change ?
      if(newTrig == m_triggerMode)
        return true;
      int mode = 0;
      switch(newTrig) {
      case TRIG_OFF:  mode = IS_SET_TRIG_OFF;   break;
      case TRIG_HILO: mode = IS_SET_TRIG_HI_LO; break;
      case TRIG_LOHI: mode = IS_SET_TRIG_LO_HI; break;
      case TRIG_SOFT: mode = IS_SET_TRIG_SOFTWARE;   break;
      }
      int ret;
      if((ret = is_SetExternalTrigger(m_phf,mode)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set trigger mode '" << g_triggerModeNames[attrValue] << "' . ErrorCode:" << ret << " ";
        return false;
      }
      m_triggerMode = newTrig;
      return true;
    }
    
    return false;
  }
  
  bool ImgIOuEyeBaseC::HandleGetAttr(const StringC &attrName, bool &attrValue)
  { 
    if(attrName == "snapshot") {
      attrValue = m_snapshot;
      return true;
    }
    return false;
  }
  
  bool ImgIOuEyeBaseC::HandleSetAttr(const StringC &attrName, const bool &attrValue)
  { 
    if(attrName == "snapshot") {
      if(m_snapshot == attrValue)
        return true;
      // Make sure capture is restarted when we leave snapshot mode.
      if(m_snapshot)
        m_state = UE_Ready;
      else {
        int ret;
        if(m_state == UE_Running) {
          if((ret = is_StopLiveVideo (m_phf,IS_DONT_WAIT)) != IS_SUCCESS) {
            SysLog(SYSLOG_ERR) << "Failed to stop live video. ErrorCode:" << ret << " ";
          }
        }
      }
      m_snapshot = attrValue;
      return true;
    }
    if(attrName == "shutter_speed") {
      RealT oldValue = 0;
      int ret;
      if((ret = is_SetExposureTime (m_phf, attrValue*1000.0,&oldValue)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set shutter speed. ErrorCode:" << ret << "\n";
      }
      return true;
    }

    return false; 
  }
  
  //: Handle get attribute (RealT)
  // Returns false if the attribute name is unknown.
  
  bool ImgIOuEyeBaseC::HandleGetAttr(const StringC &attrName, RealT &attrValue) {
    if(attrName == "trigger_delay") {
      attrValue = (RealT) is_SetTriggerDelay(m_phf,IS_GET_TRIGGER_DELAY) * 1e-6;
      return true;
    }
    if(attrName == "shutter_speed") {
      attrValue = 0; // Incase things go wrong, set to a known value.
      int ret;
      
      if((ret = is_SetExposureTime (m_phf, IS_GET_EXPOSURE_TIME,&attrValue)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to get shutter speed. ErrorCode:" << ret << "\n";
      }
      attrValue /= 1000; // Put time into seconds.
      return true;
    }
    
    return false; 
  }
  
  //: Handle set attribute (RealT)
  // Returns false if the attribute name is unknown.
  
  bool ImgIOuEyeBaseC::HandleSetAttr(const StringC &attrName, const RealT &attrValue) {
    if(attrName == "trigger_delay") {
      // Check value is sensible.
      if(attrValue < 0.0 || attrValue > 30.0)
        return true;
      // Try and set it.
      int value = Round(attrValue * 1e6);
      int ret;
      if((ret = is_SetTriggerDelay(m_phf,value)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set trigger delay to " << value << " ErrorCode:" << ret << "\n";
      }
      return true;
    }
    
    return false; 
  }
  
  bool ImgIOuEyeBaseC::BuildAttributes(AttributeCtrlBodyC &attrCtrl)
  {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "Setting up attribute. ");
    // Image size.
    attrCtrl.RegisterAttribute(AttributeTypeNumC<IntT>("width",         "Width",  true, true,  1,m_sensorInfo.nMaxWidth,  1,  m_sensorInfo.nMaxWidth));
    attrCtrl.RegisterAttribute(AttributeTypeNumC<IntT>("height",        "Height", true, true,  1,m_sensorInfo.nMaxHeight, 1, m_sensorInfo.nMaxHeight));
    
    // Setup trigger modes.
    DListC<StringC> triggerList;
    for(int i = 0;g_triggerModeNames[i] != 0;i++)
      triggerList.InsLast(g_triggerModeNames[i]);
    attrCtrl.RegisterAttribute(AttributeTypeEnumC("trigger", "External triggering mode.", true, true, triggerList, triggerList.First()));
    
    // Setup trigger delay.
    RealT minDelay = (RealT) is_SetTriggerDelay(m_phf,IS_GET_MIN_TRIGGER_DELAY) * 1e-6;
    RealT maxDelay = (RealT) is_SetTriggerDelay(m_phf,IS_GET_MAX_TRIGGER_DELAY) * 1e-6;
    RealT curDelay = (RealT) is_SetTriggerDelay(m_phf,IS_GET_TRIGGER_DELAY) * 1e-6;
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("trigger_delay", "delay after trigger to capture the frame.", true, true, minDelay,maxDelay,0.000001,curDelay));
    
    // Sort out exposure time.
    double curExposure;
    is_SetExposureTime (m_phf, IS_GET_EXPOSURE_TIME,&curExposure);
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("shutter_speed", "Shutter speed in seconds", true, true, 0,100,0.001,curExposure));
    
    // Snapshot mode.
    attrCtrl.RegisterAttribute(AttributeTypeBoolC("snapshot", "Snapshot image capture, (for use with triggering)", true, true, m_snapshot));
    
    return true;
  }
  
  
}

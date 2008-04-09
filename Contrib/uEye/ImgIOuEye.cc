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
      SysLog(SYSLOG_WARNING) << "Camera already open. ";
      return false;
    }
    m_phf = (HIDS) cameraId;
    int ret;
    RavlN::MutexLockC accessLock(m_accessMutex);
    
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
  // Should be called with camera lock aquired
  
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
  // Should be called with camera lock aquired
  
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
    
    RavlN::MutexLockC accessLock(m_accessMutex);
    
    // Start video capture if needed.
    UpdateBuffers();
    
    if(m_snapshot && m_state != UE_TriggerWait) {
      // Note: Maximum wait is 1 second at the moment.
      ONDEBUG(SysLog(SYSLOG_DEBUG) << "Freezing video for capture. ");
      if((ret = is_FreezeVideo(m_phf,10000)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to freeze video for capture. ErrorCode:" << ret << " ";
        return false;
      }
    } else {
      //ONDEBUG(SysLog(SYSLOG_DEBUG) << "Waiting for frame to arrive. ");
      // Wait for frame to arrive.
      if(is_WaitEvent(m_phf,IS_SET_EVENT_FRAME,10000) != IS_SUCCESS) {
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
    
    // Leave trigger
    if(m_state == UE_TriggerWait) {
      
      m_state = UE_Running;
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
    if(attrName == "driver") {
      attrValue = "ueye";
      return true;
    }
    if(attrName == "card") {
      attrValue = m_sensorInfo.strSensorName;
      return true;
    }
    
    return false;
  }
  
  
  
  bool ImgIOuEyeBaseC::HandleSetAttr(const StringC &attrName, const StringC &attrValue)
  {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "ImgIOuEyeBaseC::SetAttr (StringC) " << attrName << " Value='" << attrValue << "'\n");
    
    // Process the int attributes
    if(attrName == "width" || attrName == "height")
      return HandleSetAttr(attrName, attrValue.IntValue());
    
    if(attrName == "trigger") {
      for(IntT i = 0;g_triggerModeNames[i] != 0;i++) {
        if(attrValue == g_triggerModeNames[i]) {
          HandleSetAttr(attrName,i);
          return true;
        }
      }
      SysLog(SYSLOG_ERR) << "Failed to set unrecognised trigger mode '" << attrValue << "'. ";
      return true;
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
    if(attrName == "binning_vertical") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      int mode = is_SetBinning(m_phf,IS_GET_BINNING);
      if(mode & IS_BINNING_2X_VERTICAL) {
        attrValue = 2;
      } if(mode & IS_BINNING_4X_VERTICAL) {
        attrValue = 4;
      } else
        attrValue = 1;
      return true;
    }
    if(attrName == "binning_horizontal") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      int mode = is_SetBinning(m_phf,IS_GET_BINNING);
      if(mode & IS_BINNING_2X_HORIZONTAL) {
        attrValue = 2;
      } if(mode & IS_BINNING_4X_HORIZONTAL) {
        attrValue = 4;
      } else
        attrValue = 1;
      return true;
    }
    
    return false;
  }
  
  
  
  bool ImgIOuEyeBaseC::HandleSetAttr(const StringC &attrName, const IntT &attrValue)
  {
    int ret;
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "ImgIOuEyeBaseC::SetAttr (int) " << attrName << " Value=" << attrValue << "\n");
    
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
      int mode = 0;
      switch(newTrig) {
      case TRIG_OFF:  mode = IS_SET_TRIG_OFF;   break;
      case TRIG_HILO: mode = IS_SET_TRIG_HI_LO; break;
      case TRIG_LOHI: mode = IS_SET_TRIG_LO_HI; break;
      case TRIG_SOFT: mode = IS_SET_TRIG_SOFTWARE;   break;
      }
      int ret;
      if(newTrig == TRIG_OFF && m_state == UE_TriggerWait && m_snapshot) {
        
        // Switch out of trigger mode.
        m_state = UE_Running;
      }
      
      RavlN::MutexLockC accessLock(m_accessMutex);
      UpdateBuffers();
      
      if((ret = is_SetExternalTrigger(m_phf,mode)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set trigger mode '" << g_triggerModeNames[attrValue] << "' . ErrorCode:" << ret << " ";
        return true;
      }
      
      m_triggerMode = newTrig;
      if(newTrig == TRIG_OFF) 
        return true;
      
      if(m_snapshot) {
        // Note: Maximum wait is 1 second at the moment.
        ONDEBUG(SysLog(SYSLOG_DEBUG) << "Started waiting for trigger event. "); 
        if((ret = is_FreezeVideo(m_phf,IS_DONT_WAIT)) != IS_SUCCESS) {
          SysLog(SYSLOG_ERR) << "Failed to freeze video. ErrorCode:" << ret << " ";
          return false;
        }
        m_state = UE_TriggerWait;
      }
      return true;
    }
    if(attrName == "binning_vertical") {
      std::cerr << "Binning modes=" << is_SetBinning(m_phf,IS_GET_SUPPORTED_BINNING) << "\n";
      RavlN::MutexLockC accessLock(m_accessMutex);
      int mode = is_SetBinning(m_phf,IS_GET_BINNING) & ~IS_BINNING_MASK_VERTICAL;
      switch(attrValue) {
      case 1: break;
      case 2: mode = mode | IS_BINNING_2X_VERTICAL ; break;
      case 3:
      case 4: mode = mode | IS_BINNING_4X_VERTICAL ; break;
        break;
      default:
        SysLog(SYSLOG_ERR) << "Unsupported binning request. ";
        return true;
      }
      if((ret = is_SetBinning(m_phf,mode)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set binning mode '" << attrValue  << "' . ErrorCode:" << ret << " ";
        return true;
      }
      
      ResetImageSize();
      
      // Make sure images are reallocated.
      return true;
    }
    if(attrName == "binning_horizontal") {
      std::cerr << "Binning modes=" << is_SetBinning(m_phf,IS_GET_SUPPORTED_BINNING) << "\n";
      RavlN::MutexLockC accessLock(m_accessMutex);
      int mode = is_SetBinning(m_phf,IS_GET_BINNING) & ~IS_BINNING_MASK_HORIZONTAL;
      switch(attrValue) {
      case 1: break;
      case 2: mode = mode | IS_BINNING_2X_HORIZONTAL ; break;
      case 3:
      case 4: mode = mode | IS_BINNING_4X_HORIZONTAL ; break;
        break;
      default:
        SysLog(SYSLOG_ERR) << "Unsupported binning request. ";
        return true;
      }
      if((ret = is_SetBinning(m_phf,mode)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set binning mode '" << attrValue  << "' . ErrorCode:" << ret << " ";
        return true;
      }
      
      ResetImageSize();
      
      // Make sure images are reallocated.
      return true;
    }


    return false;
  }
  
  //: Reset image size
  // Should be called with lock aquired
  
  void ImgIOuEyeBaseC::ResetImageSize() {
    int ret = 0;
    if(m_state == UE_Running) {
      // Need to stop anything ?
      if((ret = is_StopLiveVideo( m_phf, IS_DONT_WAIT )) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to stop video. ErrorCode:" << ret;        
      }
      m_state = UE_Ready;
    }    
  }
  
  //: Update buffer state.
  // Should be called with lock aquired
  
  void ImgIOuEyeBaseC::UpdateBuffers() {
    int ret;
    if(m_state == UE_Ready) {
      // Make sure ring buffer is allocated so we're ready to
      // trigger.
      
      AllocateImages();
      
      if(!m_snapshot) {
        ONDEBUG(SysLog(SYSLOG_DEBUG) << "Starting streaming video capture. ");
        if((ret = is_CaptureVideo(m_phf,IS_DONT_WAIT)) != IS_SUCCESS) {
          SysLog(SYSLOG_ERR) << "Failed to capture video. Status:" << ret << " Snapshot=" << m_snapshot << " ";
        }
      }
      m_state = UE_Running;
    }
  }

  
  bool ImgIOuEyeBaseC::HandleGetAttr(const StringC &attrName, bool &attrValue)
  { 
    if(attrName == "snapshot") {
      attrValue = m_snapshot;
      return true;
    }
    if(attrName == "hardware_gamma") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      attrValue = is_SetHardwareGamma(m_phf,IS_GET_HW_GAMMA);
      return true;
    }
    if(attrName == "auto_shutter") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      double v1 = 0,v2 =0;
      attrValue = is_SetAutoParameter(m_phf,IS_GET_ENABLE_AUTO_SHUTTER,&v1,&v2);
      return true;
    }
    return false;
  }
  
  bool ImgIOuEyeBaseC::HandleSetAttr(const StringC &attrName, const bool &attrValue)
  { 
    int ret;
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "ImgIOuEyeBaseC::SetAttr (bool) " << attrName << " Value=" << attrValue << " ");
    
    if(attrName == "snapshot") {
      if(m_snapshot == attrValue)
        return true;
      // Make sure capture is restarted when we leave snapshot mode.
      if(m_snapshot)
        m_state = UE_Ready;
      else {
        if(m_state == UE_Running) {
          RavlN::MutexLockC accessLock(m_accessMutex);
          if((ret = is_StopLiveVideo (m_phf,IS_DONT_WAIT)) != IS_SUCCESS) {
            SysLog(SYSLOG_ERR) << "Failed to stop live video. ErrorCode:" << ret << " ";
          }
        }
      }
      m_snapshot = attrValue;
      return true;
    }
    if(attrName == "hardware_gamma") {
      int mode = attrValue ? IS_SET_HW_GAMMA_ON : IS_SET_HW_GAMMA_OFF;
      RavlN::MutexLockC accessLock(m_accessMutex);
      if((ret = is_SetHardwareGamma(m_phf,mode)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set hardware gain to " << attrValue << " Error:" << ret;
      }
      return true;
    }
    if(attrName == "auto_shutter") {
      double v1 = attrValue ? 1.0 : 0.0;
      double v2 = 0;
      RavlN::MutexLockC accessLock(m_accessMutex);
      if((ret = is_SetAutoParameter(m_phf,IS_SET_ENABLE_AUTO_SHUTTER,&v1,&v2)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set auto shutter to " << attrValue << " Error:" << ret;
      }
      return true;
    }
    return false; 
  }
  
  //: Handle get attribute (RealT)
  // Returns false if the attribute name is unknown.
  
  bool ImgIOuEyeBaseC::HandleGetAttr(const StringC &attrName, RealT &attrValue) {
    int ret;
    if(attrName == "trigger_delay") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      attrValue = (RealT) is_SetTriggerDelay(m_phf,IS_GET_TRIGGER_DELAY) * 1e-6;
      return true;
    }
    if(attrName == "shutter_speed") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      attrValue = 0; // Incase things go wrong, set to a known value.
      if((ret = is_SetExposureTime (m_phf, IS_GET_EXPOSURE_TIME,&attrValue)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to get shutter speed. ErrorCode:" << ret << "\n";
      }
      attrValue /= 1000; // Put time into seconds.
      return true;
    }
    if(attrName == "pixel_clock") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      attrValue = (RealT) is_SetPixelClock(m_phf,IS_GET_PIXEL_CLOCK) * 1.0e6;
      return true;
    }
    if(attrName == "gain") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      attrValue = (RealT) is_SetHardwareGain(m_phf, IS_GET_MASTER_GAIN,IS_IGNORE_PARAMETER,IS_IGNORE_PARAMETER,IS_IGNORE_PARAMETER) / 100.0;
      return true;
    }
    if(attrName == "gamma") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      attrValue = (RealT) is_SetGamma(m_phf,IS_GET_GAMMA) / 1000.0;
      return true;
    }
    if(attrName == "brightness") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      attrValue = (RealT) is_SetBrightness(m_phf,IS_GET_BRIGHTNESS) / 255.0;
      return true;
    }
    if(attrName == "contrast") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      attrValue = (RealT) is_SetBrightness(m_phf,IS_GET_CONTRAST) / 255.0;
      return true;
    }
    if(attrName == "framerate") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      double framerate = 25;
      if((ret = is_SetFrameRate(m_phf,IS_GET_FRAMERATE,&framerate)) != IS_SUCCESS)
        SysLog(SYSLOG_WARNING) << "Failed to get the current framerate. ";
      attrValue = framerate;
      return true;
    }
    
    return false; 
  }
  
  //: Handle set attribute (RealT)
  // Returns false if the attribute name is unknown.
  
  bool ImgIOuEyeBaseC::HandleSetAttr(const StringC &attrName, const RealT &attrValue) {
    int ret;
    if(attrName == "trigger_delay") {
      // Check value is sensible.
      if(attrValue < 0.0 || attrValue > 30.0)
        return true;
      // Try and set it.
      int value = Round(attrValue * 1e6);
      int ret;
      RavlN::MutexLockC accessLock(m_accessMutex);
      if((ret = is_SetTriggerDelay(m_phf,value)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set trigger delay to " << value << " ErrorCode:" << ret << "\n";
      }
      return true;
    }
    if(attrName == "pixel_clock") {
      RavlN::MutexLockC accessLock(m_accessMutex);
      if((ret = is_SetPixelClock(m_phf,attrValue/1.0e6)) != IS_SUCCESS)
        SysLog(SYSLOG_ERR) << "Failed to set pixel clock to " << attrValue << "\n";
      return true;
    }
    if(attrName == "gain") {
      RealT req = attrValue;
      if(req < 0) req = 0;
      if(req > 1.0) req = 1.0;
      int newGain = RavlN::Round(req * 100.0);
      RavlN::MutexLockC accessLock(m_accessMutex);
      if((ret = is_SetHardwareGain(m_phf,newGain,IS_IGNORE_PARAMETER,IS_IGNORE_PARAMETER,IS_IGNORE_PARAMETER)) != 0) {
        SysLog(SYSLOG_ERR) << "Failed to gain to " << attrValue << " (" << newGain << ")\n";
      }
      return true;
    }
    if(attrName == "gamma") {
      int newGamma = (RealT) attrValue / 1000.0;
      if(newGamma < 1) newGamma = 1;
      if(newGamma > 1000) newGamma = 1000;
      RavlN::MutexLockC accessLock(m_accessMutex);
      if((ret = is_SetGamma(m_phf,IS_GET_GAMMA)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set gamma to " << attrValue << " Error:" << ret;
      }
      return true;
    }
    if(attrName == "brightness") {
      int newBrightness = Round(attrValue * 255.0);
      if(newBrightness < 0) newBrightness = 0;
      if(newBrightness > 255) newBrightness = 255;
      RavlN::MutexLockC accessLock(m_accessMutex);
      if((ret = is_SetBrightness(m_phf,newBrightness)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set brightness to " << attrValue << " Error:" << ret;
      }
      return true;
    }
    if(attrName == "contrast") {
      int newContrast = Round(attrValue * 255.0);
      if(newContrast < 0) newContrast = 0;
      if(newContrast > 511) newContrast = 511;
      RavlN::MutexLockC accessLock(m_accessMutex);
      if((ret = is_SetContrast(m_phf,newContrast)) != IS_SUCCESS) {
        SysLog(SYSLOG_ERR) << "Failed to set contrast to " << attrValue << " Error:" << ret;
      }
      return true;
    }
    if(attrName == "framerate") {
      double framerate = attrValue;
      RavlN::MutexLockC accessLock(m_accessMutex);
      if((ret = is_SetFrameRate(m_phf,framerate,&framerate)) != IS_SUCCESS)
        SysLog(SYSLOG_WARNING) << "Failed to set the framerate to " << framerate << " ";
      return true;
    }
    
    return false; 
  }
  
  bool ImgIOuEyeBaseC::BuildAttributes(AttributeCtrlBodyC &attrCtrl)
  {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "Setting up attribute. ");
    int ret;
    RavlN::MutexLockC accessLock(m_accessMutex);
    
    // Information about the driver.
    attrCtrl.RegisterAttribute(AttributeTypeStringC("driver", "Name of driver", true, false,"ueye"));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("card", "Capture card", true, false,"-?-"));
    
    // Image size.
    attrCtrl.RegisterAttribute(AttributeTypeNumC<IntT>("width",  "Width",  true, true,  1,m_sensorInfo.nMaxWidth,  1,  m_sensorInfo.nMaxWidth));
    attrCtrl.RegisterAttribute(AttributeTypeNumC<IntT>("height", "Height", true, true,  1,m_sensorInfo.nMaxHeight, 1, m_sensorInfo.nMaxHeight));
    
    // TODO: Check available modes.
    attrCtrl.RegisterAttribute(AttributeTypeNumC<IntT>("binning_vertical", "Binning level 1,2,4 pixels.", true, true,  1,4, 1, 1));
    attrCtrl.RegisterAttribute(AttributeTypeNumC<IntT>("binning_horizontal", "Binning level 1,2,4 pixels.", true, true,  1,4, 1, 1));
    
#if 0
    // TODO: Check available modes.
    attrCtrl.RegisterAttribute(AttributeTypeNumC<IntT>("subsample_vertical", "Binning level 1,2,4 pixels.", true, true,  1,4, 1, 1));
    attrCtrl.RegisterAttribute(AttributeTypeNumC<IntT>("subsample_horizontal", "Binning level 1,2,4 pixels.", true, true,  1,4, 1, 1));
#endif
    
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
    
    // Hardware Gain
    double curGain;
    curGain = (RealT) is_SetHardwareGain(m_phf, IS_GET_MASTER_GAIN,IS_IGNORE_PARAMETER,IS_IGNORE_PARAMETER,IS_IGNORE_PARAMETER) / 100.0;
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("gain", "Gain 0.0 to 1.0", true, true, 0,1,0.01,curGain));
    
    // Snapshot mode.
    attrCtrl.RegisterAttribute(AttributeTypeBoolC("snapshot", "Snapshot image capture, (for use with triggering)", true, true, m_snapshot));

    // Apply gamma correction ?
    bool gammaMode = is_SetHardwareGamma(m_phf,IS_GET_HW_GAMMA);
    attrCtrl.RegisterAttribute(AttributeTypeBoolC("hardware_gamma", "Use hardware gamma correction", true, true,gammaMode));
    
    RealT gammaValue = (RealT) is_SetGamma(m_phf,IS_GET_GAMMA) / 1000;
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("gamma", "Gamma correction", true, true, 0.01,10,0.01,gammaValue));
    
    // Brightness
    RealT defaultBrightness = (RealT) is_SetBrightness(m_phf,IS_GET_BRIGHTNESS) / 255.0;
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("brightness", "Brightness as a fraction of available values", true, true, 0,1,0.01,defaultBrightness));

    // Contrast
    RealT defaultContrast = (RealT) is_SetContrast(m_phf,IS_GET_CONTRAST) / 255.0;
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("contrast", "Contrast as a fraction of available values 0.0 to 2.0", true, true, 0,2,0.005,defaultContrast));
    
    // Frame rate
    double frameRate = 25;
    if((ret = is_SetFrameRate(m_phf,IS_GET_FRAMERATE,&frameRate)) != IS_SUCCESS)
      SysLog(SYSLOG_WARNING) << "Failed to get the current framerate. ";
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("framerate", "Frames per second", true, true, 0,160,0.1,frameRate));
    
    // Pixel clock
    RealT curPixelClock = is_SetPixelClock(m_phf,IS_GET_PIXEL_CLOCK);
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("pixel_clock", "Pixel clock", true, true, 0,100e6,1e6,curPixelClock));
    
    // Auto shutter
    double v1 = 0,v2 = 0;
    bool autoShutter = is_SetAutoParameter(m_phf,IS_GET_ENABLE_AUTO_SHUTTER,&v1,&v2);
    attrCtrl.RegisterAttribute(AttributeTypeBoolC("auto_shutter", "Automaticly set the shutter speed", true, true,autoShutter));
    
    return true;
  }
  
  
}

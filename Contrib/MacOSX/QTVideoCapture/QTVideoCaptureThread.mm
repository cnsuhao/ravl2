#import "Ravl/MacOSX/QTVideoCaptureThread.h"
#import "Ravl/MacOSX/BufferCVImage.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ByteYUV422Value.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/IO.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/MacOSX/InitAutoReleasepool.hh"


#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

@implementation RavlQTCaptureThread

- (BOOL)openCamera: (const std::type_info *)pixelType
{
  
  mCaptureSession = [[QTCaptureSession alloc] init];
  QTCaptureDevice *videoDevice = [QTCaptureDevice defaultInputDeviceWithMediaType:QTMediaTypeVideo];
  
  BOOL success = NO;
  NSError *error;
  success = [videoDevice open:&error];
  
  mCaptureVideoDeviceInput = [[QTCaptureDeviceInput alloc] initWithDevice:videoDevice];
  success = [mCaptureSession addInput:mCaptureVideoDeviceInput error:&error];
  
  if(!success) {
    NSLog(@"Failed to start capture session. Error: %@", error);
    return false;
  }
  
  mCaptureVideoOutput = [[QTCaptureDecompressedVideoOutput alloc] init];
  
  id usePixelType;
  if (*pixelType == typeid(RavlImageN::ByteRGBValueC)) {
    usePixelType = [NSNumber numberWithUnsignedInt:kCVPixelFormatType_24RGB];
  } else if (*pixelType == typeid(RavlN::UInt16T)) {
    usePixelType = [NSNumber numberWithUnsignedInt:kCVPixelFormatType_16Gray];
  } else if (*pixelType == typeid(RavlImageN::ByteYUV422ValueC)) {
    usePixelType = [NSNumber numberWithUnsignedInt:kCVPixelFormatType_422YpCbCr8];
  } else if (*pixelType == typeid(RavlImageN::ByteYUVValueC)) {
    usePixelType = [NSNumber numberWithUnsignedInt:kCVPixelFormatType_444YpCbCr8];
  } else  {
    RavlAssertMsg(0,"Pixel format not recognised. ");
    return false;
  }
  
  [mCaptureVideoOutput setPixelBufferAttributes:[NSDictionary dictionaryWithObjectsAndKeys:
                                                 usePixelType,(id)kCVPixelBufferPixelFormatTypeKey,
                                                 nil] ];
  
  [mCaptureVideoOutput setAutomaticallyDropsLateVideoFrames:TRUE];
  [mCaptureVideoOutput setDelegate:self];
  
  success = [mCaptureSession addOutput:mCaptureVideoOutput error:&error];
  if (!success) {
    NSLog(@"Failed to add output. Error: %@", error);
    return false;
  }
  return TRUE;
}

- (void)startCapture
{
  ONDEBUG(NSLog(@"Starting capture. "));
  [mCaptureSession startRunning];
  ONDEBUG(NSLog(@"Capture running "));
}


- (void)stopCapture
{
  ONDEBUG(NSLog(@"Stoping capture. "));
  [mCaptureSession stopRunning];
}

- (void)setFrameHandler:(RavlImageN::QTCaptureThreadBodyC *)frameHandler
{
  mCaptureThread = frameHandler;
}


- (void)captureOutput:(QTCaptureOutput *)captureOutput 
  didOutputVideoFrame:(CVImageBufferRef)videoFrame 
     withSampleBuffer:(QTSampleBuffer *)sampleBuffer 
       fromConnection:(QTCaptureConnection *)connection
{
  if(mCaptureThread != 0)
    mCaptureThread->RecieveBuffer(videoFrame);
  else {
    NSLog(@"Nowhere to send images %@", [NSCalendarDate calendarDate]);
  }
  ONDEBUG(NSLog(@"Got image at %@", [NSCalendarDate calendarDate]));
}



@end

namespace RavlImageN {

  QTCaptureThreadBodyC::QTCaptureThreadBodyC(const RavlN::StringC &name,const std::type_info &pixelType)
    : m_name(name),
      m_captureThread(0),
      m_pixelType(pixelType)
  {
    AutoReleasepoolInit();
    m_captureThread = [[RavlQTCaptureThread alloc] init];
    [m_captureThread setFrameHandler:this];
  }

  QTCaptureThreadBodyC::~QTCaptureThreadBodyC()
  {
    [m_captureThread stopCapture];
    [m_captureThread setFrameHandler:0];
  }
  
  //: start capture
  bool QTCaptureThreadBodyC::Start()
  {
    AutoReleasepoolInit();
    if(![ m_captureThread openCamera: &m_pixelType ]) 
      return false;
    [m_captureThread startCapture];
    return true;
  }

  
  //: stop capture
  bool QTCaptureThreadBodyC::Stop() {
    [m_captureThread stopCapture];
    return true;
  }
    
  //! Handle incoming buffer
  bool QTCaptureThreadBodyC::RecieveBuffer(CVImageBufferRef &videoFrame)
  {
    RavlAssertMsg(0,"abstract method");
    return true;
  }


}


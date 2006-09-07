// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here


#include "Ravl/OS/Filename.hh"
#include "Ravl/Image/Image.hh"

#include "Ravl/Image/WindowsMediaConverter.hh"
#include "atlcomcli.h" //For CComQIPtr
#include "comutil.h"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN 
{
  #define ONE_SECOND 10000000

  //**********************Implementation of the DPWinFileRendererC class**********************

  DPWinFileRendererC::DPWinFileRendererC(const StringC &filename) 
   : m_bCanRenderFile(false), 
     m_bInitSucceeded(false),
     m_bCanSeek(false),
     m_bFrameFormat(false), 
     m_numFrames(0), 
     m_currentFrame(0), 
     m_msTimeout(10000), 
     m_dFrameRate(0), 
     m_dStreamLength(0),
     m_pGraphBuilder(NULL), 
     m_pGrabberBaseFilter(NULL), 
     m_pSampleGrabber(NULL), 
     m_pMediaControl(NULL), 
     m_pMediaEventEx(NULL), 
     m_pSeek(NULL)
  {
    m_strFileName = filename;
    m_strFileName.gsub("/","\\");
    StringC strError;
    //Initialise the filter graph and get a ROUGH estimate of the footage length
    if(!Initialise(strError)) {
      ONDEBUG(cerr << "Failed to initialise direct show :" << strError << endl);
      return ;
    }
    //Enable the call below to get an accurate estimate of the footage length 
    //GetFootageLengthAccurate();
    ONDEBUG(cerr << "Ravl DirectShow setup complete. \n");
  }

  DPWinFileRendererC::DPWinFileRendererC() 
    : m_bCanRenderFile(false), 
    m_bInitSucceeded(false),
    m_bCanSeek(false), 
    m_bFrameFormat(false), 
    m_numFrames(0), 
    m_currentFrame(0), 
    m_msTimeout(10000),
    m_dFrameRate(0), 
    m_dStreamLength(0),  
    m_pGraphBuilder(NULL), 
    m_pGrabberBaseFilter(NULL), 
    m_pSampleGrabber(NULL), 
    m_pMediaControl(NULL), 
    m_pMediaEventEx(NULL), 
    m_pSeek(NULL)
  {
    m_strFileName = "";
  }

  DPWinFileRendererC::~DPWinFileRendererC()
  {
    ReleaseInterfaces();
  }

  void DPWinFileRendererC::ReleaseInterfaces()
  {
    if(m_pSeek)
    {
      m_pSeek->Release();
      m_pSeek = NULL;
    }
    if(m_pMediaControl)
    {
      m_pMediaControl->Release();
      m_pMediaControl = NULL;
    }
    if(m_pMediaEventEx)
    {
      m_pMediaEventEx->Release();
      m_pMediaEventEx = NULL;
    }
    if(m_pGrabberBaseFilter)
    {
      m_pGrabberBaseFilter->Release();
      m_pGrabberBaseFilter = NULL;
    }
    if(m_pSampleGrabber)
    {
      m_pSampleGrabber->Release();
      m_pSampleGrabber = NULL;
    }
    if(m_pGraphBuilder)
    {
      m_pGraphBuilder->Release();
      m_pGraphBuilder = NULL;
    }
  }

  bool DPWinFileRendererC::CanRenderFile()
  {
    return m_bCanRenderFile;
  }

  bool DPWinFileRendererC::CanOpenFile()
  {
    FilenameC videoFile(m_strFileName);
    return videoFile.Exists();
  }

  void DPWinFileRendererC::GetErrorMsg(HRESULT hr, StringC& strErr) const
  {
    TCHAR szErr[MAX_ERROR_TEXT_LEN];
    char errBuff[MAX_ERROR_TEXT_LEN];

    DWORD res = AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
    if (res == 0)
    {
      sprintf_s(errBuff, "Unknown Error: 0x%2x", hr);
    }
    else
    { 
      //Convert tchar to char
      int i = 0;
      while(szErr[i] != '\0')
      {
        errBuff[i] = (char) szErr[i];
        i++;
      }
      errBuff[i] = (char) szErr[i];
    }
    strErr = errBuff;
  }       

  // Construct the filter graph returns true if it is possible to render the file

  bool DPWinFileRendererC::InitialiseFilterGraph(StringC& strErrorMsg)
  {
    if(m_bInitSucceeded)
    {
      strErrorMsg = "Already initialised.";
      return true;
    }
    ReleaseInterfaces();
    if(!CanOpenFile())
    {
      ONDEBUG(cerr << "Can't open file. '" << m_strFileName << "' \n");
      strErrorMsg = "Unable to open video file";
      return false;
    }

    // Create the graph builder
    HRESULT hr = ::CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder);
    if (FAILED(hr))
    {
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }

     //Create the "Grabber filter"
    hr = ::CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (LPVOID *)&m_pGrabberBaseFilter);
    if (FAILED(hr))
    {
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    //Add the grabber filter to the filter graph
    hr = m_pGraphBuilder->AddFilter(m_pGrabberBaseFilter,L"Grabber");
    if (FAILED(hr))
    {
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    //Get the sample grabber interface
    m_pGrabberBaseFilter->QueryInterface(IID_ISampleGrabber, (void**)&m_pSampleGrabber);
    if (FAILED(hr))
    {
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    if (m_pSampleGrabber == NULL)
    {
      ONDEBUG(cerr << "RAVL Direct Show: failed to setup grabber. \n");
      return false;
    }
    
    //Set the media type 
    //For RGB 24, every pixel is an RGBTRIPLE. Each color is one byte, with a value from 0 to 255, inclusive.
    AM_MEDIA_TYPE   mt;
    ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
    mt.majortype = MEDIATYPE_Video;
    mt.subtype = MEDIASUBTYPE_RGB24;
    mt.formattype = FORMAT_VideoInfo; 
    hr = m_pSampleGrabber->SetMediaType(&mt);
    if (FAILED(hr))
    {
      ONDEBUG(cerr << "RAVL Direct Show: failed to setup media type. " << endl);
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    //Free the media type
    FreeMediaType(mt);

    //RenderFile builds the filter graph
    WCHAR wFile[MAX_PATH];
    MultiByteToWideChar( CP_ACP, 0, m_strFileName, -1, wFile, MAX_PATH );
    hr = m_pGraphBuilder->RenderFile(wFile,NULL);
    if (FAILED(hr))
    {
      ONDEBUG(cerr << "RAVL Direct Show: Call to RenderFile failed. " << endl);
      m_bCanRenderFile = false;
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    m_bCanRenderFile = true;
  
    // QueryInterface for some basic interfaces
    m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void **)&m_pMediaControl);
    m_pGraphBuilder->QueryInterface(IID_IMediaEvent, (void **)&m_pMediaEventEx);

    if (m_pMediaControl == NULL || m_pMediaEventEx == NULL)
    {
      ONDEBUG(cerr << "RAVL Direct Show: Failed to get handles to media controls. " << endl);
      return false;
    }

    // Enable the lines below to render the video to a window   
#if 0
    m_pMediaControl->Run();
    long evCode;
    hr = m_pMediaEventEx->WaitForCompletion(INFINITE, &evCode);
    if (FAILED(hr))
    {
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
#endif 

    // Set buffering to true (copy of each sample taken before passing it on downstream)
    hr = m_pSampleGrabber->SetBufferSamples(TRUE);
    if (FAILED(hr))
    {
      ONDEBUG(cerr << "RAVL Direct Show: Failed to set BufferSamples. " << endl);
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    //Get the IMediaSeeking interface
    m_pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeek);
    if (m_pSeek == NULL)
    {
      strErrorMsg = "Failed to get seek control.";
      ONDEBUG(cerr << "RAVL Direct Show: Failed to get seek interface. " << endl);
      return false;     
    }

    //Check whether the file has absolute seeking `capabilities
    DWORD dwReqCaps = AM_SEEKING_CanSeekAbsolute | AM_SEEKING_CanSeekForwards;
    HRESULT hrCanSeek = m_pSeek->CheckCapabilities(&dwReqCaps);
    if (hrCanSeek != S_OK) 
    {
      ONDEBUG(cerr << "DPWinFileRendererC::InitialiseFilterGraph, WARNING: Seeking not supported. \n");
      // The stream cannot seek
      strErrorMsg = "Absolute seeking is not supported\n";
      m_bCanSeek = false;
      return false;
    }

    //Attempt to set the time format to frame, this makes life easier later
    hr = m_pSeek->SetTimeFormat(&TIME_FORMAT_FRAME);
    if(SUCCEEDED(hr))
    {
      m_bFrameFormat = true;
      m_bCanSeek = true;
    }
    else
    {
     hr = m_pSeek->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME);
     if(SUCCEEDED(hr))
     {
       m_bCanSeek = true;
     }
    }
    m_bInitSucceeded = true;
    strErrorMsg = "DirectShow graph initialisation succeeded";
    ONDEBUG(cerr << "RAVL Direct Show: Setup filter graph ok. " << endl);
    return true;
  }

  bool DPWinFileRendererC::IsInitialised()
  {
    return m_bInitSucceeded;
  }

  // Initialise the source info and filter graph
  bool DPWinFileRendererC::Initialise(StringC& strError)
  {
    if(!InitialiseSourceInfo(strError) || !InitialiseFilterGraph(strError))
    {
      return false;
    }
    if((int)m_dFrameRate == 0)
    {
      //Currently we have to guess a frame rate as we have no "quick and dirty" method
      //for getting the frame rate of certain files e.g. ASF
      m_dFrameRate = 25; 
      m_numFrames = Round(m_dStreamLength * m_dFrameRate);
    }
    m_bInitSucceeded = true;
    return true;
  }

  bool DPWinFileRendererC::InitialiseSourceInfo(StringC& strErrorMsg)
  {
    if(m_bInitSucceeded)
    {
      strErrorMsg = "Already initialised.";
      return true;  //Source info has already been initialised
    }

    CComQIPtr<IMediaDet> pMediaDet;
    HRESULT hr = ::CoCreateInstance(CLSID_MediaDet, NULL, CLSCTX_INPROC_SERVER, IID_IMediaDet, (void**)&pMediaDet);

    //Does the file exist and can it be read
    if(!CanOpenFile())
    {
      strErrorMsg = "Can't open file.";
      ONDEBUG(cerr << "RAVL Direct Show: can't open file. '" << m_strFileName << "' \n");
      return false;
    }
    char* fileName = const_cast<char*> (m_strFileName.chars());
    BSTR bstrFileName = _com_util::ConvertStringToBSTR(fileName);   

    //Tell the graph which file to render
    hr = pMediaDet->put_Filename(bstrFileName);
    SysFreeString(bstrFileName);
    if(FAILED(hr))
    {
      ONDEBUG(cerr << "RAVL Direct Show: failed to open file '" << fileName << "' \n"); 
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
     
    long lNumStreams = 0;
    hr = pMediaDet->get_OutputStreams(&lNumStreams);
    if(FAILED(hr))
    {
      ONDEBUG(cerr << "RAVL Direct Show: failed to get number of output streams. \n");
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    //Iterate through the streams and set the current stream to the video stream
    bool bVideoStreamExists = false;   //Paranoia really
    
    for(int i = 0; i < lNumStreams; i++)
    {
      GUID streamGUID;
      hr = pMediaDet->put_CurrentStream(i);
      hr = pMediaDet->get_StreamType(&streamGUID);
      if(streamGUID == MEDIATYPE_Video)
      {
        bVideoStreamExists = true;
        break;
      }
    }
    if(!bVideoStreamExists && lNumStreams > 1)
    {
      ONDEBUG(cerr << "RAVL Direct Show: No video stream found, or too many to choose from.  Streams: " << lNumStreams << endl);
      strErrorMsg = "No video stream exists in file ";
      strErrorMsg += m_strFileName;
      return false;
    }
    if(!bVideoStreamExists) {
      cerr << "RAVL Direct Show: No video stream found but only 1 channel. Attempting to setup video decode in blind optimism \n";
    }

    //Get a rough estimate of the number of frames, stream length and frame rate
    hr = pMediaDet->get_FrameRate(&m_dFrameRate);
    if(FAILED(hr))
    {
      ONDEBUG(cerr << "RAVL Direct Show: failed to read framerate. \n");
      GetErrorMsg(hr, strErrorMsg);
      //  return false;
    }

    hr = pMediaDet->get_StreamLength(&m_dStreamLength);
    if(FAILED(hr))
    {
      ONDEBUG(cerr << "RAVL Direct Show: failed to read stream length. ");
      GetErrorMsg(hr, strErrorMsg);
      // return false;
    }

    //Estimate the number of frames     
    m_numFrames = (long) (m_dStreamLength * m_dFrameRate);    
    
    ONDEBUG(cerr << "RAVL Direct Show: Setup source ok. \n");
    return true;
  }

  //This funtion provides a more accurate estimate of footage length
  bool DPWinFileRendererC::GetFootageLengthAccurate()
  {
    cerr <<"Begin calc footage length\n";
 
    CComQIPtr<IMediaFilter> pMediaFilter;
    m_pGraphBuilder->QueryInterface(IID_IMediaFilter, (void**)&pMediaFilter);
    HRESULT hr = pMediaFilter->SetSyncSource(NULL);  //Temporarily switch off the clock

    m_pSampleGrabber->SetBufferSamples(FALSE);
    m_pSampleGrabber->SetOneShot(FALSE);
    m_grabberCB.Init(); //Initialise the callback class
    m_pSampleGrabber->SetCallback(&m_grabberCB, 0); // 0 = Use the SampleCB callback method

    //Make sure the video is not rendered to a window
    CComQIPtr<IVideoWindow> pVideoWindow = m_pGraphBuilder;
    hr = pVideoWindow->put_AutoShow(OAFALSE);

    //Run the filter graph. Every frame triggers the SampleCB method
    StringC strErrorMsg;
    hr = m_pMediaControl->Run();
    if (FAILED(hr))
    {
       GetErrorMsg(hr, strErrorMsg);
       return false;
    }

    long timeout = 10000; //Set the timeout to 10 seconds. If it takes longer than this just use the previously estimated values
    long evCode;
    hr = m_pMediaEventEx->WaitForCompletion(timeout, &evCode);
  //  hr = m_pMediaEventEx->WaitForCompletion(INFINITE, &evCode);
    
    if(SUCCEEDED(hr) && evCode == EC_COMPLETE)
    {
      long numFrames;
      hr = m_grabberCB.GetNumFrames(numFrames);
      if(SUCCEEDED(hr))
      {
        m_numFrames = numFrames;
      }
    }
    //Cancel the callback
    m_pSampleGrabber->SetCallback(NULL, 0);
    m_pSampleGrabber->SetOneShot(TRUE);

    //Reset the clock back to the default value
    m_pGraphBuilder->SetDefaultSyncSource();
    cerr <<"End calc footage length, num frames: " << m_numFrames << "\n";    
    return true;
  }

  //: Get the frame size from the stream.

  bool DPWinFileRendererC::GetFrameSize(IndexRange2dC &frameSize) {
    //Specify the media type
    AM_MEDIA_TYPE MediaType;
    ZeroMemory(&MediaType,sizeof(MediaType));
    HRESULT hr = m_pSampleGrabber->GetConnectedMediaType(&MediaType); 
    if (FAILED(hr))
    {
      StringC strErrorMsg;
      GetErrorMsg(hr, strErrorMsg);
      ONDEBUG(cerr << "Failed to get media type. Error:" << strErrorMsg << endl);
      return false;
    } 
    // Get a pointer to the video header.
    VIDEOINFOHEADER *pVideoHeader = (VIDEOINFOHEADER*)MediaType.pbFormat;
    if (pVideoHeader == NULL)
    {
      ONDEBUG(cerr << "Failed to find video header.\n");
      FreeMediaType(MediaType);
      return false;
    }

    // The video header contains the bitmap information. 
    // Copy it into a BITMAPINFO structure.
    BITMAPINFO BitmapInfo;
    ZeroMemory(&BitmapInfo, sizeof(BitmapInfo));
    CopyMemory(&BitmapInfo.bmiHeader, &(pVideoHeader->bmiHeader), sizeof(BITMAPINFOHEADER));

    //Get the number of rows and columns in pixels

    long numRows = BitmapInfo.bmiHeader.biHeight;
    long numCols = BitmapInfo.bmiHeader.biWidth;
    frameSize = IndexRange2dC(numRows,numCols);
    FreeMediaType(MediaType);
    return true;
  }
 
  bool DPWinFileRendererC::RawBuffersIdentical(long buffSizeA, char* pBuffA, long buffSizeB, char* pBuffB)
  {
    if(buffSizeA != buffSizeB)
    {
      return false;
    }

    for(int nIndex = 0; nIndex < buffSizeA; nIndex++)
    {
      if(pBuffA[nIndex] != pBuffB[nIndex])
      {
        return false;
      }
    }
    return true;
  }
 
  //Get the raw buffer image

  bool DPWinFileRendererC::GetBufferImage(long& buffSize, char*& pBuff, StringC& strErrorMsg)
  {
    pBuff = NULL;
    buffSize = 0;
    if(!m_bCanSeek || !m_bCanRenderFile)
    {
      strErrorMsg = "Not setup correctly.";
      ONDEBUG(cerr << "DPWinFileRendererC::GetBufferImage, Stream is not seekable, failed to get buffer. \n");
      return false;
    }

    //Convert the current frame number to a time in seconds
    double multFactor = m_dStreamLength / m_numFrames;
    double dTimeInSeconds = m_currentFrame * multFactor;
    double dStopTimeInSeconds = (m_currentFrame +1.1) * multFactor;
    dStopTimeInSeconds = (dStopTimeInSeconds > m_dStreamLength ? m_dStreamLength : dStopTimeInSeconds);   

    REFERENCE_TIME rtStart = (m_bFrameFormat ? (LONGLONG) m_currentFrame : REFERENCE_TIME (dTimeInSeconds * ONE_SECOND));
    REFERENCE_TIME rtStop = (m_bFrameFormat ? (LONGLONG) (m_currentFrame) : REFERENCE_TIME (dStopTimeInSeconds * ONE_SECOND));
    	
    //Set the new "current" position to rtStart also set the stop position to this frame since we're only
    //capturing one image. Use AM_SEEKING_SeekToKeyFrame
    //for absolute position. This functionality is not supported by any of the standard DirectShow filters
    HRESULT hr = m_pSeek->SetPositions(&rtStart, AM_SEEKING_AbsolutePositioning,&rtStop, AM_SEEKING_AbsolutePositioning);
    if (FAILED(hr))
    {
      ONDEBUG(cerr << "DPWinFileRendererC::GetBufferImage, Failed to set position. \n");
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    
    //Tell the sample grabber we're only grabbing one frame  
    hr = m_pSampleGrabber->SetBufferSamples(TRUE);
    if (FAILED(hr))
    {
      ONDEBUG(cerr << "Set buffer samples failed. \n");
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    hr = m_pSampleGrabber->SetOneShot(TRUE);
    if (FAILED(hr))
    {
      ONDEBUG(cerr << "One shot mode not supported. \n");
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    // Prevent the image from being displayed in the DirectShow video window (disable if you want to see
    //the image you're capturing)
#if 1
    CComQIPtr<IVideoWindow> pVideoWindow = m_pGraphBuilder;
    hr = pVideoWindow->put_AutoShow(OAFALSE);
    if (FAILED(hr))
    {
      ONDEBUG(cerr << "DPWinFileRendererC::GetBufferImage, Failed to disable autoshow. \n");
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
#endif

    // Run the graph and wait for completion.
    hr = m_pMediaControl->Run();
    if (FAILED(hr))
    {
      ONDEBUG(cerr << "DPWinFileRendererC::GetBufferImage, Failed to run sequence. \n");
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }

    long evCode;
    hr = m_pMediaEventEx->WaitForCompletion(m_msTimeout, &evCode);
    //hr = m_pMediaEventEx->WaitForCompletion(INFINITE, &evCode);
    if (FAILED(hr))
    {
      ONDEBUG(cerr << "DPWinFileRendererC::GetBufferImage, Failed to wait for completion. \n");
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    
    //Get the image size
    hr = m_pSampleGrabber->GetCurrentBuffer(&buffSize, NULL); 
    if (FAILED(hr))
    {
      GetErrorMsg(hr, strErrorMsg);
      return false;
    }
    if(buffSize < 1)
    {
      strErrorMsg = "Invalid buffer size";
      return false;
    }
    pBuff = new char[buffSize];
    if (!pBuff) 
    {
      strErrorMsg = "Out of memory";
      return false;
    }

    hr = m_pSampleGrabber->GetCurrentBuffer(&buffSize, (long*)pBuff);
    if (FAILED(hr))
    {
      GetErrorMsg(hr, strErrorMsg);
      delete [] pBuff;
      pBuff = 0;
      return false;
    }

    return true;
  }
  
  long DPWinFileRendererC::GetTotalFrames() const
  {
    return m_numFrames;
  }

  //Get the RGB image. 
  bool DPWinFileRendererC::GetRGBImage(ImageC<ByteRGBValueC>& byteImage, StringC& strErrorMsg)
  {
    if(m_currentFrame > m_numFrames || !m_bInitSucceeded)
    {
      ONDEBUG(cerr << "Failed to get image, passed end of stream or not initalised. \n");
      return false;
    }
    long buffSize = 0;
    char* pBuff = NULL;
    if(!GetBufferImage(buffSize, pBuff, strErrorMsg))
    {
      ONDEBUG(cerr << "Failed to get image buffer. Error:" << strErrorMsg << endl);
      return false;
    }

    //Get the number of rows and columns in pixels
    IndexRange2dC frameSize;
    if(!GetFrameSize(frameSize)) {
      delete [] pBuff;
      return false;
    }
    byteImage = ImageC<ByteRGBValueC>(frameSize);    
    WriteToBuffer_RGB32((BYTE*)pBuff,byteImage);
    delete [] pBuff;

    return true;
  }

  void DPWinFileRendererC::WriteToBuffer_RGB32(BYTE *pData, ImageC<ByteRGBValueC>& image)
  {    
    // Loop through the rows
    long lNumRows = image.Rows();
    long lNumCols = image.Cols();
    int nBufferIndex = 0;
    long lHeightIndex = lNumRows -1;
    for (long y = 0; y < lNumRows; y++, lHeightIndex--)
    { 
        for (long x = 0; x < lNumCols; x++)
        {          
          ByteRGBValueC& pixelVal = image[(long)lHeightIndex][(long)x];
          pixelVal.Blue() = pData[nBufferIndex++];
          pixelVal.Green() = pData[nBufferIndex++];
          pixelVal.Red() = pData[nBufferIndex++];
        }
    }
  }

  void DPWinFileRendererC::FreeMediaType(AM_MEDIA_TYPE& mt)
  {
    if (mt.cbFormat != 0)
    {
      CoTaskMemFree((PVOID)mt.pbFormat);
      mt.cbFormat = 0;
      mt.pbFormat = NULL;
    }
    if (mt.pUnk != NULL)
    {
      // Unecessary because pUnk should not be used, but safest.
      mt.pUnk->Release();
      mt.pUnk = NULL;
    }
  }
  
  //Bounds checking on m_currentFrame left out on purpose, Get(...) returns false if frame out of range

  long DPWinFileRendererC::GetCurrentFrame() const
  {
    return m_currentFrame;
  }
  
  bool DPWinFileRendererC::SetCurrentFrame(long lNewFrameNo)
  {
    m_currentFrame = lNewFrameNo;
    return true;
  }

  bool DPWinFileRendererC::OffsetFrame(long lFrameOffset)
  {
    m_currentFrame = m_currentFrame + lFrameOffset;
    return true;
  }
  
  //**********************Implementation of the WindowsMediaConverterBodyC class**********************

  WindowsMediaConverterBodyC::WindowsMediaConverterBodyC()
    : DPWinFileRendererC()
  {
  }

  WindowsMediaConverterBodyC::WindowsMediaConverterBodyC(const StringC& strFileName) 
    : DPWinFileRendererC(strFileName)
  {
  }

  ImageC<ByteRGBValueC> WindowsMediaConverterBodyC::Get()
  {
    StringC strErrorMsg;
    ImageC<ByteRGBValueC> sampledImage;
    if(!Get(sampledImage))
      throw DataNotReadyC("Failed to read frame. ");
    return sampledImage;
  }

  bool WindowsMediaConverterBodyC::Get(ImageC<ByteRGBValueC> &buff)
  {
    StringC strErrorMsg;
    if(!IsInitialised())
    {
      ONDEBUG(cerr << "Failed to get image, stream not initalised. \n");
      return false;
    }
    // Retrieve next image.
    if(!GetRGBImage(buff, strErrorMsg)) {
      ONDEBUG(cerr << "Failed to get image from decoder. \n");
      return false;
    }
  
    //Advance the frame number
    OffsetFrame(1);
    
    return true;
  }

   bool WindowsMediaConverterBodyC::Seek(UIntT nFrame)
   {
     if(!IsInitialised())
     {
       ONDEBUG(cerr << "Failed to seek, stream not initalised \n");
       return false;
     }
     return SetCurrentFrame(nFrame);
   }

   UIntT WindowsMediaConverterBodyC::Tell() const //Return the current frame number
   {
     return (UIntT) GetCurrentFrame();
   }

   UIntT WindowsMediaConverterBodyC::Size() const//Return the total number of frames in the clip
   {
     return (UIntT) GetTotalFrames();
   }

   bool WindowsMediaConverterBodyC::CanRenderFile()
  {
    return DPWinFileRendererC::CanRenderFile();
  }
 
}
 
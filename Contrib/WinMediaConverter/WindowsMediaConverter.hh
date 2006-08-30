// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here


#ifndef WINDOWS_MEDIA_CONVERTER_H
#define WINDOWS_MEDIA_CONVERTER_H

#include "tchar.h"  //Included to prevent an error when including the DirectShow header
#include "dShow.h"  //For the DirectShow interface definitions
#include "Qedit.h"  //For the ISampleGrabber interface
#include "Ravl/DP/SPort.hh"
#include "Ravl/String.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"



namespace RavlImageN 
{
  using namespace RavlN;

   //******************************SampleGrabberCallback************************************
  // Class to hold the callback function for the Sample Grabber filter.
  class SampleGrabberCallback : public ISampleGrabberCB
  {
    public:
    
    STDMETHODIMP_(ULONG) AddRef()  { return 1; }  // Fake referance counting.
    STDMETHODIMP_(ULONG) Release() { return 2; }  // Fake referance counting.

    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject) // Query interface
    {
        if (NULL == ppvObject) return E_POINTER;
        if (riid == __uuidof(IUnknown))
        {
            *ppvObject = static_cast<IUnknown*>(this);
             return S_OK;
        }
        if (riid == __uuidof(ISampleGrabberCB))
        {
            *ppvObject = static_cast<ISampleGrabberCB*>(this);
             return S_OK;
        }
        return E_NOTIMPL;
    }

    STDMETHODIMP SampleCB(double Time, IMediaSample *pSample) //Increment the frame counter
    {
        m_numFrames++;
        return S_OK;
    }

    STDMETHODIMP BufferCB(double Time, BYTE *pBuffer, long BufferLen) //Not implemented
    {
      return E_NOTIMPL;
    }
    STDMETHODIMP Init() //Set the frame counter to zero
    {
      m_numFrames = 0;
      return S_OK;
    }
    STDMETHODIMP GetNumFrames(long &lNumFrames) //Get the total number of frames
    {
      lNumFrames = m_numFrames;
      return S_OK;
    }
  private:
    long m_numFrames; //Total number of frames in the video clip

  };



  //******************************DPWinFileRendererC************************************
  //This class constructs the DirectShow filter graph (if possible) for the selected file
  class DPWinFileRendererC
  {
  public:
    DPWinFileRendererC(const StringC &filename);  //Constructor
    DPWinFileRendererC();  //Default constructor
    ~DPWinFileRendererC(); //Destructor

    bool IsInitialised(); //Is the filter graph initialised

  private:
    DPWinFileRendererC(const DPWinFileRendererC& rhs) {}; //Private copy constructor

  protected:
    long GetCurrentFrame() const; //Get the absolute index of the current frame
    long GetTotalFrames() const;  //Get the total length of the footage in frames

    bool CanRenderFile();
    bool GetRGBImage( ImageC<ByteRGBValueC>& byteImage, StringC& strErr); //Get an RGB image at the current frame number
    bool SetCurrentFrame(long lNewFrameNo); //Update the current frame number to lNewFrameNo
    bool OffsetFrame(long lFrameOffset);    //Offset the current frame number by lFrameOffset

  private:
    //Write the buffer image to an ImageC
    void WriteToBuffer_RGB32(BYTE *pData, long lNumRows, long lNumCols, ImageC<ByteRGBValueC>& image); 
    void FreeMediaType(AM_MEDIA_TYPE& mt); //Free media type memory
    void GetErrorMsg(HRESULT hr, StringC& strErr) const; //Get a string representing a specific error
    void ReleaseInterfaces(); //Release the COM interfaces
    bool CanOpenFile(); //Check that the file exists and is readable
    bool Initialise(StringC& strError); //Initialise the source info and filter graph
    bool InitialiseFilterGraph(StringC& strErrorMsg); //Initialise the filter graph interfaces
    bool InitialiseSourceInfo(StringC& strErrorMsg); //Initialise the source info including footage length
    bool GetBufferImage(long& buffSize, char*& pBuff, StringC& strErrorMsg); //Get the buffered image from the filter graph
    bool RawBuffersIdentical(long buffSizeA, char* pBuffA, long buffSizeB, char* pBuffB); //Check whether two images are identical
    bool GetFootageLengthAccurate();//Run through the entire footage to get a more accurate length estimate

    //Member variables
    bool m_bCanRenderFile;  //Can the filter graph handle this footage
    bool m_bInitSucceeded;  //Has initialisation succeeded
    bool m_bCanSeek;        //Is the footage seekable
    bool m_bFrameFormat;    //Does this format support frame seeking
    long m_numFrames;       //Total number of frames in the video clip
    long m_currentFrame;    //Current frame number
    long m_msTimeout;       //Timeout when waiting for events (in milliseconds)
    double m_dFrameRate;    //Frame rate in frames per sec
    double m_dStreamLength; //Length of the video clip in seconds

    StringC m_strFileName;  //Name of the file to be captured\rendered

    //DirectShow interfaces
    IGraphBuilder* m_pGraphBuilder;
    IBaseFilter*    m_pGrabberBaseFilter;
    ISampleGrabber* m_pSampleGrabber;
    IMediaControl* m_pMediaControl;
    IMediaEvent* m_pMediaEventEx;
    IMediaSeeking* m_pSeek;
    
    SampleGrabberCallback m_grabberCB;
  };

  //******************************WindowsMediaConverterBodyC************************************
  class WindowsMediaConverterBodyC : public DPISPortBodyC<ImageC<ByteRGBValueC> >,  public DPWinFileRendererC
  {
  public:
    WindowsMediaConverterBodyC();   //Default constructor
    WindowsMediaConverterBodyC(const StringC& strFileName); //Constructor
    ~WindowsMediaConverterBodyC() {}; //Destructor

  public:
    virtual ImageC<ByteRGBValueC> Get();  //Get an image at the current frame number
    virtual bool Get(ImageC<ByteRGBValueC> &buff);  //Get an image at the current frame number
    virtual bool Seek(UIntT nFrame); //Update the current frame number by seeking to nFrame
    virtual UIntT Tell() const; //Return the current frame number
    virtual UIntT Size() const; //Return the total number of frames in the clip
    bool CanRenderFile();       //Can the filter graph render this file
  };

  //******************************WindowsMediaConverterC************************************
  class WindowsMediaConverterC : public DPISPortC<ImageC<ByteRGBValueC> > 
  {
  public:
    WindowsMediaConverterC(const StringC &strFileName)    //Constructor
      : DPEntityC(*new WindowsMediaConverterBodyC(strFileName)) {};
  };
};

#endif //WINDOWS_MEDIA_CONVERTER_H
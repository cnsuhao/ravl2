// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FFMPEGVIDEOENCODER_HEADER
#define RAVL_FFMPEGVIDEOENCODER_HEADER 1
//! rcsid="$Id: FFmpegVideoDecoder.hh 6523 2008-01-29 12:45:27Z craftit $"
//! lib=RavlLibFFmpeg

#include "Ravl/Image/FFmpegPacketStream.hh"
#include "Ravl/Image/FFmpegEncodePacketStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/FFmpegPacket.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/DP/AttributeCtrl.hh"
#include "Ravl/DP/AttributeValueTypes.hh"
#include "Ravl/DP/AttributeType.hh"

extern "C" {
struct SwsContext;
}

extern "C" {
#if defined(LIBAVFORMAT_VERSION_MAJOR) && LIBAVFORMAT_VERSION_MAJOR >= 52
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#else 
#include <avformat.h>
#include <avcodec.h>
#endif
}

namespace RavlImageN {
  using namespace RavlImageN;
#define STREAM_PIX_FMT PIX_FMT_RGB24 /* default pix_fmt */  
//static int sws_flags = SWS_BICUBIC;
  //! userlevel=Develop
  //: FFmpeg Video decoder.



//! userlevel=Develop
  //: FFmpeg Video decoder.
  
  class FFmpegVideoEncoderBaseC
  {
  public:
    FFmpegVideoEncoderBaseC(DPOPortC<FFmpegPacketC> &packetStream,IntT videoStreamId,IntT codecId);
    //: Constructor.
    
    FFmpegVideoEncoderBaseC();
    //: Default constructor.
    
    ~FFmpegVideoEncoderBaseC();
    //: Destructor.
    
    bool Open(DPOPortC<FFmpegPacketC> &packetStream,IntT videoStreamId,IntT codecId);
    //: Open a stream.
    
    bool EncodeFrame();
    //: Decode the next frame.
    
    bool PutFrame(const ImageC<ByteRGBValueC> &frame);
    //: Get a frame of video from stream.

    bool Put();
    
    //bool tempory_function_header(DPOPortC<FFmpegPacketC> &packetStream,IntT _videoStreamId,IntT codecId);
   
    bool GetHandleAttr(const StringC &attrName,StringC &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    bool GetHandleAttr(const StringC &attrName,IntT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    bool GetHandleAttr(const StringC &attrName,RealT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    bool SetHandleAttr(const StringC &attrName,const RealT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    bool SetHandleAttr(const StringC &attrName,const IntT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    bool SetHandleAttr(const StringC &attrName,const StringC &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    bool GetHandleAttr(const StringC &attrName,bool &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
  private:
     bool finishOpen();

  protected:
    void InitAttr(AttributeCtrlBodyC &attrCtrl);
    //: Initalise attributes.
    
    IntT videoStreamId;             // Id of video stream we're currently decoding.
    AVCodecContext *vCodecCtx,*pcodecctx;      // Video codec.
    DPOSPortC<FFmpegPacketC> output; // Output stream.
    AVFrame *pFrame,*tmp_picture,*picture,*outpFrame,*out_picture;
    mutable FFmpegPacketC packet;           // Current packet.
    int      bytesRemaining;
    uint8_t  *rawData,*video_outbuf,*picture_buf,*out_picture_buf,*picture_buf2;
    AVStream *streamInfo;
    SwsContext *pSWSCtx,*pSWSctx;
    bool m_haveFullSeek,header_done,open_done;
    IntT frame_count,video_outbuf_size,size,width,height,numBytes;
    FFmpegEncodePacketStreamC psc;
    StringC filename,out_filename;
    AVFormatContext *pFormatCtx;
    CodecID codec_id;
    //AttributeCtrlC attributes;
  };
  


  template<class ImageT> 
  class ImgDPOFFmpegBodyC
    : public DPOPortBodyC<ImageT>,
      public FFmpegVideoEncoderBaseC
  {
  public:
    ImgDPOFFmpegBodyC() 
    { InitAttr(*this); }
    //: Constructor.
    
    ImgDPOFFmpegBodyC(DPOPortC<FFmpegPacketC> &packetStream,IntT videoStreamId,IntT codecId) 
      : FFmpegVideoEncoderBaseC(packetStream,videoStreamId,codecId)
    { InitAttr(*this);
     }
    //: Constructor.
    
   virtual bool Put(const ImageC<ByteRGBValueC> &buff)
    { 
       return PutFrame(buff); 
     }
    //: Get next image.

    virtual bool Put()
    {
       return true;   //PutFrame(buff); 
     }
    
    virtual bool IsPutReady() const 
    { 
       if(!output.IsValid()) return false; return output.IsPutReady(); 
    }
    //: Is some data ready ?
    // TRUE = yes.
    // Defaults to !IsGetEOS().
    
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue) {
      if(FFmpegVideoEncoderBaseC::GetHandleAttr(attrName,attrValue))
        return true;
      return DPOPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue) {
      if(FFmpegVideoEncoderBaseC::GetHandleAttr(attrName,attrValue))
        return true;
      return DPOPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,RealT &attrValue) {
      if(FFmpegVideoEncoderBaseC::GetHandleAttr(attrName,attrValue))
        return true;
      return DPOPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    virtual bool SetAttr(const StringC &attrName,const RealT &attrValue) {
      if(FFmpegVideoEncoderBaseC::SetHandleAttr(attrName,attrValue)) {
        return true;
      }
      return DPOPortBodyC<ImageT>::SetAttr(attrName,attrValue);
    }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    virtual bool SetAttr(const StringC &attrName,const IntT &attrValue) {
      if(FFmpegVideoEncoderBaseC::SetHandleAttr(attrName,attrValue)) {
        return true;
      }
      return DPOPortBodyC<ImageT>::SetAttr(attrName,attrValue);
    }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    virtual bool SetAttr(const StringC &attrName,const StringC &attrValue) {
      if(FFmpegVideoEncoderBaseC::SetHandleAttr(attrName,attrValue)) {
        return true;
      }
      return DPOPortBodyC<ImageT>::SetAttr(attrName,attrValue);
    }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.


    virtual bool GetAttr(const StringC &attrName,bool &attrValue) {
      if(FFmpegVideoEncoderBaseC::GetHandleAttr(attrName,attrValue))
        return true;
      return DPOPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    //virtual bool Discard()
    //{ return DecodeFrame(); }
    //: Discard the next output datum.

  protected:

  };


  template<class ImageT> 
  class ImgDPOFFmpegC
    : public DPOPortC<ImageT>
  {
  public:
    ImgDPOFFmpegC(DPOPortC<FFmpegPacketC> &packetStream,IntT videoStreamId,IntT codecId)
      : DPEntityC(*new ImgDPOFFmpegBodyC<ImageT>(packetStream,videoStreamId,codecId))
    { 
     }
    //: Constructor.
    
    ImgDPOFFmpegC()
      : DPEntityC(true)
    {}
    //: Default constructor. 


  protected:

  };
  
  
}

#endif

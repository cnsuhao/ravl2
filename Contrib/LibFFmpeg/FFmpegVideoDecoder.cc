// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLibFFmpeg

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS 1
#include <stdint.h>
#endif

#include "Ravl/Image/FFmpegVideoDecoder.hh"
#include "Ravl/Exception.hh"
#include "Ravl/DP/AttributeValueTypes.hh"

#if LIBAVFORMAT_VERSION_INT >= ((51<<16)+(12<<8)+1)
#define LIBAVFORMAT_USE_SWSCALER
#endif

#ifdef LIBAVFORMAT_USE_SWSCALER
extern "C" {
  #include <swscale.h>
}
#endif

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  FFmpegVideoDecoderBaseC::FFmpegVideoDecoderBaseC(DPISPortC<FFmpegPacketC> &_packetStream,IntT _videoStreamId,IntT _codecId) 
    : videoStreamId(-1),
      pCodecCtx(0),
      pFrame(0),
      bytesRemaining(0),
      rawData(0),
      streamInfo(0),
      pSWSCtx(0)
  {
    if(!Open(_packetStream,_videoStreamId,_codecId))
      throw ExceptionOperationFailedC("Failed to open video stream. ");
  }
  
  //: Default constructor.
  
  FFmpegVideoDecoderBaseC::FFmpegVideoDecoderBaseC() 
    : videoStreamId(-1),
      pCodecCtx(0),
      pFrame(0),
      bytesRemaining(0),
      rawData(0),
      streamInfo(0),
      pSWSCtx(0)
  {}
  
  //: Destructor.
  
  FFmpegVideoDecoderBaseC::~FFmpegVideoDecoderBaseC() {
    // Clean up codec
    if(pCodecCtx != 0)
      avcodec_close(pCodecCtx);
    if(pFrame != 0)
      av_free(pFrame);
#ifdef LIBAVFORMAT_USE_SWSCALER
    if(pSWSCtx != 0)
      sws_freeContext(pSWSCtx); 
#endif
  }
  
  //: Open a stream.
  
  bool FFmpegVideoDecoderBaseC::Open(DPISPortC<FFmpegPacketC> &packetStream,IntT _videoStreamId,IntT codecId) {
    if(pCodecCtx != 0) {
      cerr << "FFmpegVideoDecoderBaseC::Open, Stream already open. \n";
      return false;
    }
    input = packetStream;
    videoStreamId = _videoStreamId;
    ONDEBUG(cerr << "FFmpegVideoDecoderBaseC::Open, CodecId = " << codecId << "\n");
    
    // Get a pointer to the codec context for the video stream
    
    // Do we really need this, can't we get away with just using the codecId ?
    FFmpegPacketStreamC ps(packetStream);
    if(!ps.IsValid()) {
      cerr << "FFmpegVideoDecoderBaseC::Open, Unsupported packet stream type. \n";
      return false;      
    }
    streamInfo = ps.FormatCtx()->streams[videoStreamId];
    pCodecCtx = streamInfo->codec;
    
    // Find the decoder for the video stream
    AVCodec *pCodec = avcodec_find_decoder(static_cast<CodecID>(codecId));
    if (pCodec == NULL) {
      cerr << "FFmpegVideoDecoderBaseC::Open, Failed to find codec. \n";
      return false;
    }
    
    ONDEBUG(cerr << "FFmpegVideoDecoderBaseC::Open codec found(" << (pCodec->name != NULL ? pCodec->name : "NULL") << ")" << endl);

/*
    // Inform the codec that we can handle truncated bitstreams
    // i.e. bitstreams where frame boundaries can fall in the middle of packets
    if (pCodec->capabilities & CODEC_CAP_TRUNCATED)
      pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;
*/
    bool ret = false;
    
    // Open codec
    if (avcodec_open(pCodecCtx, pCodec) >= 0) {
      ONDEBUG(cerr << "FFmpegVideoDecoderBaseC::Open codec constructed ok. " << endl);
      ret = true;
    }
    
    // Hack to correct wrong frame rates that seem to be generated by some 
    // codecs
    /*
    if(pCodecCtx->frame_rate>1000 && pCodecCtx->frame_rate_base==1)
      pCodecCtx->frame_rate_base=1000;
    */

    // Allocate a frame.
    pFrame=avcodec_alloc_frame();
    return true;
  }
  
  //: Decode the next frame.
  
  bool FFmpegVideoDecoderBaseC::DecodeFrame() {
    int             bytesDecoded;
    int             frameFinished;
    
    // Decode packets until we have decoded a complete frame
    while(true) {
      // Work on the current packet until we have decoded all of it
      while(bytesRemaining > 0) {
        // Decode the next chunk of data
        bytesDecoded=avcodec_decode_video(pCodecCtx, pFrame,
                                          &frameFinished, rawData, bytesRemaining);
        
        // Was there an error?
        if(bytesDecoded < 0) {
          cerr << "FFmpegVideoDecoderBaseC::DecodeFrame, Error while decoding frame. ";
          return false;
        }
        
        bytesRemaining -= bytesDecoded;
        rawData += bytesDecoded;
        
        // Did we finish the current frame? Then we can return
        if(frameFinished)
          return true;
      }
      
      // Read the next packet, skipping all packets that aren't for this
      // stream
      do {
        if(!input.Get(packet)) {
          // There can't be any more frames in the stream.
          return false; // Failed to find next packet.
        }
      } while(packet.StreamIndex() != videoStreamId);
      
      bytesRemaining = packet.Size();
      rawData = packet.Data();
    }
    
    return false;
  }
  
  //: Get a frame of video from stream.
  
  bool FFmpegVideoDecoderBaseC::GetFrame(ImageC<ByteRGBValueC> &frame) {
    if(!DecodeFrame())
      return false;
    //cerr << "FFmpegVideoDecoderBaseC::GetFrame, Got frame. \n";
    AVFrame *pFrameRGB = avcodec_alloc_frame();
    // Determine required buffer size and allocate buffer
    IntT numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,pCodecCtx->height);
    uint8_t *buffer=new uint8_t[numBytes];
    avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,pCodecCtx->width, pCodecCtx->height);
    
#ifdef LIBAVFORMAT_USE_SWSCALER
    // Need to setup scaler ?
    if(pSWSCtx == 0) {
      pSWSCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
    }
    
    sws_scale(pSWSCtx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
#else    
    img_convert((AVPicture *)pFrameRGB, PIX_FMT_RGB24, (AVPicture*)pFrame, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
#endif
    
    frame = ImageC<ByteRGBValueC>(pCodecCtx->height,pCodecCtx->width,static_cast<ByteRGBValueC *>((void *)buffer),true);
    av_free(pFrameRGB);
    
    return true;
  }

  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoDecoderBaseC::GetAttr(const StringC &attrName,StringC &attrValue) {
    if(attrName == "filename" || attrName == "title" || attrName == "author" || 
       attrName == "copyright"|| attrName == "comment"|| attrName == "album") {
      if(!input.IsValid() || !input.GetAttr(attrName,attrValue))
        attrValue = StringC("");
      return true;
    }
    if(attrName == "aspectratio") {
      if(pCodecCtx == 0)
        attrValue = "?";
      else
        attrValue = StringC(pCodecCtx->sample_aspect_ratio.num) + ":" + StringC(pCodecCtx->sample_aspect_ratio.den);
      return true;
    }
    return false;
  }
    
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoDecoderBaseC::GetAttr(const StringC &attrName,IntT &attrValue) {
    return false;
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoDecoderBaseC::GetAttr(const StringC &attrName,RealT &attrValue) {
    if(attrName == "framerate") {
      if(!input.IsValid() || !input.GetAttr(attrName,attrValue))
        attrValue = 0.0;
      return true;
    }
    return false;
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoDecoderBaseC::GetAttr(const StringC &attrName,bool &attrValue) {
    return false;
  }
  
  //: Initalise attributes.
  
  void FFmpegVideoDecoderBaseC::InitAttr(AttributeCtrlBodyC &attrCtrl) {
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("framerate","Frame rate of video",true,false,0.0,1000.0,0.01,25));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("aspectratio","Aspect ratio",true,false,"4:3"));
    
    attrCtrl.RegisterAttribute(AttributeTypeStringC("filename","Original filename of stream",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("title","Title of stream",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("author","Author",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("copyright","Copyright for material",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("comment","Comment",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("album","album",true,false,""));
    
  }
  
  //: Seek to location in stream.
  // Returns FALSE, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool FFmpegVideoDecoderBaseC::Seek(UIntT off) {
    return FFmpegVideoDecoderBaseC::Seek64(off);
  }
  
  //: Find current location in stream.
  
  UIntT FFmpegVideoDecoderBaseC::Tell() const {
    return FFmpegVideoDecoderBaseC::Tell64();
  }
  
  //: Find the total size of the stream.
  
  UIntT FFmpegVideoDecoderBaseC::Size() const {
    return FFmpegVideoDecoderBaseC::Size64();
  }
  
  //: Find the total size of the stream.
  
  UIntT FFmpegVideoDecoderBaseC::Start() const {
    return FFmpegVideoDecoderBaseC::Start64();
  }
  
  //: Find current location in stream.
  
  Int64T FFmpegVideoDecoderBaseC::Tell64() const {
    if(!input.IsValid()) return 0;
    return input.Tell64();
  }
  
  //: Seek to location in stream.
  // Returns FALSE, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool FFmpegVideoDecoderBaseC::Seek64(Int64T off) {
    if(!input.IsValid()) return false;
    ONDEBUG(cerr << "FFmpegVideoDecoderBaseC::Seek64 to " << off << " \n");
    // Be carefull seeking forward with some codec's

#if 0
    if(pCodecCtx->codec_id == CODEC_ID_MPEG2VIDEO){
      ONDEBUG(cerr << "FFmpegVideoDecoderBaseC::Seek64, Using seek hack. " << off << " @ " << Tell64() << "\n");
      input.Seek64(off-25);
      for(UIntT i = 0; i < 25;i++)
        DecodeFrame();
      return true;
    }
#endif

    return input.Seek64(off);
  }
  
  //: Find the total size of the stream.
  
  Int64T FFmpegVideoDecoderBaseC::Size64() const {
    if(!input.IsValid()) return 0;
    return input.Size64();   
  }
  
  //: Find the total size of the stream.
  
  Int64T FFmpegVideoDecoderBaseC::Start64() const {
    if(!input.IsValid()) return 0;
    return input.Start64();
  }

  //: Change position relative to the current one.
  
  bool FFmpegVideoDecoderBaseC::DSeek64(Int64T off) {
    if(!input.IsValid())
      return false;

#if 0
    // Be carefull seeking forward with some codec's
    if(pCodecCtx->codec_id == CODEC_ID_MPEG2VIDEO) {
      ONDEBUG(cerr << "FFmpegVideoDecoderBaseC::DSeek64, Using seek hack." << off << " \n");
      if(off >= 0) {
        // Seek forward by decoding frames.
        for(Int64T i = 0;i < off;i++)
          DecodeFrame();
        return true;
      }
    }
#endif

    return input.DSeek64(off);
  }
  
  //: Change position relative to the current one.
  
  bool FFmpegVideoDecoderBaseC::DSeek(Int64T off) {
    return DSeek64(off);
  }
  
}

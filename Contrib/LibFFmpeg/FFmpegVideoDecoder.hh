// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FFMPEGVIDEODECODER_HEADER
#define RAVL_FFMPEGVIDEODECODER_HEADER 1
//! rcsid="$Id: FFmpegVideoDecoder.hh 7406 2009-12-07 16:57:04Z simondennis $"
//! lib=RavlLibFFmpeg

#include "Ravl/Image/FFmpegPacketStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

extern "C" {
struct SwsContext;
}

namespace RavlN {
  using namespace RavlImageN;
  
  //! userlevel=Develop
  //: FFmpeg Video decoder.
  
  class FFmpegVideoDecoderBaseC
  {
  public:
    FFmpegVideoDecoderBaseC(DPISPortC<FFmpegPacketC> &packetStream,IntT videoStreamId,IntT codecId);
    //: Constructor.
    
    FFmpegVideoDecoderBaseC();
    //: Default constructor.
    
    ~FFmpegVideoDecoderBaseC();
    //: Destructor.
    
    bool Open(DPISPortC<FFmpegPacketC> &packetStream,IntT videoStreamId,IntT codecId);
    //: Open a stream.
    
    bool DecodeFrame();
    //: Decode the next frame.
    
    bool GetFrame(ImageC<ByteRGBValueC> &frame);
    //: Get a frame of video from stream.
    
    bool GetAttr(const StringC &attrName,StringC &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    bool GetAttr(const StringC &attrName,IntT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    bool GetAttr(const StringC &attrName,RealT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    bool GetAttr(const StringC &attrName,bool &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    bool Seek(UIntT off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    UIntT Tell() const; 
    //: Find current location in stream.
    
    UIntT Size() const; 
    //: Find the total size of the stream.
    
    UIntT Start() const; 
    //: Find the total size of the stream.
    
    Int64T Tell64() const; 
    //: Find current location in stream.
    
    bool Seek64(Int64T off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    Int64T Size64() const; 
    //: Find the total size of the stream.

    Int64T Start64() const; 
    //: Find the total size of the stream.

    bool DSeek64(Int64T off);
    //: Change position relative to the current one.
    
    bool DSeek(Int64T off);
    //: Change position relative to the current one.

    virtual bool SetAttr(const StringC &attrName,RealT &attrValue) {
      OStreamC os("output.txt",true,true,true);
      os << "  bool FFmpegVideoDecoderBaseC::SetAttr(const StringC &attrName,RealT &attrValue) { called " << attrName << endl;
      os.Close();
     // if(FFmpegVideoEncoderBaseC::SetAttr(attrName,attrValue)) {
        return true;
      //}
      //return DPOPortBodyC<ImageT>::SetAttr(attrName,attrValue);
    }
    
  protected:
    void InitAttr(AttributeCtrlBodyC &attrCtrl);
    //: Initalise attributes.
    
    IntT videoStreamId;             // Id of video stream we're currently decoding.
    AVCodecContext *pCodecCtx;      // Video codec.
    DPISPortC<FFmpegPacketC> input; // Input stream.
    AVFrame *pFrame;
    FFmpegPacketC packet;           // Current packet.
    int      bytesRemaining;
    uint8_t  *rawData;
    AVStream *streamInfo;
    SwsContext *pSWSCtx;
    bool m_haveFullSeek;
  };
  


  template<class ImageT> 
  class ImgIOFFmpegBodyC
    : public DPISPortBodyC<ImageT>,
      public FFmpegVideoDecoderBaseC
  {
  public:
    ImgIOFFmpegBodyC() 
    { InitAttr(*this); }
    //: Constructor.
    
    ImgIOFFmpegBodyC(DPISPortC<FFmpegPacketC> &packetStream,IntT videoStreamId,IntT codecId) 
      : FFmpegVideoDecoderBaseC(packetStream,videoStreamId,codecId)
    { InitAttr(*this); }
    //: Constructor.
    
    virtual bool Get(ImageC<ByteRGBValueC> &buff)
    { return GetFrame(buff); }
    //: Get next image.

    virtual ImageC<ByteRGBValueC> Get() { 
      ImageC<ByteRGBValueC> buff;
      if(!GetFrame(buff))
        throw DataNotReadyC("Frame not read.");
      return buff;
    }
    //: Get next image.
    
    virtual bool IsGetReady() const 
    { if(!input.IsValid()) return false; return input.IsGetReady(); }
    //: Is some data ready ?
    // TRUE = yes.
    // Defaults to !IsGetEOS().
    
    virtual bool IsGetEOS() const
    { if(!input.IsValid()) return true; return input.IsGetEOS(); }
    //: Has the End Of Stream been reached ?
    // TRUE = yes.
    
    bool Seek(UIntT off)
    { return FFmpegVideoDecoderBaseC::Seek(off); }
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    bool DSeek64(Int64T off) 
    { return FFmpegVideoDecoderBaseC::DSeek64(off); }
    //: Change position relative to the current one.
    
    bool DSeek(Int64T off) 
    { return FFmpegVideoDecoderBaseC::DSeek(off); }
    //: Change position relative to the current one.
    
    UIntT Tell() const
    { return FFmpegVideoDecoderBaseC::Tell(); }
    //: Find current location in stream.
    
    UIntT Size() const
    { return FFmpegVideoDecoderBaseC::Size(); }
    //: Find the total size of the stream.
    
    UIntT Start() const
    { return FFmpegVideoDecoderBaseC::Start(); }
    //: Find the total size of the stream.
    
    Int64T Tell64() const
    { return FFmpegVideoDecoderBaseC::Tell64(); }
    //: Find current location in stream.
    
    bool Seek64(Int64T off)
    { return FFmpegVideoDecoderBaseC::Seek64(off); }
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    Int64T Size64() const
    { return FFmpegVideoDecoderBaseC::Size64(); }
    //: Find the total size of the stream.

    Int64T Start64() const
    { return FFmpegVideoDecoderBaseC::Start64(); }
    //: Find the total size of the stream.
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue) {
      if(FFmpegVideoDecoderBaseC::GetAttr(attrName,attrValue))
        return true;
      return DPISPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue) {
      if(FFmpegVideoDecoderBaseC::GetAttr(attrName,attrValue))
        return true;
      return DPISPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,RealT &attrValue) {
      if(FFmpegVideoDecoderBaseC::GetAttr(attrName,attrValue))
        return true;
      return DPISPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,bool &attrValue) {
      if(FFmpegVideoDecoderBaseC::GetAttr(attrName,attrValue))
        return true;
      return DPISPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    virtual bool SetAttr(const StringC &attrName,RealT &attrValue) {
      OStreamC os("output.txt",true,true,true);
      os << "  bool ImgIOFFmpegBodyC::SetAttr(const StringC &attrName,RealT &attrValue) { called " << attrName << endl;
      os.Close();
     // if(FFmpegVideoEncoderBaseC::SetAttr(attrName,attrValue)) {
        return true;
      //}
      //return DPOPortBodyC<ImageT>::SetAttr(attrName,attrValue);
    }
    
    virtual bool Discard()
    { return DecodeFrame(); }
    //: Discard the next input datum.

  protected:
  };

  template<class ImageT> 
  class ImgIOFFmpegC
    : public DPISPortC<ImageT>
  {
  public:
    ImgIOFFmpegC(DPISPortC<FFmpegPacketC> &packetStream,IntT videoStreamId,IntT codecId)
      : DPEntityC(*new ImgIOFFmpegBodyC<ImageT>(packetStream,videoStreamId,codecId))
    {}
    //: Constructor.
    
    ImgIOFFmpegC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
  protected:
    
  };
  
  
}

#endif

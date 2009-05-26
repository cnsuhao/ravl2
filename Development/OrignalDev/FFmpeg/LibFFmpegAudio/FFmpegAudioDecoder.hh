#line 1 "/media/project/work/PHD/Ravl_Code/Contrib/LibFFmpegAudio/FFmpegAudioDecoder.hh"
#ifndef RAVL_FFMPEGAUDIODECODER_HEADER
#define RAVL_FFMPEGAUDIODECODER_HEADER 1

#include "Ravl/Audio/FFmpegAudioPacketStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Audio/Types.hh"

namespace RavlN {
  using namespace RavlAudioN;
  
  //! userlevel=Develop
  //: FFmpeg Audio decoder.
  
  class FFmpegAudioDecoderBaseC
  {
  public:
    FFmpegAudioDecoderBaseC(DPISPortC<FFmpegAudioPacketC> &packetStream,IntT audioStreamId,IntT codecId);
    //: Constructor.
    
    FFmpegAudioDecoderBaseC();
    //: Default constructor.
    
    ~FFmpegAudioDecoderBaseC();
    //: Destructor.
    
    bool Open(DPISPortC<FFmpegAudioPacketC> &packetStream,IntT audioStreamId,IntT codecId);
    //: Open a stream.
    
    bool DecodeFrame();
    //: Decode the next frame.
    
    bool GetFrame(SampleElemC<2,Int16T> &frame);
    //: Get a frame of audio from stream.
    
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
    
  protected:
    void InitAttr(AttributeCtrlBodyC &attrCtrl);
    //: Initalise attributes.
    
    IntT audioStreamId;             // Id of audio stream we're currently decoding.
    AVCodecContext *pCodecCtx;      // Audio codec.
    DPISPortC<FFmpegAudioPacketC> input; // Input stream.
    AVFrame *pFrame;
    int16_t audio_buf[100000];
    FFmpegAudioPacketC packet;           // Current packet.
    int      bytesRemaining;
    uint8_t  *rawData;
    AVStream *streamInfo;
    int buffSize;
    IntT channels;
    IntT pos;
    RealT frac;
  };
  

  template<class ImageT> 
  class AudioIOFFmpegBodyC
    : public DPISPortBodyC<ImageT>,
      public FFmpegAudioDecoderBaseC
  {
  public:
    AudioIOFFmpegBodyC() 
    { InitAttr(*this); }
    //: Constructor.
    
    AudioIOFFmpegBodyC(DPISPortC<FFmpegAudioPacketC> &packetStream,IntT audioStreamId,IntT codecId) 
      : FFmpegAudioDecoderBaseC(packetStream,audioStreamId,codecId)
    { InitAttr(*this); }
    //: Constructor.
    
    virtual bool Get(SampleElemC<2,Int16T> &buff)
    { return GetFrame(buff); }
    //: Get next image.

    virtual SampleElemC<2,Int16T> Get() { 
      SampleElemC<2,Int16T> buff;
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
    { return FFmpegAudioDecoderBaseC::Seek(off); }
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    bool DSeek64(Int64T off) 
    { return FFmpegAudioDecoderBaseC::DSeek64(off); }
    //: Change position relative to the current one.
    
    bool DSeek(Int64T off) 
    { return FFmpegAudioDecoderBaseC::DSeek(off); }
    //: Change position relative to the current one.
    
    UIntT Tell() const
    { return FFmpegAudioDecoderBaseC::Tell(); }
    //: Find current location in stream.
    
    UIntT Size() const
    { return FFmpegAudioDecoderBaseC::Size(); }
    //: Find the total size of the stream.
    
    UIntT Start() const
    { return FFmpegAudioDecoderBaseC::Start(); }
    //: Find the total size of the stream.
    
    Int64T Tell64() const
    { return FFmpegAudioDecoderBaseC::Tell64(); }
    //: Find current location in stream.
    
    bool Seek64(Int64T off)
    { return FFmpegAudioDecoderBaseC::Seek64(off); }
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    Int64T Size64() const
    { return FFmpegAudioDecoderBaseC::Size64(); }
    //: Find the total size of the stream.

    Int64T Start64() const
    { return FFmpegAudioDecoderBaseC::Start64(); }
    //: Find the total size of the stream.
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue) {
      if(FFmpegAudioDecoderBaseC::GetAttr(attrName,attrValue))
        return true;
      return DPISPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue) {
      if(FFmpegAudioDecoderBaseC::GetAttr(attrName,attrValue))
        return true;
      return DPISPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,RealT &attrValue) {
      if(FFmpegAudioDecoderBaseC::GetAttr(attrName,attrValue))
        return true;
      return DPISPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,bool &attrValue) {
      if(FFmpegAudioDecoderBaseC::GetAttr(attrName,attrValue))
        return true;
      return DPISPortBodyC<ImageT>::GetAttr(attrName,attrValue);
    }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool Discard()
    { return DecodeFrame(); }
    //: Discard the next input datum.

  protected:
    
  };

  template<class ImageT> 
  class AudioIOFFmpegC
    : public DPISPortC<ImageT>
  {
  public:
    AudioIOFFmpegC(DPISPortC<FFmpegAudioPacketC> &packetStream,IntT audioStreamId,IntT codecId)
      : DPEntityC(*new AudioIOFFmpegBodyC<ImageT>(packetStream,audioStreamId,codecId))
    {}
    //: Constructor.
    
    AudioIOFFmpegC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
  protected:
    
  };
  
  
}

#endif

#include "Ravl/Audio/FFmpegAudioDecoder.hh"
#include "Ravl/Exception.hh"
#include "Ravl/DP/AttributeValueTypes.hh"

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  FFmpegAudioDecoderBaseC::FFmpegAudioDecoderBaseC(DPISPortC<FFmpegAudioPacketC> &_packetStream,IntT _audioStreamId,IntT _codecId) 
    : audioStreamId(-1),
      pCodecCtx(0),
      pFrame(0),
      bytesRemaining(0),
      rawData(0),
      streamInfo(0),
      pos(0)

  {
    if(!Open(_packetStream,_audioStreamId,_codecId))
      throw ExceptionOperationFailedC("Failed to open audio stream. ");
  }
  
  //: Default constructor.
  
  FFmpegAudioDecoderBaseC::FFmpegAudioDecoderBaseC() 
    : audioStreamId(-1),
      pCodecCtx(0),
      pFrame(0),
      bytesRemaining(0),
      rawData(0),
      streamInfo(0),
      pos(0)
  {}

  //: Destructor.
  
  FFmpegAudioDecoderBaseC::~FFmpegAudioDecoderBaseC() {
    // Clean up codec
    if(pCodecCtx != 0)
      avcodec_close(pCodecCtx);
    if(pFrame != 0)
      av_free(pFrame);
  }
  
  //: Open a stream.
  
  bool FFmpegAudioDecoderBaseC::Open(DPISPortC<FFmpegAudioPacketC> &packetStream,IntT _audioStreamId,IntT codecId) {
    if(pCodecCtx != 0) {
      cerr << "FFmpegAudioDecoderBaseC::Open, Stream already open. \n";
      return false;
    }
    input = packetStream;
    audioStreamId = _audioStreamId;
    
    ONDEBUG(cerr << "FFmpegAudioDecoderBaseC::Open, CodecId = " << codecId << "\n");
    
    FFmpegPacketStreamC ps(packetStream);
    if(!ps.IsValid()) {
      cerr << "FFmpegAudioDecoderBaseC::Open, Unsupported packet stream type. \n";
      return false;      
    }
    
    frac = ps.convFactor();
    streamInfo = ps.FormatCtx()->streams[audioStreamId];
    pCodecCtx = streamInfo->codec;
    channels = pCodecCtx->channels;
    // Find the decoder for the audio stream
    AVCodec *pCodec = avcodec_find_decoder(static_cast<CodecID>(codecId));
    if (pCodec == NULL) {
      cerr << "FFmpegAudioDecoderBaseC::Open, Failed to find codec. \n";
      return false;
    }
    
    ONDEBUG(cerr << "FFmpegAudioDecoderBaseC::Open codec found(" << (pCodec->name != NULL ? pCodec->name : "NULL") << ")" << endl);

    bool ret = false;
    
    // Open codec
    if (avcodec_open(pCodecCtx, pCodec) >= 0) {
      ONDEBUG(cerr << "FFmpegAudioDecoderBaseC::Open codec constructed ok. " << endl);
      ret = true;
    }

    return true;
  }
  
  //: Decode the next frame.
  
  bool FFmpegAudioDecoderBaseC::DecodeFrame() {
    int             bytesDecoded;
    int             frameFinished;

    while(true) {
      // Work on the current packet until we have decoded all of it
      while(bytesRemaining > 0) {
	
        // Decode the next chunk of data
	bytesDecoded=avcodec_decode_audio(pCodecCtx, audio_buf,
                                          &frameFinished, rawData, bytesRemaining);
	
        
        // Was there an error?
        if(bytesDecoded < 0) {
          cerr << "FFmpegAudioDecoderBaseC::DecodeFrame, Error while decoding frame. ";
          return false;
        }

        bytesRemaining -= bytesDecoded;
	buffSize = frameFinished;
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
      } while(packet.StreamIndex() != audioStreamId);
       
      bytesRemaining = packet.Size();
      rawData = packet.Data();
    }
    return false;
  }
  
  //: Get a frame of audio from stream.
  
  bool FFmpegAudioDecoderBaseC::GetFrame(SampleElemC<2,Int16T> &frame) {
    
    if(pos == buffSize/2){
      pos = 0; 
    if(!DecodeFrame())
	return false;
    }
   
    for(IntT i = 0; i < channels; i++){
      frame.channel[i] = audio_buf[pos];
      pos++;
    }
    if(channels < 2)
      frame.channel[1] = frame.channel[0];
    return true;
  }

  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegAudioDecoderBaseC::GetAttr(const StringC &attrName,StringC &attrValue) {
    if(attrName == "filename" || attrName == "title" || attrName == "author" || 
       attrName == "copyright"|| attrName == "comment"|| attrName == "album") {
      if(!input.IsValid() || !input.GetAttr(attrName,attrValue))
        attrValue = StringC("");
      return true;
    }
    if(attrName == "samplerate") {
      if(pCodecCtx == 0)
	attrValue = "?";
      else
	attrValue = StringC(pCodecCtx->sample_rate);
      return true;
    }
    if(attrName == "codec") {
      AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
      if(pCodecCtx == 0)
	attrValue = "?";
      else
	attrValue = pCodec->name;
      return true;
    }
    return false;
  }
    
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegAudioDecoderBaseC::GetAttr(const StringC &attrName,IntT &attrValue) {
    return false;
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegAudioDecoderBaseC::GetAttr(const StringC &attrName,RealT &attrValue) {
     if(attrName == "bitrate") {
      if(pCodecCtx == 0)
	attrValue = -1;
      else
	attrValue = pCodecCtx->bit_rate;
      return true;
    }
    if(attrName == "samplerate") {
      if(!input.IsValid() || !input.GetAttr(attrName,attrValue))
	attrValue = 0.0;
      return true;
    }
    if(attrName == "channels") {
      if(pCodecCtx == 0)
	attrValue = 0;
      else
	attrValue = channels;
      return true;
    }
    return false;
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegAudioDecoderBaseC::GetAttr(const StringC &attrName,bool &attrValue) {
    return false;
  }
  
  //: Initalise attributes.
  
  void FFmpegAudioDecoderBaseC::InitAttr(AttributeCtrlBodyC &attrCtrl) {
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("samplerate","Sample rate of audio",true,false,0.0,1000.0,0.01,48000));
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("bitrate","Bit rate",true,false,0.0,1000.0,0.01,48000));
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("channels","Number of channels",true,false,0.0,1000.0,0.01,4));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("codec","codec",true,false,""));
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
  
  bool FFmpegAudioDecoderBaseC::Seek(UIntT off) {
    return FFmpegAudioDecoderBaseC::Seek64(off);
  }
  
  //: Find current location in stream.
  
  UIntT FFmpegAudioDecoderBaseC::Tell() const {
    return FFmpegAudioDecoderBaseC::Tell64();
  }
  
  //: Find the total size of the stream.
  
  UIntT FFmpegAudioDecoderBaseC::Size() const {
    return FFmpegAudioDecoderBaseC::Size64();
  }
  
  //: Find the total size of the stream.
  
  UIntT FFmpegAudioDecoderBaseC::Start() const {
    return FFmpegAudioDecoderBaseC::Start64();
  }
  
  //: Find current location in stream.
  
  Int64T FFmpegAudioDecoderBaseC::Tell64() const {
    if(!input.IsValid()) return 0;
    return input.Tell64() + pos/channels;
  }
  
  //: Seek to location in stream.
  // Returns FALSE, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool FFmpegAudioDecoderBaseC::Seek64(Int64T off) {
    pos = 0;
    if(!input.IsValid()) return false;
    ONDEBUG(cerr << "FFmpegAudioDecoderBaseC::Seek64 to " << off << " \n");
    // Be carefull seeking forward with some codec's

     input.Seek64(off);
     DecodeFrame();
     /*RealT rawtimestamp = 0;
     if(off > 0)
       rawtimestamp = packet.DecodeTimeStamp()*frac;
     while(off-rawtimestamp > buffSize+4800){
       DecodeFrame();
       rawtimestamp = packet.DecodeTimeStamp()*frac;
     }
    
      cerr << "pos " << off - rawtimestamp  << "\n";
     */
    return 0;
  }
  
  //: Find the total size of the stream.
  
  Int64T FFmpegAudioDecoderBaseC::Size64() const {
    if(!input.IsValid()) return 0;
    return input.Size64();   
  }
  
  //: Find the total size of the stream.
  
  Int64T FFmpegAudioDecoderBaseC::Start64() const {
    if(!input.IsValid()) return 0;
    return input.Start64();
  }

  //: Change position relative to the current one.
  
  bool FFmpegAudioDecoderBaseC::DSeek64(Int64T off) {
    if(!input.IsValid()) return false;
/*#if 1
    // Be carefull seeking forward with some codec's
    if(pCodecCtx->codec_id == CODEC_ID_MPEG2VIDEO) {
      ONDEBUG(cerr << "FFmpegAudioDecoderBaseC::DSeek64, Using seek hack." << off << " \n");
      if(off >= 0) {
        // Seek forward by decoding frames.
        for(Int64T i = 0;i < off;i++)
          DecodeFrame();
        return true;
      }
    }
#endif*/
    return input.DSeek64(off);
  }
  
  //: Change position relative to the current one.
  
  bool FFmpegAudioDecoderBaseC::DSeek(Int64T off) {
    return DSeek64(off);
  }
  
}

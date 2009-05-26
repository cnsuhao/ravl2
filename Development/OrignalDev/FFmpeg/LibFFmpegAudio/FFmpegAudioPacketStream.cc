#include "Ravl/Audio/FFmpegAudioPacketStream.hh"
#include "Ravl/DP/AttributeValueTypes.hh"
#include "Ravl/Exception.hh"

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  


  //: Constructor
  
  FFmpegAudioPacketStreamBodyC::FFmpegAudioPacketStreamBodyC(const StringC &filename) 
    : pFormatCtx(0),
      positionRefStream(0),
      currentTimeStamp(0),
      frameRate(0),
      frameRateBase(0),
      startFrame(0),
      haveSeek(true)
  { 
    Init();
    if(!Open(filename))
      throw ExceptionOperationFailedC("Failed to open file. ");
  }
  
  //: Default constructor.
  
  FFmpegAudioPacketStreamBodyC::FFmpegAudioPacketStreamBodyC()
    : pFormatCtx(0),
      positionRefStream(0),
      currentTimeStamp(0),
      frameRate(0),
      frameRateBase(0),
      startFrame(0),
      haveSeek(true)
  { Init(); }
  
  //: Initalise attributes.
  
  void FFmpegAudioPacketStreamBodyC::Init() {
    RegisterAttribute(AttributeTypeNumC<RealT>("framerate","Frame rate of video",true,false,0.0,1000.0,0.01,25));
    RegisterAttribute(AttributeTypeNumC<RealT>("samplerate","Sample rate of audio",true,false,0.0,1000.0,0.01,48000));
    RegisterAttribute(AttributeTypeNumC<RealT>("bitrate","Bit rate",true,false,0.0,1000.0,0.01,48000));
    RegisterAttribute(AttributeTypeStringC("filename","Original filename of stream",true,false,""));
    RegisterAttribute(AttributeTypeStringC("title","Title of stream",true,false,""));
    RegisterAttribute(AttributeTypeStringC("author","Author",true,false,""));
    RegisterAttribute(AttributeTypeStringC("copyright","Copyright for material",true,false,""));
    RegisterAttribute(AttributeTypeStringC("comment","Comment",true,false,""));
    RegisterAttribute(AttributeTypeStringC("album","album",true,false,""));
  }
  
  //: Destructor.
  
  FFmpegAudioPacketStreamBodyC::~FFmpegAudioPacketStreamBodyC() {
    // Close the video file
    if(pFormatCtx != 0)
      av_close_input_file(pFormatCtx);    
  }

  //: Find info about first audio stream.
  
  bool FFmpegAudioPacketStreamBodyC::FirstAudioStream(IntT &videoStreamId,IntT &codecId) {
    
    // Find the first audio stream
    for (UIntT i = 0; i < pFormatCtx->nb_streams; i++) {
      if (pFormatCtx->streams[i]->codec->codec_type != CODEC_TYPE_AUDIO) 
        continue;
      
      // Get a pointer to the codec context for the audio stream
      AVCodecContext *pCodecCtx = pFormatCtx->streams[i]->codec;
      
      // Find the decoder for the audio stream
      AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
      if (pCodec == NULL) 
        continue;
      
      videoStreamId = i;
      codecId = pCodecCtx->codec_id;
      sampleRate = pCodecCtx->sample_rate;
      channels = pCodecCtx->channels;
      
      // !!!!!!!!! Format Specific Hacks !!!!!!!!!!!!!!!

      StringC inputFormatName = pFormatCtx->iformat->name;
      ONDEBUG(cerr << "iformat=" << inputFormatName << "\n");
      
      StringC codecName;
      if(pCodec->name != 0)
        codecName = pCodec->name;
      
      ONDEBUG(cerr << "iformat=" << inputFormatName << " Codec=" << codecName << "\n");

      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      
      positionRefStream = videoStreamId;
      AVStream *avstream = pFormatCtx->streams[positionRefStream];
      
      frameRate     = avstream->time_base.num;
      frameRateBase = avstream->time_base.den/sampleRate;
      startFrame = Time2Frame(pFormatCtx->start_time);      
      
      ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::FirstAudioStream Index=" << av_find_default_stream_index(pFormatCtx) << " " << positionRefStream << " \n");
      
      
      ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::FirstAudioStream, FrameRate=" << frameRate << " FrameRateBase=" << frameRateBase << " Wrap=" << avstream->pts_wrap_bits << "\n");
      return true;
    }
    
    return false;
  }
  
  //: Check for a readable audio stream.
  
  bool FFmpegAudioPacketStreamBodyC::CheckForAudio() {
    // Check the file is open!
    if(pFormatCtx == 0) {
      ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::CheckForAudio no stream." << endl);
      return false;
    }

    ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::CheckForAudio streams= "<< pFormatCtx->nb_streams << endl);
    
    // Find the first audio stream
    for (UIntT i = 0; i < pFormatCtx->nb_streams; i++) {
      if (pFormatCtx->streams[i]->codec->codec_type != CODEC_TYPE_AUDIO) 
        continue;
      
      // Get a pointer to the codec context for the video stream
      AVCodecContext *pCodecCtx = pFormatCtx->streams[i]->codec;
      
      // Find the decoder for the video stream
      AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
      if (pCodec == NULL) 
        continue;
      
      ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::CheckForAudio codec found(" << (pCodec->name != NULL ? pCodec->name : "NULL") << ")" << endl);

/*
      // Inform the codec that we can handle truncated bitstreams
      // i.e. bitstreams where frame boundaries can fall in the middle of packets
      if (pCodec->capabilities & CODEC_CAP_TRUNCATED)
        pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;
*/
      bool ret = false;
      
      // Open codec
      if (avcodec_open(pCodecCtx, pCodec) >= 0) {
        ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::CheckForAudio codec constructed ok. " << endl);
        ret = true;
      }
      
      // Clean up codec
      avcodec_close(pCodecCtx);
      
      // Did we succeed ?
      if(ret) 
        return true;
    }
    
    return false;
  }
  
  
  //: Open file.
  
  bool FFmpegAudioPacketStreamBodyC::Open(const StringC &filename) {
    ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Open(" << filename << "), Called \n");
    
    // Open video file
    if (av_open_input_file(&pFormatCtx, filename, NULL, 0, NULL) != 0) {
      ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Open(" << filename << "), Failed to open file. \n");
      return false;
    }
    
    // Retrieve stream information
    if (av_find_stream_info(pFormatCtx) < 0) {
      ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Open(" << filename << "), Failed to find stream info. \n");
      return false;
    }
    AVStream *avstream = pFormatCtx->streams[positionRefStream];
      
    // Setup some default values.
    if(pFormatCtx->nb_streams >= 1) {
      positionRefStream = -1;
      frameRate     = avstream->time_base.num;
      frameRateBase = avstream->time_base.den/sampleRate;
      ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Open, FrameRate=" << frameRate << " FrameRateBase=" << frameRateBase << " \n");
    }
      
    ONDEBUG(dump_format(pFormatCtx, 0, filename, false));
    ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Open(" << filename << "), Completed ok. Streams=" << pFormatCtx->nb_streams << "\n");
    return true;
  }
  
  //: Get a packet from the stream.
  
  FFmpegAudioPacketC FFmpegAudioPacketStreamBodyC::Get() {
    FFmpegAudioPacketC packet(true);
   
    if(av_read_frame(pFormatCtx, &packet.Packet()) < 0)
      throw DataNotReadyC("No more packets to read. ");    
    
    if(packet.StreamIndex() == positionRefStream) {
      if(packet.DecodeTimeStamp() != (Int64T) AV_NOPTS_VALUE1)
        currentTimeStamp = Time2Frame(packet.DecodeTimeStamp());
    }
    return packet;
  }
  
  //: Get a packet from the stream.
  
  bool FFmpegAudioPacketStreamBodyC::Get(FFmpegAudioPacketC &packet) {
    
    packet = FFmpegAudioPacketC(true);
    if(av_read_frame(pFormatCtx, &packet.Packet()) < 0)
      return false;
   
    if(packet.StreamIndex() == positionRefStream) {
      if(packet.DecodeTimeStamp() != (Int64T) AV_NOPTS_VALUE1) {
	currentTimeStamp = Time2Frame(packet.DecodeTimeStamp());
	// This is acutally the next frame to be decoded.
	ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Get, currentTimeStamp=" << rawTimeStamp << " " << ((RealT) rawTimeStamp / AV_TIME_BASE) <<" " <<packet.DecodeTimeStamp() << " Frame=" << Time2Frame(rawTimeStamp) << " Flags=" << hex << packet.Flags() << dec << "\n");
      }
    }
    return true;
  }
  
  //: Is get ready ?
  
  bool FFmpegAudioPacketStreamBodyC::IsGetReady() const
  { return pFormatCtx != 0; }
  
  //: End of stream ?
  
  bool FFmpegAudioPacketStreamBodyC::IsGetEOS() const
  { return pFormatCtx == 0; }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegAudioPacketStreamBodyC::GetAttr(const StringC &attrName,StringC &attrValue) {
    if(attrName=="duration") {
      if(pFormatCtx == 0) {
        attrValue = StringC();
        return true;
      }
      attrValue = StringC((Int64T)(pFormatCtx->duration));
      return true;
    }
    if(attrName=="filename") {
      if(pFormatCtx == 0) {
        attrValue = StringC();
        return true;
      }
      attrValue = pFormatCtx->filename;
      return true;
    }
    if(attrName=="title") {
      if(pFormatCtx == 0) {
        attrValue = StringC();
        return true;
      }
      attrValue = pFormatCtx->title;
      return true;
    }
    if(attrName=="author") {
      if(pFormatCtx == 0) {
        attrValue = StringC();
        return true;
      }
      attrValue = pFormatCtx->author;
      return true;
    }
    if(attrName=="copyright") {
      if(pFormatCtx == 0) {
        attrValue = StringC();
        return true;
      }
      attrValue = pFormatCtx->copyright;
      return true;
    }
    if(attrName=="comment") {
      if(pFormatCtx == 0) {
        attrValue = StringC();
        return true;
      }
      attrValue = pFormatCtx->comment;
      return true;
    }
    if(attrName=="album") {
      if(pFormatCtx == 0) {
        attrValue = StringC();
        return true;
      }
      attrValue = pFormatCtx->album;
      return true;
    }
    
    return DPISPortBodyC<FFmpegAudioPacketC>::GetAttr(attrName,attrValue);
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegAudioPacketStreamBodyC::GetAttr(const StringC &attrName,IntT &attrValue) {
    return DPISPortBodyC<FFmpegAudioPacketC>::GetAttr(attrName,attrValue);
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegAudioPacketStreamBodyC::GetAttr(const StringC &attrName,RealT &attrValue) {
     if(attrName == "bitrate") {
      if(pFormatCtx == 0)
	attrValue = -1;
      else
	attrValue = pFormatCtx->bit_rate;
      return true;
    }
    if(attrName == "samplerate"){
      attrValue = sampleRate;
      return true;
    }
    return DPISPortBodyC<FFmpegAudioPacketC>::GetAttr(attrName,attrValue);
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegAudioPacketStreamBodyC::GetAttr(const StringC &attrName,bool &attrValue) {
    return DPISPortBodyC<FFmpegAudioPacketC>::GetAttr(attrName,attrValue);
  }
  
  //: Seek to location in stream.
  // Returns FALSE, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool FFmpegAudioPacketStreamBodyC::Seek(UIntT off) {
    return Seek64(off);
  }
  
  bool FFmpegAudioPacketStreamBodyC::DSeek(IntT off) {
    return FFmpegAudioPacketStreamBodyC::DSeek64(off);
  }
  
  //: Find current location in stream.
  
  UIntT FFmpegAudioPacketStreamBodyC::Tell() const {
    return FFmpegAudioPacketStreamBodyC::Tell64();
  }
  
  //: Find the total size of the stream.
  
  UIntT FFmpegAudioPacketStreamBodyC::Size() const {
    Int64T val = FFmpegAudioPacketStreamBodyC::Size64();
    if(val < 0) return  ((UIntT) -1);
    return val;
  }
  
  //: Find current location in stream.
  
  Int64T FFmpegAudioPacketStreamBodyC::Tell64() const {
    ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Tell64 = " << currentTimeStamp << " \n");
    return currentTimeStamp;
  }
   
  //: Seek to location in stream.
  // Returns FALSE, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool FFmpegAudioPacketStreamBodyC::DSeek64(Int64T off) {
    ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::DSeek64 Delta=" << off << " \n");
    if(!haveSeek) {
      // Can we just dump frames ?
      if(off >= 0 && off < 100) {
        for(Int64T i = 0;i < off;i++)
          Discard();
        return true;
      }
      else
      {
        // are we just seeking to the beginning?
        if (off + currentTimeStamp == Time2Frame(pFormatCtx->start_time))
        {
          return Seek64(off + currentTimeStamp);
        }
      }
      // Nope we can't seek.
      return false;
    }
    return Seek64(off + currentTimeStamp);
  }
  
  //: Seek to location in stream.
  // Returns FALSE, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool FFmpegAudioPacketStreamBodyC::Seek64(Int64T off) {
    if(pFormatCtx == 0)
      return false;
    ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Seek64 to " << off << " (Time:" << Frame2Time(off) << ")\n");
    // Stop if we don't have a stream index and this isn't a trivial seek
   /* if(!(haveSeek || Time2Frame(pFormatCtx->start_time) == off)) {
      cerr << "FFmpegAudioPacketStreamBodyC::Seek64, Format doesn't support seeking. \n";
      return false;
  }*/ 
    
    if(!av_seek_frame(pFormatCtx, positionRefStream, Frame2Time(off), 0) < 0){
      if(!av_seek_frame(pFormatCtx, -1, Frame2Time(off), 0) < 0){
	cerr << "FFmpegAudioPacketStreamBodyC::Seek, Seek failed. " << off << " \n";
	return false;
      }
    }

    currentTimeStamp = off;
    return true;
  }
  
  //: Find the total size of the stream.
  
  Int64T FFmpegAudioPacketStreamBodyC::Size64() const {
    const AVStream *st = pFormatCtx->streams[positionRefStream];
    
    if(pFormatCtx == 0)
      return 0;
    ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Size64, Duration=" << pFormatCtx->duration << " Start=" << pFormatCtx->start_time << " FrameRateBase=" << frameRateBase << "  " << "\n";)
    if(pFormatCtx->duration <= 0)
      return -1;
    
    return Time2Frame((pFormatCtx->duration)*st->time_base.den/st->time_base.num/AV_TIME_BASE)+Start64();
  }
  
  //: Find the total size of the stream.
  
  Int64T FFmpegAudioPacketStreamBodyC::Start64() const {
    if(pFormatCtx == 0)
      return 0;
    const AVStream *st = pFormatCtx->streams[positionRefStream];
    ONDEBUG(cerr << "FFmpegAudioPacketStreamBodyC::Start64, " << pFormatCtx->start_time << " Frame=" << Time2Frame(pFormatCtx->start_time) << "\n");
    return Time2Frame(pFormatCtx->start_time*st->time_base.den/st->time_base.num/AV_TIME_BASE);
  }
  
  //: Find the total size of the stream.
  
  UIntT FFmpegAudioPacketStreamBodyC::Start() const {
    return FFmpegAudioPacketStreamBodyC::Start64();
  }
  
  Int64T FFmpegAudioPacketStreamBodyC::Frame2Time(Int64T arg) const {
    RealT frac = (RealT) frameRate / (RealT) frameRateBase;
    return llround(((RealT) arg / frac));
  }
  
  //: Convert a  time into a frame no
  
  Int64T FFmpegAudioPacketStreamBodyC::Time2Frame(Int64T arg) const {
    RealT frac = (RealT) frameRate / (RealT) frameRateBase;
    return llround(((RealT) arg) * frac);
  }
  
}

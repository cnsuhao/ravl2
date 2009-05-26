#line 1 "/media/project/work/PHD/Ravl_Code/Contrib/LibFFmpegAudio/FFmpegAudioPacketStream.hh"
#ifndef RAVL_FFMPEG_AVFORMAT_HEADER 
#define RAVL_FFMPEG_AVFORMAT_HEADER 

#include "Ravl/DP/SPort.hh"
#include "Ravl/Audio/FFmpegAudioPacket.hh"

#include <ffmpeg/avformat.h>

namespace RavlN {
  
  
  //: FFmpeg packet stream.
  
  class FFmpegAudioPacketStreamBodyC 
    : public DPISPortBodyC<FFmpegAudioPacketC>
  {
  public:
    FFmpegAudioPacketStreamBodyC(const StringC &filename);
    //: Constructor
    
    FFmpegAudioPacketStreamBodyC();
    //: Default constructor.
    
    ~FFmpegAudioPacketStreamBodyC();
    //: Destructor.
    
    bool Open(const StringC &filename);
    //: Open file.
    
    bool CheckForAudio();
    //: Check for a readable video stream.
    
    AVFormatContext *FormatCtx()
    { return pFormatCtx; }
    //: Access format context.
    
    bool FirstAudioStream(IntT &videoStreamId,IntT &codecId);
    //: Find info about first video stream.
    
    virtual FFmpegAudioPacketC Get();
    //: Get a packet from the stream.
    
    virtual bool Get(FFmpegAudioPacketC &packet);
    //: Get a packet from the stream.
    
    virtual bool IsGetReady() const;
    //: Is get ready ?
    
    virtual bool IsGetEOS() const;
    //: End of stream ?
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,RealT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,bool &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual UIntT Tell() const; 
    //: Find current location in stream.
    
    virtual UIntT Size() const; 
    //: Find the total size of the stream.
    
    virtual UIntT Start() const; 
    //: Find the total size of the stream.
    
    virtual Int64T Tell64() const; 
    //: Find current location in stream.

    virtual bool DSeek64(Int64T off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool Seek64(Int64T off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual Int64T Size64() const; 
    //: Find the total size of the stream.

    virtual Int64T Start64() const; 
    //: Find the total size of the stream.
    
    RealT convFactor(){return frameRate/frameRateBase;}
    
  protected:
    void Init();
    //: Initalise attributes.
    
    StringC filename;
    AVFormatContext *pFormatCtx;
    
    IntT positionRefStream; // Stream to use as a position reference.
    Int64T currentTimeStamp;
    Int64T previousTimeStamp;
    RealT frameRate;
    RealT frameRateBase;
    IntT channels;
    StringC codec;
    RealT sampleRate;
    Int64T startFrame; // Frame number of start of sequence. 
    bool haveSeek; // Do we have seeking ?    
    
    Int64T Frame2Time(Int64T frame) const;
    //: Convert a frame no into a time
    
    Int64T Time2Frame(Int64T time) const;
    //: Convert a  time into a frame no
    
  };
    

  //! userlevel=Normal
  //: FFmpeg packet stream. 
  //!cwiz:author
  
  class FFmpegPacketStreamC
    : public DPISPortC<FFmpegAudioPacketC>
  {
  public:
    FFmpegPacketStreamC(const StringC & filename) 
      : DPEntityC(*new FFmpegAudioPacketStreamBodyC(filename))
    {}
    //: Constructor 
    //!cwiz:author
    
    FFmpegPacketStreamC(bool)
      : DPEntityC(*new FFmpegAudioPacketStreamBodyC())
    {}
    //: Constructor.
    
    FFmpegPacketStreamC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
    FFmpegPacketStreamC(const DPISPortC<FFmpegAudioPacketC> &other)
      : DPEntityC(dynamic_cast<const FFmpegAudioPacketStreamBodyC *>(other.BodyPtr(other)))
    {}
    //: Upcast constructor.
    
    bool Open(const StringC & filename) 
    { return Body().Open(filename); }
    //: Open file. 
    //!cwiz:author
    
    bool CheckForAudio() 
    { return Body().CheckForAudio(); }
    //: Check for a readable video stream. 
    //!cwiz:author

    AVFormatContext *FormatCtx()
    { return Body().FormatCtx(); }
    //: Access format context.
    
    bool FirstAudioStream(IntT &videoStreamId,IntT &codecId)
    { return Body().FirstAudioStream(videoStreamId,codecId); }
    //: Find info about first video stream.
    
    RealT convFactor(){
      return Body().convFactor();
   }
    
  protected:
    FFmpegPacketStreamC(FFmpegAudioPacketStreamBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor. 
    
    FFmpegAudioPacketStreamBodyC& Body()
    { return dynamic_cast<FFmpegAudioPacketStreamBodyC &>(DPEntityC::Body()); }
    //: Body Access. 
    
    const FFmpegAudioPacketStreamBodyC& Body() const
    { return dynamic_cast<const FFmpegAudioPacketStreamBodyC &>(DPEntityC::Body()); }
    //: Body Access. 
    
  };
}


#endif


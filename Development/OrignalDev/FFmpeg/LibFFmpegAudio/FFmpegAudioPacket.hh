#line 1 "/home/jack/Desktop/svn/PHD/Ravl_Code/Contrib/LibFFmpegAudio/FFmpegAudioPacket.hh"
#ifndef RAVL_FFMPEGPACKET_HEADEER
#define RAVL_FFMPEGPACKET_HEADEER 1

#include "Ravl/RefCounter.hh"

//link ffmpeg as a purely c library since all c++ wrapper functions were removed
extern "C" {
   #include <ffmpeg/avformat.h>
   #include <ffmpeg/avcodec.h>
}

//fix complaint about INT64_C
#define INT64_C
#define __STDC_CONSTANT_MACROS
#include <stdint.h>
	     	     
//define new AV_NOPTS_VALUE1
#define   AV_NOPTS_VALUE1  0x8000000000000000LL

namespace RavlN {

  //! userlevel=Develop
  //: FFmpeg data packet.
  
  class FFmpegAudioPacketBodyC 
    : public RCBodyC
  {
  public:
    FFmpegAudioPacketBodyC() 
    { packet.data = 0;}
    //: Default constructor.
    
    ~FFmpegAudioPacketBodyC();
    //: Destructor.
    
    AVPacket &Packet()
    { return packet; }
    //: Access packet.
    
    IntT StreamIndex() const
    { return packet.stream_index; }
    //: Access stream index of packet.
    
    ByteT *Data()
    { return packet.data; }
    //: Access data.
    
    UIntT Size() const
    { return packet.size; }
    //: Access size of packet.
    
    Int64T TimeStamp()
    { return packet.pts; }
    //: Presentation time stamp.
    
    Int64T DecodeTimeStamp()
    { return packet.dts; }
    //: Decode time stamp.
    
    IntT Flags() const 
    { return packet.flags; }
    //: Access packet flags
    
  protected:
    AVPacket packet;
  };
  
  //! userlevel=Normal
  //: FFmpeg data packet. 
  //!cwiz:author
  
  class FFmpegAudioPacketC
    : public RCHandleC<FFmpegAudioPacketBodyC>
  {
  public:
    FFmpegAudioPacketC(bool) 
      : RCHandleC<FFmpegAudioPacketBodyC>(*new FFmpegAudioPacketBodyC())
    {}
    //: Constructor. 
    //!cwiz:author
    
    FFmpegAudioPacketC() 
    {}
    //: Default constructor
    // Creates an invalid constructor.
    
    AVPacket & Packet() 
    { return Body().Packet(); }
    //: Access packet. 
    //!cwiz:author
    
    IntT StreamIndex() const
    { return Body().StreamIndex(); }
    //: Access stream index of packet.
    
    ByteT *Data()
    { return Body().Data(); }
    //: Access data.
    
    UIntT Size() const
    { return Body().Size(); }
    //: Access size of packet.
    
    Int64T TimeStamp()
    { return Body().TimeStamp(); }
    //: Presentation time stamp.
    
    Int64T DecodeTimeStamp()
    { return Body().DecodeTimeStamp(); }
    //: Decode time stamp.
    
    IntT Flags() const 
    { return Body().Flags(); }
    //: Access packet flags
    
  protected:
    FFmpegAudioPacketC(FFmpegAudioPacketBodyC &bod)
     : RCHandleC<FFmpegAudioPacketBodyC>(bod)
    {}
    //: Body constructor. 
    
    FFmpegAudioPacketBodyC& Body()
    { return static_cast<FFmpegAudioPacketBodyC &>(RCHandleC<FFmpegAudioPacketBodyC>::Body()); }
    //: Body Access. 
    
    const FFmpegAudioPacketBodyC& Body() const
    { return static_cast<const FFmpegAudioPacketBodyC &>(RCHandleC<FFmpegAudioPacketBodyC>::Body()); }
    //: Body Access. 
    
  };

}


#endif

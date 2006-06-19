// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FFMPEGPACKET_HEADEER
#define RAVL_FFMPEGPACKET_HEADEER 1
//! rcsid="$Id$"
//! lib=RavlLibFFmpeg
//! docentry = "Ravl.API.Images.Video.Video IO.LibFFmpeg"

#include "Ravl/RefCounter.hh"
#include <ffmpeg/avformat.h>

namespace RavlN {

  //! userlevel=Develop
  //: FFmpeg data packet.
  
  class FFmpegPacketBodyC 
    : public RCBodyC
  {
  public:
    FFmpegPacketBodyC() 
    { packet.data = 0; }
    //: Default constructor.
    
    ~FFmpegPacketBodyC();
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
  
  class FFmpegPacketC
    : public RCHandleC<FFmpegPacketBodyC>
  {
  public:
    FFmpegPacketC(bool) 
      : RCHandleC<FFmpegPacketBodyC>(*new FFmpegPacketBodyC())
    {}
    //: Constructor. 
    //!cwiz:author
    
    FFmpegPacketC() 
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
    FFmpegPacketC(FFmpegPacketBodyC &bod)
     : RCHandleC<FFmpegPacketBodyC>(bod)
    {}
    //: Body constructor. 
    
    FFmpegPacketBodyC& Body()
    { return static_cast<FFmpegPacketBodyC &>(RCHandleC<FFmpegPacketBodyC>::Body()); }
    //: Body Access. 
    
    const FFmpegPacketBodyC& Body() const
    { return static_cast<const FFmpegPacketBodyC &>(RCHandleC<FFmpegPacketBodyC>::Body()); }
    //: Body Access. 
    
  };

}


#endif

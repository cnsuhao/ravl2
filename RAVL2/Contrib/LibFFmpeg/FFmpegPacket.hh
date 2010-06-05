// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FFMPEGPACKET_HEADEER
#define RAVL_FFMPEGPACKET_HEADEER 1
//! rcsid="$Id: FFmpegPacket.hh 7406 2009-12-07 16:57:04Z simondennis $"
//! lib=RavlLibFFmpeg
//! docentry = "Ravl.API.Images.Video.Video IO.LibFFmpeg"

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS 1
#include <stdint.h>
#endif

#include "Ravl/RefCounter.hh"
#include <iostream>
#include "Ravl/Stream.hh"
//link ffmpeg as a purely c library since all c++ wrapper functions were removed
extern "C" {
#if defined(LIBAVFORMAT_VERSION_MAJOR) && LIBAVFORMAT_VERSION_MAJOR >= 52
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#else 
#include <avcodec.h>
#include <avformat.h>
#endif
}

#ifndef INT64_C
#define INT64_C 1
#endif
	     	     
//define new AV_NOPTS_VALUE1
#define   AV_NOPTS_VALUE1  0x8000000000000000LL

namespace RavlN {
using namespace std;
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
    { 
      return packet; }
    //: Access packet.
    
    IntT StreamIndex() const
    { return packet.stream_index; }
    //: Access stream index of packet.
    
    void setPacket(AVPacket &pak) {
       packet = pak;}

    void setWidthHeight(SizeT wid,SizeT hgt) {
       width = wid;
       height = hgt;
    }

    IntT getWidth() {
       return width;
    }
 
    IntT getHeight() {
       return height;
    }

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
    mutable AVPacket packet;
    mutable IntT width,height;
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
    { 
      }
    //: Constructor. 
    //!cwiz:author
    
    FFmpegPacketC() 
    {}
    //: Default constructor
    // Creates an invalid constructor.
    
    AVPacket & Packet() 
    { 
      return Body().Packet(); }
    //: Access packet. 
    //!cwiz:author
    
    void setPacket(AVPacket &pak) {
    return Body().setPacket(pak);}
 
    void setWH(SizeT wid,SizeT hgt) {
       return Body().setWidthHeight(wid,hgt);
    }

    IntT getWidth() {
       return Body().getWidth();
    }

    IntT getHeight() {
       return Body().getHeight();
    }

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

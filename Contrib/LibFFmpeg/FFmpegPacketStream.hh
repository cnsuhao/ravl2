// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FFMPEG_AVFORMAT_HEADER 
#define RAVL_FFMPEG_AVFORMAT_HEADER 
//! rcsid="$Id$"
//! lib=RavlLibFFmpeg
//! docentry = "Ravl.API.Images.Video.Video IO.LibFFmpeg"

#include "Ravl/DP/SPort.hh"
#include "Ravl/Image/FFmpegPacket.hh"

extern "C" {
#include <ffmpeg/avformat.h>
}

namespace RavlN {
  
  
  //: FFmpeg packet stream.
  
  class FFmpegPacketStreamBodyC 
    : public DPISPortBodyC<FFmpegPacketC>
  {
  public:
    FFmpegPacketStreamBodyC(const StringC &filename);
    //: Constructor
    
    FFmpegPacketStreamBodyC();
    //: Default constructor.
    
    ~FFmpegPacketStreamBodyC();
    //: Destructor.
    
    bool Open(const StringC &filename);
    //: Open file.
    
    bool CheckForVideo();
    //: Check for a readable video stream.
    
    AVFormatContext *FormatCtx()
    { return pFormatCtx; }
    //: Access format context.
    
    bool FirstVideoStream(IntT &videoStreamId,IntT &codecId);
    //: Find info about first video stream.
    
    virtual FFmpegPacketC Get();
    //: Get a packet from the stream.
    
    virtual bool Get(FFmpegPacketC &packet);
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
    
  protected:
    void Init();
    //: Initalise attributes.
    
    StringC filename;
    AVFormatContext *pFormatCtx;
    
    IntT positionRefStream; // Stream to use as a position reference.
    Int64T currentTimeStamp;
    Int64T frameRate;
    Int64T frameRateBase;
    
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
    : public DPISPortC<FFmpegPacketC>
  {
  public:
    FFmpegPacketStreamC(const StringC & filename) 
      : DPEntityC(*new FFmpegPacketStreamBodyC(filename))
    {}
    //: Constructor 
    //!cwiz:author
    
    FFmpegPacketStreamC(bool)
      : DPEntityC(*new FFmpegPacketStreamBodyC())
    {}
    //: Constructor.
    
    FFmpegPacketStreamC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
    FFmpegPacketStreamC(const DPISPortC<FFmpegPacketC> &other)
      : DPEntityC(dynamic_cast<const FFmpegPacketStreamBodyC *>(other.BodyPtr(other)))
    {}
    //: Upcast constructor.
    
    bool Open(const StringC & filename) 
    { return Body().Open(filename); }
    //: Open file. 
    //!cwiz:author
    
    bool CheckForVideo() 
    { return Body().CheckForVideo(); }
    //: Check for a readable video stream. 
    //!cwiz:author

    AVFormatContext *FormatCtx()
    { return Body().FormatCtx(); }
    //: Access format context.
    
    bool FirstVideoStream(IntT &videoStreamId,IntT &codecId)
    { return Body().FirstVideoStream(videoStreamId,codecId); }
    //: Find info about first video stream.
    
  protected:
    FFmpegPacketStreamC(FFmpegPacketStreamBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor. 
    
    FFmpegPacketStreamBodyC& Body()
    { return dynamic_cast<FFmpegPacketStreamBodyC &>(DPEntityC::Body()); }
    //: Body Access. 
    
    const FFmpegPacketStreamBodyC& Body() const
    { return dynamic_cast<const FFmpegPacketStreamBodyC &>(DPEntityC::Body()); }
    //: Body Access. 
    
  };
}


#endif


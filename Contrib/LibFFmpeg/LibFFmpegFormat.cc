// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id$"
//! lib=RavlLibFFmpeg
//! author = "Warren Moore"
//! file="Ravl/Contrib/LibFFmpeg/LibFFmpegFormat.cc"

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS 1
#include <stdint.h>
#endif

#include "Ravl/Image/LibFFmpegFormat.hh"
#include "Ravl/Image/ImgIOFFmpeg.hh"
#include <ctype.h>
#include "Ravl/DP/ByteFileIO.hh"
#include "Ravl/DP/SPortAttach.hh"
#include "Ravl/Image/FFmpegPacketStream.hh"
#include "Ravl/Image/FFmpegVideoDecoder.hh"

#include <avcodec.h>
#include <avformat.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN
{
  
  void InitLibFFmpegFormat()
  {}



  FileFormatLibFFmpegBodyC::FileFormatLibFFmpegBodyC() :
    FileFormatBodyC("ffmpeg", "FFmpeg file input.")
  {
    av_register_all();
  }
  
  
  const type_info &FileFormatLibFFmpegBodyC::ProbeLoad(IStreamC &in, const type_info &obj_type) const
  {
    ONDEBUG(cerr << "FileFormatLibFFmpegBodyC::ProbeLoad(IStreamC &,...) called" << endl);
    
    if (!in.good())
      return typeid(void);
    
    ONDEBUG(cerr << "FileFormatLibFFmpegBodyC::ProbeLoad(IStreamC&,...) not an FFmpeg supported file" << endl);
    return typeid(void); 
  }



  const type_info &FileFormatLibFFmpegBodyC::ProbeLoad(const StringC &filename,
                                                      IStreamC &in,
                                                      const type_info &obj_type) const
  {
    ONDEBUG(cerr << "FileFormatLibFFmpegBodyC::ProbeLoad(const StringC&,IStreamC&,...) called (" << filename << ")" << endl);
    
    if (!in.good())
      return typeid(void);
    
    if (IsSupported(filename.chars()))
    {
      return typeid(ImageC<ByteRGBValueC>);
    }
    
    ONDEBUG(cerr << "FileFormatLibFFmpegBodyC::ProbeLoad(const StringC&,IStreamC&,...) not an FFmpeg supported file (" << filename << ")" << endl);
    return typeid(void);
  }



  const type_info &FileFormatLibFFmpegBodyC::ProbeSave(const StringC &filename,
                                                       const type_info &obj_type,
                                                       bool forceFormat ) const
  {
    //ONDEBUG(cerr << "FileFormatLibFFmpegBodyC::ProbeSave(const StringC&,...) not supported" << endl);
    return typeid(void);   
  }


  
  DPIPortBaseC FileFormatLibFFmpegBodyC::CreateInput(const StringC &filename, const type_info &obj_type) const
  {
    ONDEBUG(cerr << "FileFormatLibFFmpegBodyC::CreateInput(const StringC&,...) called (" << filename << ")" << endl);
    
    if (IsSupported(filename.chars()))
    {
      //return SPort(DPIByteFileC(fn) >> ImgILibFFmpegC(true));
      FFmpegPacketStreamC packetStream(filename);
      IntT codecId = -1;
      IntT videoStreamId = -1;
      if(!packetStream.FirstVideoStream(videoStreamId,codecId))
        return DPIPortBaseC();
      return ImgIOFFmpegC<ImageC<ByteRGBValueC> >(packetStream,videoStreamId,codecId);
    }
    
    ONDEBUG(cerr << "FileFormatLibFFmpegBodyC::CreateInput(const StringC&,...) not an FFmpeg supported file (" << filename << ")" << endl);
    return DPIPortBaseC();
  }



  DPOPortBaseC FileFormatLibFFmpegBodyC::CreateOutput(const StringC &filename, const type_info &obj_type) const
  {
    return DPOPortBaseC();  
  }



  DPIPortBaseC FileFormatLibFFmpegBodyC::CreateInput(IStreamC &in, const type_info &obj_type) const
  {
    return DPIPortBaseC();
  }



  DPOPortBaseC FileFormatLibFFmpegBodyC::CreateOutput(OStreamC &out, const type_info &obj_type) const
  {
    return DPOPortBaseC();  
  }



  const type_info &FileFormatLibFFmpegBodyC::DefaultType() const
  { 
    return typeid(ImageC<ByteRGBValueC>); 
  }



  bool FileFormatLibFFmpegBodyC::IsSupported(const char *filename) const
  {
    ONDEBUG(cerr << "FileFormatLibFFmpegBodyC::IsSupported(const char *) called (" << filename << ")" << endl);
    FFmpegPacketStreamC stream(true);
    bool ret = false;
    if(stream.Open(filename)) 
      ret = stream.CheckForVideo();
    ONDEBUG(cerr << "FileFormatLibFFmpegBodyC::IsSupported(const char *) " << (ret ? "succeeded" : "failed") << endl);
    return ret;
  }
  
  
  
  static FileFormatLibFFmpegC Init;  



}

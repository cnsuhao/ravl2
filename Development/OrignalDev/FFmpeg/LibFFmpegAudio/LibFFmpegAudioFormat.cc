// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id: LibFFmpegFormat.cc 5003 2005-07-04 07:50:49Z craftit $"
//! lib=RavlLibFFmpeg
//! author = "Warren Moore"
//! file="Ravl/Contrib/LibFFmpeg/LibFFmpegFormat.cc"

#include "Ravl/Audio/LibFFmpegAudioFormat.hh"
#include <ctype.h>
#include "Ravl/DP/ByteFileIO.hh"
#include "Ravl/DP/SPortAttach.hh"
#include "Ravl/Audio/FFmpegAudioPacketStream.hh"
#include "Ravl/Audio/FFmpegAudioDecoder.hh"

#include <ffmpeg/avcodec.h>
#include <ffmpeg/avformat.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlAudioN
{
  
  void InitLibFFmpegAudioFormat()
  {}

  FileFormatLibFFmpegAudioBodyC:: FileFormatLibFFmpegAudioBodyC() :
    FileFormatBodyC("ffmpeg", "FFmpeg file input.")
  {
    av_register_all();
  }
  
  const type_info & FileFormatLibFFmpegAudioBodyC::ProbeLoad(IStreamC &in, const type_info &obj_type) const
  {
    ONDEBUG(cerr << " FileFormatLibFFmpegAudioBodyC::ProbeLoad(IStreamC &,...) called" << endl);
    
    if (!in.good())
      return typeid(void);
    
    ONDEBUG(cerr << " FileFormatLibFFmpegAudioBodyC::ProbeLoad(IStreamC&,...) not an FFmpeg supported file" << endl);
    return typeid(void); 
  }

  const type_info & FileFormatLibFFmpegAudioBodyC::ProbeLoad(const StringC &filename,
                                                      IStreamC &in,
                                                      const type_info &obj_type) const
  {
    ONDEBUG(cerr << " FileFormatLibFFmpegAudioBodyC::ProbeLoad(const StringC&,IStreamC&,...) called (" << filename << ")" << endl);
    
    if (!in.good())
      return typeid(void);
    
    if (IsSupported(filename.chars()))
    {
      return typeid(SampleElemC<2,Int16T> );
    }
    
    ONDEBUG(cerr << " FileFormatLibFFmpegAudioBodyC::ProbeLoad(const StringC&,IStreamC&,...) not an FFmpeg supported file (" << filename << ")" << endl);
    return typeid(void);
  }



  const type_info & FileFormatLibFFmpegAudioBodyC::ProbeSave(const StringC &filename,
                                                       const type_info &obj_type,
                                                       bool forceFormat ) const
  {
    ONDEBUG(cerr << " FileFormatLibFFmpegAudioBodyC::ProbeSave(const StringC&,...) not supported" << endl);
    return typeid(void);   
  }


  
  DPIPortBaseC FileFormatLibFFmpegAudioBodyC::CreateInput(const StringC &filename, const type_info &obj_type) const
  {
    ONDEBUG(cerr << " FileFormatLibFFmpegAudioBodyC::CreateInput(const StringC&,...) called (" << filename << ")" << endl);
    
    if (IsSupported(filename.chars()))
    {
      FFmpegPacketStreamC packetStream(filename);
      IntT codecId = -1;
      IntT audioStreamId = -1;
      if(!packetStream.FirstAudioStream(audioStreamId,codecId))
        return DPIPortBaseC();
      return AudioIOFFmpegC<SampleElemC<2,Int16T> >(packetStream,audioStreamId,codecId);
    }
    
    ONDEBUG(cerr << " FileFormatLibFFmpegAudioBodyC::CreateInput(const StringC&,...) not an FFmpeg supported file (" << filename << ")" << endl);
    return DPIPortBaseC();
  }



  DPOPortBaseC FileFormatLibFFmpegAudioBodyC::CreateOutput(const StringC &filename, const type_info &obj_type) const
  {
    return DPOPortBaseC();  
  }



  DPIPortBaseC FileFormatLibFFmpegAudioBodyC::CreateInput(IStreamC &in, const type_info &obj_type) const
  {
    return DPIPortBaseC();
  }



  DPOPortBaseC FileFormatLibFFmpegAudioBodyC::CreateOutput(OStreamC &out, const type_info &obj_type) const
  {
    return DPOPortBaseC();  
  }



  const type_info & FileFormatLibFFmpegAudioBodyC::DefaultType() const
  { 
    return typeid(SampleElemC<2,Int16T>); 
  }



  bool FileFormatLibFFmpegAudioBodyC::IsSupported(const char *filename) const
  {
    ONDEBUG(cerr << " FileFormatLibFFmpegAudioBodyC::IsSupported(const char *) called (" << filename << ")" << endl);
    FFmpegPacketStreamC stream(true);
    bool ret = false;
    ret = stream.CheckForAudio();
    if(stream.Open(filename)) 
      ret = stream.CheckForAudio();
    ONDEBUG(cerr << " FileFormatLibFFmpegAudioBodyC::IsSupported(const char *) " << (ret ? "succeeded" : "failed") << endl);
    return ret;
  }

  static FileFormatLibFFmpegAudioC Init;  

}

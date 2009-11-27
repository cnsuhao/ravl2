// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLibFFmpeg
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS 1
#include <stdint.h>
#endif

#include <stdio.h>

#include "Ravl/Image/FFmpegEncodePacketStream.hh"
#include "Ravl/DP/AttributeValueTypes.hh"
#include "Ravl/Exception.hh"
#include "Ravl/String.hh"
/*
extern "C" {
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavcodec/avcodec.h>
}
*/
#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  


  //: Constructor
  
  FFmpegEncodePacketStreamBodyC::FFmpegEncodePacketStreamBodyC(const StringC &filename) 
    : pFormatCtx(0),
      fmt(0),
      audio_st(0),
      video_st(0),
      audio_pts(0),
      video_pts(0),
      positionRefStream(0),
      currentTimeStamp(0),
      frameRate(0),
      frameRateBase(0),
      startFrame(0),
      haveSeek(true),
      width(1280),
      height(544),
      compression(31),
      header_done(false),
      done_header(0),
      header_not_done_yet(true)
  { 
    Init();
    if(!Open(filename))
      throw ExceptionOperationFailedC("Failed to open file. ");
  }
  
  //: Default constructor.
  
  FFmpegEncodePacketStreamBodyC::FFmpegEncodePacketStreamBodyC()
    : pFormatCtx(0),
      fmt(0),
      audio_st(0),
      video_st(0),
      audio_pts(0),
      video_pts(0),
      positionRefStream(0),
      currentTimeStamp(0),
      frameRate(0),
      frameRateBase(0),
      startFrame(0),
      haveSeek(true),
      width(1280),
      height(544),
      compression(31),
      header_done(false),
      done_header(0),
      header_not_done_yet(true)
  { Init(); }
  
  //: Initalise attributes.
  
  void FFmpegEncodePacketStreamBodyC::Init() {
    RegisterAttribute(AttributeTypeNumC<RealT>("framerate","Frame rate of video",true,false,0.0,1000.0,0.01,25));
    ONDEBUG(std::cerr << "FFmpegDPOPacketStreamBodyC::Init. \n";)
    RegisterAttribute(AttributeTypeStringC("filename","Original filename of stream",true,false,""));
    RegisterAttribute(AttributeTypeStringC("title","Title of stream",true,false,""));
    RegisterAttribute(AttributeTypeStringC("author","Author",true,false,""));
    RegisterAttribute(AttributeTypeStringC("copyright","Copyright for material",true,false,""));
    RegisterAttribute(AttributeTypeStringC("comment","Comment",true,false,""));
    RegisterAttribute(AttributeTypeStringC("album","album",true,false,""));
    RegisterAttribute(AttributeTypeNumC<IntT>("compression","compression ratio",true,false,1,31,1,31));
  }
  
  //: Destructor.
  
  FFmpegEncodePacketStreamBodyC::~FFmpegEncodePacketStreamBodyC() {
    // Close the video file
    if(video_st != 0) {
       if(pFormatCtx != 0) {
          av_write_trailer(pFormatCtx);
       }
    }
      ONDEBUG(std::cerr << "FFmpegDPOPacketStreamBodyC::~FFmpegDPOPacketStreamBodyC. \n";)
  }

  //: Find info about first video stream.
  
  bool FFmpegEncodePacketStreamBodyC::FirstVideoStream(IntT &videoStreamId,IntT &codecId) {
          ONDEBUG(cerr << "FFmpegDPOPacketStreamBodyC::FirstVideoStream " << " \n");
    // Find the first video stream
/*
    for (UIntT i = 0; i < pFormatCtx->nb_streams; i++) {
      if (pFormatCtx->streams[i]->codec->codec_type != CODEC_TYPE_VIDEO) 
        continue;
      ONDEBUG(cerr << "FFmpegDPOPacketStreamBodyC::FirstVideoStream pCodeCtx" << " \n");      
      // Get a pointer to the codec context for the video stream
      AVCodecContext *pCodecCtx = pFormatCtx->streams[i]->codec;
      ONDEBUG(cerr << "FFmpegDPOPacketStreamBodyC::FirstVideoStream pCodec" << " \n");
      // Find the encoder for the video stream
      AVCodec *pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
      if (pCodec == NULL) 
        continue;
      ONDEBUG(cerr << "FFmpegDPOPacketStreamBodyC::FirstVideoStream vieostreamid" << " \n");      
      videoStreamId = i;
      codecId = pCodecCtx->codec_id;  //CODEC_ID_H264;  //pCodecCtx->codec_id;
      ONDEBUG(cerr << "FFmpegDPOPacketStreamBodyC::FirstVideoStream codecid" << " \n");      
      StringC inputFormatName = "";  //pFormatCtx->iformat->name;
      ONDEBUG(cerr << "FFmpegDPOPacketStreamBodyC::FirstVideoStream inputformatname" << " \n");
      StringC codecName;
      if(pCodec->name != 0)
        codecName = pCodec->name;
      
      ONDEBUG(cerr << "iformat=" << inputFormatName << " Codec=" << codecName << "\n");

#if 1
      // !!!!!!!!! Format Specific Hacks !!!!!!!!!!!!!!!
      if(inputFormatName == "asf" || inputFormatName == "mpeg" || codecName == "mpeg4") {
        ONDEBUG(std::cerr << "Non-seekable stream. \n";)
        haveSeek = false;
      }
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#endif
      
      positionRefStream = videoStreamId;
      AVStream *avstream = pFormatCtx->streams[positionRefStream];
      
      frameRate     = avstream->time_base.num*avstream->r_frame_rate.num;
      frameRateBase = avstream->time_base.den*avstream->r_frame_rate.den;
      startFrame = Time2Frame(pFormatCtx->start_time);      
      
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::FirstVideoStream Index=" << av_find_default_stream_index(pFormatCtx) << " " << positionRefStream << " \n");
      
      
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::FirstVideoStream, FrameRate=" << frameRate << " FrameRateBase=" << frameRateBase << " Wrap=" << avstream->pts_wrap_bits << "\n");

     
      return true;
    }
*/
    positionRefStream = videoStreamId;
    codecId = codecid;    
    return true;
    //return false;
  }
  
  
  //: Check for a readable video stream.
  
  bool FFmpegEncodePacketStreamBodyC::CheckForOutPut() {
    // Check the file is open!
    if(pFormatCtx == 0) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::CheckForOutPut no stream." << endl);
      return false;
    }
    
    // Find the first video stream.
    for (UIntT i = 0; i < pFormatCtx->nb_streams; i++) {
      if (pFormatCtx->streams[i]->codec->codec_type != CODEC_TYPE_VIDEO) 
        continue;
      
      // Get a pointer to the codec context for the video stream.
      AVCodecContext *pCodecCtx = pFormatCtx->streams[i]->codec;

    pCodecCtx->codec_type = CODEC_TYPE_VIDEO;
     pCodecCtx->pix_fmt = PIX_FMT_YUV420P; 

      // Find the encoder for the video stream
      AVCodec *pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
      if (pCodec == NULL) {
        continue;
      }

      // Inform the codec that we can handle truncated bitstreams.
      // i.e. bitstreams where frame boundaries can fall in the middle of packets.
      if (pCodec->capabilities & CODEC_CAP_TRUNCATED)
        pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;

      // Open codec.
      bool ret = false;
      if (avcodec_open(pCodecCtx, pCodec) >= 0) {
        ONDEBUG(cerr << "FFmpegPacketStreamBodyC::CheckForOutPut codec constructed ok. " << endl);
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
  

//////////////////////////////////////////////
/*float t, tincr, tincr2;
int16_t *samples;
uint8_t *audio_outbuf;
int audio_outbuf_size;
int audio_input_frame_size;
AVFrame *picture, *tmp_picture;
uint8_t *video_outbuf;
int frame_count, video_outbuf_size;
*/

 void FFmpegEncodePacketStreamBodyC::close_video(AVFormatContext *oc, AVStream *st)
{
    avcodec_close(st->codec);
    av_free(picture->data[0]);
    av_free(picture);
    if (tmp_picture) {
        av_free(tmp_picture->data[0]);
        av_free(tmp_picture);
    }
    av_free(video_outbuf);
}

 void FFmpegEncodePacketStreamBodyC::close_audio(AVFormatContext *oc, AVStream *st)
{
    avcodec_close(st->codec);

    av_free(samples);
    av_free(audio_outbuf);
}





 AVFrame *FFmpegEncodePacketStreamBodyC::alloc_picture(int pix_fmt, int width, int height)
{
    AVFrame *picture;
    uint8_t *picture_buf;
    int size;

    picture = avcodec_alloc_frame();
    if (!picture)
        return NULL;
    size = avpicture_get_size(pix_fmt, width, height);
    picture_buf = (uint8_t *)av_malloc(size);
    if (!picture_buf) {
        av_free(picture);
        return NULL;
    }
    avpicture_fill((AVPicture *)picture, picture_buf,
                   pix_fmt, width, height);
    return picture;
}


/* add a video output stream */
 AVStream *FFmpegEncodePacketStreamBodyC::add_video_stream(AVFormatContext *oc, IntT codec_id, IntT width,IntT height, Int64T qmax_val = 1)
{


    AVCodecContext *c;
    AVStream *st;
    st = av_new_stream(oc, 0);
    if (!st) {
        fprintf(stderr, "Could not alloc stream\n");
        exit(1);
    }
    c = st->codec;
    c->codec_id = (CodecID)codec_id;
    c->codec_type = CODEC_TYPE_VIDEO;

    /* resolution must be a multiple of two */
    c->width = width;  //img_w;
    c->height = height;   //img_h;
    c->pix_fmt = PIX_FMT_YUV420P;
    if(c->codec_id != CODEC_ID_H264) {
       c->bit_rate = 2000000;
    }
    //c->max_qdiff = 1;

    /* time base: this is the fundamental unit of time (in seconds) in terms
       of which frame timestamps are represented. for fixed-fps content,
       timebase should be 1/framerate and timestamp increments should be
       identically 1. */
    c->time_base.den = 25;  //STREAM_FRAME_RATE;
    c->time_base.num = 1;
    //st->time_base.den = 25;
    //st->time_base.num = 1;
    //c->qmax = 25;
    c->qmax = qmax_val;



    // below are for the x264 codec parameters
    if(c->codec_id == CODEC_ID_H264) {
       c->flags |= CODEC_FLAG_LOOP_FILTER;
       //c->bit_rate = 400000;
       c->me_method = ME_HEX;
       c->me_range = 16;
       c->me_cmp = FF_CMP_CHROMA;
       c->scenechange_threshold = 40;
       c->keyint_min = 25;
       c->me_subpel_quality = 5;
       c->gop_size = 250;
       c->i_quant_factor = 0.71;
    
       c->coder_type = 1;
    
       c->partitions = X264_PART_I4X4 + X264_PART_P8X8 + X264_PART_B8X8;
    }


    #if 1  
    #endif
    if (c->codec_id == CODEC_ID_MPEG2VIDEO) {
        /* just for testing, we also add B frames */
        c->max_b_frames = 2;
    }
    if (c->codec_id == CODEC_ID_MPEG1VIDEO){
        /* Needed to avoid using macroblocks in which some coeffs overflow.
           This does not happen with normal video, it just happens here as
           the motion of the chroma plane does not match the luma plane. */
        c->mb_decision=2;
    }
    
    // some formats want stream headers to be separate
    if( !compare(StringC(oc->oformat->name), StringC("mp4")) || 
        !compare(StringC(oc->oformat->name), StringC("mov")) || 
        !compare(StringC(oc->oformat->name), StringC("3gp")) )
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;

    return st;


}



 /* add an audio output stream
 */
 AVStream *FFmpegEncodePacketStreamBodyC::add_audio_stream(AVFormatContext *oc, int codec_id)
{
    AVCodecContext *c;
    AVStream *st;

    st = av_new_stream(oc, 1);
    if (!st) {
        fprintf(stderr, "Could not alloc stream\n");
        exit(1);
    }

    c = st->codec;
    c->codec_id = (CodecID)codec_id;
    c->codec_type = CODEC_TYPE_AUDIO;

    /* put sample parameters */
    c->bit_rate = 64000;
    c->sample_rate = 44100;
    c->channels = 2;
    return st;
}


 void FFmpegEncodePacketStreamBodyC::open_audio(AVFormatContext *oc, AVStream *st)
{
    AVCodecContext *c;
    AVCodec *codec;

    c = st->codec;

    /* find the audio encoder */
    codec = avcodec_find_encoder(c->codec_id);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }

    /* open it */
    if (avcodec_open(c, codec) < 0) {
        fprintf(stderr, "could not open codec\n");
        exit(1);
    }

    /* init signal generator */
    t = 0;
    tincr = 2 * M_PI * 110.0 / c->sample_rate;
    /* increment frequency by 110 Hz per second */
    tincr2 = 2 * M_PI * 110.0 / c->sample_rate / c->sample_rate;

    audio_outbuf_size = 10000;
    audio_outbuf = (uint8_t *)av_malloc(audio_outbuf_size);

    /* ugly hack for PCM codecs (will be removed ASAP with new PCM
       support to compute the input frame size in samples */
    if (c->frame_size <= 1) {
        audio_input_frame_size = audio_outbuf_size / c->channels;
        switch(st->codec->codec_id) {
        case CODEC_ID_PCM_S16LE:
        case CODEC_ID_PCM_S16BE:
        case CODEC_ID_PCM_U16LE:
        case CODEC_ID_PCM_U16BE:
            audio_input_frame_size >>= 1;
            break;
        default:
            break;
        }
    } else {
        audio_input_frame_size = c->frame_size;
    }
    samples = (int16_t *)av_malloc(audio_input_frame_size * 2 * c->channels);
}

 void FFmpegEncodePacketStreamBodyC::open_video(AVFormatContext *oc, AVStream *st)
{
    AVCodec *codec;
    AVCodecContext *c;

    c = st->codec;
    /* find the video encoder */
    codec = avcodec_find_encoder(c->codec_id);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }

    /* open the codec */
    if (avcodec_open(c, codec) < 0) {
        fprintf(stderr, "could not open codec, if you are using .h264 please make sure you have an ffmpeg installed that is built with libx264 enabled.\n");
        exit(1);
    }

    video_outbuf = NULL;
    if (!(oc->oformat->flags & AVFMT_RAWPICTURE)) {
        /* allocate output buffer */
        /* XXX: API change will be done */
        /* buffers passed into lav* can be allocated any way you prefer,
           as long as they're aligned enough for the architecture, and
           they're freed appropriately (such as using av_free for buffers
           allocated with av_malloc) */
        video_outbuf_size = 200000;
        video_outbuf = (uint8_t *)av_malloc(video_outbuf_size);
    }

    /* allocate the encoded raw picture */
    picture = alloc_picture(c->pix_fmt, c->width, c->height);
    if (!picture) {
        fprintf(stderr, "Could not allocate picture\n");
        exit(1);
    }

    /* if the output format is not YUV420P, then a temporary YUV420P
       picture is needed too. It is then converted to the required
       output format */
    tmp_picture = NULL;
    if (c->pix_fmt != PIX_FMT_YUV420P) {
        tmp_picture = alloc_picture(PIX_FMT_YUV420P, c->width, c->height);
        if (!tmp_picture) {
            fprintf(stderr, "Could not allocate temporary picture\n");
            exit(1);
        }
    }
}



  //: Open file.
  
  bool FFmpegEncodePacketStreamBodyC::Open(const StringC &filename) {
    ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << filename << "), Called \n");

    //Find output format.
    fmt = guess_format(NULL, filename, NULL);
    if (!fmt) {
        ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << filename << "), Failed to find format. \n");
        return false;
    }
    
   //Allocate the output media context.
   pFormatCtx = av_alloc_format_context();
   if(!pFormatCtx) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << filename << "), Failed allocate output media context. \n");
      return false;
    }
    
    pFormatCtx->oformat = fmt;

    codecid = pFormatCtx->oformat->video_codec;

    //Set output parameters, must be done even if no parameters.
    if(av_set_parameters(pFormatCtx,NULL) < 0) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << out_filename << "), Failed to set parameters. \n");
      return false;
    }

/*
    if(fmt->video_codec != CODEC_ID_NONE) {
       video_st = add_video_stream(pFormatCtx,pFormatCtx->oformat->video_codec,width,height,compression);
    }

    //Set output parameters, must be done even if no parameters.
    if(av_set_parameters(pFormatCtx,NULL) < 0) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << filename << "), Failed to set parameters. \n");
      return false;
    }       

    //Print format to stdout. remove later
    dump_format(pFormatCtx,0,filename,1);

    //Open audio and video codecs and encode buffers.
    if(video_st) {
       open_video(pFormatCtx,video_st);
    }
    //Could comment out as i dont have any audio data to write any way.
    if(audio_st) {
       open_audio(pFormatCtx,audio_st);
    }

    //Open output file.
    if(!(fmt->flags & AVFMT_NOFILE)) {
       if(url_fopen(&pFormatCtx->pb,filename,URL_WRONLY) < 0) {
          ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << filename << "), Failed to open output file. \n");
          return false;
       }
    }
    //Write header.
    if(av_write_header(pFormatCtx) < 0 ) {
          ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << filename << "), Failed to write header. \n");
          return false;
    }
  */
    if(false) {   //done_header == 0 && header_not_done_yet == true ) {  //header_done == 0) {
    /* close each codec */
    if (video_st)
        close_video(pFormatCtx, video_st);
    if (audio_st)
        close_audio(pFormatCtx, audio_st);

    /* free the streams */
    IntT i;
    for(i = 0; i < pFormatCtx->nb_streams; i++) {
        av_freep(&pFormatCtx->streams[i]->codec);
        av_freep(&pFormatCtx->streams[i]);
    }

#if (defined(LIBAVFORMAT_VERSION_INT) && LIBAVFORMAT_VERSION_INT >= (52 << 16)) || \
    (defined(LIBAVFORMAT_VERSION_MAJOR) && LIBAVFORMAT_VERSION_MAJOR >= 52)
    if (!(fmt->flags & AVFMT_NOFILE)) {
        /* close the output file */
        url_fclose(pFormatCtx->pb);
    }
#else
    if (!(fmt->flags & AVFMT_NOFILE)) {
        /* close the output file */
        url_fclose(&pFormatCtx->pb);
    }
#endif

    /* free the stream */
    av_free(pFormatCtx);
    pFormatCtx = 0;
    }
    out_filename = filename;

    return true;
  }


  bool FFmpegEncodePacketStreamBodyC::finishOpen(IntT &widthin, IntT &heightin) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::finishOpen(" << out_filename << "). \n");

/////////////////////////////////////////////////////////////////////////////
    /* free the stream */
    av_free(pFormatCtx);
    pFormatCtx = 0;

    fmt = guess_format(NULL, out_filename, NULL);
    if (!fmt) {
        ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << out_filename << "), Failed to find format. \n");
        return false;
    }
    
   //Allocate the output media context.
   pFormatCtx = av_alloc_format_context();
   if(!pFormatCtx) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << out_filename << "), Failed allocate output media context. \n");
      return false;
    }
    
    pFormatCtx->oformat = fmt;

    codecid = pFormatCtx->oformat->video_codec;

    //Set output parameters, must be done even if no parameters.
    if(av_set_parameters(pFormatCtx,NULL) < 0) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << out_filename << "), Failed to set parameters. \n");
      return false;
    }

///////////////////////////////////////////////////////////////////////

      if(fmt->video_codec != CODEC_ID_NONE) {
       video_st = add_video_stream(pFormatCtx,pFormatCtx->oformat->video_codec,widthin,heightin,compression);
       videoStreamId = pFormatCtx->nb_streams -1;
    }

    //Set output parameters, must be done even if no parameters.
/*    if(av_set_parameters(pFormatCtx,NULL) < 0) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << out_filename << "), Failed to set parameters. \n");
      return false;
    }       
*/
    //Print format to stdout. remove later
    //dump_format(pFormatCtx,0,filename,1);

    //Open audio and video codecs and encode buffers.
    if(video_st) {
       open_video(pFormatCtx,video_st);
       video_codec_context = video_st->codec;
    }
    //Could comment out as i dont have any audio data to write any way.
    if(audio_st) {
       open_audio(pFormatCtx,audio_st);
       audio_codec_context = audio_st->codec;
    }

    //Open output file.
    if(!(fmt->flags & AVFMT_NOFILE)) {
       if(url_fopen(&pFormatCtx->pb,out_filename,URL_WRONLY) < 0) {
          ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << out_filename << "), Failed to open output file. \n");
          return false;
       }
    }
    //Write header.
    if(av_write_header(pFormatCtx) < 0 ) {
          ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << out_filename << "), Failed to write header. \n");
          return false;
    }
    return true;
  }
  
  bool FFmpegEncodePacketStreamBodyC::Put() {
    ONDEBUG(std::cerr << "FFmpegPacketStreamBodyC::Put(). \n");

  }

  //: Put a packet from the stream.
  
  bool FFmpegEncodePacketStreamBodyC::Put(const FFmpegPacketC &packet) {
    ONDEBUG(std::cerr << "FFmpegPacketStreamBodyC::Put(FFmpegPacketC &packet). \n");
   /* if(done_header == 0) {
       done_header = 1;
       write_nbr = 0;
       header_not_done_yet = false;
       width = const_cast<FFmpegPacketC&>(packet).getWidth();
       height = const_cast<FFmpegPacketC&>(packet).getHeight();
       finishOpen();
       //Open(out_filename);
       //header_not_done_yet = false;
    }*/
    FFmpegPacketC &pack = const_cast<FFmpegPacketC&>(packet);
    write_nbr++;
    int res = av_write_frame(pFormatCtx,&pack.Packet());
    if(res < 0) {
       ONDEBUG(std::cerr << "FFmpegPacketStreamBodyC::Put, av_interleaved_write_frame failed. \n");
       return false;
    }
       ONDEBUG(std::cerr << "FFmpegPacketStreamBodyC::Put, av_interleaved_write_frame success value is . " << res << " packet size is " << pack.Size() << " filename is " << pFormatCtx->nb_streams << " \n");
    ONDEBUG(std::cerr << "FFmpegPacketStreamBodyC::Put(FFmpegPacketC &packet). \n");
    return true;
  }
  
  //: Is get ready ?
  
  bool FFmpegEncodePacketStreamBodyC::IsPutReady() const
  { return pFormatCtx != 0; }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegEncodePacketStreamBodyC::GetAttr(const StringC &attrName,StringC &attrValue) {
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
    if(attrName=="fullseek") {
      attrValue = StringC(haveSeek);
      return true;
    }
    
    return DPOSPortBodyC<FFmpegPacketC>::GetAttr(attrName,attrValue);
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegEncodePacketStreamBodyC::GetAttr(const StringC &attrName,IntT &attrValue) {
    return DPOSPortBodyC<FFmpegPacketC>::GetAttr(attrName,attrValue);
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegEncodePacketStreamBodyC::GetAttr(const StringC &attrName,RealT &attrValue) {
    if(attrName == "framerate") {
      const AVStream *st = pFormatCtx->streams[positionRefStream];
      if(st->time_base.num != 0)
        attrValue = (RealT) st->r_frame_rate.num/st->r_frame_rate.den;
      else
        attrValue = (RealT) st->time_base.den;
      return true;
    }
    if(attrName == "compression") {
       
    }
    return DPOSPortBodyC<FFmpegPacketC>::GetAttr(attrName,attrValue);
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegEncodePacketStreamBodyC::GetAttr(const StringC &attrName,bool &attrValue) {
    if(attrName == "fullseek") {
      attrValue = haveSeek;
      return true;
    }
    return DPOSPortBodyC<FFmpegPacketC>::GetAttr(attrName,attrValue);
  }


  bool FFmpegEncodePacketStreamBodyC::SetAttr(const StringC &attrName,RealT &attrValue) {
     if(attrName == "compression") {
        compression = attrValue;
        return true;
     }
     return DPOSPortBodyC<FFmpegPacketC>::SetAttr(attrName,attrValue);
  }
  
  //: Seek to location in stream.
  // Returns FALSE, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  //: Convert a frame no into a time
  Int64T FFmpegEncodePacketStreamBodyC::Frame2Time(Int64T arg) const {
    RealT frac = (RealT) frameRate / (RealT) frameRateBase;
    return llround((RealT) arg / frac);
  }
  
  //: Convert a  time into a frame no
  
  Int64T FFmpegEncodePacketStreamBodyC::Time2Frame(Int64T arg) const {
    RealT frac = (RealT) frameRate / (RealT) frameRateBase;
    return llround((RealT) arg * frac);
  }
}

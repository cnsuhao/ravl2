#include "Ravl/Audio/AudioIOFFmpeg.hh"
#include "Ravl/IO.hh"
#include "Ravl/BitStream.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/RGBcYUV.hh"
#include <fstream>
#include "Ravl/DP/AttributeValueTypes.hh"

#define DODEBUG 1

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif



namespace RavlAudioN
{


  
  static const IntT g_cacheSize = 20;
  

  
  AudioILibFFmpegBodyC::AudioILibFFmpegBodyC() :
    m_imageCache(g_cacheSize)
  {
    BuildAttributes();
  }
  

  
  AudioILibFFmpegBodyC::~AudioILibFFmpegBodyC()
  {
  }
  

  
  bool AudioILibFFmpegBodyC::Get(SampleElemC<2,Int16T> &img)
  {
    return false;
  }
  

  
  bool AudioILibFFmpegBodyC::Seek(UIntT off)
  {
    ONDEBUG(cerr << "AudioILibFFmpegBodyC::Seek (" << off << ")" << endl;)
    return false;
  }


  
  UIntT AudioILibFFmpegBodyC::Size() const
  {
    return ((UIntT)(-1));
  }
  

  
  bool AudioILibFFmpegBodyC::Seek64(StreamPosT off)
  {
    ONDEBUG(cerr << "AudioILibFFmpegBodyC::Seek (" << off << ")" << endl;)
    return false;
  }
  

  
  StreamPosT AudioILibFFmpegBodyC::Size64() const
  {
    return -1;
  }
  
  
  
  bool AudioILibFFmpegBodyC::IsGetEOS() const
  {
    ONDEBUG(cerr << "AudioILibFFmpegBodyC::IsGetEOS end found" << endl;)
    return true;
  }



  bool AudioILibFFmpegBodyC::GetAttr(const StringC &attrName,StringC &attrValue)
  {
    return DPPortBodyC::GetAttr(attrName,attrValue);
  }



  void AudioILibFFmpegBodyC::BuildAttributes() 
  {
//    RegisterAttribute(AttributeTypeStringC("frametype", "MPEG frame type", true, false));
  }
  
  
  
}


// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id: ImgDPOFFmpeg.cc 6685 2008-03-27 14:44:47Z craftit $"
//! lib=RavlLibFFmpeg
//! author = "Warren Moore"
//! file = "Ravl/LibFFmpeg/ImgDPOFFmpeg.cc"

#include "Ravl/Image/ImgDPOFFmpeg.hh"
#include "Ravl/IO.hh"
#include "Ravl/BitStream.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/RGBcYUV.hh"
#include <fstream>
#include "Ravl/DP/AttributeValueTypes.hh"

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif



namespace RavlImageN
{


  
  static const IntT g_cacheSize = 20;
  

  
  ImgOLibFFmpegBodyC::ImgOLibFFmpegBodyC() :
    m_imageCache(g_cacheSize)
  {
    BuildAttributes();
  }
  

  
  ImgOLibFFmpegBodyC::~ImgOLibFFmpegBodyC()
  {
  }
  

  
  bool ImgOLibFFmpegBodyC::Put(const ImageC<ByteRGBValueC> &img)
  {
    return false;
  }

  bool ImgOLibFFmpegBodyC::Put()
  {
    return false;
  }

  //: Seek to location in stream.
  
  bool ImgOLibFFmpegBodyC::DSeek64(StreamPosT off) {
    RavlAssert(0);
    return false;    
  }
    
  //: Seek to location in stream.
  
  bool ImgOLibFFmpegBodyC::DSeek(IntT off) {
    RavlAssert(0);
    return false;
  }
  
  
  bool ImgOLibFFmpegBodyC::Seek(UIntT off)
  {
    ONDEBUG(cerr << "ImgOLibFFmpegBodyC::Seek (" << off << ")" << endl;)
    return false;
  }


  
  UIntT ImgOLibFFmpegBodyC::Size() const
  {
    return ((UIntT)(-1));
  }
  

  
  bool ImgOLibFFmpegBodyC::Seek64(StreamPosT off)
  {
    ONDEBUG(cerr << "ImgOLibFFmpegBodyC::Seek (" << off << ")" << endl;)
    return false;
  }
  

  
  StreamPosT ImgOLibFFmpegBodyC::Size64() const
  {
    return -1;
  }
  
  
  
  bool ImgOLibFFmpegBodyC::PutEOS() const
  {
    ONDEBUG(cerr << "ImgOLibFFmpegBodyC::PutEOS end found" << endl;)
    return true;
  }

  bool ImgOLibFFmpegBodyC::IsPutReady() const
  {
    ONDEBUG(cerr << "ImgOLibFFmpegBodyC::IsPutReady() end found" << endl;)
    return true;
  }

  /*bool ImgOLibFFmpegBodyC::GetAttr(const StringC &attrName,StringC &attrValue)
  {
    return DPPortBodyC::GetAttr(attrName,attrValue);
  }*/



  void ImgOLibFFmpegBodyC::BuildAttributes() 
  {
//    RegisterAttribute(AttributeTypeStringC("frametype", "MPEG frame type", true, false));
  }
  
  
  
}


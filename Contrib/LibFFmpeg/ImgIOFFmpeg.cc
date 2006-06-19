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
//! file = "Ravl/LibFFmpeg/ImgIOFFmpeg.cc"

#include "Ravl/Image/ImgIOFFmpeg.hh"
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



namespace RavlImageN
{


  
  static const IntT g_cacheSize = 20;
  

  
  ImgILibFFmpegBodyC::ImgILibFFmpegBodyC() :
    m_imageCache(g_cacheSize)
  {
    BuildAttributes();
  }
  

  
  ImgILibFFmpegBodyC::~ImgILibFFmpegBodyC()
  {
  }
  

  
  bool ImgILibFFmpegBodyC::Get(ImageC<ByteRGBValueC> &img)
  {
    return false;
  }
  

  
  bool ImgILibFFmpegBodyC::Seek(UIntT off)
  {
    ONDEBUG(cerr << "ImgILibFFmpegBodyC::Seek (" << off << ")" << endl;)
    return false;
  }


  
  UIntT ImgILibFFmpegBodyC::Size() const
  {
    return ((UIntT)(-1));
  }
  

  
  bool ImgILibFFmpegBodyC::Seek64(StreamPosT off)
  {
    ONDEBUG(cerr << "ImgILibFFmpegBodyC::Seek (" << off << ")" << endl;)
    return false;
  }
  

  
  StreamPosT ImgILibFFmpegBodyC::Size64() const
  {
    return -1;
  }
  
  
  
  bool ImgILibFFmpegBodyC::IsGetEOS() const
  {
    ONDEBUG(cerr << "ImgILibFFmpegBodyC::IsGetEOS end found" << endl;)
    return true;
  }



  bool ImgILibFFmpegBodyC::GetAttr(const StringC &attrName,StringC &attrValue)
  {
    return DPPortBodyC::GetAttr(attrName,attrValue);
  }



  void ImgILibFFmpegBodyC::BuildAttributes() 
  {
//    RegisterAttribute(AttributeTypeStringC("frametype", "MPEG frame type", true, false));
  }
  
  
  
}


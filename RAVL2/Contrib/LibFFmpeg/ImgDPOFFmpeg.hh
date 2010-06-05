/// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_IMGDPOFFMPEG_HEADER
#define RAVL_IMGDPOFFMPEG_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id: ImgDPOFFmpeg.hh 6685 2008-03-27 14:44:47Z craftit $"
//! lib=RavlLibFFmpeg
//! author = "Warren Moore"
//! file = "Ravl/Contrib/LibFFmpeg/ImgDPOFFmpeg.hh"

#include "Ravl/DP/StreamOp.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Hash.hh"
#include "Ravl/AVLTree.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/DList.hh"
#include "Ravl/Cache.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/DP/SPort.hh"


namespace RavlImageN
{
  class ImgOLibFFmpegBodyC 
    : public DPOPortBodyC<ImageC<ByteRGBValueC> >,
      public DPSeekCtrlBodyC
      //public AttributeCtrlBodyC
  {
  public:
    ImgOLibFFmpegBodyC();
    //: Constructor.
    
    virtual ~ImgOLibFFmpegBodyC();
    //: Destructor.
    
   virtual bool Put(const ImageC<ByteRGBValueC> &img);
    //: Get next frame.

   virtual bool Put();

   virtual bool IsPutReady() const;
    //: Is it the EOS

  private:
    CacheC<StreamPosT,Tuple2C<ImageC<ByteRGBValueC>,IntT> > m_imageCache;   // Frame cache
  };

  
  class ImgOLibFFmpegC :
    public DPOPortC<ImageC<ByteRGBValueC> >,
    public DPSeekCtrlC
    //public AttributeCtrlC
  {
  public:
    ImgOLibFFmpegC() :
      DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    bool Put(const ImageC<ByteRGBValueC> & img) 
    {   
        return Body().Put(img);
     }
    //: Get next frame. 
    //!cwiz:author

    bool Put() 
    {  
        return true;   //Body().Put(img);
    }

    bool IsPutReady() const
    { return Body().IsPutReady(); }
    //: Is it the EOS 
    

    ImgOLibFFmpegC(bool) :
      DPEntityC(*new ImgOLibFFmpegBodyC())
    {}
    //: Constructor.
  
  private:
    ImgOLibFFmpegBodyC &Body()
    { //return static_cast<ImgOLibFFmpegBodyC &>(DPOStreamOpC< ByteT, ImageC<ByteRGBValueC> >::Body());}
      return static_cast<ImgOLibFFmpegBodyC &>(DPOPortC<ImageC<ByteRGBValueC> >::Body());}
    //: Access body.

    const ImgOLibFFmpegBodyC &Body() const
    { //return static_cast<const ImgOLibFFmpegBodyC &>(DPOStreamOpC< ByteT, ImageC<ByteRGBValueC> >::Body()); }
      return static_cast<const ImgOLibFFmpegBodyC &>(DPOPortC<ImageC<ByteRGBValueC> >::Body()); }
    //: Access body.
  };
  
  
  
}

#endif

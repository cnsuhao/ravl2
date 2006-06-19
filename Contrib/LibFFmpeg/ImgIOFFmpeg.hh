// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
#ifndef RAVL_IMGIOFFMPEG_HEADER
#define RAVL_IMGIOFFMPEG_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id$"
//! lib=RavlLibFFmpeg
//! author = "Warren Moore"
//! file = "Ravl/Contrib/LibFFmpeg/ImgIOFFmpeg.hh"

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
  
  class ImgILibFFmpegBodyC 
    : public DPIStreamOpBodyC< ByteT, ImageC<ByteRGBValueC> >,
      public DPSeekCtrlBodyC
  {
  public:
    ImgILibFFmpegBodyC();
    //: Constructor.
    
    virtual ~ImgILibFFmpegBodyC();
    //: Destructor.
    
    virtual ImageC<ByteRGBValueC> Get()
    {
      ImageC<ByteRGBValueC> img;
      if (!Get(img))
        throw DataNotReadyC("Failed to get next frame.");
      return img;
    }
    //: Get next frame.
    
    virtual bool Get(ImageC<ByteRGBValueC> &img);
    //: Get next frame.
    
    virtual UIntT Tell() const
    { return ((UIntT)-1); }
    //: Find current location in stream.
    
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    
    virtual UIntT Size() const;
    //: Get the size of the file in frames (-1 if not known)
    
    virtual StreamPosT Tell64() const
    { return -1; }
    //: Find current location in stream.
    
    virtual bool Seek64(StreamPosT off);
    //: Seek to location in stream.
    
    virtual StreamPosT Size64() const;
    //: Get the size of the file in frames (-1 if not known)
    
    virtual bool IsGetEOS() const;
    //: Is it the EOS

    virtual bool GetAttr(const StringC &attrName,StringC &attrValue);
    //: Get a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
  private:
    virtual void BuildAttributes();
    //: Register stream attributes

  private:
    CacheC<StreamPosT,Tuple2C<ImageC<ByteRGBValueC>,IntT> > m_imageCache;   // Frame cache
  };

  
  
  class ImgILibFFmpegC :
    public DPIStreamOpC< ByteT, ImageC<ByteRGBValueC> >,
    public DPSeekCtrlC
  {
  public:
    ImgILibFFmpegC() :
      DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ImageC<ByteRGBValueC> Get() 
    { return Body().Get(); }
    //: Get next frame. 
    //!cwiz:author
    
    bool Get(ImageC<ByteRGBValueC> & img) 
    { return Body().Get(img); }
    //: Get next frame. 
    //!cwiz:author
    
    UIntT Tell() const
    { return Body().Tell(); }
    //: Find current location in stream. 
    //!cwiz:author
    
    bool Seek(UIntT off) 
    { return Body().Seek(off); }
    //: Seek to location in stream. 
    //!cwiz:author
    
    UIntT Size() const
    { return Body().Size(); }
    //: Get the size of the file in frames (-1 if not known) 
    //!cwiz:author
    
    StreamPosT Tell64() const
    { return Body().Tell64(); }
    //: Find current location in stream. 
    //!cwiz:author
    
    bool Seek64(StreamPosT off) 
    { return Body().Seek64(off); }
    //: Seek to location in stream. 
    //!cwiz:author
    
    StreamPosT Size64() const
    { return Body().Size64(); }
    //: Get the size of the file in frames (-1 if not known) 
    //!cwiz:author
    
    bool IsGetEOS() const
    { return Body().IsGetEOS(); }
    //: Is it the EOS 
    //!cwiz:author
    
    bool GetAttr(const StringC & attrName,StringC & attrValue) 
    { return Body().GetAttr(attrName,attrValue); }
    //: Get a stream attribute. 
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    //!cwiz:author

    ImgILibFFmpegC(bool) :
      DPEntityC(*new ImgILibFFmpegBodyC())
    {}
    //: Constructor.

  private:
    ImgILibFFmpegBodyC &Body()
    { return static_cast<ImgILibFFmpegBodyC &>(DPIStreamOpC< ByteT, ImageC<ByteRGBValueC> >::Body()); }
    //: Access body.

    const ImgILibFFmpegBodyC &Body() const
    { return static_cast<const ImgILibFFmpegBodyC &>(DPIStreamOpC< ByteT, ImageC<ByteRGBValueC> >::Body()); }
    //: Access body.
  };
  
  
  
}

#endif

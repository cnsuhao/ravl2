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
/*  
  class ImgOLibFFmpegBodyC 
    : public DPOStreamOpBodyC< ByteT, ImageC<ByteRGBValueC> >,
      public DPSeekCtrlBodyC
  {
*/
  class ImgOLibFFmpegBodyC 
    : public DPOPortBodyC<ImageC<ByteRGBValueC> >,
      public DPSeekCtrlBodyC
  {
  public:
    ImgOLibFFmpegBodyC();
    //: Constructor.
    
    virtual ~ImgOLibFFmpegBodyC();
    //: Destructor.
    
   virtual bool Put(const ImageC<ByteRGBValueC> &img);
    //: Get next frame.

   virtual bool Put();
    
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
    
    virtual bool DSeek64(StreamPosT off);
    //: Seek to location in stream.
    
    virtual bool DSeek(IntT off);
    //: Seek to location in stream.
    
    virtual bool Seek64(StreamPosT off);
    //: Seek to location in stream.
    
    virtual StreamPosT Size64() const;
    //: Get the size of the file in frames (-1 if not known)
    
    virtual bool PutEOS() const;
    //: Is it the EOS

    virtual bool IsPutReady() const;
    //: Is it the EOS

    //virtual bool GetAttr(const StringC &attrName,StringC &attrValue);
    //: Get a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
  private:
    virtual void BuildAttributes();
    OStreamC strm;
    //: Register stream attributes

  private:
    CacheC<StreamPosT,Tuple2C<ImageC<ByteRGBValueC>,IntT> > m_imageCache;   // Frame cache
  };

  
/*  
  class ImgOLibFFmpegC :
    public DPOStreamOpC< ByteT, ImageC<ByteRGBValueC> >,
    public DPSeekCtrlC
  {
*/
  class ImgOLibFFmpegC :
    public DPOPortC<ImageC<ByteRGBValueC> >,
    public DPSeekCtrlC
  {
  public:
    ImgOLibFFmpegC() :
      DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    //ImageC<ByteRGBValueC> Get() 
    //{ return Body().Get(); }
    //: Get next frame. 
    //!cwiz:author
    
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
    
    bool PutEOS() const
    { return Body().PutEOS(); }
    //: Is it the EOS 
    //!cwiz:author

    bool IsPutReady() const
    { return Body().IsPutReady(); }
    //: Is it the EOS 
    
    //bool GetAttr(const StringC & attrName,StringC & attrValue) 
    //{ return Body().GetAttr(attrName,attrValue); }
    //: Get a stream attribute. 
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    //!cwiz:author

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

#ifndef RAVL_AUDIOIOFFMPEG_HEADER
#define RAVL_AUDIOIOFFMPEG_HEADER 1

#include "Ravl/DP/StreamOp.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Hash.hh"
#include "Ravl/AVLTree.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/DList.hh"
#include "Ravl/Cache.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/DP/SPort.hh"
#include "Ravl/Audio/Types.hh"

namespace RavlAudioN
{
  
  class AudioILibFFmpegBodyC 
  : public DPIStreamOpBodyC< SampleElemC<2,Int16T> , SampleElemC<2,Int16T> >,
      public DPSeekCtrlBodyC
  {
  public:
    AudioILibFFmpegBodyC();
    //: Constructor.
    
    virtual ~AudioILibFFmpegBodyC();
    //: Destructor.
    
    virtual SampleElemC<2,Int16T> Get()
    {
     SampleElemC<2,Int16T> img;
      if (!Get(img))
        throw DataNotReadyC("Failed to get next frame.");
      return img;
    }
    //: Get next frame.
    
    virtual bool Get(SampleElemC<2,Int16T> &img);
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
    CacheC<StreamPosT,Tuple2C<SampleElemC<2,Int16T>,IntT> > m_imageCache;   // Frame cache
  };

  
  
  class AudioILibFFmpegC :
      public DPIStreamOpC< Int16T, SampleElemC<2,Int16T> >,
    public DPSeekCtrlC
  {
  public:
    AudioILibFFmpegC() :
      DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SampleElemC<2,Int16T> Get() 
    { return Body().Get(); }
    //: Get next frame. 
    //!cwiz:author
    
    bool Get(SampleElemC<2,Int16T> & img) 
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

    AudioILibFFmpegC(bool) :
      DPEntityC(*new AudioILibFFmpegBodyC())
    {}
    //: Constructor.

  private:
    AudioILibFFmpegBodyC &Body()
    { return dynamic_cast<AudioILibFFmpegBodyC &>(DPIStreamOpC< Int16T, SampleElemC<2,Int16T> >::Body()); }
    //: Access body.

    const AudioILibFFmpegBodyC &Body() const
    { return dynamic_cast<const AudioILibFFmpegBodyC &>(DPIStreamOpC< Int16T, SampleElemC<2,Int16T> >::Body()); }
    //: Access body.
  };
  
  
  
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMGIOYUV_HEADER
#define RAVLIMAGE_IMGIOYUV_HEADER 1
////////////////////////////////////////////////////
//! file="Ravl/Image/VideoIO/ImgIOyuv.hh"
//! lib=RavlVideoIO
//! docentry="Ravl.API.Images.Video.Video IO"
//! example=exImgSeq.cc
//! rcsid="$Id$"
//! author="Charles Galambos"
//! date="08/04/99"

#include "Ravl/DP/SPort.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Assert.hh"

namespace RavlImageN {
  
  ///////////////////////////////////
  //! userlevel=Develop
  //: Basic information about a cif file
  
  class DPImageYUVBaseBodyC {
  public:  
    DPImageYUVBaseBodyC(const Index2dC &size = Index2dC(576,720))
      : frameSize(0),
      frameNo(0),
      seqSize((UIntT) -1)
      { SetupForVariant(size); }
    //: Constructor.
    // This constructs with the basic yuv format.
    
    bool SetupForVariant(const StringC &suffix);
    //: Setup for cif variant.
    // str should be one of :
    // sqcif,qcif,cif,4cif,16cif
    
    bool SetupForVariant(const Index2dC &size);
    //: Setup for cif variant.
    // Where size in the size of the Y image.
    
    inline UIntT CalcOffset(UIntT frameNo) const {
      RavlAssert(frameSize > 0);
      return frameSize * frameNo; 
    }
    //: Calculate the offset of a frame.

    inline IntT CalcOffset(IntT frameNo) const  {
      RavlAssert(frameSize > 0);
      return frameSize * frameNo; 
    }
    //: Calculate the offset of a frame.
  
    void SetSequenceSize(UIntT val) { seqSize = val; }
    //: Set the sequence size.
    
    UIntT SeqSize() const { return seqSize; }
    //: Get the sequence size.
    
    
  protected:
    static inline bool is_odd (IndexC x) {return bool (x%2 != 0);}
    // Is an index odd ?
    
    ImageRectangleC rect; // Size of YUV variant. Origin 0,0
    UIntT frameSize; // Size of one frame in bytes.
    UIntT frameNo; // Current frameno.
    UIntT seqSize;  // Number of frames in sequence, ((UIntT) -1) if unknown
  };
  
  ///////////////////////////////////
  //! userlevel=Develop
  //: Load a YUV image in YUV format.
  
  class DPIImageYUVBodyC 
    : public DPISPortBodyC<ImageC<ByteYUVValueC> >,
      public DPImageYUVBaseBodyC
  {
  public:  
    DPIImageYUVBodyC(const IStreamC &nStrm,const Index2dC &size = Index2dC(576,720));
    //: Constructor from stream 
    
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off);
    //: Delta Seek, goto location relative to the current one.
  
    virtual UIntT Tell() const; 
    //: Find current location in stream.
    
    virtual UIntT Size() const; 
  //: Find the total size of the stream.
    
    virtual ImageC<ByteYUVValueC> Get();
    //: Get next image.
    
    virtual bool Get(ImageC<ByteYUVValueC> &buff);
    //: Get next image.
    
    virtual bool IsGetReady() const 
      { return strm.good(); }
    //: Is some data ready ?
    // TRUE = yes.
    // Defaults to !IsGetEOS().
    
    virtual bool IsGetEOS() const
      { return strm.good(); }
    //: Has the End Of Stream been reached ?
  // TRUE = yes.
    
  protected:
    IStreamC strm;
  };
  
  ///////////////////////////////////
  //! userlevel=Develop
  //: Save a YUV image in YUV format.
  
  class DPOImageYUVBodyC 
    : public DPOSPortBodyC<ImageC<ByteYUVValueC> >,
      public DPImageYUVBaseBodyC
  {
  public:
    DPOImageYUVBodyC(const OStreamC &nStrm,const Index2dC &size  = Index2dC(576,720));
    //: Constructor from stream 
    
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off);
    //: Delta Seek, goto location relative to the current one.
    
    virtual UIntT Tell() const; 
    //: Find current location in stream.
    
    virtual UIntT Size() const; 
    //: Find the total size of the stream.
  
    bool Put(const ImageC<ByteYUVValueC> &Img);
    //: Put image to a stream.
    
    virtual bool IsPutReady() const 
      { return strm.good(); }
    //: Read to write some data ?
    // TRUE = yes.
    
    virtual void PutEOS() {}
    //: Put End Of Stream marker.
    
  protected:  
    OStreamC strm;
  };

  //! userlevel=Normal
  //: Load a YUV image in YUV format.
  
  class DPIImageYUVC 
    : public DPISPortC<ImageC<ByteYUVValueC> >
  {
  public:
    DPIImageYUVC(const StringC &fn);
    //: Constructor from filename.  
    
    DPIImageYUVC(const IStreamC &nStrm,const Index2dC &size = Index2dC(576,720))
      : DPEntityC(*new DPIImageYUVBodyC(nStrm,size))
      {}
    //: Constructor from stream 
    
  };
  
  //! userlevel=Normal
  //: Save a YUV image in YUV format.
  
  class DPOImageYUVC 
    : public DPOSPortC<ImageC<ByteYUVValueC> >
  {
  public:
    DPOImageYUVC(const StringC &fn);
    //: Constructor from filename.  
    
    DPOImageYUVC(const OStreamC &nStrm,const Index2dC &size = Index2dC(576,720))
      : DPEntityC(*new DPOImageYUVBodyC(nStrm,size))
      {}
    //: Constructor from stream 
    
  };

}

#endif

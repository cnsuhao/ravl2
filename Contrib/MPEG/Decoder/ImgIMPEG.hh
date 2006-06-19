// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMPEG_HEADER
#define RAVLIMAGE_IMPEG_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id: ImgIMPEG.hh 3317 2003-08-20 14:50:13Z ees1wc $"
//! userlevel=Normal
//! file="Ravl/Image/ExternalVideoIO/ImgIMpeg.hh"
//! lib=RavlMPEG
//! author="Ramesh Krishna"
//! docentry="Ravl.Images.Video.Video IO.MPEG2"
//! example=exImgIO.cc
//! date="29/10/2001"

#include "Ravl/DP/Port.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBAValue.hh"

extern "C" {
#include <mpeg.h>
}

namespace RavlImageN {

  //: MPEG Decoder Utilities
  
  class DPImageIMPEGBaseC {
  public:    
    DPImageIMPEGBaseC();
    //: Constructor.
    
    ~DPImageIMPEGBaseC();
    //: Destructor.
    
  protected:    
    
    FILE *MpegI;
    ImageDesc MpegImgI;
    unsigned char *MpegPixels;
    char *TmpPixels;
    int CurFrame;
    bool EOS;
  };
  
  //! userlevel=Develop
  //: MPEG Decoder.
  
  class DPIImageMPEGByteRGBBodyC 
    : public DPIPortBodyC<ImageC<ByteRGBAValueC> >,
      public DPImageIMPEGBaseC
  {

  public:
    ImageDesc MpegImgI;

    DPIImageMPEGByteRGBBodyC(StringC fn);
    //: Constructor from filename.
    
    DPIImageMPEGByteRGBBodyC(const IStreamC &in);
    //: Constructor from stream.
    
    virtual bool IsGetEOS() const
    { return EOS; }
    //: Is valid data ?
    
  protected:
    ImageC<ByteRGBAValueC> Get();
    int MPEGSeekProc(int off, int whence);
    ImageDesc *DPIImageMPEGOpen();
    
    unsigned char *MpegPixels;
    
    typedef struct rgb_tag {
      unsigned char b1, b2, b3, b4;
    };
    
    rgb_tag *rgb;
    
    IStreamC inf; // Infile.
  };
  

  //! userlevel=Normal
  //: Load a RGB image in MPEG format.
  
  class DPIImageMPEGByteRGBC 
    : public DPIPortC<ImageC<ByteRGBAValueC> > 
  {
    public:
    DPIImageMPEGByteRGBC(StringC fn);
    //: Constructor from filename.  
    
    DPIImageMPEGByteRGBC(const IStreamC &strm);
    //: Constructor from stream 
  };
  
}

#endif

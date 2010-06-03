// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPIMAGEIOPPM_HEADER
#define RAVLDPIMAGEIOPPM_HEADER
///////////////////////////////////////////////////
//! userlevel=Develop
//! rcsid="$Id: ImgIMPEGB.hh 3317 2003-08-20 14:50:13Z ees1wc $"
//! file="Ravl/Image/ExternalImageIO/ImgIOMpegB.hh"
//! lib=ExtImgIO
//! docentry="Ravl.Images.Video.Video IO.MPEG2"
//! author="Charles Galambos"
//! date="29/10/98"

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Image/ImgIOMpeg.hh"
#include "Ravl/Image/ByteRGBValue.hh"


namespace RavlImageN {

  //: MPEG Utilities
  
  class DPImageIOMPEGBaseC {


  public:    
    DPImageIOMPEGBaseC();
    //: Constructor.
    
    ~DPImageIOMPEGBaseC();
    //: Destructor.
    

  protected:    

    unsigned char *buffer;

    // Output   (ENCODER)
    int MpegEncInitd;
    int MpegEncOpend;

    int BufferSize;
    int PixelSize;  // bits
    Boolean EOS;
    int EncBufferSize;
    int EncPixelSize;  // bits
    unsigned char *EncBuffer;
    int EncVertSize;
    int EncHorizSize;

    // Input   (DECODER)
    FILE *MpegI;
    ImageDesc MpegImgI;
    unsigned char *MpegPixels;
    char *TmpPixels;
    int CurFrame;
    ImageC<ByteRGBValueC> img;

  };
  


  //: Load an RGB image.
  
  class DPIImageMPEGByteRGBBodyC :                    // DECODER
    public DPIPortBodyC<ImageC<ByteRGBValueC> >,
    public DPImageIOMPEGBaseC
  {
    FILE *MpegI;
    unsigned char *MpegPixels;

    typedef struct rgb_tag
    {
      unsigned char b1, b2, b3, b4;
    };

    rgb_tag *rgb;


  public:
    ImageDesc MpegImgI;

    DPIImageMPEGByteRGBBodyC(StringC fn);
    //: Constructor from filename.
    
    DPIImageMPEGByteRGBBodyC(const IStreamC &in);
    //: Constructor from stream.
    
    virtual bool IsGetEOS() const;
    //: Is valid data ?
    
  protected:
    ImageC<ByteRGBValueC> Get();
    int MPEGSeekProc(int off, int whence);
    int MPEGCloseProc();
    ImageDesc *DPIImageMPEGOpen();
//    static toff_t MPEGSizeProc(thandle_t);
    
    
    IStreamC inf; // Infile.
    bool done;
  };
  



  //: Save a ByteRGB image.
  
  class DPOImageMPEGByteRGBBodyC :                        // ENCODER
    public DPOPortBodyC<ImageC<ByteRGBValueC> >,
    public DPImageIOMPEGBaseC
  {

    typedef struct rgb_tag
    {
      unsigned char b1, b2, b3, b4;
    };

    rgb_tag *rgb;

  public:
    DPOImageMPEGByteRGBBodyC(StringC fn);
    //: Constructor from filename.
    
    DPOImageMPEGByteRGBBodyC(const OStreamC &strm);
    //: Constructor from filename.

    int MPEGEncCloseProc();
    
    virtual bool Put(const ImageC<ByteRGBValueC> &dat);
    //: Put data.
    
    virtual bool IsPutReady() const ;
    //: Is port ready for data ?

//    bool SetAttr(const StringC &attrName,const StringC &attrValue);
    
  protected:
    OStreamC outf; // Infile.
    bool done;
    StringC MpegFile;
  };

}
#endif

#ifndef DPIMAGEIOPPM_HEADER
#define DPIMAGEIOPPM_HEADER
///////////////////////////////////////////////////
//! userlevel=Develop
//! rcsid="$Id$"
//! file="amma/Image/ExtImgIO/ImgIOTiffB.hh"
//! lib=ExtImgIO
//! docentry="Image.Image IO"
//! author="Charles Galambos"
//! date="29/10/98"

#include "amma/Filename.hh"
#include "amma/RGBImage.hh"
#include "amma/ByteImag.hh"
#include "amma/DP/FileFormat.hh"
#include "amma/DP/Port.hh"
#include "amma/Stream.hh"

#include <tiffio.h>



//: TIFF Utilities

class DPImageIOTIFFBaseC {
public:    
  DPImageIOTIFFBaseC();
  //: Constructor.
  
  ~DPImageIOTIFFBaseC();
  //: Destructor.

 protected:
  //typedef	void* thandle_t;	/* client data handle */
  
  //static void TIFFErrorHandler(const char*, const char*, va_list);
  //  static void *TIFFExtendProc(TIFF*);
  
  
  TIFF *tif;
};

//: Load a RGBA image.

class DPIImageTIFFByteRGBABodyC : 
  public DPIPortBodyC<ImageC<ByteRGBXValueC> >,
  public DPImageIOTIFFBaseC
{
public:
  DPIImageTIFFByteRGBABodyC(FilenameC fn);
  //: Constructor from filename.
  
  DPIImageTIFFByteRGBABodyC(const IStreamC &in);
  //: Constructor from stream.
  
  virtual BooleanT IsGetEOS() const;
  //: Is valid data ?
  
  virtual ImageC<ByteRGBXValueC> Get();
  //: Get next piece of data.
  
protected:
  static tsize_t TIFFReadProc(thandle_t, tdata_t, tsize_t);
  static tsize_t TIFFWriteProc(thandle_t, tdata_t, tsize_t);
  static toff_t  TIFFSeekProc(thandle_t, toff_t, int);
  static int TIFFCloseProc(thandle_t);
  static toff_t TIFFSizeProc(thandle_t);
  static int TIFFMapFileProc(thandle_t, tdata_t*, toff_t*);
  static void TIFFUnmapFileProc(thandle_t, tdata_t, toff_t);


  IStreamC inf; // Infile.
  BooleanT done;
};

//: Save a ByteRGBA image.

class DPOImageTIFFByteRGBABodyC : 
  public DPOPortBodyC<ImageC<ByteRGBXValueC> >,
  public DPImageIOTIFFBaseC
{
public:
  DPOImageTIFFByteRGBABodyC(FilenameC fn);
  //: Constructor from filename.
  
  DPOImageTIFFByteRGBABodyC(const OStreamC &strm);
  //: Constructor from filename.
  
  virtual BooleanT Put(const ImageC<ByteRGBXValueC> &dat);
  //: Put data.
  
  virtual BooleanT IsPutReady() const ;
  //: Is port ready for data ?
  
protected:
  static tsize_t TIFFReadProc(thandle_t, tdata_t, tsize_t);
  static tsize_t TIFFWriteProc(thandle_t, tdata_t, tsize_t);
  static toff_t  TIFFSeekProc(thandle_t, toff_t, int);
  static int TIFFCloseProc(thandle_t);
  static toff_t TIFFSizeProc(thandle_t);
  static int TIFFMapFileProc(thandle_t, tdata_t*, toff_t*);
  static void TIFFUnmapFileProc(thandle_t, tdata_t, toff_t);
  
  OStreamC outf; // Infile.
  BooleanT done;
};

#endif

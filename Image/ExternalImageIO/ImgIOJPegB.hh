#ifndef DPIMAGEIOJPEG_HEADER
#define DPIMAGEIOJPEG_HEADER
///////////////////////////////////////////////////
//! userlevel=Develop
//! rcsid="$Id$"
//! file="amma/Image/ExtImgIO/ImgIOJPegB.hh"
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

#include <setjmp.h>

extern "C" {
#include <jpeglib.h>
};


//: JPeg Utilities

class DPImageIOJPegBaseC {
public:    
  DPImageIOJPegBaseC();
  //: Constructor.

  ~DPImageIOJPegBaseC();
  //: Destructor.

  struct my_error_mgr {
    struct jpeg_error_mgr pub;	/* "public" fields */
    jmp_buf setjmp_buffer;	/* for return to caller */
  };
  
  typedef struct my_error_mgr * my_error_ptr;

  const static unsigned int defaultBufferSize = 4096;
  
  unsigned int BufferSize() const
    { return defaultBufferSize; }
  //: Access buffer size.
  
protected:
  
  BooleanT initalised;
  my_error_mgr jerr;
  unsigned char *buffer;
};

class DPImageIOJPegIBaseC;

typedef struct {
  struct jpeg_source_mgr pub;	/* public fields */
  BooleanT start_of_file;
  DPImageIOJPegIBaseC *obj;
  unsigned char *buffer;
} amma_source_mgr;

class DPImageIOJPegIBaseC 
  : public DPImageIOJPegBaseC
{
public:
  DPImageIOJPegIBaseC(const IStreamC &fin);
  //: Constructor.

  ~DPImageIOJPegIBaseC();
  //: Desctructor
  
  void InitI(IStreamC &is);
  //: Initalise Input.

  IStreamC &FIn()
    { return fin; }
  //: Access output stream.

  BooleanT BaseIsGetEOS() const {
    if(!initalised)
      return true;
    if(source_mgr.pub.bytes_in_buffer > 0)
      return false;
    return const_cast<IStreamC &>(fin).IsEndOfStream();
  }
  //: Test if we're at the end of the stream.
protected:
  BooleanT SetupFormat(const type_info &ti);
  //: Setup input format.
  // Must be called after header has been read.
  
  IStreamC fin;
  
  amma_source_mgr source_mgr;
  
  struct jpeg_decompress_struct cinfo;
};

class DPImageIOJPegOBaseC;

typedef struct {
  struct jpeg_destination_mgr pub; /* public fields */
  DPImageIOJPegOBaseC *obj;
  unsigned char *buffer;
} amma_destination_mgr;

class DPImageIOJPegOBaseC 
  : public DPImageIOJPegBaseC
{
public:
  DPImageIOJPegOBaseC(const OStreamC &fout,int compression = 75);
  //: Constructor.

  ~DPImageIOJPegOBaseC();
  //: Desctructor

  void InitO(OStreamC &os);
  //: Initalise output.
  
  OStreamC &FOut()
    { return fout; }
  //: Access output stream.
protected:
  BooleanT SetupFormat(const type_info &ti);
  //: Setup output format.
  
  OStreamC fout;
  int compression;
  
  amma_destination_mgr destination_mgr;
  struct jpeg_compress_struct cinfo;
};

//: Load a PPM image.

template<class PixelT>
class DPIImageJPegBodyC 
  : public DPIPortBodyC<ImageC<PixelT> >,
    public DPImageIOJPegIBaseC
{
public:
  DPIImageJPegBodyC(FilenameC fn);
  //: Constructor from filename.
  
  DPIImageJPegBodyC(const IStreamC &in);
  //: Constructor from stream.
  // Not supported at the moment...
  
  virtual BooleanT IsGetEOS() const;
  //: Is valid data ?
  
  virtual ImageC<PixelT> Get();
  //: Get next piece of data.
  
  virtual BooleanT Get(ImageC<PixelT> &buff);
  //: Get next piece of data.
protected:
  BooleanT Read(ImageC<PixelT> &buf);
  //: Read image data.
};

//: Save a  image.

template<class PixelT>
class DPOImageJPegBodyC : 
  public DPOPortBodyC<ImageC<PixelT> >,
  public DPImageIOJPegOBaseC
{
public:
  DPOImageJPegBodyC(FilenameC fn,int compression = 75);
  //: Constructor from filename.
  
  DPOImageJPegBodyC(const OStreamC &strm,int compression = 75);
  //: Constructor from filename.
  // Not supported at the moment...
  
  virtual BooleanT Put(const ImageC<PixelT> &dat);
  //: Put data.
  
  virtual BooleanT IsPutReady() const ;
  //: Is port ready for data ?

  
protected:
  BooleanT Write(const ImageC<PixelT> &buf);
  //: Write image data.
  
  amma_destination_mgr dstMgr;
  
};
//////// DPIImageJPegBodyC ///////////////////////////////////////////////

//: Constructor from filename.

template<class PixelT>
DPIImageJPegBodyC<PixelT>::DPIImageJPegBodyC(FilenameC nfn) 
  : DPImageIOJPegIBaseC(nfn)
{}

//: Constructor from stream.


template<class PixelT>
DPIImageJPegBodyC<PixelT>::DPIImageJPegBodyC(const IStreamC &in)
  : DPImageIOJPegIBaseC(in)
{}

//: Is valid data ?

template<class PixelT>
BooleanT DPIImageJPegBodyC<PixelT>::IsGetEOS() const 
{ return BaseIsGetEOS(); }

//: Get next piece of data.

template<class PixelT>
ImageC<PixelT> DPIImageJPegBodyC<PixelT>::Get() {
  ImageC<PixelT> ret;
  if(BaseIsGetEOS())
    return ret;
  if(!Read(ret))
    cerr << "DPIImageJPegBodyC<PixelT>::Get(), Error reading file.\n";
  return ret;
}

//: Get next piece of data.

template<class PixelT>
BooleanT DPIImageJPegBodyC<PixelT>::Get(ImageC<PixelT> &buff) {
  if(fin.IsEndOfStream())
    return false;
  return Read(buff);
}

//: Read image data.

template<class PixelT>
BooleanT DPIImageJPegBodyC<PixelT>::Read(ImageC<PixelT> &buff) {
  
  // Establish the setjmp return context for my_error_exit to use.
  if (setjmp(jerr.setjmp_buffer)) {
    // If we get here, the JPEG code has signaled an error.
    return false;
  }
  
  jpeg_read_header(&cinfo, TRUE);
  
  jpeg_start_decompress(&cinfo);
  
  /* We may need to do some setup of our own at this point before reading
   * the data.  After jpeg_start_decompress() we have the correct scaled
   * output image dimensions available, as well as the output colormap
   * if we asked for color quantization.
   */ 
  
  buff = ImageC<PixelT>(cinfo.image_height,cinfo.image_width);  
  JSAMPROW buffer[1];	/* pointer to JSAMPLE row[s] */

  const IndexT LCol = buff.LCol();
  IndexT crow = buff.TRow();
  
  while (cinfo.output_scanline < cinfo.output_height) {
    buffer[0] = (JSAMPROW) (& (buff[crow++][LCol]));
    jpeg_read_scanlines(&cinfo,buffer , 1);    
  }
  
  jpeg_finish_decompress(&cinfo);
  
  return true;
}

//// DPOImageJPegBodyC /////////////////////////////////////////////

//: Constructor from filename.

template<class PixelT>
DPOImageJPegBodyC<PixelT>::DPOImageJPegBodyC(FilenameC nfn,int ncompression) 
  : DPImageIOJPegOBaseC(OStreamC(nfn),ncompression)
{}

//: Constructor from filename.

template<class PixelT>
DPOImageJPegBodyC<PixelT>::DPOImageJPegBodyC(const OStreamC &strm,int ncompression) 
  : DPImageIOJPegOBaseC(strm,ncompression)
{}

//: Put data.

template<class PixelT>
BooleanT DPOImageJPegBodyC<PixelT>::Put(const ImageC<PixelT> &dat) {
  if(!initalised) {
    cerr << "DPOImageJPegBodyC<PixelT>::Write(), Not initalised. \n";
    return false;
  }
  if(!fout.good())
    return false;
  return Write(dat);
}

//: Is port ready for data ?

template<class PixelT>
BooleanT DPOImageJPegBodyC<PixelT>::IsPutReady() const {
  if(!initalised)
    return false;
  return fout.good();
}

//: Write image data.

template<class PixelT>
BooleanT DPOImageJPegBodyC<PixelT>::Write(const ImageC<PixelT> &buff) {
  
  // Establish the setjmp return context for my_error_exit to use.
  if (setjmp(jerr.setjmp_buffer)) {
    cerr << "DPOImageJPegBodyC<PixelT>::Write(), Error found. \n";
    // If we get here, the JPEG code has signaled an error.
    return false;
  }
  
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
  
  cinfo.image_width = buff.Cnum(); 	/* image width and height, in pixels */
  cinfo.image_height = buff.Rnum();
  
  if(!SetupFormat(typeid(PixelT)))
    return false; /* Don't know pixel type... */
  
  jpeg_set_defaults(&cinfo);
  
  jpeg_set_quality(&cinfo, compression, TRUE /* limit to baseline-JPEG values */);
  
  jpeg_start_compress(&cinfo, TRUE);
  
  const IndexT LCol = buff.LCol();
  IndexT crow = buff.TRow();
  while (cinfo.next_scanline < cinfo.image_height) {
    row_pointer[0] = (JSAMPROW)(& (buff[crow++][LCol]));
    jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  
  jpeg_finish_compress(&cinfo);
  
  return true;
}

#endif

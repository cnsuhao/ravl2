#ifndef IMGIOJPEG_HEADER
#define IMGIOJPEG_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! file="amma/Image/ExtImgIO/ImgIOJPeg.hh"
//! lib=ExtImgIO
//! author="Charles Galambos"
//! docentry="Image.Image IO"
//! example=exImgIO.cc
//! date="29/10/98"

#include "amma/DP/Port.hh"
#include "amma/Image.hh"
#include "amma/RGBValue.hh"
#include "amma/YUVValue.hh"
#include "amma/GreyVal.hh"
#include "amma/Stream.hh"
#include "amma/Filename.hh"

//: Load a RGB image in JPEG format.
// Use via function found in amma/StdType/DataProc/FileFormatIO.hh

class DPIImageJPegByteRGBC :  public DPIPortC<ImageC<ByteRGBValueC> >
{
public:
  DPIImageJPegByteRGBC(FilenameC fn);
  //: Constructor from filename.  
  
  DPIImageJPegByteRGBC(const IStreamC &strm);
  //: Constructor from stream 
};

//: Save a RGB image in JPEG format.

class DPOImageJPegByteRGBC :  public DPOPortC<ImageC<ByteRGBValueC> >
{
public:
  DPOImageJPegByteRGBC(FilenameC fn,int compression = 75);
  //: Constructor from filename.  
  
  DPOImageJPegByteRGBC(const OStreamC &strm,int compression = 75);
  //: Constructor from stream.  
};

//: Load a YUV image in JPEG format.
// Use via function found in amma/StdType/DataProc/FileFormatIO.hh

class DPIImageJPegByteYUVC :  public DPIPortC<ImageC<ByteYUVValueC> >
{
public:
  DPIImageJPegByteYUVC(FilenameC fn);
  //: Constructor from filename.  
  
  DPIImageJPegByteYUVC(const IStreamC &strm);
  //: Constructor from stream 
};

//: Save a YUV image in JPEG format.

class DPOImageJPegByteYUVC :  public DPOPortC<ImageC<ByteYUVValueC> >
{
public:
  DPOImageJPegByteYUVC(FilenameC fn,int compression = 75);
  //: Constructor from filename.  
  
  DPOImageJPegByteYUVC(const OStreamC &strm,int compression = 75);
  //: Constructor from stream.  
};

//: Load a Grey image in JPEG format.
// Use via function found in amma/StdType/DataProc/FileFormatIO.hh

class DPIImageJPegByteGreyC :  public DPIPortC<ImageC<ByteGreyValueT> >
{
public:
  DPIImageJPegByteGreyC(FilenameC fn);
  //: Constructor from filename.  
  
  DPIImageJPegByteGreyC(const IStreamC &strm);
  //: Constructor from stream 
};

//: Save a Grey image in JPEG format.

class DPOImageJPegByteGreyC :  public DPOPortC<ImageC<ByteGreyValueT> >
{
public:
  DPOImageJPegByteGreyC(FilenameC fn,int compression = 75);
  //: Constructor from filename.  
  
  DPOImageJPegByteGreyC(const OStreamC &strm,int compression = 75);
  //: Constructor from stream.  
};


#endif

#ifndef IMGIOTIFF_HEADER
#define IMGIOTIFF_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! file="amma/Image/ExtImgIO/ImgIOTiff.hh"
//! lib=ExtImgIO
//! author="Charles Galambos"
//! docentry="Image.Image IO"
//! example=exImgIO.cc
//! date="29/10/98"

#include "amma/DP/Port.hh"
#include "amma/RGBImage.hh"
#include "amma/ByteImag.hh"
#include "amma/Stream.hh"

//: Load a RGB image in PPM format.
// Use via function found in amma/StdType/DataProc/FileFormatIO.hh

class DPIImageTIFFByteRGBAC :  public DPIPortC<ImageC<ByteRGBXValueC> >
{
public:
  DPIImageTIFFByteRGBAC(FilenameC fn);
  //: Constructor from filename.  
  
  DPIImageTIFFByteRGBAC(const IStreamC &strm);
  //: Constructor from stream 
};

//: Save a RGB image in PPM format.

class DPOImageTIFFByteRGBAC :  public DPOPortC<ImageC<ByteRGBXValueC> >
{
public:
  DPOImageTIFFByteRGBAC(FilenameC fn);
  //: Constructor from filename.  
  
  DPOImageTIFFByteRGBAC(const OStreamC &strm);
  //: Constructor from stream.  
};

#endif

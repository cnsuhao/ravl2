#ifndef IMGIOPNG_HEADER
#define IMGIOPNG_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! file="amma/Image/ExtImgIO/ImgIOPNG.hh"
//! lib=ExtImgIO
//! author="Charles Galambos"
//! docentry="Image.Image IO"
//! example=exImgIO.cc
//! date="29/10/98"

#include "amma/DP/Port.hh"
#include "amma/RGBImage.hh"
#include "amma/Stream.hh"

//: Load a RGB image in PPM format.
// Use via function found in amma/StdType/DataProc/FileFormatIO.hh

class DPIImagePNGByteRGBC :  public DPIPortC<ImageC<ByteRGBValueC> >
{
public:
  DPIImagePNGByteRGBC(FilenameC fn);
  //: Constructor from filename.  
  
  DPIImagePNGByteRGBC(const IStreamC &strm);
  //: Constructor from stream 
};

//: Save a RGB image in PPM format.

class DPOImagePNGByteRGBC :  public DPOPortC<ImageC<ByteRGBValueC> >
{
public:
  DPOImagePNGByteRGBC(FilenameC fn);
  //: Constructor from filename.  
  
  DPOImagePNGByteRGBC(const OStreamC &strm);
  //: Constructor from stream.  
};



//: Load a RGB image in PPM format.
// Use via function found in amma/StdType/DataProc/FileFormatIO.hh

class DPIImagePNGByteGreyC 
  :  public DPIPortC<ImageC<ByteGreyValueT> >
{
public:
  DPIImagePNGByteGreyC(FilenameC fn);
  //: Constructor from filename.  
  
  DPIImagePNGByteGreyC(const IStreamC &strm);
  //: Constructor from stream 
};

//: Save a RGB image in PPM format.

class DPOImagePNGByteGreyC 
  : public DPOPortC<ImageC<ByteGreyValueT> >
{
public:
  DPOImagePNGByteGreyC(FilenameC fn);
  //: Constructor from filename.  
  
  DPOImagePNGByteGreyC(const OStreamC &strm);
  //: Constructor from stream.  
};



#endif

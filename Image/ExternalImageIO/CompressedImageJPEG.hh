// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_COMPRESSEDIMAGEJPEG_HEADER
#define RAVLIMAGE_COMPRESSEDIMAGEJPEG_HEADER 1
//! lib=RavlExtImgIO
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.IO.Formats"

#include "Ravl/Array1d.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Buffer containing a compressed image.
  
  class CompressedImageJPEGC 
    : public SArray1dC<char>
  {
  public:
    CompressedImageJPEGC(const SArray1dC<char> &buff)
      : SArray1dC<char>(buff)
    {}
    //: Construct from char buffer
    
    CompressedImageJPEGC()
    {}
    //: Default constructor.
    
  };
  
  ostream &operator<<(ostream &strm,const CompressedImageJPEGC &data);
  //: Write to standard stream.
  
  istream &operator>>(istream &strm,CompressedImageJPEGC &data);
  //: Read from standard stream
  
  BinOStreamC &operator<<(BinOStreamC &strm,const CompressedImageJPEGC &data);
  //: Write to standard stream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,CompressedImageJPEGC &data);
  //: Read from standard stream
  
  CompressedImageJPEGC RGBImage2CompressedImageJPEG(const ImageC<ByteRGBValueC> &img);
  //: Convert RGB image to a compressed buffer.
  
  ImageC<ByteRGBValueC> CompressedImageJPEG2RGBImage(const CompressedImageJPEGC &img);
  //: Convert compressed buffer to a RGB image
  
}


#endif

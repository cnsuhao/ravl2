// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMGIOJPEG_HEADER
#define RAVLIMGIOJPEG_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! file="amma/Image/ExtImgIO/ImgIOJPeg.hh"
//! lib=ExtImgIO
//! author="Charles Galambos"
//! docentry="Ravl.Image.IO.Formats"
//! example=exImgIO.cc
//! date="29/10/98"

#include "Ravl/DP/Port.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Stream.hh"

namespace RavlN {
  
  //: Load a RGB image in JPEG format.
  // Use via function found in amma/StdType/DataProc/FileFormatIO.hh
  
  class DPIImageJPegByteRGBC 
    : public DPIPortC<ImageC<ByteRGBValueC> >
  {
  public:
    DPIImageJPegByteRGBC(const StringC &fn);
    //: Constructor from filename.  
    
    DPIImageJPegByteRGBC(const IStreamC &strm);
    //: Constructor from stream 
  };
  
  //: Save a RGB image in JPEG format.
  
  class DPOImageJPegByteRGBC 
    : public DPOPortC<ImageC<ByteRGBValueC> >
  {
  public:
    DPOImageJPegByteRGBC(const StringC &fn,int compression = 75);
    //: Constructor from filename.  
    
    DPOImageJPegByteRGBC(const OStreamC &strm,int compression = 75);
    //: Constructor from stream.  
  };
  
  //: Load a YUV image in JPEG format.
  // Use via function found in amma/StdType/DataProc/FileFormatIO.hh
  
  class DPIImageJPegByteYUVC 
    : public DPIPortC<ImageC<ByteYUVValueC> >
  {
  public:
    DPIImageJPegByteYUVC(const StringC &fn);
    //: Constructor from filename.  
    
    DPIImageJPegByteYUVC(const IStreamC &strm);
    //: Constructor from stream 
  };
  
  //: Save a YUV image in JPEG format.
  
  class DPOImageJPegByteYUVC 
    : public DPOPortC<ImageC<ByteYUVValueC> >
  {
  public:
    DPOImageJPegByteYUVC(const StringC &fn,int compression = 75);
    //: Constructor from filename.  
    
    DPOImageJPegByteYUVC(const OStreamC &strm,int compression = 75);
    //: Constructor from stream.  
  };
  
  //: Load a Grey image in JPEG format.
  // Use via function found in amma/StdType/DataProc/FileFormatIO.hh
  
  class DPIImageJPegByteGreyC 
    : public DPIPortC<ImageC<ByteT> >
  {
  public:
    DPIImageJPegByteGreyC(const StringC &fn);
    //: Constructor from filename.  
    
    DPIImageJPegByteGreyC(const IStreamC &strm);
    //: Constructor from stream 
  };
  
  //: Save a Grey image in JPEG format.
  
  class DPOImageJPegByteGreyC 
    : public DPOPortC<ImageC<ByteT> >
  {
  public:
    DPOImageJPegByteGreyC(const StringC &fn,int compression = 75);
    //: Constructor from filename.  
    
    DPOImageJPegByteGreyC(const OStreamC &strm,int compression = 75);
    //: Constructor from stream.  
  };
  
}

#endif

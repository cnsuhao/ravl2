// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_AVIFILEIO_HEADER
#define RAVLIMAGE_AVIFILEIO_HEADER 1
////////////////////////////////////////////////////
//! rcsid="$Id: AVIFileIO.hh 5240 2005-12-06 17:16:50Z plugger $"
//! file="Ravl/Contrib/AVIFile/AVIFileIO.hh"
//! lib=RavlAVIFile
//! example=testAVIFile.cc
//! docentry="Ravl.API.Images.Video.Video IO"
//! author="James Smith"
//! date="19/01/2004"

#include "Ravl/DP/SPort.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

#include <avifile/avifile.h>

namespace RavlImageN {
  
  ///////////////////////////////////
  //! userlevel=Develop
  //: Save a sequence of RGB images using the AVIFile library.
  
  class DPOAVIFileBodyC 
    : public DPOPortBodyC<ImageC<ByteRGBValueC> >
  {
  public:
    DPOAVIFileBodyC(const StringC& filename);
    //: Constructor from filename
    
    virtual ~DPOAVIFileBodyC()
    { TidyUp(); }
    //: Destructor
    // Closes stream.
    
    bool Put(const ImageC<ByteRGBValueC> &img);
    //: Put image to a stream.
    
    void PutEOS()
    { TidyUp(); }
    //: Put end of stream marker

    bool IsPutReady() const;
    //: Ready to write some data ?
    // TRUE = yes.
    
    bool GetAttr(const StringC &attrName,StringC &attrValue);
    //: Get a string stream attribute.
    // Returns false if the attribute name is unknown.
  
    bool GetAttr(const StringC &attrName,IntT &attrValue);
    //: Get a IntT stream attribute.
    // Returns false if the attribute name is unknown.

    bool SetAttr(const StringC &attrName,const StringC &attrValue);
    //: Set an string stream attribute.
    // Returns false if the attribute name is unknown.
  
    bool SetAttr(const StringC &attrName,const IntT &attrValue);
    //: Set an IntT stream attribute.
    // Returns false if the attribute name is unknown.

  protected:

    void TidyUp();
    //: Tidy up the streams up.

    void RegisterAttributes();
    //: Register attributes
  
    void SetupAVIFile(const StringC& filename);
    //: Setup AVI File

    bool SetupAVIStream(const ImageC<ByteRGBValueC> &img);
    //: Setup AVI Stream
    // img is an image from which to get frame size information.

    IAviWriteFile* m_pFile;
    //: AVI file writer

    IAviVideoWriteStream* m_pStream;
    //: AVI video stream

    StringC m_str4CC;
    //: FOURCC code

    IntT m_iFrameRate;
    //: Frames per second

    BitmapInfo m_oBitmapInfo;
    //: Bitmap info block

  };

  
  //! userlevel=Normal
  //: Save a sequence of RGB images using the AVIFile library.

  class DPOAVIFileC 
    : public DPOPortC<ImageC<ByteRGBValueC> >
  {
  public:
    DPOAVIFileC(const StringC& filename)
    : DPEntityC(*new DPOAVIFileBodyC(filename))
      {}
    //: Constructor from filename.  
    
  };
  
}



#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! userlevel=Normal
//! rcsid="$Id: AVIFileIO.cc 3904 2004-01-27 17:36:45Z vap-james $"
//! lib=RavlAVIFile
//! file="Ravl/Contrib/AVIFile/AVIFileIO.cc"

#include "Ravl/Image/AVIFileIO.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Math.hh"
#include "Ravl/DP/AttributeValueTypes.hh"

#include <avifile/avm_fourcc.h>
#include <avifile/except.h>
#include <avifile/utils.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
    
  //: Constructor from filename

  DPOAVIFileBodyC::DPOAVIFileBodyC(const StringC& filename) :
    m_pFile(NULL),
    m_pStream(NULL),
    m_str4CC("IV50"), // will change to "mjpg" later
    m_iFrameRate(25)
  {
    // Register sttributes
    RegisterAttributes();
    // Open AVI file
    SetupAVIFile(filename);
  }

  //: Destructor.
  // Closes stream.
  
  void DPOAVIFileBodyC::TidyUp() {
    ONDEBUG(cerr << "DPOAVIFileBodyC::TidyUp()" << endl);
    // Close AVI stream
    if (m_pStream) {
      ONDEBUG(cerr << "DPOAVIFileBodyC::TidyUp(), Stopping stream" << endl);
      m_pStream->Stop();
      m_pStream = NULL;
    }
    // Close AVI file
    if (m_pFile) {
      ONDEBUG(cerr << "DPOAVIFileBodyC::TidyUp(), Closing file" << endl);
      delete m_pFile;
      m_pFile = NULL;
    }
  }

  //: Register attributes
  
  void DPOAVIFileBodyC::RegisterAttributes() {
    RegisterAttribute(AttributeTypeStringC("fourcc","FOURCC codec id",true,true));
    RegisterAttribute(AttributeTypeNumC<IntT>("framerate","Frame rate",true,true,1,100,1,m_iFrameRate));
  }

  //: Get a string stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool DPOAVIFileBodyC::GetAttr(const StringC &attrName,StringC &attrValue) {
    if(attrName == "fourcc") {
      attrValue = m_str4CC;
      return true; 
    }
    return DPOPortBodyC<ImageC<ByteRGBValueC> >::GetAttr(attrName,attrValue);
  }

  //: Get an IntT stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool DPOAVIFileBodyC::GetAttr(const StringC &attrName,IntT &attrValue) {
    if(attrName == "framerate") {
      attrValue = m_iFrameRate;
      return true; 
    }
    return DPOPortBodyC<ImageC<ByteRGBValueC> >::GetAttr(attrName,attrValue);
  }
  
  //: Set a string stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool DPOAVIFileBodyC::SetAttr(const StringC &attrName,const StringC &attrValue) {
    if(attrName == "fourcc") {
      // Store string
      m_str4CC = attrValue.Copy();
      // Crop first four characters
      m_str4CC = m_str4CC.before(4);
      // Pad string with spaces up to four characters
      IntT iPadding = 4 - m_str4CC.Size();
      if (iPadding > 0) {
	for (int i=0; i<iPadding; i++)
	  m_str4CC += ' ';
      }
      // Done
      return true; 
    }
    return DPOPortBodyC<ImageC<ByteRGBValueC> >::SetAttr(attrName,attrValue);
  }

  //: Set an IntT stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool DPOAVIFileBodyC::SetAttr(const StringC &attrName,const IntT &attrValue) {
    if(attrName == "framerate") {
      m_iFrameRate = attrValue;
      return true;
    }
    return DPOPortBodyC<ImageC<ByteRGBValueC> >::SetAttr(attrName,attrValue);
  }

  //: Setup AVI file
  
  void DPOAVIFileBodyC::SetupAVIFile(const StringC& filename) {    
    // Open AVI file for output
    try {
      // Create file
      m_pFile = CreateIAviWriteFile(filename);
    } catch (BaseError err) {
      ONDEBUG(cerr << "DPOAVIFileBodyC::SetupAVIFile, could not open file " << filename << " for writing." << endl);
      ONDEBUG(cerr << " -- AVIFile error follows: " << endl);
      ONDEBUG(err.PrintAll());
      m_pFile = NULL;
    }
    // Done for now
    return;
  }

  //: Setup AVI Stream
  
  bool DPOAVIFileBodyC::SetupAVIStream(const ImageC<ByteRGBValueC> &img) {
    if (!m_pFile) return false;
    if (m_pStream) return true;
    // Setup AVI stream
    try {
      // Set up bitmap info block
      m_oBitmapInfo = BitmapInfo(img.Cols(),img.Rows(),24);
      m_oBitmapInfo.SetRGB();
    
      // Create FOURCC    
      int fourcc = mmioFOURCC(m_str4CC[0], m_str4CC[1], m_str4CC[2], m_str4CC[3]);

      // Add video stream to output file
      m_pStream = m_pFile->AddVideoStream(fourcc, &m_oBitmapInfo, 1000000/m_iFrameRate);

      // Add frames    
      m_pStream->Start();

    } catch (BaseError err) {
      ONDEBUG(cerr << "DPOAVIFileBodyC::SetupAVIStream, could not setup stream." << endl);
      ONDEBUG(cerr << " -- AVIFile error follows: " << endl);
      ONDEBUG(err.PrintAll());
      m_pStream = NULL;
      return false;
    }
    return true;
  }

  //: Put image to a stream.
  
  bool DPOAVIFileBodyC::Put(const ImageC<ByteRGBValueC> &img) {
    // Make sure the stream is set up properly
    if (!m_pStream && !SetupAVIStream(img)) {
      // Stream isn't ready
      return false;
    }
    // Create AVIFile format image
    const ByteRGBValueC* pixel = &img[img.Frame().Origin()];
    CImage im(&m_oBitmapInfo);
    // Copy pixel data
    if (avm_img_is_rgb(im.Format())) {
      switch (im.Depth()) {
      case 24: {
	memcpy(im.Data(), pixel, img.Rows() * img.Cols() * 3);
      } break;
      default:
	cerr << "DPOAVIFileBodyC::Put - Unsupported RGB colour depth!" << endl;
	return false;
      }
    }
    else if (avm_img_is_bgr(im.Format())) {
      switch (im.Depth()) {
      case 24: {
	uint8_t* pixel = im.Data();
	for (unsigned int r=0; r<img.Rows(); r++) {
	  for (unsigned int c=0; c<img.Cols(); c++) {
	    *pixel++ = img[r][c].Blue();
	    *pixel++ = img[r][c].Green();
	    *pixel++ = img[r][c].Red();
	  }
	}
      } break;
      default:
	cerr << "DPOAVIFileBodyC::Put - Unsupported BGR colour depth!" << endl;
	return false;
      }	
    }
    else {
      cerr << "DPOAVIFileBodyC::Put - Unsupported colour format!" << endl;
      return false;
    }
    // Add to stream
    m_pStream->AddFrame(&im);
    // Done
    return true;
  }
    
  //: Ready to write some data ?
  
  bool DPOAVIFileBodyC::IsPutReady() const {
    return m_pFile;
  }
    
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMGIOTIFF_HEADER
#define RAVLIMGIOTIFF_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! file="Ravl/Image/ExternalImageIO/ImgIOTiff.hh"
//! lib=ExtImgIO
//! author="Charles Galambos"
//! docentry="Image.Image IO"
//! example=exImgIO.cc
//! date="29/10/98"

#include "Ravl/DP/Port.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBAValue.hh"

namespace RavlN {
  
  //: Load a RGB image in PPM format.
  // Use via function found in amma/StdType/DataProc/FileFormatIO.hh
  
  class DPIImageTIFFByteRGBAC 
    : public DPIPortC<ImageC<ByteRGBAValueC> > {
    public:
    DPIImageTIFFByteRGBAC(StringC fn);
    //: Constructor from filename.  
    
    DPIImageTIFFByteRGBAC(const IStreamC &strm);
    //: Constructor from stream 
  };

  //: Save a RGB image in PPM format.
  
  class DPOImageTIFFByteRGBAC 
    : public DPOPortC<ImageC<ByteRGBAValueC> > {
    public:
    DPOImageTIFFByteRGBAC(StringC fn);
    //: Constructor from filename.  
    
    DPOImageTIFFByteRGBAC(const OStreamC &strm);
    //: Constructor from stream.  
  };
}

#endif

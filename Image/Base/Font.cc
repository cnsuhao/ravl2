// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/Image/Font.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Image/PSFFont.h"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArr1Iter.hh"

namespace RavlImageN {

  //: Load default font.
  
  FontC::FontC(bool)
  {
    (*this) = LoadPSF1(PROJECT_OUT "/Tools/Fonts/default8x16.psf");
  }
  
  FontC LoadPSF1(const StringC &fontFile) {
    psf1_header hdr; //: psf file
    
    IStreamC inf(fontFile);
    if(!inf) {
      cerr << "FontC::LoadPsf(), Failed to open font file '" << fontFile << "'\n";
      return FontC();
    }
    
    // Read the header.
    
    inf.read((char *) &hdr,sizeof(psf1_header));    
    if((hdr.magic[0] != PSF1_MAGIC0) || (hdr.magic[1] != PSF1_MAGIC1))
      return FontC(); // Not a PSF1 font.
    int height = hdr.charsize;
    int ng = 255;
    if(hdr.mode & PSF1_MODE512)
      ng = 512;
    
    SArray1dC<ImageC<ByteT> > glyphs(ng);
    SArray1dC<ByteT > buf(height);
    for(SArray1dIterC<ImageC<ByteT> > it(glyphs);it;it++) {
      // Read glyph
      ImageC<ByteT> img(height,8);
      *it = img;
      inf.read((char *) &(buf[0]),height);
      for(IntT i=0;i < height;i++) {
	int dat = buf[i]; 
	for(IntT j = 7;j >= 0;j--) 
	  if((dat >> j) & 1) 
	    img[i][7-j]=255;
      }
    }
    
    return FontC(glyphs);
  }
  
}

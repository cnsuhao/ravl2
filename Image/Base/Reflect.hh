// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_REFLECT_HEADER
#define RAVLIMAGE_REFLECT_HEADER 1
//! author="Charles Galambos"
//! userlevel=Normal
//! docentry="Ravl.Images"
//! rcsid="$Id$"
//! lib=RavlImage
//! date="13/2/2003"

#include "Ravl/Image/Image.hh"

namespace RavlImageN {
  
  template<class PixelT>
  void ReflectVertical(const ImageC<PixelT> &img,ImageC<PixelT> &out) {
    if(out.Frame() != img.Frame())
      out = ImageC<PixelT>(img.Frame());
    IndexC minc = img.Range2().Min();
    IndexC maxc = img.Range2().Max();
    for(IndexC i = img.Range1().Min();i <= img.Range1().Max();i++) {
      const PixelT *p1 = &(img[i][minc]);
      const PixelT *ep = &(img[i][maxc]);
      PixelT *p2 = &(out[i][minc]);
      for(;p1 <= ep;p1++,p2++)
	*p2 = *p1;
    }
  }
}


#endif

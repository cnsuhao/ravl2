// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SOBOLIMAGE_HEADER
#define RAVL_SOBOLIMAGE_HEADER 1
//////////////////////////////////////////////////////////
//! docentry="Ravl.Images.Misc"
//! file="Ravl/Image/IPStream/Lines/SobelImg.hh"
//! lib=RavlImage
//! author="Charles Galambos"
//! rcsid="$Id$"
//! date="07/01/99"

#include "Ravl/Image/Image.hh"

namespace RavlImageN {
  
  ImageC<UIntT> SobolImage(const ImageRectangleC &rect);
  //! userlevel=Normal
  //: Generate a sobel image of a given size.
  
}
#endif

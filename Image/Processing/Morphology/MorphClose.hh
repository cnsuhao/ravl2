// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_OPEN_HEADER
#define RAVLIMAGE_OPEN_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImage
//! author="Charles Galambos"
//! userlevel=Normal
//! docentry="Ravl.Images.Morphology"

#include "Ravl/Image/Dilate.hh"
#include "Ravl/Image/Erode.hh"

namespace RavlImageN {
  
  template<class DataT> 
  void MorphBinaryClose(const ImageC<DataT>& image, const ImageC<DataT>& kernel,ImageC<DataT>& result,DataT inRegion = 1) {
    ImageC<DataT> tmp;
    BinaryErode(image,kernel,tmp,inRegion);
    BinaryDilate(tmp,kernel,result,inRegion);
  }
  
}
#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_ERODE_HEADER
#define RAVLIMAGE_ERODE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImage
//! author="Joel Mitchelson"
//! userlevel=Normal
//! docentry="Ravl.Images.Morphology"
//! file="Ravl/Image/Processing/Morphology/Erode.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/Rectangle2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter.hh"

namespace RavlImageN
{
  template<class DataT> 
  void BinaryErode(const ImageC<DataT>& image, const ImageC<DataT>& kernel,ImageC<DataT>& result,DataT inRegion = 1)
  {
    ImageRectangleC resRect(image.Rectangle());
    resRect.TRow() -= kernel.Rectangle().TRow();
    resRect.BRow() -= kernel.Rectangle().BRow();
    resRect.LCol() -= kernel.Rectangle().LCol();
    resRect.RCol() -= kernel.Rectangle().RCol();
    RavlAssertMsg(resRect.Area() > 0,"Erode, ERROR: Rectangle too small.");
    if(!result.Rectangle().Contains(resRect)) // Check the result rectangle is large enough.
      result = ImageC<DataT>(resRect); // If its not make another.
    
    Array2dIterC<DataT> res(result,resRect);
    for(Rectangle2dIterC rit(image.Frame(),kernel.Frame());rit;rit++,res++) {
      *res = inRegion;
      for(Array2dIter2C<DataT,DataT> it(kernel,Array2dC<DataT>(image,rit.Window()));it;it++) {
	if(it.Data1() && (it.Data2() == 0)) {
	  *res = 0;
	  break;
	}
      }
    }
  }
  //: Binary erosion
  // This code does not deal with boundry conditions, the output rectangle is smaller than the input. 
  // The center of the kernel is take to be the origin (0,0), the results are placed in the corresponding location in the 'result'
  // image. If results rectangle is not large enough it will be reallocated.
  
}

#endif

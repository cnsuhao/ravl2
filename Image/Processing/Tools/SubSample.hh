// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SUBSAMPLE_HEADER
#define RAVL_SUBSAMPLE_HEADER 1
////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Images.Misc"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Tools/SubSample.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Average.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Subsample by 2 in each direction.
  
  template<class PixelT>
  ImageC<PixelT> SubSample22(const ImageC<PixelT> &Img) {
    PixelT *imgVal[2];
    PixelT *resVal,*eor;
    int i;
    IndexC pxlRow;
    IndexC resRow;
    
    ImageRectangleC workRect = Img.Rectangle();  
    workRect.End().Col() =  workRect.LCol() + (workRect.Cols() & ~1);      // Round down.
    workRect.End().Row() =  workRect.TRow() + (workRect.Rows() & ~1);      // Round down.
    
    ImageRectangleC resultRect;
    resultRect.Origin().Col()   = workRect.LCol() >> 1;
    resultRect.Origin().Row()   = workRect.TRow() >> 1;
    resultRect.End().Col() = resultRect.Origin().Col() + (workRect.Cols() >> 1)-1;
    resultRect.End().Row() = resultRect.Origin().Row() + (workRect.Rows() >> 1)-1;
    
    ImageC<PixelT> result(resultRect); // Result image.
    const int len = result.End().Col() - result.Origin().Col();
    
    resRow = resultRect.TRow();
    pxlRow = workRect.TRow();
    for(;pxlRow < workRect.BRow();pxlRow += 2,resRow++) {
      imgVal[0] =  img.Row(pxlRow);
      imgVal[1] =  img.Row(pxlRow+1);
      resVal =  result.Row(resRow);
      eor = resVal[len]; // Where's the end of row?
      for(;resVal < eor;i += 2,imgVal[0] += 2,imgVal[1] += 2,resVal++)
	*resVal = Average(imgVal[0][0],imgVal[0][1],imgVal[1][0],imgVal[1][1]);
    }
    return result;
  }
  

}


#endif

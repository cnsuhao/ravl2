// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_BILINEARINTERPOLATION_HEADER
#define RAVLIMAGE_BILINEARINTERPOLATION_HEADER 1
///////////////////////////////////////////////////////////////
//! docentry="Ravl.Images.Warping"
//! lib=RavlImageProc
//! author="Kieron Messer"
//! rcsid="$Id$"
//! date="05/05/1999"
//! file="Ravl/Image/Processing/Filters/BilinearInterpolation.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Scale an image using bi-Linear Interpolation.
  
  template <class InT, class OutT = InT>
  class BilinearInterpolationC
  {
  public:
    BilinearInterpolationC(const ImageRectangleC &ir)
      : rec(ir)
    {}
    //: Constructor.
    // 'ir' is the output rectangle.
    
    ImageC<OutT> Apply(const ImageC<InT> &img);
    //: Interpolate input image working rectangle into
    //: output image rectangle.
    // The output rectangle is specified in the constructor.
    
  protected:
    ImageRectangleC rec;    
  };
  
  template <class InT, class OutT>
  ImageC<OutT> BilinearInterpolationC<InT, OutT>::Apply(const ImageC<InT> &im)
  {
    ImageC<OutT> res(rec);
    
    IntT imRows  = im.Rows();
    IntT imCols  = im.Cols();
    
    Index2dC y1,y2,y3,y4;
    RealT t, u;
    RealT minC, minR;
    RealT jOff = im.LCol();
    RealT j,i = im.TRow();
    
    // First check for degenerate cases...
    
    if(imRows <= 0 && imCols <= 0) // Empty image.
      return res; 
    
    if(imRows == 1 && imCols == 1) { // Just one pixel.
      res[res.Rectangle().Origin()] = im[im.Rectangle().Origin()];
      return res;
    }
    
    RealT stepC = ((RealT)imCols-1.000001)/(RealT)rec.Cols();
    RealT stepR = ((RealT)imRows-1.000001)/(RealT)rec.Rows();
    
    if(imRows == 1) { // Just one row.
      y3.Row() = im.Rectangle().Origin().Row();
      y4.Row() = y3.Row();
      j = jOff;
      for(Array2dIterC<OutT> it(res);it.IsElm();it.Next()) {
	minC = Floor(j);
	t = (j - minC);
	j += stepC; 
	
	IntT iMinC = (IntT) minC;
	y4.Col() = iMinC;
	y3.Col() = iMinC+1;
	if(iMinC == im.Rectangle().RCol()) {// Hack!!!
	  cerr << "ERROR: Overflow in interpolation (C). \n";
	  break;
	}
	
	it.Data() = (OutT)((im[y4] * (1.0-t)) + 
			   (im[y3] * t ) 
			   );
      }
      return res;
    }
    
    if(imCols == 1) { // Just one columb.    
      y2.Col() = im.Rectangle().Origin().Col();
      y4.Col() = y2.Col();
      for(Array2dIterC<OutT> it(res);it.IsElm();it.Next()) {
	minR = Floor(i);
	u = (i - minR);
	i += stepR;
	IntT iMinR = (IntT) minR;
	y4.Row() = iMinR;
	y2.Row() = iMinR+1;
	if(iMinR == im.Rectangle().BRow()) {// Hack!!!
	  cerr << "ERROR: Overflow in interpolation (R) \n";
	  break;
	}
	it.Data() = (OutT)((im[y4] * (1.0-u)) + 
			   (im[y2] * u));
      }
      
      return res;
    }
    
    for(Array2dIterC<OutT> it(res);it.IsElm();) {
      minR = Floor(i);
      u = (i - minR);
      i += stepR;
      
      IntT iMinR = (IntT) minR;
      j = jOff;
      
      y1.Row() = iMinR+1;
      y2.Row() = iMinR+1;
      y3.Row() = iMinR;
      y4.Row() = iMinR;
      
      do {
	minC = Floor(j);
	t = (j - minC);
	j += stepC; 
	
	IntT iMinC = (IntT) minC;
	
	y1.Col() = iMinC+1; 
	y3.Col() = iMinC+1;
	y2.Col() = iMinC;
	y4.Col() = iMinC;
	
	it.Data() = (OutT)((im[y4] * ((1.0-t) * (1.0-u))) + 
			   (im[y3] * (     t  * (1.0-u))) + 
			   (im[y2] * ((1.0-t) *      u )) +
			   (im[y1] * (     t  *      u )) 
			   );
      } while(it.Next()); // True while in same row.
      
    }
    return res;
  }
  
}
#endif

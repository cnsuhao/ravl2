// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_CONVOLVE2D_HEADER
#define RAVLIMAGE_CONVOLVE2D_HEADER 1
/////////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Charles Galambos"
//! lib=RavlImage
//! file="Ravl/Image/Processing/Filters/Convolve2d.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Rectangle2dIter.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: 2D Convolution
  
  template<class KernelPixelT,class InPixelT = KernelPixelT,class OutPixelT = InPixelT,class SumTypeT = KernelPixelT>
  class Convolve2dC {
  public:
    Convolve2dC()
    {}
    //: Default constructor.

    Convolve2dC(const ImageC<KernelPixelT> &nkernel)
    { SetKernel(nkernel); }
    //: Default constructor.
    
    void SetKernel(const ImageC<KernelPixelT> &nkernel) { 
      kernel = nkernel.Rotate180(); // The apply method actualy does correlation.
    }
    //: Set the convolution kernel.
    
    void Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const;
    //: Do convolution on image 'in', put the output in 'result' 
    
    void operator()(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const
    { Apply(in,result); }
    
  protected:
    ImageC<KernelPixelT> kernel;
  };
  
  template<class KernelPixelT,class InPixelT,class OutPixelT,class SumTypeT>
  void Convolve2dC<KernelPixelT,InPixelT,OutPixelT,SumTypeT>::Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const {
    RavlAssertMsg(kernel.Frame().Area() > 0,"Convolution kernel too small. ");
    ImageRectangleC resRect = in.Rectangle();
    resRect.TRow() -= kernel.Rectangle().TRow();
    resRect.BRow() -= kernel.Rectangle().BRow();
    resRect.LCol() -= kernel.Rectangle().LCol();
    resRect.RCol() -= kernel.Rectangle().RCol();
    RavlAssertMsg(resRect.Area() > 0,"Convole2dC::Apply(), ERROR: Input rectangle too small.");
    if(!result.Rectangle().Contains(resRect)) // Check the result rectangle is large enough.
      result = ImageC<OutPixelT>(resRect); // If its not make another.
      
    Array2dIterC<OutPixelT> res(result,resRect);
    for(Rectange2dIterC rit(in.Frame(),kernel.Frame());rit;rit++,res++) {
      BufferAccess2dIter2C<KernelPixelT,InPixelT> it(kernel,kernel.Range1(),kernel.Range2(),
					     in,rit.Window().Range1(),rit.Window().Range2());
      SumTypeT sum = (SumTypeT) (it.Data1() * it.Data2());
      it++;
      for(;it;it++)
	sum += (SumTypeT) it.Data1() * (SumTypeT) it.Data2();
      *res =(OutPixelT) sum;
    }
  }
  //: Do convolution.

#if RAVL_USE_MMX
  template <> void Convolve2dC<short,short,short,short>::Apply(const ImageC<short> &in,ImageC<short> &result) const;
  //: Use some MMX code to speed this up.
  
  template <> void Convolve2dC<short,short,short,int>::Apply(const ImageC<short> &in,ImageC<short> &result) const;
  //: Use some MMX code to speed this up.
#endif
}

#endif

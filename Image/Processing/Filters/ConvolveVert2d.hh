// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_CONVOLVERT2D_HEADER
#define RAVLIMAGE_CONVOLVERT2D_HEADER 1
/////////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Charles Galambos"
//! lib=RavlImage
//! docentry="Ravl.Images.Filtering"
//! file="Ravl/Image/Processing/Filters/ConvolveVert2d.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Rectangle2dIter.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Vertontal 2D Convolution with a 1D filter.
  
  template<class KernelPixelT,class InPixelT = KernelPixelT,class OutPixelT = InPixelT,class SumTypeT = KernelPixelT>
  class ConvolveVert2dC {
  public:
    ConvolveVert2dC()
    {}
    //: Default constructor.

    ConvolveVert2dC(const Array1dC<KernelPixelT> &ncolKernel)
    { SetKernel(ncolKernel); }
    //: Default constructor.
    
    void SetKernel(const Array1dC<KernelPixelT> &ncolKernel) { 
      colKernel = ncolKernel.Copy();
      colKernel.Reverse();  // Reverse mask as Appy method actually does correlation.
    }
    //: Set the convolution kernel.
    // Note: Currently this rotates the mast around the central element,
    // not about the 0 index as other convolution methods in RAVL.
    
    void Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const;
    //: Do convolution on image 'in', put the output in 'result' 
    
    void operator()(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const
    { Apply(in,result); }
    
  protected:
    Array1dC<KernelPixelT> colKernel;
  };
  
  template<class KernelPixelT,class InPixelT,class OutPixelT,class SumTypeT>
  void ConvolveVert2dC<KernelPixelT,InPixelT,OutPixelT,SumTypeT>::Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const {
    RavlAssertMsg(colKernel.Size() > 0,"Convolution kernel too small. ");
    ImageRectangleC resRect = in.Rectangle();
    resRect.TRow() -= colKernel.IMin();
    resRect.BRow() -= colKernel.IMax();
    RavlAssertMsg(resRect.Area() > 0,"ConvoleVert2dC::Apply(), ERROR: Input rectangle too small.");
    if(!result.Rectangle().Contains(resRect)) // Check the result rectangle is large enough.
      result = ImageC<OutPixelT>(resRect); // If its not make another.
    UIntT ksize = colKernel.Range().Size();
    UIntT rowSep = in.Stride();
    for(Array2dIter2C<OutPixelT,InPixelT> it(result,in,resRect);it;it++) { // ,resRect
      const KernelPixelT *kp = &(colKernel[colKernel.IMin()]);
      const KernelPixelT *eol = &kp[ksize];
      const InPixelT *ip = &it.Data2();
      SumTypeT sum = (SumTypeT) ((*ip) * (*kp));
      ip += rowSep;
      kp++;
      for(;kp != eol;kp++,ip += rowSep)
	sum += ((*ip) * (*kp));
      it.Data1() = (OutPixelT) sum;
    }
  }
  
}

#endif

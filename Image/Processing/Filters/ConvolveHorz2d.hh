// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_CONVOLHORZ2D_HEADER
#define RAVLIMAGE_CONVOLHORZ2D_HEADER 1
/////////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Charles Galambos"
//! lib=RavlImage
//! file="Ravl/Image/Processing/Filters/ConvolveHorz2d.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Rectangle2dIter.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Horzontal 2D Convolution with a 1D filter.
  
  template<class KernelPixelT,class InPixelT = KernelPixelT,class OutPixelT = InPixelT,class SumTypeT = KernelPixelT>
  class ConvolveHorz2dC {
  public:
    ConvolveHorz2dC()
    {}
    //: Default constructor.

    ConvolveHorz2dC(const Array1dC<KernelPixelT> &nrowKernel)
    { SetKernel(nrowKernel); }
    //: Default constructor.
    
    void SetKernel(const Array1dC<KernelPixelT> &nrowKernel) { 
      rowKernel = nrowKernel.Copy();
      rowKernel.Reverse(); // Reverse mask as Appy method actually does correlation.
    }
    //: Set the convolution kernel.
    // Note: Currently this rotates the mast around the central element,
    // not about the 0 index as other convolution methods in RAVL.
    
    void Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const;
    //: Do convolution on image 'in', put the output in 'result' 
    
    void operator()(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const
    { Apply(in,result); }
    //: () Style apply.
    
  protected:
    Array1dC<KernelPixelT> rowKernel;
  };
  
  template<class KernelPixelT,class InPixelT,class OutPixelT,class SumTypeT>
  void ConvolveHorz2dC<KernelPixelT,InPixelT,OutPixelT,SumTypeT>::Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const {
    RavlAssertMsg(rowKernel.Size() > 0,"Convolution kernel too small. ");
    ImageRectangleC resRect = in.Rectangle();
    resRect.LCol() -= rowKernel.IMin();
    resRect.RCol() -= rowKernel.IMax();
    RavlAssertMsg(resRect.Area() > 0,"ConvoleHorz2dC::Apply(), ERROR: Input rectangle too small.");
    if(!result.Rectangle().Contains(resRect)) // Check the result rectangle is large enough.
      result = ImageC<OutPixelT>(resRect); // If its not make another.
    UIntT ksize = rowKernel.Range().Size();
    for(Array2dIter2C<OutPixelT,InPixelT> it(result,in,false);it;it++) { // ,resRect
      const KernelPixelT *kp = &(rowKernel[rowKernel.IMin()]);
      const KernelPixelT *eol = &kp[ksize];
      const InPixelT *ip = &it.Data2();
      SumTypeT sum = (KernelPixelT) (*ip) * (*kp);
      ip++;
      kp++;
      for(;kp != eol;kp++,ip++)
	sum += (SumTypeT) (*ip) * (SumTypeT) (*kp);
      it.Data1() = (OutPixelT) sum;
    }
  }

  
}

#endif

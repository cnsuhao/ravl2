// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_CONVOLVESEPARABLE2D_HEADER
#define RAVLIMAGE_CONVOLVESEPARABLE2D_HEADER 1
/////////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.Images.Filtering"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Filters/ConvolveSeparable2d.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ConvolveHorz2d.hh"
#include "Ravl/Image/ConvolveVert2d.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Separable 2D Convolution
  
  template<class KernelPixelT,class InPixelT = KernelPixelT,class OutPixelT = InPixelT,class SumTypeT = KernelPixelT>
  class ConvolveSeparable2dC {
  public:
    ConvolveSeparable2dC()
    {}
    //: Default constructor.

    ConvolveSeparable2dC(const Array1dC<KernelPixelT> &nrowKernel,const Array1dC<KernelPixelT> &ncolKernel)
    { SetKernel(nrowKernel,ncolKernel); }
    //: Default constructor.
    
    void SetKernel(const Array1dC<KernelPixelT> &nrowKernel,const Array1dC<KernelPixelT> &ncolKernel) { 
      horz.SetKernel(nrowKernel);
      vert.SetKernel(ncolKernel);
    }
    //: Set the convolution kernel.
    
    void Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const;
    //: Do convolution on image 'in', put the output in 'result' 
    
    void operator()(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const
    { Apply(in,result); }
    
  protected:
    ConvolveVert2dC<KernelPixelT,InPixelT,SumTypeT,SumTypeT>  vert;
    ConvolveHorz2dC<KernelPixelT,SumTypeT,OutPixelT,SumTypeT> horz;
  };
  
  template<class KernelPixelT,class InPixelT,class OutPixelT,class SumTypeT>
  void ConvolveSeparable2dC<KernelPixelT,InPixelT,OutPixelT,SumTypeT>::Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const {
    ImageC<SumTypeT> tmp;
    vert.Apply(in,tmp);
    horz.Apply(tmp,result);
  }
  //: Do convolution.
  
}

#endif

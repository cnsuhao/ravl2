#ifndef RAVLIMAGE_CONVOLVESEPARABLE2D_HEADER
#define RAVLIMAGE_CONVOLVESEPARABLE2D_HEADER 1
/////////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ConvolveHorz2d.hh"
#include "Ravl/Image/ConvolveVert2d.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Separable 2D Convolution
  
  template<class KernelPixelT,class InPixelT = KernelPixelT,class OutPixelT = InPixelT>
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
    ConvolveVert2dC<KernelPixelT,InPixelT,KernelPixelT>  vert;
    ConvolveHorz2dC<KernelPixelT,KernelPixelT,OutPixelT> horz;
  };
  
  template<class KernelPixelT,class InPixelT,class OutPixelT>
  void ConvolveSeparable2dC<KernelPixelT,InPixelT,OutPixelT>::Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const {
    ImageC<KernelPixelT> tmp;
    vert.Apply(in,tmp);
    horz.Apply(tmp,result);
  }
  //: Do convolution.
  
}

#endif

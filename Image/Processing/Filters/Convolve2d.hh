#ifndef RAVLIMAGE_CONVOLVE2D_HEADER
#define RAVLIMAGE_CONVOLVE2D_HEADER 1
/////////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Rectangle2dIter.hh"
namespace RavlImageN {
  
  //! userlevel=Normal
  //: 2D Convolution
  
  template<class KernelPixelT,class InPixelT = KernelPixelT,class OutPixelT = InPixelT>
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
  
  template<class KernelPixelT,class InPixelT,class OutPixelT>
  void Convolve2dC<KernelPixelT,InPixelT,OutPixelT>::Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const {
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
      Array2dIter2C<KernelPixelT,InPixelT> it(kernel,Array2dC<InPixelT>(in,rit.Window()));
      KernelPixelT sum = (KernelPixelT) (it.Data1() * it.Data2());
      it++;
      for(;it;it++)
	sum += (KernelPixelT) (it.Data1() * it.Data2());
      *res = (OutPixelT) sum;
    }
  }
  //: Do convolution.
  
}


#endif

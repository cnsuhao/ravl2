#ifndef RAVLIMAGE_CONVOLHORZ2D_HEADER
#define RAVLIMAGE_CONVOLHORZ2D_HEADER 1
/////////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Rectangle2dIter.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Horzontal 2D Convolution with a 1D filter.
  
  template<class KernelPixelT,class InPixelT = KernelPixelT,class OutPixelT = InPixelT>
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
      rowKernel.Reverse();
    }
    //: Set the convolution kernel.
    
    void Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const;
    //: Do convolution on image 'in', put the output in 'result' 
    
    void operator()(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const
    { Apply(in,result); }
    
  protected:
    Array1dC<KernelPixelT> rowKernel;
  };
  
  template<class KernelPixelT,class InPixelT,class OutPixelT>
  void ConvolveHorz2dC<KernelPixelT,InPixelT,OutPixelT>::Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const {
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
      KernelPixelT sum = (KernelPixelT) (*ip) * (*kp);
      ip++;
      kp++;
      for(;kp != eol;kp++,ip++)
	sum += (KernelPixelT) (*ip) * (*kp);
      it.Data1() = sum;
    }
  }

  
}

#endif


#include "Ravl/Image/Convolve2d.hh"


namespace RavlImageN {

#if RAVL_USE_MMX  
  
  void Convolve2dC<short,short,short>::Apply(const ImageC<short> &in,ImageC<short> &result) const {
    RavlAssertMsg(kernel.Frame().Area() > 0,"Convolution kernel too small. ");
    ImageRectangleC resRect = in.Rectangle();
    resRect.TRow() -= kernel.Rectangle().TRow();
    resRect.BRow() -= kernel.Rectangle().BRow();
    resRect.LCol() -= kernel.Rectangle().LCol();
    resRect.RCol() -= kernel.Rectangle().RCol();
    RavlAssertMsg(resRect.Area() > 0,"Convole2dC::Apply(), ERROR: Input rectangle too small.");
    if(!result.Rectangle().Contains(resRect)) // Check the result rectangle is large enough.
      result = ImageC<short>(resRect); // If its not make another.
    
    Array2dIterC<short> res(result,resRect);
    for(Rectange2dIterC rit(in.Frame(),kernel.Frame());rit;rit++,res++) {
      Array2dIter2C<short,short> it(kernel,Array2dC<short>(in,rit.Window()));
      int sum = 0;
      for(;it;it++)
	sum += (it.Data1() * it.Data2());
      *res = (short) sum;
    }
  }
  //: Do convolution.

#endif  
}

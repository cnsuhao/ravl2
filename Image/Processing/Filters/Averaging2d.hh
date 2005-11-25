#ifndef RAVLIMAGE_AVERAGING2D_HEADER
#define RAVLIMAGE_AVERAGING2D_HEADER 1

//! author="Bill Christmas"
//! docentry="Ravl.Images.Filtering"

#include "Ravl/Image/SumRectangles.hh"
#include "Ravl/Image/Image.hh"

namespace RavlImageN {
  using namespace RavlN;
  

  //! userlevel=Normal
  //: Averaging filter
  // Can also be used as a summing filter by omitting the normalising step.<br>
  // <b><font color="cc0088">Note:</font></b> This filter is not recommended  for byte pixel types.

  template<class InPixelT,class OutPixelT> 
  class Averaging2dC {

  public:
    Averaging2dC()
    {}
    //: Default constructor.
    
    Averaging2dC(UIntT MaskHeight, UIntT MaskWidth, bool Norm=true)
      : mask(Index2dC(0,0), MaskHeight, MaskWidth),
        norm(Norm)
    {}
    //: Construct from mask dimensions
    //!param: Norm - if true, normalising step is performed
    
    ImageC<OutPixelT> Apply (const ImageC<InPixelT> &in) const {
      ImageC<OutPixelT> op;
      SumRectangles(in, mask, op) ;
      if (norm) op /= mask.Area();
      return op;
    }
    //: Performs an averaging filter on image 'in'.
    // Returns a new filtered image.
    
  private:

    IndexRange2dC mask;
    bool norm;
    
  };
}
#endif

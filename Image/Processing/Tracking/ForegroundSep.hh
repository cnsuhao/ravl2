#ifndef FOREGROUNDSEP_HH
#define FOREGROUNDSEP_HH

//! userlevel=Normal
//! author="Bill Christmas, Phil McLauchlan"
//! docentry="Ravl.Images.Mosaic"
//! lib=RavlImageProc

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ImageMatcher.hh"

namespace RavlImageN {

  //! userlevel=Normal
  //! autoLink=on
  //: Class to separate foreground objects in a sequence of images from a background image.
  // <p> It is typically used to separate out foreground objects from a sequence of images for which a mosaic has been created (see <a href="RavlImageN.MosaicBuilderC.html">MosaicBuilderC</a>).  It assumes a homography between each input image and background.</p>
  // <p> The operations can be roughly summarised as:</p><ul>
  // <li> subtract the projected background from the image</li>
  // <li> threshold the difference to create a foreground mask</li>
  // <li> apply some morphological opening to the mask</li>
  // <li> use the mask to create a foreground image from the input image </li></ul>

  class ForegroundSepC {
  public:
    ForegroundSepC(const ImageC<ByteRGBValueC>& mosaic, RealT mosaicZHomog, RealT imageZHomog, int fgThreshold=25);
    //: Constructor: Initialises background image and threshold for foreground / background separation.
    
    void SetMask(const ImageC<bool>& nmask)
      { mask = nmask; }
    //: Set binary mask to exclude regions from tracker
    // Pixels set to false are excluded.

    bool SetMask(const StringC& fileName);
    //: Set binary mask to exclude regions from tracker
    // Pixels set to zero are excluded.

    ImageC<ByteRGBValueC> Apply(const ImageC<ByteRGBValueC>& img, const Matrix3dC& homog);
    //: Computes foreground image for corresponding input image and homography
    
  private:
    ImageC<ByteRGBValueC> mosaic;
    RealT mosaicZHomog;
    RealT imageZHomog;
    ImageC<bool> kernel;
    ImageMatcherC matcher;  
    int fgThreshold;  
    ImageC<bool> mask;
  };
  
}

#endif


#include "Ravl/Image/YCbCrBT709Value.hh"
#include "Ravl/Image/RGBValue.hh"

namespace RavlImageN {
  
  // Convert a pixel type from RGB to YCbCrBT709
  
  void RGBFloat2YCbCrBT709Float(const RGBValueC<float> &value,YCbCrBT709ValueC<float> &outValue) {
    outValue.Set( + 0.21259    * value.Red() + 0.71521    * value.Green() + 0.07220    * value.Blue(),
                  - 0.11719 * value.Red() - 0.39423 * value.Green() + 0.51141      * value.Blue(),
                  + 0.51141      * value.Red() - 0.46454 * value.Green() - 0.04688 * value.Blue());
  }
  
  // Convert a pixel type from YCbCrBT709 to RGB
  
  void YCbCrBT709Float2RGBFloat(const YCbCrBT709ValueC<float> &value,RGBValueC<float> &outValue) {
    outValue.Set(value.Y() + 0.00000 * value.Cb() + 1.53967    * value.Cr(),
                 value.Y() - 0.18317    * value.Cb() - 0.45764    * value.Cr(),
                 value.Y() + 1.81421     * value.Cb() + 0.00000 * value.Cr());
  }
  
     
}

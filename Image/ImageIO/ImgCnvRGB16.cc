///////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/DP/Converter.hh"
#include "amma/Image/ImageConv.hh"
#include "amma/Image2Iter.hh"

#include "amma/Image.hh"
#include "amma/RGBValue.hh"

void InitRGB16ImageCnv()
{}

namespace StdImageN
{
  // Byte colour to UInt16 colour image.
  
  ImageC<RGBValueU16C> ByteRGBImageCT2RGBValueU16CImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<RGBValueU16C> ret(dat.Rectangle());
    for(Image2IterC<RGBValueU16C,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = RGBValueU16C(it.Data2());
    return ret;
  }
  
  //  UInt16 colour image to Byte colour.
  
  ImageC<ByteRGBValueC> RGBValueU16CImageCT2ByteRGBImageCT(const ImageC<RGBValueU16C> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Image2IterC<ByteRGBValueC,RGBValueU16C> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = ByteRGBValueC(it.Data2().Red(),it.Data2().Green(),it.Data2().Blue());
    return ret;
  }
  
  // Register conversions...
  
  DP_REGISTER_CONVERTION(ByteRGBImageCT2RGBValueU16CImageCT,1);
  DP_REGISTER_CONVERTION(RGBValueU16CImageCT2ByteRGBImageCT,2);
  
}

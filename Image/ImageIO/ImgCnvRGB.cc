///////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/DP/Converter.hh"
#include "amma/Image/ImageConv.hh"
#include "amma/Image2Iter.hh"

#include "amma/Image.hh"
#include "amma/RGBValue.hh"

void InitRGBImageCnv()
{}

namespace StdImageN
{
  
  // Byte RGBX to Byte RGB 
  
  ImageC<ByteRGBValueC> ByteRGBXImageCT2ByteRGBImageCT(const ImageC<ByteRGBXValueC> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Image2IterC<ByteRGBValueC,ByteRGBXValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = it.Data2();
    return ret;
  }

  // Byte RGB to Byte RGBX 
  
  ImageC<ByteRGBXValueC> ByteRGBImageCT2ByteRGBXImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<ByteRGBXValueC> ret(dat.Rectangle());
    for(Image2IterC<ByteRGBXValueC,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) {
      it.Data1() = ByteRGBXValueC(it.Data2(),0xff);
    }
    return ret;
  }
    
  // Byte colour to real colour image.
  
  ImageC<RGBPointC> ByteRGBImageCT2RealRGBImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<RGBPointC> ret(dat.Rectangle());
    for(Image2IterC<RGBPointC,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = RGBPointC(it.Data2());
    return ret;
  }
  
  // Real colour to byte colour image.

  ImageC<ByteRGBValueC> RealRGBImageCT2ByteRGBImageCT(const ImageC<RGBPointC> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Image2IterC<ByteRGBValueC,RGBPointC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = ByteRGBValueC(it.Data2());
    return ret;
  }

  // Register conversions...
  DP_REGISTER_CONVERTION(ByteRGBXImageCT2ByteRGBImageCT,1.25);
  DP_REGISTER_CONVERTION(ByteRGBImageCT2ByteRGBXImageCT,1);
  DP_REGISTER_CONVERTION(ByteRGBImageCT2RealRGBImageCT ,1);
  DP_REGISTER_CONVERTION(RealRGBImageCT2ByteRGBImageCT ,8);
  
}

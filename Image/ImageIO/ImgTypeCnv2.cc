
#include "amma/DP/Converter.hh"
#include "amma/Image/ImageConv.hh"
#include "amma/Image2Iter.hh"

#include "amma/Image.hh"
#include "amma/GreyVal.hh"
#include "amma/RGBValue.hh"
#include "amma/YUVValue.hh"

void InitStdImageCnv2()
{}

namespace StdImageN
{
  

  // Real YUV -> RGB
  
  ImageC<RGBPointC> RealYUVImageCT2RealRGBImageCT(const ImageC<YUVPointC> &dat) {
    ImageC<RGBPointC> ret(dat.Rectangle());
    for(Image2IterC<RGBPointC,YUVPointC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = RGBPointC(it.Data2());
    return ret;
  }


  // Real RGB -> YUV

  ImageC<YUVPointC> RealRGBImageCT2RealYUVImageCT(const ImageC<RGBPointC> &dat) {
    ImageC<YUVPointC> ret(dat.Rectangle());
    for(Image2IterC<YUVPointC,RGBPointC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = RGBPointC(it.Data2());
    return ret;
  }


  // Byte grey level to byte YUV colour image.
  ImageC<ByteGreyValueT> ByteYUVImageCT2ByteImageCT(const ImageC<ByteYUVValueC> &dat) { 
    ImageC<ByteGreyValueT> ret(dat.Rectangle());
    for(Image2IterC<ByteGreyValueT,ByteYUVValueC> it(ret,dat);it.IsElm();it.Next())
      it.Data1() = it.Data2().Y();
    return ret;  
  }

  // Byte colour to byte grey image.
  
  ImageC<ByteGreyValueT> RGBImageCT2ByteImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<ByteGreyValueT> ret(dat.Rectangle());
    for(Image2IterC<ByteGreyValueT,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = (ByteGreyValueT) ((IntT) ((IntT) it.Data2().Red() + it.Data2().Green() + it.Data2().Blue()) / 3);
    return ret;
  }
  // Byte Colour to double image.

  ImageC<DoubleImageValueT> RGBImageCT2DoubleImageCT(const ImageC<ByteRGBValueC> &dat)  { 
    ImageC<DoubleImageValueT> ret(dat.Rectangle());
    for(Image2IterC<DoubleImageValueT,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = (RealT) ((RealT) it.Data2().Red() + it.Data2().Green() + it.Data2().Blue()) / 3;
    return ret;
  }
  
  // Byte YUV to byte RGB image.

  ImageC<ByteRGBValueC> YUVImageCT2RGBImageCT(const ImageC<ByteYUVValueC> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Image2IterC<ByteRGBValueC,ByteYUVValueC> it(ret,dat);it.IsElm();it.Next()) {
      RGBPointC p(YUVValueC(it.Data2()));
      it.Data1() = p.Cut();
    }
    return ret;
  }

  // Byte RGB to byte YUV image.
  
  ImageC<ByteYUVValueC> RGBImageCT2YUVImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<ByteYUVValueC> ret(dat.Rectangle());
    for(Image2IterC<ByteYUVValueC,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next())
      it.Data1() = YUVValueC(RGBPointC(it.Data2())).Cut();
    return ret;
  }

  
  DP_REGISTER_CONVERTION(ByteYUVImageCT2ByteImageCT   ,3);
  DP_REGISTER_CONVERTION(YUVImageCT2RGBImageCT              ,1);
  DP_REGISTER_CONVERTION(RGBImageCT2YUVImageCT              ,1);
  
  DP_REGISTER_CONVERTION(RGBImageCT2DoubleImageCT     ,3);
  DP_REGISTER_CONVERTION(RGBImageCT2ByteImageCT       ,3.1);
  
  DP_REGISTER_CONVERTION(RealYUVImageCT2RealRGBImageCT,1);
  DP_REGISTER_CONVERTION(RealRGBImageCT2RealYUVImageCT,1);
  
}

///////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/DP/Converter.hh"
#include "amma/Image/ImageConv.hh"
#include "amma/Image2Iter.hh"

#include "amma/Image.hh"
#include "amma/GreyVal.hh"
#include "amma/RGBValue.hh"
#include "amma/YUVValue.hh"

extern void InitStdImageCnv2();

void InitStdImageCnv()
{ InitStdImageCnv2(); }

//ByteYUVValueC
// Some type conversions for standard images.

namespace StdImageN
{
  // Byte to double image.

  ImageC<DoubleImageValueT> ByteImageCT2DoubleImageCT(const ImageC<ByteGreyValueT> &dat) { 
    ImageC<DoubleImageValueT> ret(dat.Rectangle());
    for(Image2IterC<DoubleImageValueT,ByteGreyValueT> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = (DoubleImageValueT) it.Data2();
    return ret;
  }
  
  // Byte to int image.
  
  ImageC<IntT> ByteImageCT2IntImageCT(const ImageC<ByteGreyValueT> &dat) { 
    ImageC<IntT> ret(dat.Rectangle());
    for(Image2IterC<IntT,ByteGreyValueT> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = (IntT) it.Data2();
    return ret;
  }

  // Int to double image.
  
  ImageC<DoubleImageValueT> IntImageCT2DoubleImageCT(const ImageC<IntT> &dat)   { 
    ImageC<DoubleImageValueT> ret(dat.Rectangle());
    for(Image2IterC<DoubleImageValueT,IntT> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = (DoubleImageValueT) it.Data2();
    return ret;
  }


  // Byte grey level to colour image.
  
  ImageC<ByteRGBValueC> ByteImageCT2ByteRGBImageCT(const ImageC<ByteGreyValueT> &dat) { 
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Image2IterC<ByteRGBValueC,ByteGreyValueT> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = ByteRGBValueC(it.Data2(),it.Data2(),it.Data2());
    return ret;  
  }
  
  // Byte grey level to byte YUV colour image.
  
  ImageC<ByteYUVValueC> ByteImageCT2ByteYUVImageCT(const ImageC<ByteGreyValueT> &dat) { 
    ImageC<ByteYUVValueC> ret(dat.Rectangle());
    for(Image2IterC<ByteYUVValueC,ByteGreyValueT> it(ret,dat);it.IsElm();it.Next())
      it.Data1() = ByteYUVValueC(it.Data2(),0,0);
    return ret;  
  }
  
  // Double -> Byte (clipped to fit)
  // This will clip, then round the double value (NOT floor!) to fit in a byte value 0 to 255.
  
  ImageC< ByteGreyValueT> DoubleImageCT2ByteImageCT(const ImageC< DoubleImageValueT> &dat) { 
    ImageC< ByteGreyValueT> ret(dat.Rectangle());
    for(Image2IterC< ByteGreyValueT,DoubleImageValueT> it(ret,dat);it.IsElm();it.Next()) {
      it.Data1() = (it.Data2()>255.0) ? 255 : (it.Data2()<0.0) ? 0 : ((ByteGreyValueT) (it.Data2() + 0.5));
    }
    return ret;
  }
  
  
  
  // Handle converters.
  
  DP_REGISTER_CONVERTION(ByteImageCT2ByteRGBImageCT   ,1);
  DP_REGISTER_CONVERTION(ByteImageCT2ByteYUVImageCT   ,1);
  DP_REGISTER_CONVERTION(ByteImageCT2IntImageCT       ,1);
  
  DP_REGISTER_CONVERTION(ByteImageCT2DoubleImageCT          ,1);
  DP_REGISTER_CONVERTION(DoubleImageCT2ByteImageCT    ,8);
  DP_REGISTER_CONVERTION(IntImageCT2DoubleImageCT     ,1);
}

///////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/DP/Converter.hh"
#include "amma/Image/ImageConv.hh"
#include "amma/Image2Iter.hh"

#include "amma/Image.hh"
#include "amma/GreyVal.hh"
#include "amma/RGBValue.hh"
#include "amma/YUVValue.hh"

void InitStdImageCnv3()
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

  
  
}

///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinImgIO.hh"
#include "amma/VYUValue.hh"

void InitImgIOByteVYU()
{}

ImageC<ByteVYUValueC> YUVImageCT2VYUImageC(const ImageC<ByteYUVValueC> &dat)  
{ 
  ImageC<ByteVYUValueC> ret(dat.Rectangle());
  for(Image2IterC<ByteVYUValueC,ByteYUVValueC> it(ret,dat);it.IsElm();it.Next()) 
    it.Data1() = ByteVYUValueC(it.Data2().V()+0x80,it.Data2().Y(),it.Data2().U()+0x80);
  return ret;
}

ImageC<ByteYUVValueC> VYUImageTC2YUVImageCT(const ImageC<ByteVYUValueC> &dat)
{
  ImageC<ByteYUVValueC> ret(dat.Rectangle());
  for(Image2IterC<ByteYUVValueC,ByteVYUValueC> it(ret,dat);it.IsElm();it.Next()) 
    it.Data1() = ByteYUVValueC(it.Data2().Y(),it.Data2().U()-0x80,it.Data2().V() - 0x80);
  return ret;
}

ImageC<ByteGreyValueT> VYUImageC2ByteGreyValueT(const ImageC<ByteVYUValueC> &dat)
{
  ImageC<ByteGreyValueT> ret(dat.Rectangle());
  for(Image2IterC<ByteGreyValueT,ByteVYUValueC> it(ret,dat);it.IsElm();it.Next())
    it.Data1() = it.Data2().Y();
  return ret;
}

ImageC<DoubleImageValueT> VYUImageC2DoubleImageValueT(const ImageC<ByteVYUValueC> &dat)
{
  ImageC<DoubleImageValueT> ret(dat.Rectangle());
  for(Image2IterC<DoubleImageValueT,ByteVYUValueC> it(ret,dat);it.IsElm();it.Next())
    it.Data1() = (DoubleImageValueT) it.Data2().Y();
  return ret;
}

ImageC<ByteVYUValueC> ByteGreyValueT2VYUImageC(const ImageC<ByteGreyValueT> &dat)
{ 
  ImageC<ByteVYUValueC> ret(dat.Rectangle());
  for(Image2IterC<ByteVYUValueC,ByteGreyValueT> it(ret,dat);it.IsElm();it.Next()) 
    it.Data1() = ByteVYUValueC(0,it.Data2(),0);
  return ret;
}

DP_REGISTER_CONVERTION(VYUImageTC2YUVImageCT,1);
DP_REGISTER_CONVERTION(YUVImageCT2VYUImageC,1);
DP_REGISTER_CONVERTION(VYUImageC2ByteGreyValueT,3);
DP_REGISTER_CONVERTION(ByteGreyValueT2VYUImageC,1);
DP_REGISTER_CONVERTION(VYUImageC2DoubleImageValueT,1); // Here really for speed.

FileFormatStreamC<ImageC<ByteVYUValueC> > FileFormatStream_ImageC_ByteVYUValueC;
FileFormatBinStreamC<ImageC<ByteVYUValueC> > FileFormatBinStream_ImageC_ByteVYUValueC;

static TypeNameC type2(typeid(ImageC<ByteVYUValueC>),"ImageC<ByteVYUValueC>");

BinOStreamC &operator << (BinOStreamC &out,const ImageC<ByteVYUValueC> &img)
{ 
  out << img.Rectangle();
  
  IntT width = img.Cnum() * 3;
  IndexT atrow = img.TRow();
  IndexT offset = img.LCol();
  
  IndexT brow = img.BRow();
  for(;atrow <= brow;atrow++)
    out.OBuff((const char *) &(img[atrow][offset]),width);  
  return out;
}

BinIStreamC &operator >> (BinIStreamC &in,ImageC<ByteVYUValueC> &img)
{ 
  ImageRectangleC rect;
  in >> rect;
  img = ImageC<ByteVYUValueC>(rect);
  
  IntT width = img.Cnum() * 3;
  IndexT atrow = img.TRow();
  IndexT offset = img.LCol();
  
  IndexT brow = img.BRow();
  for(;atrow <= brow;atrow++)
    in.IBuff((char *) &(img[atrow][offset]),width);
  return in;
}


/////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/DP/Converter.hh"
#include "amma/DP/FrameInfo.hh"
#include "amma/Image.hh"
#include "amma/GreyVal.hh"
#include "amma/RGBValue.hh"
#include "amma/YUVValue.hh"
#include "amma/VYUValue.hh"

#include "amma/TypeName.hh"

using namespace StdDP;

void InitFrameImageCnv()
{}

static TypeNameC type1(typeid(FrameC<ImageC<ByteGreyValueT> >),"FrameC<ImageC<ByteGreyValueT>>");
static TypeNameC type2(typeid(FrameC<ImageC<ByteYUVValueC> >),"FrameC<ImageC<ByteYUVValueC>>");
static TypeNameC type3(typeid(FrameC<ImageC<ByteRGBValueC> >),"FrameC<ImageC<ByteRGBValueC>>");
static TypeNameC type4(typeid(FrameC<ImageC<ByteVYUValueC> >),"FrameC<ImageC<ByteVYUValueC>>");

#define SORTOUT(NAME,X) \
X ConvertFromFrame_ ## NAME (const FrameC<X> &dat) { return dat.Data(); } \
FrameC<X> ConvertToFrame_ ## NAME (const X &dat) { return FrameC<X>(dat); } \
DP_REGISTER_CONVERTION(ConvertFromFrame_ ## NAME,2); \
DP_REGISTER_CONVERTION(ConvertToFrame_ ## NAME,1)

SORTOUT(ImageC_ByteGreyValueT,ImageC<ByteGreyValueT>);
SORTOUT(ImageC_ByteYUVValueC,ImageC<ByteYUVValueC>);
SORTOUT(ImageC_ByteVYUValueC,ImageC<ByteVYUValueC>);
SORTOUT(ImageC_ByteRGBValueC,ImageC<ByteRGBValueC>);
SORTOUT(ImageC_IntT,ImageC<IntT>);

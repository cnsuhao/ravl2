//////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/DP/Converter.hh"
#include "amma/GreyVal.hh"
#include "amma/RGBValue.hh"
#include "amma/YUVValue.hh"
#include "amma/NumImage.hh"

#define SORTOUT(NAME,X) \
ImageC<X> ConvertFromNumImage_ ## NAME (const NumImageC<X> &dat) { return ImageC<X>(dat); } \
NumImageC<X> ConvertToNumImage_ ## NAME (const ImageC<X> &dat) { return NumImageC<X>(dat); } \
DP_REGISTER_CONVERTION(ConvertFromNumImage_ ## NAME,2); \
DP_REGISTER_CONVERTION(ConvertToNumImage_ ## NAME,1)

SORTOUT(ImageC_ByteGreyValueT,ByteGreyValueT);
SORTOUT(ImageC_ByteYUVValueC,ByteYUVValueC);
SORTOUT(ImageC_ByteRGBValueC,ByteRGBValueC);
SORTOUT(ImageC_Int,IntT);
SORTOUT(ImageC_Real,RealT);
SORTOUT(ImageC_RGBValue,RGBValueC);
SORTOUT(ImageC_YUVValue,YUVValueC);


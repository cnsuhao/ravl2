///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id: ImgIOU16RGB.cc 4 2001-04-11 12:45:55Z craftit $"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinImgIO.hh"
#include "amma/BinIORGBValue.hh"
#include "amma/RGBImage.hh"

void InitImgIOU16RGB()
{}

namespace StdImageN
{
  FileFormatStreamC<ImageC<RGBValueU16C> > FileFormatStream_ImageC_RGBValueU16C;
  FileFormatBinStreamC<ImageC<RGBValueU16C> > FileFormatBinStream_ImageC_RGBValueU16C;
}

static TypeNameC type2(typeid(ImageC<RGBValueU16C>),"ImageC<RGBValueU16C>");


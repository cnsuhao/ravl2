////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinIOPixel.hh"
#include "amma/Pixel.hh"
#include "amma/DList.hh"

void InitPixelIO()
{}

static TypeNameC type1(typeid(PixelC),"PixelC");
static TypeNameC type2(typeid(DListC<PixelC>),"DListC<PixelC>");
static TypeNameC type3(typeid(DListC<DListC<PixelC> >),"DListC<DListC<PixelC>>");

FileFormatStreamC<PixelC > FileFormatStream_PixelC;
FileFormatStreamC<DListC<PixelC > > FileFormatStream_DListC_PixelC;
FileFormatStreamC<DListC<DListC<PixelC > > > FileFormatStream_DListC_DListC_PixelC;

FileFormatBinStreamC<PixelC > FileFormatBinStream_PixelC;
FileFormatBinStreamC<DListC<PixelC > > FileFormatBinStream_DListC_PixelC;
FileFormatBinStreamC<DListC<DListC<PixelC > > > FileFormatBinStream_DListC_DListC_PixelC;



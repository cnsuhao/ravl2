///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinImgIO.hh"
#include "amma/BinIORGBValue.hh"
#include "amma/ReRGBImg.hh"

void InitImgIORealRGB()
{}

ImageC<RGBPointC> DPConvRealRGBImageC2ImageCT(const RealRGBImageC &dat)  
{ return ImageC<RGBPointC>(dat); }

RealRGBImageC DPConvImageCT2RealRGBImageC(const ImageC<RGBPointC> &dat)  
{ return RealRGBImageC(dat); }

DP_REGISTER_CONVERTION(DPConvRealRGBImageC2ImageCT,1);
DP_REGISTER_CONVERTION(DPConvImageCT2RealRGBImageC,1);

FileFormatStreamC<ImageC<RGBPointC> > FileFormatStream_ImageC_RGBPointC;
FileFormatBinStreamC<ImageC<RGBPointC> > FileFormatBinStream_ImageC_RGBPointC;

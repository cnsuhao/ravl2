///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinIOYUVValue.hh"
#include "amma/BinImgIO.hh"
#include "amma/ReYUVImg.hh"

void InitImgIORealYUV()
{}

namespace StdDP {
  ImageC<YUVPointC> DPConvRealYUVImageC2ImageCT(const RealYUVImageC &dat)  
  { return ImageC<YUVPointC>(dat); }
  
  RealYUVImageC DPConvImageCT2RealYUVImageC(const ImageC<YUVPointC> &dat)  
  { return RealYUVImageC(dat); }

  DP_REGISTER_CONVERTION(DPConvRealYUVImageC2ImageCT,1);
  DP_REGISTER_CONVERTION(DPConvImageCT2RealYUVImageC,1);
  
  FileFormatStreamC<ImageC<YUVPointC> > FileFormatStream_ImageC_YUVPointC;
  FileFormatBinStreamC<ImageC<YUVPointC> > FileFormatBinStream_ImageC_YUVPointC;
}

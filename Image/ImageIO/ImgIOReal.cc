///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinImgIO.hh"
#include "amma/DoubleIm.hh"

void InitImgIOReal()
{}


ImageC<DoubleImageValueT> DPConvDoubleImageC2ImageCT(const DoubleImageC &dat)  
{ return ImageC<DoubleImageValueT>(dat); }

DoubleImageC DPConvImageCT2DoubleImageC(const ImageC<DoubleImageValueT> &dat)  
{ return DoubleImageC(dat); }

DP_REGISTER_CONVERTION(DPConvDoubleImageC2ImageCT,1);
DP_REGISTER_CONVERTION(DPConvImageCT2DoubleImageC,1);

FileFormatStreamC<ImageC<DoubleImageValueT> > FileFormatStream_ImageC_DoubleImageValueT;
FileFormatBinStreamC<ImageC<DoubleImageValueT> > FileFormatBinStream_ImageC_DoubleImageValueT;

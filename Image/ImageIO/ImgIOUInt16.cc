///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinImgIO.hh"

void InitImgIOUInt16()
{}

//ImageC<ByteGreyValueT>  DPConvByteImageC2ImageCT(const ByteImageC &dat)  
//{ return ImageC<ByteGreyValueT>(dat); }
//ByteImageC DPConvImageCT2ByteImageC(const ImageC<ByteGreyValueT> &dat)  
//{ return ByteImageC(dat); }
//DP_REGISTER_CONVERTION(DPConvByteImageC2ImageCT,1);
//DP_REGISTER_CONVERTION(DPConvImageCT2ByteImageC,1);

FileFormatStreamC<ImageC<GreyValueU16T> > FileFormatStream_ImageC_GreyValueU16T;
FileFormatBinStreamC<ImageC<GreyValueU16T> > FileFormatBinStream_ImageC_GreyValueU16T;

static TypeNameC type2(typeid(ImageC<GreyValueU16T>),"ImageC<GreyValueU16T>");

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"

namespace RavlN {
  
  void InitImgIOInt()
  {}
  
  // Byte to double image.

  ImageC<RealT> UIntTImageCT2DoubleImageCT(const ImageC<UIntT> &dat) { 
    ImageC<RealT> ret(dat.Rectangle());
    for(Array2dIter2C<RealT,UIntT> it(ret,dat);it;it++) 
      it.Data1() = (RealT) it.Data2();
    return ret;
  }
  
#if 0
  ImageC<UIntT> UInt16TImageCT2UIntTImageCT(const ImageC<GreyValueU16T> &dat) { 
    ImageC<UIntT> ret(dat.Rectangle());
    for(Image2IterC<UIntT,GreyValueU16T> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = it.Data2();
    return ret;
  }

  ImageC<GreyValueU16T> UIntTImageCT2UInt16TImageCT(const ImageC<UIntT> &dat) { 
    ImageC<GreyValueU16T> ret(dat.Rectangle());
    for(Image2IterC<GreyValueU16T,UIntT> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = it.Data2();
    return ret;
  }
#endif
  
  DP_REGISTER_CONVERTION(UIntTImageCT2DoubleImageCT,1);
#if 0
  DP_REGISTER_CONVERTION(UInt16TImageCT2UIntTImageCT,1);
  DP_REGISTER_CONVERTION(UIntTImageCT2UInt16TImageCT,2);
#endif
  
  static TypeNameC type1(typeid(ImageC<IntT>),"ImageC<IntT>");  
  static TypeNameC type2(typeid(ImageC<UIntT>),"ImageC<UIntT>");

#if 0  
  DP_REGISTER_CONVERTION(DPConvIntImageC2ImageCT,1);
  DP_REGISTER_CONVERTION(DPConvImageCT2IntImageC,1);
#endif
  
  FileFormatStreamC<ImageC<IntT> > FileFormatStream_ImageC_IntT;
  FileFormatBinStreamC<ImageC<IntT> > FileFormatBinStream_ImageC_IntT;
  FileFormatStreamC<ImageC<UIntT> > FileFormatStream_ImageC_UIntT;
  FileFormatBinStreamC<ImageC<UIntT> > FileFormatBinStream_ImageC_UIntT;
  
}

// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImage
//! file="Ravl/Image/Base/ImageConv.cc"

#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/RGBcYUV.hh"

// Some type conversions for standard images.

namespace RavlImageN {

static ImageC<ByteT> DoubleImageCT2ByteImageCT_L(const ImageC< RealT> &dat)
{
  ImageC< ByteT> ret(dat.Rectangle());
  for(Array2dIter2C< ByteT,RealT> it(ret,dat);it.IsElm();it.Next())
  {
    it.Data1() = (it.Data2() > 255.0) ? 255 :
                                        (it.Data2()<0.0) ? 0 :
                                                           ((ByteT) (it.Data2() + 0.5));
  }
  return ret;
}

//preparations for different version of image convertors (for SSE optimization)
typedef ImageC<ByteT> DoubleImageCT2ByteImageCT_T(const ImageC< RealT> &Dat);
DoubleImageCT2ByteImageCT_T *DoubleImageCT2ByteImageCT_F = &DoubleImageCT2ByteImageCT_L;


  // Byte to double image.

  ImageC<RealT> ByteImageCT2DoubleImageCT(const ImageC<ByteT> &dat) {
    ImageC<RealT> ret(dat.Rectangle());
    for(Array2dIter2C<RealT,ByteT> it(ret,dat);it.IsElm();it.Next())
      it.Data1() = (RealT) it.Data2();
    return ret;
  }

  // Byte to int image.

  ImageC<IntT> ByteImageCT2IntImageCT(const ImageC<ByteT> &dat) {
    ImageC<IntT> ret(dat.Rectangle());
    for(Array2dIter2C<IntT,ByteT> it(ret,dat);it.IsElm();it.Next())
      it.Data1() = (IntT) it.Data2();
    return ret;
  }

  // Int to double image.

  ImageC<RealT> IntImageCT2DoubleImageCT(const ImageC<IntT> &dat)   {
    ImageC<RealT> ret(dat.Rectangle());
    for(Array2dIter2C<RealT,IntT> it(ret,dat);it.IsElm();it.Next())
      it.Data1() = (RealT) it.Data2();
    return ret;
  }


  // Byte grey level to colour image.

  ImageC<ByteRGBValueC> ByteImageCT2ByteRGBImageCT(const ImageC<ByteT> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteRGBValueC,ByteT> it(ret,dat);it.IsElm();it.Next())
      it.Data1() = ByteRGBValueC(it.Data2(),it.Data2(),it.Data2());
    return ret;
  }

  // Byte grey level to byte YUV colour image.

  ImageC<ByteYUVValueC> ByteImageCT2ByteYUVImageCT(const ImageC<ByteT> &dat) {
    ImageC<ByteYUVValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteYUVValueC,ByteT> it(ret,dat);it.IsElm();it.Next())
      it.Data1() = ByteYUVValueC(it.Data2(),0,0);
    return ret;
  }

  // Double -> Byte (clipped to fit)
  // This will clip, then round the double value (NOT floor!) to fit in a byte value 0 to 255.
  ImageC<ByteT> DoubleImageCT2ByteImageCT(const ImageC< RealT> &dat) {
    return DoubleImageCT2ByteImageCT_F(dat);
  }

}

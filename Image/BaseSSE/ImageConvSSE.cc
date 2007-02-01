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
//#include "Ravl/Array2dIter2.hh"
//#include "Ravl/Image/ByteRGBValue.hh"
//#include "Ravl/Image/ByteYUVValue.hh"
//#include "Ravl/Image/RealRGBValue.hh"
//#include "Ravl/Image/RealYUVValue.hh"
//#include "Ravl/Image/RGBcYUV.hh"

#include "Ravl/CPUID.hh"

#include <emmintrin.h>

namespace RavlImageN
{

static ImageC<ByteT> RealImage2ByteImage(const ImageC<RealT> &img)
{
  ImageC< ByteT> ret(img.Rectangle());

  //cout << "RealImage2ByteImage: Using SSE instructions." << endl;

  IntT off = img.Frame().Range1().Min().V();
  IntT len = img.Frame().Cols();

  for(BufferAccessIter2C<BufferAccessC<ByteT>,BufferAccessC<RealT> > it(ret,img);it;it++) {
    //it.Data1() = (it.Data2()>255.0) ? 255 : (it.Data2()<0.0) ? 0 : ((ByteT) (it.Data2() + 0.5));

    __m128d min = _mm_set1_pd (0);
    __m128d max = _mm_set1_pd (255);
    __m128d voff = _mm_set1_pd (0.5);
    ByteT *brs = &it.Data1()[off];
    ByteT *ber = &(brs[len&~1]);
    RealT *rrs = &it.Data2()[off];
    for(;brs < ber;) {
      __m128i ivs = _mm_cvttpd_epi32(_mm_max_pd (_mm_min_pd (_mm_add_pd (_mm_loadu_pd (rrs),voff),max),min));
      *(brs++) = (ByteT) _mm_cvtsi128_si32 (ivs);
      *(brs++) = (ByteT) _mm_cvtsi128_si32 ( _mm_shuffle_epi32(ivs,_MM_SHUFFLE (1,1,1,1)));
      rrs += 2;
    }
    if(len & 1) {
      __m128i ivs = _mm_cvttpd_epi32(_mm_max_pd (_mm_min_pd (_mm_load_sd (rrs),max),min));
      *brs = (ByteT) _mm_cvtsi128_si32 (ivs);
    }
  }

  return ret;
}

//magic trick which changes the usual image convertion behaviour
typedef ImageC<ByteT> DoubleImageCT2ByteImageCT_T(const ImageC< RealT> &Dat);
extern DoubleImageCT2ByteImageCT_T *DoubleImageCT2ByteImageCT_F;

static int SetNewFunctions()
{
  if(SSE2())
  {
    //cout << "ImageConvSSE: Using SSE instructions." << endl;
    DoubleImageCT2ByteImageCT_F = &RealImage2ByteImage;
  }
  else
  {
    //cout << "ImageConvSSE: CPU does not have SSE instructions." << endl;
  }
  return 1;
}

static int a = SetNewFunctions();


}

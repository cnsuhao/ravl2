// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Array2dIter2.hh"

namespace RavlImageN {
  
  ImageC<RealT> FloatTImageCT2RealImageCT(const ImageC<FloatT> &dat) {
    ImageC<RealT> ret(dat.Frame());
    for(Array2dIter2C<RealT,FloatT> it(ret,dat);it;it++)
      it.Data1() = (RealT) it.Data2();
    return ret;
  }
  //: FloatT -> RealT
  
  ImageC<FloatT> RealTImageCT2FloatImageCT(const ImageC<RealT> &dat) {
    ImageC<FloatT> ret(dat.Frame());
    for(Array2dIter2C<FloatT,RealT> it(ret,dat);it;it++)
      it.Data1() = (FloatT) it.Data2();
    return ret;
  }
  //: RealT -> FloatT
  
  ImageC<FloatT> ByteRGBImageCT2FloatImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<FloatT> ret(dat.Frame());
    for(Array2dIter2C<FloatT,ByteRGBValueC> it(ret,dat);it;it++)
      it.Data1() = (FloatT) ((FloatT) it.Data2().Red() + (FloatT) it.Data2().Green() + (FloatT) it.Data2().Blue()) / 3.0;
    return ret;
  }
  //: Byte Colour to float image.
  
}

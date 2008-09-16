// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlImage
//! file="Ravl/Image/Base/ImageConv5.cc"

#include "Ravl/Image/ByteYCbCrBT601Value.hh"
#include "Ravl/Image/UInt16YCbCrBT601Value.hh"
#include "Ravl/Image/ByteYCbCr422BT601Value.hh"
#include "Ravl/Image/UInt16YCbCr422BT601Value.hh"
#include "Ravl/Image/RGBValue.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Image.hh"

namespace RavlImageN {
  
  //: Convert an ByteYCbCrBT601ValueC to a byte value.
  
  ImageC<ByteT> YCbCrBT601Value8Image2ByteImage(const ImageC<ByteYCbCrBT601ValueC> &dat) {
    ImageC<ByteT> ret(dat.Rectangle()); 
    for(Array2dIter2C<ByteT,ByteYCbCrBT601ValueC> it(ret,dat);it;it++) 
      it.Data1() = it.Data2().Y();
    return ret;
  }
  
  //: Convert an UInt16YCbCrBT601ValueC to a UInt16T value.
  
  ImageC<UInt16T> UInt16YCbCrBT601ValueImage2UInt16Image(const ImageC<UInt16YCbCrBT601ValueC> &dat) {
    ImageC<UInt16T> ret(dat.Rectangle()); 
    for(Array2dIter2C<UInt16T,UInt16YCbCrBT601ValueC> it(ret,dat);it;it++) 
      it.Data1() = it.Data2().Y();
    return ret;
  }
  
  //: Convert an ByteYCbCrBT601ValueC to a UInt16YCbCrBT601ValueC value.
  
  ImageC<UInt16YCbCrBT601ValueC> YCbCrBT601Value8Image2UInt16YCbCrBT601ValueImage(const ImageC<ByteYCbCrBT601ValueC> &dat) {
    ImageC<UInt16YCbCrBT601ValueC> ret(dat.Rectangle()); 
    for(Array2dIter2C<UInt16YCbCrBT601ValueC,ByteYCbCrBT601ValueC> it(ret,dat);it;it++) 
      it.Data1() = it.Data2();
    return ret;
  }
  
  
  //: Convert YCbCrBT601 to RGB in floating point format.
  
  ImageC<RGBValueC<float> > YCbCrBT601ValueFloatImage2ImageRGBValueFloat(const ImageC<YCbCrBT601ValueC<float> > &dat) {
    ImageC<RGBValueC<float> > ret(dat.Rectangle());
    for(Array2dIter2C<RGBValueC<float>,YCbCrBT601ValueC<float> > it(ret,dat);it;it++) 
      YCbCrBT601Float2RGBFloat(it.Data1(),it.Data2());
    return ret;
  }
  
  //: Convert RGB to YCbCrBT601 in floating point format.
  
  ImageC<YCbCrBT601ValueC<float> > ImageRGBValueFloat2YCbCrBT601ValueFloatImage(const ImageC<RGBValueC<float> > &dat) {
    ImageC<YCbCrBT601ValueC<float> > ret(dat.Rectangle());
    for(Array2dIter2C<YCbCrBT601ValueC<float>,RGBValueC<float> > it(ret,dat);it;it++)
      RGBFloat2YCbCrBT601Float(it.Data1(),it.Data2());
    return ret;
  }
  
  ImageC<RGBValueC<float> > RealRGBImageCT2RGBImageCFloat(const ImageC<RealRGBValueC> & dat ) {
    ImageC<RGBValueC<float> > ret(dat.Rectangle());
    for(Array2dIter2C<RGBValueC<float>,RealRGBValueC > it(ret,dat);it;it++) 
      it.Data1() = it.Data2();
    return ret ;
  }
  
  ImageC<RealRGBValueC> RGBImageCFloat2RealRGBImageCT(const ImageC<RGBValueC<float> > & dat ) {
    ImageC<RealRGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<RealRGBValueC,RGBValueC<float> > it(ret,dat);it;it++) 
      it.Data1() = it.Data2();
    return ret ;
  }

  //: Convert YCbCrBT601 to RGB in byte point format.
  
  ImageC<ByteRGBValueC> ByteYCbCrBT601ValueImage2ByteRGBImage(const ImageC<ByteYCbCrBT601ValueC> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteRGBValueC,ByteYCbCrBT601ValueC > it(ret,dat);it;it++) 
      it.Data1() = it.Data2().ByteRGB();
    return ret ;
  }
  
  //: Convert byte RGB to YCbCrBT601.

  ImageC<ByteYCbCrBT601ValueC > ByteRGBImage2ByteYCbCrBT601ValueImage(const ImageC<ByteRGBValueC> &dat) {
    ImageC<ByteYCbCrBT601ValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteYCbCrBT601ValueC,ByteRGBValueC> it(ret,dat);it;it++) 
      it.Data1() = ByteYCbCrBT601ValueC(it.Data2());
    return ret ;
  }

  
}

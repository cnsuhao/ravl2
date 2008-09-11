// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlImage
//! file="Ravl/Image/Base/ImageConv5.cc"

#include "Ravl/Image/YCbCrBT601Value8.hh"
#include "Ravl/Image/YCbCrBT601Value16.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Image.hh"

namespace RavlImageN {
  
  //: Convert an YCbCrBT601Value8C to a byte value.
  
  ImageC<ByteT> YCbCrBT601Value8Image2ByteImage(const ImageC<YCbCrBT601Value8C> &dat) {
    ImageC<ByteT> ret(dat.Rectangle()); 
    for(Array2dIter2C<ByteT,YCbCrBT601Value8C> it(ret,dat);it;it++) 
      it.Data1() = it.Data2().Y();
    return ret;
  }
  
  //: Convert an YCbCrBT601Value16C to a UInt16T value.
  
  ImageC<UInt16T> YCbCrBT601Value16Image2UInt16Image(const ImageC<YCbCrBT601Value16C> &dat) {
    ImageC<UInt16T> ret(dat.Rectangle()); 
    for(Array2dIter2C<UInt16T,YCbCrBT601Value16C> it(ret,dat);it;it++) 
      it.Data1() = it.Data2().Y();
    return ret;
  }
  
  //: Convert an YCbCrBT601Value8C to a YCbCrBT601Value16C value.
  
  ImageC<YCbCrBT601Value16C> YCbCrBT601Value8Image2YCbCrBT601Value16Image(const ImageC<YCbCrBT601Value8C> &dat) {
    ImageC<YCbCrBT601Value16C> ret(dat.Rectangle()); 
    for(Array2dIter2C<YCbCrBT601Value16C,YCbCrBT601Value8C> it(ret,dat);it;it++) 
      it.Data1() = it.Data2();
    return ret;
  }

  
}

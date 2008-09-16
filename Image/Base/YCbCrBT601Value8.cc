// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlImage
//! file="Ravl/Image/Base/YCbCrBT601Value8.cc"

#include "Ravl/BinStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/YCbCrBT601Value8.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN {

  //: Conversion from byte RGB.
  
  YCbCrBT601Value8C::YCbCrBT601Value8C(const ByteRGBValueC &brgb)
  {
    const float R = brgb.Red();
    const float G = brgb.Green();
    const float B = brgb.Blue();
    this->data[0] = 16  + 1.0/256.0 * (   65.738  * R +  129.057  * G +  25.064  * B);
    this->data[1] = 128 + 1.0/256.0 * ( - 37.945  * R -   74.494  * G + 112.439  * B);
    this->data[2] = 128 + 1.0/256.0 * (  112.439  * R -   94.154  * G -  18.285  * B);
  }
  
  //: Conversion from floating point RGB.
  
  YCbCrBT601Value8C::YCbCrBT601Value8C(const RGBValueC<float> &brgb)
  {
    const float &R = brgb.Red();
    const float &G = brgb.Green();
    const float &B = brgb.Blue();
    
    this->data[0] = 16  + ( 65.481  * R + 128.553  * G +  24.966  * B);
    this->data[1] = 128 + (-37.797  * R -  74.203  * G + 112.0    * B);
    this->data[2] = 128 + (112.0    * R -  93.786  * G -  18.214  * B);
  }
  
  
  //: Convert to 8 bit RGB.
  
  ByteRGBValueC YCbCrBT601Value8C::ByteRGB() const {
#if 1
    double r = ( 298.082 * Y() + 408.583 * Cr()                  ) / 256.0 - 222.921;
    double g = ( 298.082 * Y() - 100.291 * Cb() - 208.120 * Cr() ) / 256.0 + 135.576;
    double b = ( 298.082 * Y() + 516.412 * Cb()                  ) / 256.0 - 276.836;
    std::cerr << "r=" << r << " g=" << g << " b=" << b <<"\n";
    return ByteRGBValueC(ClipRange(Round(r),0,255),
                         ClipRange(Round(g),0,255),
                         ClipRange(Round(b),0,255)
                         );
#endif
  }

  //: Convert to a floating point RGB value.
  
  RGBValueC<float> YCbCrBT601Value8C::FloatRGB() const {
    RGBValueC<float> ret;
    RGBFloat2YCbCrBT601Float(FloatYCbCr(),ret);
    return ret;
  }
  
  static TypeNameC type2(typeid(YCbCrBT601Value8C),"YCbCrBT601Value8C");
  
  ////////////////////////////////////////////////////////////
  // Accelerated IO routines...
  
  BinOStreamC &operator << (BinOStreamC &out,const ImageC<YCbCrBT601Value8C> &img) { 
    out << img.Rectangle();
    
    IntT width = img.Cols() * 3;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++) 
      out.OBuff((const char *) &(img[atrow][offset]),width);  
    return out;
  }
  
  BinIStreamC &operator >> (BinIStreamC &in,ImageC<YCbCrBT601Value8C> &img) { 
    ImageRectangleC rect;
    in >> rect;
    img = ImageC<YCbCrBT601Value8C>(rect);
    
    IntT width = img.Cols() * 3;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++) 
      in.IBuff((char *) &(img[atrow][offset]),width);  

    return in;
  }
  
  BinOStreamC &operator<<(BinOStreamC &out,const YCbCrBT601Value8C &img) {
    out << img.Y() << img.Cb() << img.Cr();
    return out;
  }
  //: Save pixel to binary stream
  
  BinIStreamC &operator>>(BinIStreamC &in,YCbCrBT601Value8C &img) {
    in >> img.Y() >> img.Cb() >> img.Cr();
    return in;
  }
  //: Load pixel from binary stream
  
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_YCBCRBT601VALUE8_HEADER
#define RAVL_YCBCRBT601VALUE8_HEADER 1
/////////////////////////////////////////////////////
//! file="Ravl/Image/Base/ByteYCbCrBT601Value.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.Pixel Types"

#include "Ravl/Image/YCbCrBT601Value.hh"
#include "Ravl/Stream.hh"

namespace RavlImageN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
#endif
  class ByteRGBValueC;
  
  //! userlevel=Normal
  //: Byte YCbCr value class.
  // See http://en.wikipedia.org/wiki/YCbCr for details.
  
  // Note this class's relationship with 16 bit values is special, when 
  // converting to 16 bit values they are multiplied by 256.
  
  class YCbCrBT601Value8C
    : public YCbCrBT601ValueC<UInt8T>
  {
  public:
    YCbCrBT601Value8C()
    {}
    //: Default constructor.
    // Creates an undefined value.
    
    YCbCrBT601Value8C(const UInt8T &y,const UInt8T &Cb,const UInt8T &Cr) 
      : YCbCrBT601ValueC<UInt8T>(y,Cb,Cr)
    {}
    //: Construct from component values.
    
    YCbCrBT601Value8C(const YCbCrBT601ValueC<float> &oth)
      : YCbCrBT601ValueC<UInt8T>(ClipRange(16.0  + oth[0]*256.0,0.0,255.0),
                                 ClipRange(128.0 + oth[1]*256.0,0.0,255.0),
                                 ClipRange(128.0 + oth[2]*256.0,0.0,255.0))
    {}
    //: Convert from floating point values.
    
    YCbCrBT601Value8C(UInt16T y,UInt16T b,UInt16T r)
      : YCbCrBT601ValueC<UInt8T>(y>>8,b>>8,r>>8)
    {}
    //: Construct from 16 bit components.
    
    YCbCrBT601Value8C(const TFVectorC<UInt8T,3> &v)
      : YCbCrBT601ValueC<UInt8T>(v)
    {}
    //: Constructor from base class.
    
    YCbCrBT601Value8C(const YCbCrBT601ValueC<UInt16T> &value)
      : YCbCrBT601ValueC<UInt8T>(value[0]>>8,
                                 value[1]>>8,
                                 value[2]>>8)
    {}
    //: Convert from 16 bit version.
    
    YCbCrBT601Value8C(const ByteRGBValueC &brgb);
    //: Conversion from byte RGB.
    
    YCbCrBT601Value8C(const RGBValueC<float> &brgb);
    //: Conversion from floating point RGB.
    
    YCbCrBT601ValueC<float> FloatYCbCr() const
    { return YCbCrBT601ValueC<float>(((float) data[0] -  16.0)/256.0,
                                     ((float) data[1] - 128.0)/256.0,
                                     ((float) data[2] - 128.0)/256.0 
                                     ); }
    //: Convert to floating point values.
    
    operator YCbCrBT601ValueC<UInt16T>() const
    { return YCbCrBT601ValueC<UInt16T>((UInt16T) data[0]<<8,
                                       (UInt16T) data[1]<<8,
                                       (UInt16T) data[2]<<8); 
    }
    //: Convert to 16 bit.
    
    ByteRGBValueC ByteRGB() const;
    //: Convert to 8 bit RGB.
    
    RGBValueC<float> FloatRGB() const;
    //: Convert to a floating point RGB value.
    
  };
  
  template<class DataT> class ImageC;

  BinOStreamC &operator<<(BinOStreamC &out,const ImageC<YCbCrBT601Value8C> &img);
  //: Save byte image to binary stream 
  
  BinIStreamC &operator>>(BinIStreamC &in,ImageC<YCbCrBT601Value8C> &img);  
  //: Load byte image from binary stream 
  
  BinOStreamC &operator<<(BinOStreamC &out,const YCbCrBT601Value8C &img);
  //: Save pixel to binary stream
  
  BinIStreamC &operator>>(BinIStreamC &in,YCbCrBT601Value8C &img);
  //: Load pixel from binary stream
  
}


namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  
  template<>
  struct NumericalTraitsC<RavlImageN::YCbCrBT601Value8C > {
    typedef RavlImageN::YCbCrBT601ValueC<Int32T> AccumT;    //: Type to use for accumulator, guarantee's at least 2x no bits for interger types.
    typedef RavlImageN::YCbCrBT601ValueC<RealT> RealAccumT; //: Type to use for a floating point accumulator.
    typedef RavlImageN::YCbCrBT601ValueC<Int64T> LongAccumT; //: Type to use for accumulators that can take large sums.(10000's of elements at least.)
  };
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_YCBCRVALUE8_HEADER
#define RAVL_YCBCRVALUE8_HEADER 1
/////////////////////////////////////////////////////
//! file="Ravl/Image/Base/ByteYCbCrValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.Pixel Types"

#include "Ravl/Image/YCbCrValue.hh"
#include "Ravl/Stream.hh"

namespace RavlImageN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
#endif
  
  //! userlevel=Normal
  //: Byte YCbCr value class.
  
  class YCbCrValue8C
    : public YCbCrValueC<UInt8T>
  {
  public:
    YCbCrValue8C()
    {}
    //: Default constructor.
    // Creates an undefined value.
    
    YCbCrValue8C(const UInt8T &y,const UInt8T &Cb,const UInt8T &Cr) {
      this->data[0] = y;
      this->data[1] = Cb;
      this->data[2] = Cr;
    }
    //: Construct from component values.
    
    YCbCrValue8C(const TFVectorC<UInt8T,3> &v)
      : YCbCrValueC<UInt8T>(v)
    {}
    //: Constructor from base class.
    
    template<class OCompT>
    YCbCrValue8C(const YCbCrValueC<OCompT> &oth) 
      : YCbCrValueC<UInt8T>(oth)
    {}
    //: Construct from another component type.
    
  };
  
  template<class DataT> class ImageC;

  BinOStreamC &operator<<(BinOStreamC &out,const ImageC<YCbCrValue8C> &img);
  //: Save byte image to binary stream 
  
  BinIStreamC &operator>>(BinIStreamC &in,ImageC<YCbCrValue8C> &img);  
  //: Load byte image from binary stream 
  
  BinOStreamC &operator<<(BinOStreamC &out,const YCbCrValue8C &img);
  //: Save pixel to binary stream
  
  BinIStreamC &operator>>(BinIStreamC &in,YCbCrValue8C &img);
  //: Load pixel from binary stream
  
}


namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  
  template<>
  struct NumericalTraitsC<RavlImageN::YCbCrValue8C > {
    typedef RavlImageN::YCbCrValueC<Int32T> AccumT;    //: Type to use for accumulator, guarantee's at least 2x no bits for interger types.
    typedef RavlImageN::YCbCrValueC<RealT> RealAccumT; //: Type to use for a floating point accumulator.
    typedef RavlImageN::YCbCrValueC<Int64T> LongAccumT; //: Type to use for accumulators that can take large sums.(10000's of elements at least.)
  };
}

#endif

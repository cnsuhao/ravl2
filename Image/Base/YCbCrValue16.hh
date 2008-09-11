// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_YCBCRVALUE16_HEADER
#define RAVL_YCBCRVALUE16_HEADER 1
/////////////////////////////////////////////////////
//! file="Ravl/Image/Base/ByteYCbCrValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.Pixel Types"

#include "Ravl/Image/YCbCrValue.hh"
#include "Ravl/Types.hh"
#include "Ravl/Stream.hh"

namespace RavlImageN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
#endif
  
  //! userlevel=Normal
  //: Byte YCbCr value class.
  
  class YCbCrValue16C
    : public YCbCrValueC<UInt16T>
  {
  public:
    YCbCrValue16C()
    {}
    //: Default constructor.
    // creates an undefined YCbCr pixel.
    
    YCbCrValue16C(UInt16T y,UInt16T b,UInt16T r)
      : YCbCrValueC<UInt16T>(y,b,r)
    {}
    //: Construct from components.
    
    template<class OCompT>
    YCbCrValue16C(const YCbCrValueC<OCompT> &oth) 
      : YCbCrValueC<UInt16T>(oth)
    {}
    //: Construct from another component type.
    
  };
  
  template<class DataT> class ImageC;
  
  BinOStreamC &operator<<(BinOStreamC &out,const ImageC<YCbCrValue16C> &img);
  //: Save byte image to binary stream 
  
  BinIStreamC &operator>>(BinIStreamC &in,ImageC<YCbCrValue16C> &img);  
  //: Load byte image from binary stream 
  
  BinOStreamC &operator<<(BinOStreamC &out,const YCbCrValue16C &img);
  //: Save pixel to binary stream
  
  BinIStreamC &operator>>(BinIStreamC &in,YCbCrValue16C &img);
  //: Load pixel from binary stream
  
}


namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  
  template<>
  struct NumericalTraitsC<RavlImageN::YCbCrValue16C > {
    typedef RavlImageN::YCbCrValueC<UInt32T> AccumT;    //: Type to use for accumulator, guarantee's at least 2x no bits for interger types.
    typedef RavlImageN::YCbCrValueC<RealT> RealAccumT; //: Type to use for a floating point accumulator.
    typedef RavlImageN::YCbCrValueC<UInt64T> LongAccumT; //: Type to use for accumulators that can take large sums.(10000's of elements at least.)
  };
}

#endif

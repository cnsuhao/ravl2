// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_YCBCRBT601VALUE16_HEADER
#define RAVL_YCBCRBT601VALUE16_HEADER 1
/////////////////////////////////////////////////////
//! file="Ravl/Image/Base/ByteYCbCrValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.Pixel Types"

#include "Ravl/Image/YCbCrBT601Value.hh"
#include "Ravl/Types.hh"
#include "Ravl/Stream.hh"

namespace RavlImageN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
#endif
  
  //! userlevel=Normal
  //: Byte YCbCr value class.
  
  class YCbCrBT601Value16C
    : public YCbCrBT601ValueC<UInt16T>
  {
  public:
    YCbCrBT601Value16C()
    {}
    //: Default constructor.
    // creates an undefined YCbCr pixel.
    
    YCbCrBT601Value16C(UInt16T y,UInt16T b,UInt16T r)
      : YCbCrBT601ValueC<UInt16T>(y,b,r)
    {}
    //: Construct from components.
    
    template<class OCompT>
    YCbCrBT601Value16C(const YCbCrBT601ValueC<OCompT> &oth) 
      : YCbCrBT601ValueC<UInt16T>(oth)
    {}
    //: Construct from another component type.
    
  };
  
  template<class DataT> class ImageC;
  
  BinOStreamC &operator<<(BinOStreamC &out,const ImageC<YCbCrBT601Value16C> &img);
  //: Save byte image to binary stream 
  
  BinIStreamC &operator>>(BinIStreamC &in,ImageC<YCbCrBT601Value16C> &img);  
  //: Load byte image from binary stream 
  
  BinOStreamC &operator<<(BinOStreamC &out,const YCbCrBT601Value16C &img);
  //: Save pixel to binary stream
  
  BinIStreamC &operator>>(BinIStreamC &in,YCbCrBT601Value16C &img);
  //: Load pixel from binary stream
  
}


namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  
  template<>
  struct NumericalTraitsC<RavlImageN::YCbCrBT601Value16C > {
    typedef RavlImageN::YCbCrBT601ValueC<UInt32T> AccumT;    //: Type to use for accumulator, guarantee's at least 2x no bits for interger types.
    typedef RavlImageN::YCbCrBT601ValueC<RealT> RealAccumT; //: Type to use for a floating point accumulator.
    typedef RavlImageN::YCbCrBT601ValueC<UInt64T> LongAccumT; //: Type to use for accumulators that can take large sums.(10000's of elements at least.)
  };
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DVSREALRGBVALUE_HEADER
#define RAVL_DVSREALRGBVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id: RealRGBValue.hh 5240 2005-12-06 17:16:50Z plugger $"
//! file="Ravl/Image/Base/RealRGBValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.API.Images.Pixel Types"

#include "Ravl/Image/RGBValue.hh"
#include "Ravl/Traits.hh"

namespace RavlImageN {
  
  class RealDVSYUVValueC;
  
  //: Real RGB value class.
  
  class RealDVSRGBValueC
    : public RGBValueC<RealT>
  {
  public:
    RealDVSRGBValueC()
    {}
    //: Default constructor.
    // creates an undefined RGB pixel.
    
    RealDVSRGBValueC(RealT r,RealT g, RealT b)
      : RGBValueC<RealT>(r,g,b)
    {}
    //: Construct from components.

    inline RealDVSRGBValueC(const RealYUVValueC &v);
    //: Convert from a YUV pixel.
    // Implementation in Ravl/Image/RGBcYUV.hh include
    // this header when needed.

    
    RealDVSRGBValueC(const RGBValueC<RealT> &oth)
      : RGBValueC<RealT>(oth)
    {}
    //: Base class constructor.
    
    RealDVSRGBValueC(const RGBValueC<ByteT> &oth)
      : RGBValueC<RealT>(oth.Red(),oth.Green(),oth.Blue())
    {}
    //: Construct from a byte RGB value.
    
    RealDVSRGBValueC(const TFVectorC<RealT,3> &oth)
      : RGBValueC<RealT>(oth)
    {}
    //: Base class constructor.
    
    
  };

}

namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  
  template<>
  struct NumericalTraitsC<RavlImageN::RealDVSRGBValueC> {
    typedef RavlImageN::RealDVSRGBValueC AccumT;    //: Type to use for accumulator, guarantee's at least 2x no bits for interger types.
    typedef RavlImageN::RealDVSRGBValueC RealAccumT; //: Type to use for a floating point accumulator.
    typedef RavlImageN::RealDVSRGBValueC LongAccumT; //: Type to use for accumulators that can take large sums.(10000's of elements at least.)
  };
}

#endif

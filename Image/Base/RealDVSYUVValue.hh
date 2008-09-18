// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDVSREALYUVVALUE_HEADER
#define RAVLDVSREALYUVVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id: RealYUVValue.hh 5240 2005-12-06 17:16:50Z plugger $"
//! file="Ravl/Image/Base/RealDVSYUVValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Simon Ennis"
//! date="24/01/2001"
//! docentry="Ravl.API.Images.Pixel Types.YCbCr"

#include "Ravl/Image/YUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"

namespace RavlImageN {
  
  using namespace RavlN;

  class RealDVSRGBValueC;
  
  //! userlevel=Normal
  //: Real YUV value class.
  
  class RealDVSYUVValueC
    : public YUVValueC<RealT>
  {
  public:
    RealDVSYUVValueC()
      {}
    //: Default constructor.
    // creates an undefined YUV pixel.
    
    RealDVSYUVValueC(RealT y,RealT u, RealT v)
      : YUVValueC<RealT>(y,u,v)
      {}
    //: Construct from components.

    inline RealDVSYUVValueC(const RealRGBValueC &v);
    //: Construct from a RGB pixel.
    
    RealDVSYUVValueC(const YUVValueC<RealT> &oth)
      : YUVValueC<RealT>(oth)
      {}
    //: Default constructor.
    // creates an undefined YUV pixel.

  };

}


namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  
  template<>
  struct NumericalTraitsC<RavlImageN::RealDVSYUVValueC > {
    typedef RavlImageN::RealDVSYUVValueC AccumT;    //: Type to use for accumulator, guarantee's at least 2x no bits for interger types.
    typedef RavlImageN::RealDVSYUVValueC RealAccumT; //: Type to use for a floating point accumulator.
    typedef RavlImageN::RealDVSYUVValueC LongAccumT; //: Type to use for accumulators that can take large sums.(10000's of elements at least.)
  };
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLFVECTOR_HEADER
#define RAVLFVECTOR_HEADER 1
//////////////////////////////////////////////////
//! rcsid=$Id$
//! file="Ravl/Math/LinearAlgebra/FixedSize/FVector.hh"
//! lib=RavlMath
//! userlevel=Develop
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Geometry"

#include "Ravl/TFVector.hh"
#include "Ravl/StdMath.hh"

namespace RavlN {
  
  template <unsigned int N>
  class TFPointC;
  
  //! userlevel=Advanced
  //: Real Vector with templated size
  
  template<unsigned int N>
  class FVectorC
    : public TFVectorC<RealT,N>
  {
  public:
    FVectorC()
      {}
    //: Default constructor.
    
    FVectorC(const TFVectorC<RealT,N> &oth)
      : TFVectorC<RealT,N>(oth)
      {}
    //: Base constructor.
    
    explicit FVectorC(const TFPointC<N> &oth)
      : TFVectorC<RealT,N>(oth)
      {}
    //: Base constructor.

    bool IsReal() const {
      for(UIntT i = 0;i < N;i++)
	if(IsNan(data[i]) || IsInf(data[i]))
	  return false;
      return true;
    }
    //: Test if matrix only contains real values.
    // This will return false if either nan's (Not an number) 
    // or infinite values are found.
    
    RealT Magnitude() const 
      { return Sqrt(SumSqr()); }
    //: Calculate the magintude of the vector.
    
  };
}

#endif

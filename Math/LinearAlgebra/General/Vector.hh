// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_VECTOR_HEADER
#define RAVL_VECTOR_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/General/Vector.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Linear Algebra"

#include "Ravl/TVector.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Vector of real values.
  
  class VectorC
    : public TVectorC<RealT>
  {
  public:
    VectorC()
    {}
    //: Default constructor.
    
    explicit VectorC(UIntT size)
      : TVectorC<RealT>(size)
    {}
    //: Constructor.
    // Create a vector of 'size' elements
    
    VectorC(const TVectorC<RealT> &oth)
      : TVectorC<RealT>(oth)
    {}
    //: Base class constructor.
    
    VectorC(const SArray1dC<RealT> &oth)
      : TVectorC<RealT>(oth)
    {}
    //: Base class constructor.

    VectorC(const Slice1dC<RealT> &oth,bool alwaysCopy = true)
      : TVectorC<RealT>(oth,alwaysCopy)
    {}
    //: Construct from a slice 
    
    template<unsigned int N>
    inline VectorC(const TFVectorC<RealT,N> &dat) 
      : TVectorC<RealT>(dat)
    {}
    //: Construct from a fixed size array.
    
    VectorC(RealT v1,RealT v2)
      : TVectorC<RealT>(2)
    {
      (*this)[0] = v1;
      (*this)[1] = v2;
    }
    //: Create a vector with two real values.

    VectorC(RealT v1,RealT v2,RealT v3)
      : TVectorC<RealT>(3)
    {
      (*this)[0] = v1;
      (*this)[1] = v2;
      (*this)[2] = v3;
    }
    //: Create a vector with three real values.

    VectorC(RealT v1,RealT v2,RealT v3,RealT v4)
      : TVectorC<RealT>(4)
    {
      (*this)[0] = v1;
      (*this)[1] = v2;
      (*this)[2] = v3;
      (*this)[3] = v4;
    }
    //: Create a vector with four real values.
    
    VectorC(RealT v1,RealT v2,RealT v3,RealT v4,RealT v5)
      : TVectorC<RealT>(5)
    {
      (*this)[0] = v1;
      (*this)[1] = v2;
      (*this)[2] = v3;
      (*this)[3] = v4;
      (*this)[4] = v5;
    }
    //: Create a vector with five real values.

    VectorC(RealT v1,RealT v2,RealT v3,RealT v4,RealT v5,RealT v6)
      : TVectorC<RealT>(6)
    {
      (*this)[0] = v1;
      (*this)[1] = v2;
      (*this)[2] = v3;
      (*this)[3] = v4;
      (*this)[4] = v5;
      (*this)[5] = v6;
    }
    //: Create a vector with six real values.

    
    bool IsReal() const;
    //: Test if vector only contains real values.
    // This will return false if either nan's (Not an number) 
    // or infinite values are found.
    
  };
  
}

#endif

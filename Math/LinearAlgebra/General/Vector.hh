// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLVECTOR_HEADER
#define RAVLVECTOR_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/Vector.hh"
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
    
    VectorC(UIntT size)
      : TVectorC<RealT>(size)
      {}
    //: Default constructor.

    VectorC(const TVectorC<RealT> &oth)
      : TVectorC<RealT>(oth)
      {}
    //: Base class constructor.

    VectorC(const SArray1dC<RealT> &oth)
      : TVectorC<RealT>(oth)
      {}
    //: Base class constructor.
    
    bool IsReal() const;
    //: Test if vector only contains real values.
    // This will return false if either nan's (Not an number) 
    // or infinite values are found.
    
  };
  
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RavlRandomGauss_HEADER
#define RavlRandomGauss_HEADER 1
///////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! file="Ravl/Core/Math/RandomGauss.hh"
//! lib=RavlCore
//! author="Andrew Stoddart"
//! date="26/04/1995"
//! docentry="Ravl.Core.Math"

#include "Ravl/Random.hh"

namespace RavlN {  
  
  //! userlevel=Normal
  //: Generate random number with a gaussian distribution.
  
  class RandomGaussC {
  public:
    RandomGaussC();
    //: Default.

    float Generate(RandomSeedT &seed);
    //: Generate with external seed.
    
    float Generate() {
      return Generate(seed);
    }
    //: Generate number with internal seed.
    
  protected:
    RandomSeedT seed;
    bool iset;
    float gset;
    float gasdev;
  };

};


#endif

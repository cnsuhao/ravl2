// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RANDOM_HEADER
#define RAVL_RANDOM_HEADER 1
///////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! file="Ravl/Core/Math/Random.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Core.Math"

#include "Ravl/Types.hh"
#include "Ravl/config.h"
#include <stdlib.h>

extern "C" {
  extern long nrand48(unsigned short *);
  extern double erand48(unsigned short *);
};

namespace RavlN {  
  
  typedef unsigned short RandomSeedT[3];
  //: Seed for random number
  
  const long int RandomIntMaxValue = ((UIntT) (1 << 31))-1;
  
  inline long int RandomInt(RandomSeedT & idum) 
  { return nrand48(idum); }
  //: Returns an integer between 0 and RandomIntMaxValue.
  
  long int RandomInt();
  //: Returns an integer between 0 and RandomIntMaxValue.
  
  inline double Random1(RandomSeedT & idum)
  { return  erand48(idum); }
  //: Returns a random number between 0 and 1 with a uniform distribution.
  
  double Random1();
  //: Returns a random number between 0 and 1 with a uniform distribution.
  
  float  RandomGauss();
  //: Returns a Gaussian distributed zero mean random
  //: number with variance 1.0.
  // RandomGauss is based on Random1.
  
  void RandomSeedDefault(int i);
  //: Set the seed for the default random number generator.
}

#endif

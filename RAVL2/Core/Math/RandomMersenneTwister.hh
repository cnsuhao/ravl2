// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// file-header-ends-here
#ifndef RAVL_RANDOMMERSENNETWISTER_HEADER
#define RAVL_RANDOMMERSENNETWISTER_HEADER 1
///////////////////////////////////////////////////////////////////////////
//! rcsid="$Id: RandomMersenneTwister.hh 5437 2006-04-05 11:09:32Z ees1wc $"
//! userlevel=Normal
//! file="Ravl/Core/Math/RandomMersenneTwister.hh"
//! lib=RavlCore
//! author="James Smith"
//! date="31/10/2002"
//! docentry="Ravl.API.Math.Random Numbers"
//! license=own

#include "Ravl/Types.hh"
#include "Ravl/config.h"

namespace RavlN {  
  

  //: Mersenne Twister Random number generator
  // http://www.math.keio.ac.jp/~matumoto/emt.html. 
  // This generator is not cryptographically secure. 
  // You need to use a one-way (or hash) function to obtain 
  // a secure random sequence.

  // This class is based on the standard Mersenne Twister 
  // implemention my19937ar.c - copyright notice follows

  // <PRE>
  // A C-program for MT19937, with initialization improved 2002/1/26.
  // Coded by Takuji Nishimura and Makoto Matsumoto.
  // 
  // Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
  // All rights reserved.                          
  // </PRE>

  class RandomMersenneTwisterC {
  public:

    RandomMersenneTwisterC();
    //: Constructor

    RandomMersenneTwisterC(unsigned long seed);
    //: Constructor with seed

    void Seed(unsigned long seed);
    //: Initialises the random number generator with the passed seed

    void Seed(unsigned long init_key[], unsigned long key_length);
    //: Initialises the random number generator with the passed array
    // This is for using seed values greater then can be stored in an unsigned long

    unsigned long UInt();
    //: Returns an unsigned integer uniformly distributed between 0 and RandomIntMaxValue

    long Int();
    //: Returns a signed integer

    double Double();
    //: Returns a double uniformly distributed between 0 and 1

    double Double2();
    //: Alternative double generation function
    // Returns a double uniformly distributed between 0 and 1

    double Double3();
    //: Alternative double generation function
    // Returns a double uniformly distributed between 0 and 1

    double Double53();
    //: Returns a 53-bit precision double uniformly distributed between 0 and 1
    
  protected:

    unsigned long mt[624]; /* the array for the state vector  */
    unsigned long mti; /* mti==N+1 means mt[N] is not initialized */

  };

}

#endif

//! rcsid="$Id$"

#include "Ravl/Math.hh"


namespace RavlN {
  
  // The following is code is based on an implementation 
  // found in the ccmath library.
  
  RealT Pow(RealT y,int n) { 
    RealT s=1.; 
    unsigned m,j; 
    if(!n)
      return s;
    if(n < 0) { 
      m = -n; 
      y = 1. / y;
    } else 
      m = n;
    for(j = 1; j <= m ;j <<= 1) { 
      if(j & m) 
	s *= y; 
      y *= y;
    }
    return s;
  }
  
}

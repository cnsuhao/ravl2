// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// IAPS - Image analysis program system
// 
// File name  : RandomGs.cc
// Description: 
// Last change: 26.04.1995
// Author     : Andrew Stoddart (A.Stoddart@ee.surrey.ac.uk)
// Libraries  : Mstd
// ------------------------------------------------------------------------
//
// Modifications:
//
//
//
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Math/RandomGs.cc"

#include "Ravl/StdMath.hh" // sqrt(), log()
#include "Ravl/RandomGauss.hh"
#include "Ravl/MTLocks.hh"

namespace RavlN {
  
  extern RandomSeedT randomIdum;
  // The default variable of generators.

  static RandomGaussC rg;
  
  //: Default.
  
  RandomGaussC::RandomGaussC() {
    MTWriteLockC lock(1);
    //seed = ?;
  }
  
  //: Generate the next value.
  
  float RandomGaussC::Generate(RandomSeedT &seed) {
    float v1,v2,fac,r;
    if (iset==0) {
      do {
	v1=(float)(2.0 * Random1(seed) - 1.0);
	v2=(float)(2.0 * Random1(seed) - 1.0);
	r=v1*v1 + v2*v2;
      } while (r>=1.0);
      fac=(float)sqrt(-2.0 * log(r)/r);
      gset=v1 * fac;
      gasdev=v2 * fac;
      iset=1;
      return gasdev;
    }
    iset=0;
    return gset;
  }
  
  float  RandomGauss() {
    MTWriteLockC lock(1);
    return rg.Generate(randomIdum);
  }

  
}




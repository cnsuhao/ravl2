// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/ScalMath.hh"
#include "Ravl/StdConst.hh"
#include <iostream.h>

namespace RavlN {
#if !RAVL_NEW_ANSI_CXX_DRAFT
  const IntT RavlPreComputedFactorialSize = 32; 
#endif
  
#if RAVL_NEW_ANSI_CXX_DRAFT
  RealT RavlPreComputedFactorial[RavlPreComputedFactorialSize]
  ={1.0, 1.0, 2.0, 6.0, 24.0, 120.0};
  // The table of precomputed factorials.   
#else
  // FIXME :- Do better ?? 
  RealT RavlPreComputedFactorial[32]
  ={1.0, 1.0, 2.0, 6.0, 24.0, 120.0};
#endif

  
  static IntT Init() {
    // Initialization of the table of precomputed factorials.
    RavlPreComputedFactorial[0] = 1.0;
    for (IntT i = 1; i < RavlPreComputedFactorialSize; i++)
      RavlPreComputedFactorial[i] = RavlPreComputedFactorial[i-1] * RealT(i);  
    return 0;
  }
  
  static IntT init = Init();
  
}




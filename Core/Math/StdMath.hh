// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_StdMath_HEADER
#define RAVL_StdMath_HEADER 1
///////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Math/StdMath.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Radek Marik"
//! docentry="Ravl.Core.Math"
//! rcsid="$Id$"
//! date="20/11/95"

#include "Ravl/config.h"
#include "Ravl/Math.hh"
#include "Ravl/StdConst.hh"

#if RAVL_HAVE_FLOAT_H
#include <float.h>
#endif
#if RAVL_HAVE_NAN_H
#include <nan.h>
#endif
#if RAVL_HAVE_IEEEFP_H
#include <ieeefp.h>
#endif

#if defined(__linux__) || defined(__sol2__) || defined(__sgi__)
extern "C" {
  double hypot(double a,double b);
};
#endif

#if defined(__sol2__)
extern "C" {
  double erf __P((double)); // not in standard <math.h> file
  double erfc __P((double)); // not in standard <math.h> file
}
#endif
#if defined(__linux__)
extern "C" {
  double erf(double x); // not in standard <math.h> file
  double erfc(double x); // not in standard <math.h> file
}
#endif

#if defined(__sgi__) 
// These are need because of problems with
// defining _POSIX_C_SOURCE=... on the SGI
extern double erf (double x);
extern double erfc (double x);
#endif

//: The Ravl namespace.

namespace RavlN {
  
  inline RealT Cbrt(RealT r) {
#if defined(BORLAND) || defined(GNU) || defined(__sgiCC__) 
    return pow(r,1.0/3.0);
#elif !defined VISUAL_CPP
    return cbrt(r);
#else
    RealT dem = 3.0;  // Get a compile warning unless we do this
    return pow(r, 1.0/dem);
#endif
  }
  //: Returns the cube root of 'x'.
  
#if !defined(VISUAL_CPP) && !defined(__cygwin__)
  // FIXME:- We have to sort this out..
  
  inline RealT Erf(RealT x)
  { return erf(x); }
  //: Returns the error function of x. Erf(x) = 2/sqrt(pi)*integral from 0 to x of exp(-t*t) dt.
  
  inline RealT Erfc(RealT x)
  { return erfc(x); }
  //: Returns 1.0 - Erf(x). (Use when x is large)
#endif
  
  inline RealT Log2(RealT r) {
    RavlAssertMsg(r > 0.0,"Log2(RealT r): Can't take log of zero or negative number.");
    return log(r)/RavlConstN::ln2;
  }
  //: Returns logarithm to base 2.
  
  inline bool IsPow2(IntT i) {
    IntT j = 1;
    while(j < i) 
      j *= 2;
    return i==j;
  }
  //: Is interger power of 2 ?
  // Returns true if 'i' is a power of 2.
    
  inline bool IsInf(RealT i) {
#if defined(__linux__) 
    return isinf(i);
#else
#if defined(VISUAL_CPP)
    return !_finite(i);
#else
    return !finite(i);
#endif
#endif
  }
  //: Is infinit ?
  
  inline bool IsPInf(RealT i)
  { return ((bool) (i > 0)) && IsInf(i); }
  //: Is positive infinity ?
  
  inline bool IsNInf(RealT i)
  { return ((bool) (i < 0)) && IsInf(i); }
  //: Is negative infinity ?
  
  inline bool IsNan(RealT i) {
#if defined(VISUAL_CPP)
    if(_isnan(i)==0) return false;
    return true;
#else
#if defined(__sgi__) || defined(__sol2__)
    return isnand(i);
#else
    return isnan(i);
#endif
#endif
  }
  //: Is Not A Number ?
  
  inline RealT  Radians(RealT angle)
  { return angle/180.0 * RavlConstN::pi; }
  //: Convert angle from degrees to radians.
  
  inline RealT Degrees(RealT angle)
  { return angle/RavlConstN::pi * 180.0; }
  //: Convert angle from radians to degrees.
  
  
}  
#endif


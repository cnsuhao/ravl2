// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_HEADER
#define RAVLMATH_HEADER 1
////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Math"
//! file="Ravl/Core/Base/Math.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"

// This file contains some alias for basic maths functions.
// for a more complete set use Ravl/StdMath.hh

#include "Ravl/config.h"
#include "Ravl/Types.hh"
#include "Ravl/Assert.hh"
#include <math.h>

#if defined(__linux__) || defined(__sol2__) || defined(__sgi__)
extern "C" {
  double hypot(double a,double b);
};
#endif

//: Ravl namespace.

namespace RavlN {
  // Basic algebraic functions
  // -------------------------

  template<class DataT>
  inline DataT Abs(const DataT &a)
  { return (a>=0) ? a : -a; }
  //: Returns the absolute value of 'a'
  
  template<class DataT>
  inline DataT Sign(const DataT &a)
  { return (a>=0) ? 1 : -1; }
  //: Returns the sign of the real number 'a'.
  
  inline RealT Sign(RealT a, RealT b)
  { return b >= 0.0 ? Abs(a) : - Abs(a); }
  //: Returns the value 'a' with a sign of 'b'.
  
  inline IntT Round(RealT x)
  { return (x >= 0) ? (IntT) (x+0.5) : (IntT) (x-0.5); }
  //: Returns the value x rounded to the nearest integer.
  
  inline IntT Floor(RealT x)
  { return (IntT) floor(x); }
  //: Returns the greatest integral  value  less  than  or equal  to  'x'.
  
  template<class DataT>
  inline void SetToZero(DataT &dat)
  { dat = 0; } 
  //: Set 'dat' to zero.
  // In cases where this doesn't work, a specialised version
  // should be provided.

  template<class DataT>
  inline DataT Sqr(const DataT &x)
  { return x * x; }
  //: Returns the square of 'x'.

  inline RealT Sqrt(RealT x) {
    RavlAssertMsg(x >= 0,"Sqrt(RealT r): Square root of negative number. ");
    return sqrt(x);
  }
  //: Returns the square root of 'x'.

  template<class DataT>
  inline DataT Min(const DataT &a,const DataT &b)
  { return a < b ? a : b; }
  //: Returns the smaller value from 'a' and 'b'.
  
  template<class DataT>
  inline DataT Max(const DataT &a,const DataT &b)
  { return a > b ? a : b; }
  //: Returns the bigger value from 'a' and 'b'.

  inline RealT Log(RealT r) {
    RavlAssertMsg(r > 0.0,"Log(RealT r): Can't take log of zero or negative number.");
    return log(r);
  }
  //: Returns log(r).
  
  inline RealT Pow(RealT x, RealT y)
  { return pow(x,y); }
  //: Returns 'x' raised to the power 'y'.
  
  RealT Pow(RealT x, IntT y);
  //: Returns 'x' raised to the power 'y' where y is an integer..
  
  inline RealT Exp(RealT r){
#if !defined VISUAL_CPP
    return r < -30.0 ? 0.0 : exp(r);
#else
    return exp(r);
#endif
  }
  //: Returns safe exp(r).

  inline IntT ILog2(IntT i) {
    IntT mex = 0;
    while((i/=2) != 0) mex++;
    return(mex);
  }
  //: Interger Log 2
  // "i" = 2 ^ "mex", "mex" = ?
  
  inline RealT Sin(RealT x)
  { return sin(x); }
  //: Returns the sine of 'x'.
  
  inline RealT ASin(RealT x) { 
    RavlAssertMsg(x >= -1 && x <= 1,"ASin(RealT r): Value out range, r < -1 or r > 1. ");
    return asin(x); 
  }
  //: Returns the arc sine of 'x'.
  
  inline RealT Cos(RealT x)
  { return cos(x); }
  //: Returns the cosine of 'x'.
  
  inline RealT ACos(RealT x) { 
    RavlAssertMsg(x >= -1 && x <= 1,"ACos(RealT r): Value out range, r < -1 or r > 1. ");
    return acos(x); 
  }
  //: Returns the arc cosine of 'x'.
  
  inline RealT ATan(RealT x)
  { return atan(x); }
  //: Returns the arc tangent of 'x' in the range -pi/2 .. +pi/2.
  
  inline RealT ATan2(RealT y, RealT x)
  { return atan2(y,x); }
  //: Returns the arc tangent of 'y/x' in the range -pi .. +pi.
  
  inline RealT Sinh(RealT x)
  { return sinh(x); }
  //: Returns the sine of 'x'.
  
  inline RealT Cosh(RealT x)
  { return cosh(x); }
  //: Returns the cosine of 'x'.
  
  inline RealT Pythag(RealT a, RealT b) {
#if RAVL_HAVE_HYPOT
    return hypot(a,b);
#else
    RealT absA = Abs(a);
    RealT absB = Abs(b);
    return absA > absB 
      ? absA * Sqrt(1.0 + Sqr(absB/absA)) 
      : absB!=0
      ? absB * Sqrt(1.0 + Sqr(absA/absB))
      : RealT(0.0);
#endif
  }
  //: Computes sqrt(sqr(a)+sqr(b)) without destructive overflow or underflow.

  inline bool IsSmall(RealT a,RealT norm,RealT isSmall =1e-8)
  { return ( (Abs(a/norm)) < isSmall );  }
  //: Is a small relative to 'norm' ?
  // This code used to be as follows, but it was changed because
  // using x==y for floats is a bad idea, and eventually caused
  // trouble on Visual C++.  (AJS)
  
  //  float b = (float) ((double) Abs(a) + norm);
  //  return (b == (float) norm);

  inline bool IsAlmostZero(RealT v,RealT threshold = 1.0e-12) 
  { return Abs(v) < threshold; }
  //: Test is a real value is near zero.
  // Use with care. 

  template<class DataT>
  inline  DataT MinComponent(DataT a)
  { return a; }
  //: Returns the smallest component from 'a'.
  
  template<class DataT>
  inline DataT MaxComponent(DataT a)
  { return a; }
  //: Returns the Biggest component from 'a'.
  
  template<class DataT>
  inline  DataT ScaleMin(DataT a,DataT b)
  { return MinComponent(a) < MinComponent(b) ? a : b; }
  //: Returns the argument which has the smallest component from 'a' and 'b'.
  // In a manner suitable for scaling operations.
  
  template<class DataT>
  inline DataT ScaleMax(DataT a,DataT b)
  { return MaxComponent(a) > MaxComponent(b) ? a : b; }
  //: Returns the argument which has the largest component from 'a' and 'b'.
  // In a manner suitable for scaling operations.  

}


#endif

#ifndef USEFULFN_HH
#define USEFULFN_HH
////////////////////////////////////////////////////////////////////////
//! file="amma/StdType/Math/UsefulFn.hh"
//! lib=Mmath
//! userlevel=Normal
//! author="Radek Marik"
//! docentry="Ravl.Math"
//! rcsid="$Id$"
//! date="06/08/95"

#include "amma/StdType.hh"

// mathematical functions
// ======================

inline
RealT Radian(RealT angle);
// conversion from degree into radian

inline
RealT Degree(RealT angle);
// conversion from radian into degree

inline
RealT Step(RealT a);
// step function
// return 1 if a>=0 otherwise 0

inline
RealT RSqr(RealT r);
// return r*r

IntT ILog2(IntT i);
// "i" = 2 ^ "mex", "mex" = ?

inline RealT PowRI(RealT r, IntT n);
// Returns r^n.

// useful function
// ===============

#ifndef GNU
// GNU C++ 2.4.5 is crazy

template <class T>
inline
void AMMA_Swap(T & t1, T & t2);
// swap contents of t1 and t2

template <class T>
inline
T AMMA_Max(const T t1, const T t2);
// returns the greater item of t1 and t2

template <class T>
inline
T AMMA_Min(const T t1, const T t2);
// returns the less item of t1 and t2

#endif

inline
IntT Maximum(IntT a, IntT b);
// Returns the biggest number from 'a' and 'b'.

inline
IntT Minimum(IntT a, IntT b);
// Returns the smallest number from 'a' and'b'.

inline
RealT Maximum(RealT a, RealT b);
// Returns the biggest number from 'a' and 'b'.

inline
RealT Minimum(RealT a, RealT b);
// Returns the smallest number from 'a' and 'b'.

inline
IntT Maximum(IntT a, IntT b, IntT c);
// Returns the biggest number from 'a', 'b', and 'c'.

inline
IntT Minimum(IntT a, IntT b, IntT c);
// Returns the smallest number from 'a', 'b', and 'c'.

inline
RealT Maximum(RealT a, RealT b, RealT c);
// Returns the biggest number from 'a', 'b', and 'c'.

inline
RealT Minimum(RealT a, RealT b, RealT c);
// Returns the smallest number from 'a', 'b', and 'c'.


// =================================================================
// *********** TEMPLATES implementation ****************************
// =================================================================

template <class T>
inline 
void 
AMMA_Swap(T & t1, T & t2)
//==================
{
  T t = t1;
  t1 = t2;
  t2 = t;
}

template <class T>
inline
T 
AMMA_Max(const T t1, const T t2)
//=========================
{
  return((t1>=t2) ? t1: t2);
}

template <class T>
inline
T 
AMMA_Min(const T t1, const T t2)
//=========================
{
  return((t1<=t2) ? t1: t2);
}

/*
#ifdef GNU
// HELP to GNU C++
#if __GNUC_MINOR__ >= 6
extern template void AMMA_Swap(IntT, IntT); // force instantiation
extern template IntT AMMA_Max(const IntT, const IntT); // force instantiation
extern template IntT AMMA_Min(const IntT, const IntT); // force instantiation
extern template void AMMA_Swap(RealT, RealT); // force instantiation
extern template RealT AMMA_Max(const RealT, const RealT); // force instantiation
extern template RealT AMMA_Min(const RealT, const RealT); // force instantiation
#else
extern inline void dummy () // will not be emitted
{
  AMMA_Swap(0, 1);
  AMMA_Max(0, 1);
  AMMA_Min(0, 1);
  AMMA_Swap(0.0, 1.0);
  AMMA_Max(0.0, 1.0);
  AMMA_Min(0.0, 1.0);
}
#endif
#endif
*/

#include "amma/Error.hh"
#include "amma/StdConst.hh"

//====================================================================
//======= UsefulFn ===================================================
//====================================================================

inline
RealT 
Radian(RealT angle)
//=================
{ return angle/180.0 * StdConstC::pi; }

inline
RealT Degree(RealT angle)
//=======================
{ return angle/StdConstC::pi * 180.0; }

inline
RealT Step(RealT a)
//=================
{ return  a>=0.0 ? 1.0 : 0.0; }

inline
RealT 
RSqr(RealT r)
//===========
{ return r*r; }

inline
RealT 
PowRI(RealT r, IntT n)
//====================
// a better solution is: sum of r, r^2, r^4, ... according to bits in n
{
  if (n==0) return 1.0;
  RealT res = (n>0) ? r : 1.0/r;
  while(--n > 0) 
    res *= r;
  return res;
}

inline
IntT 
Maximum(IntT a, IntT b)
//=====================
{ return (a>=b) ?  a : b; }

inline
IntT 
Minimum(IntT a, IntT b)
//=====================
{ return (a<=b) ?  a : b; }

inline
RealT 
Maximum(RealT a, RealT b)
//=======================
{ return (a>=b) ?  a : b; }

inline
RealT 
Minimum(RealT a, RealT b)
//=======================
{ return (a<=b) ?  a : b; }

inline
IntT 
Maximum(IntT a, IntT b, IntT c)
//=============================
{ return Maximum(Maximum(a,b), c); }

inline
IntT 
Minimum(IntT a, IntT b, IntT c)
//=============================
{ return Minimum(Minimum(a,b), c); }

inline
RealT 
Maximum(RealT a, RealT b, RealT c)
//================================
{ return Maximum(Maximum(a,b), c); }

inline
RealT 
Minimum(RealT a, RealT b, RealT c)
//================================
{ return Minimum(Minimum(a,b), c); }

#endif
// IAPS - Image analysis program system. 
// End of include file UsefulFn.hh









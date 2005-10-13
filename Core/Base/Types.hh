// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TYPES_HEADER
#define RAVL_TYPES_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Misc"
//! file="Ravl/Core/Base/Types.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/config.h"
// Common forward declarations

#if RAVL_HAVE_STREAMASCLASS
#if RAVL_HAVE_STDNAMESPACE
namespace std {
  class istream;
  class ostream;
}
#else
class istream;
class ostream;
#endif
#else
#if RAVL_HAVE_ANSICPPHEADERS
#include <iosfwd>
#else
#include <iostream.h>
#endif
#endif

//!maindoc=1
//: Ravl namespace
// This namespace contains all the core ravl functionality.

namespace RavlN {  
#if RAVL_HAVE_STDNAMESPACE
  using namespace std;
#endif  
  
  class BinOStreamC;
  class BinIStreamC;

  typedef int IntT;
  //: Integer of at least 32 bits
  
  typedef unsigned int UIntT;
  //: Unsigned Integer of at least 32 bits
  
  typedef double RealT;
  //: Real value of at least 64 bits.
  
  typedef float FloatT;
  //: Real value of at least 32 bits.
  
  typedef unsigned char ByteT;
  //: Unigned byte of 8 bits
  
  typedef unsigned char UByteT;
  //: Unigned byte of 8 bits
  
  typedef signed char SByteT;
  //: Signed byte of 8 bits
  
  typedef unsigned short UInt16T;
  //: Unsigned int of 16 bits.
  
  typedef short Int16T;
  //: Signed int of 16 bits.
  
#ifdef __GNUC__
  __extension__ typedef signed long long int Int64T;
  //: 64 bit signed integer.
  
  __extension__ typedef unsigned long long int UInt64T;
  //: 64 bit unsigned integer.
  
#elif RAVL_COMPILER_VISUALCPP
  typedef __int64 Int64T;
  //: 64 bit signed integer.
  
  typedef unsigned __int64 UInt64T;
  //: 64 bit unsigned integer.  
#else
  typedef signed long long int Int64T;
  //: 64 bit signed integer.
  
  typedef unsigned long long int UInt64T;
  //: 64 bit unsigned integer.
#endif
  
#if RAVL_OS_LINUX64
  typedef UInt64T SizeT;
#else
  typedef UIntT SizeT;
#endif 
  //: Type which can index any item in memory.
  
#if RAVL_USE_LARGEFILESUPPORT
  typedef UInt64T StreamOffsetT;
  //: Type which can index any offset in a file.
  // This is used internally in RAVL.
#else
  typedef UIntT StreamOffsetT;
  //: Type which can index any offset in a file.
  // This is used internally in RAVL.  
#endif
  
  typedef StreamOffsetT StreamSizeT;
  //: Size of stream.  This is seperate to allow large file support.
  
  template<class DataT>
  void Swap(DataT &v1,DataT &v2) {
    DataT t = v1;
    v1 = v2;
    v2 = t;
  }
  //: Swap the values of two variables.

  inline
  void SetZero(ByteT &x)
  { x = 0; }
  //: Set byte value to zero.
  
  inline
  void SetZero(IntT &x)
  { x = 0; }
  //: Set integer value to zero.
  
  inline
  void SetZero(UIntT &x)
  { x = 0; }
  //: Set unsigned integer value to zero.
  
  inline
  void SetZero(RealT &x)
  { x = 0; }
  //: Set real value to zero.
  
  inline
  void SetZero(SByteT &x)
  { x = 0; }
  //: Set signed byte value to zero.

  inline
  void SetZero(FloatT &x)
  { x = 0; }
  //: Set float value to zero.

  inline 
  void SetZero(Int16T &x) 
  { x = 0; } 
  //: Set integer value to zero.

  inline
  void SetZero(Int64T &x)
  { x = 0; }
  //: Set integer value to zero.
  
  inline
  void SetZero(UInt64T &x)
  { x = 0; }
  //: Set unsigned integer value to zero.
  
  
  template<class K>
  inline K StdCopy(const K &dat)
  { return dat.Copy(); }
  //: Copy.
  
  inline const char *StdCopy(const char *dat)
  { return dat; } 
  //: Copy constant 'C' style string.
  // No point in copying a constant string.
  // If otherwise you should use StringC intead.
  
  inline long double StdCopy(long double x) { return x; }
  //: Copy long double.
  
  inline double StdCopy(double x) { return x; }
  //: Copy double.
  
  inline float StdCopy(float x) { return x; }
  //: Copy float.

  inline bool StdCopy(bool x)
  { return x; }
  //: Copy bool.
  
  inline short StdCopy(short x)
  { return x; }
  //: Copy short.
  
  inline unsigned short StdCopy(unsigned short x)
  { return x; }
  //: Copy short.
  
  inline int StdCopy(int x)
  { return x; }
  //: Copy int.
  
  inline unsigned int StdCopy(unsigned int x)
  { return x; }
  //: Copy unsigned int.
  
  inline long StdCopy(long x)
  { return x; }
  //: Copy long
  
  inline unsigned long StdCopy(unsigned long x)
  { return x; }
  //: Copy unsigned long.
  
  inline char StdCopy(char x) 
  { return x; }
  //: Copy char.
  
  inline char StdCopy(unsigned char x) { return x; }
  //: Copy unsigned char.
  
  inline Int64T StdCopy(Int64T x) { return x; }
  //: Copy 64 bit int.
  
  inline UInt64T StdCopy(UInt64T x) { return x; }
  //: Copy unsigned 64 bit int.

};

#endif

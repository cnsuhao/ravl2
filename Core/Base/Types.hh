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

#if !USE_GCC30 
class istream;
class ostream;
#else
#include <iostream.h>
#endif

//!maindoc=1
//: Ravl namespace
// This namespace contains all the core ravl functionality.

namespace RavlN {  
  
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
#else
  typedef signed long long int Int64T;
  //: 64 bit signed integer.
  
  typedef unsigned long long int UInt64T;
  //: 64 bit unsigned integer.
#endif
  
  typedef UIntT SizeT;
  //: Type which can index any item in memory.
  
#if RAVL_USE_LARGEFILESUPPORT
  typedef UIntT StreamOffsetT;
  //: Type which can index any offset in a file.
  // This is used internally in RAVL.
#else
  typedef UInt64T StreamOffsetT;
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
  void SetZero(Int64T &x)
  { x = 0; }
  //: Set integer value to zero.
  
  inline
  void SetZero(UInt64T &x)
  { x = 0; }
  //: Set unsigned integer value to zero.
};

#endif

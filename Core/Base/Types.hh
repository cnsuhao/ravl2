// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTYPES_HEADER
#define RAVLTYPES_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core"
//! file="Ravl/Core/Base/Types.hh"
//! lib=RavlCore
//! userlevel=Default
//! author=""
//! date=""

#include "Ravl/config.h"
// Common forward declarations

#if !USE_GCC30 
class istream;
class ostream;
#else
#include <iostream.h>
#endif


//: Ravl namespace

namespace RavlN {  
  
  typedef int IntT;
  //: Integer of at least 32 bits
  
  typedef unsigned int UIntT;
  //: Unsigned Integer of at least 32 bits
  
  typedef double RealT;
  //: Real value of at least 32 bits.
  
  typedef float FloatT;
  //: Real value of at least 16 bits.
  
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
  
  typedef UIntT SizeT;
  //: Type which can index any item in memory.
  
  typedef int StreamSizeT;
  //: Size of stream.  This is seperate to allow large file support.
  
  template<class DataT>
  void Swap(DataT &v1,DataT &v2) {
    DataT t = v1;
    v1 = v2;
    v2 = t;
  }
  //: Swap the values of two variables.
};

#endif

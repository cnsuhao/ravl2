// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_STDHASH_HEADER
#define RAVL_STDHASH_HEADER 1
///////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/StdHash.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="1/9/1996"
//! docentry="Ravl.Core.Hash Tables"
//! example=WordFreq.cc
//! userlevel=Normal
//! rcsid="$Id$"

#include "Ravl/Types.hh"

namespace RavlN {
  
  template<class K>
  inline UIntT StdHash(const K &dat) 
  { return dat.Hash(); }
  //: Default hash function.
  
  template<class K>
  inline bool HashIsEqual(const K &d1,const K &d2) 
  { return (bool) (d1 == d2); }
  
  bool HashIsEqual(const char *d1,const char *d2);
  //: Compair 'C' style strings.
  
  UIntT StdHash(const char *dat);
  //: Hash 'C' style strings.
  
  inline UIntT StdHash(bool dat) 
  { return (UIntT) dat; }
  //: Hash a bool.
  // Not alot you can do with this.
  
  inline UIntT StdHash(const short dat) 
  { return (UIntT) (dat >> 7) ^ dat; }
  //: Hash short.
  
  inline UIntT StdHash(const unsigned short dat) 
  { return (UIntT) (dat >> 7) ^ dat; }
  //: Hash unsigned short.
  
  inline UIntT StdHash(const int dat) 
  { return (UIntT) (dat >> 11) ^ dat; }
  //: Hash int.
  
  inline UIntT StdHash(const unsigned int dat) 
  { return (UIntT) (dat >> 11) ^ dat; }
  //: Hash unsigned int.
  
  inline UIntT StdHash(const long dat) 
  { return (UIntT) (dat >> 11) ^ dat; }
  //: Hash long value.
  
  inline UIntT StdHash(const unsigned long dat) 
  { return (UIntT) (dat >> 11) ^ dat; }
  //: Hash unsigned long.
  
  inline UIntT StdHash(const char dat) 
  { return (UIntT) (dat >> 3) ^ dat; }
  //: Hash char.
  
  inline UIntT StdHash(const unsigned char dat) 
  { return (UIntT) (dat >> 3) ^ dat; }
  //: Hash unsigned char.
  
  inline
  UIntT StdHash(void *ptr) { 
#ifdef RAVL_OS_LINUX64
return (reinterpret_cast<UInt64T>(ptr) >> 2 ) ^ (reinterpret_cast<UInt64T>(ptr)>>15) ;
#else 
return (reinterpret_cast<UIntT>(ptr) >> 2) ^ (reinterpret_cast<UIntT>(ptr) >> 15);
#endif 
}
  //: Hash function for void ptr's.
  
// Disable "possible loss of data" warning
#if RAVL_COMPILER_VISUALCPP
#pragma warning ( push )
#pragma warning ( disable : 4244 )
#endif

  inline UIntT StdHash(const Int64T dat) 
  { return (UIntT) (dat >> 17) ^ (dat >> 32) ^ dat; }
  //: Hash 64 bit int.
  
  inline UIntT StdHash(const UInt64T dat) 
  { return (UIntT) (dat >> 17) ^ (dat >> 32) ^ dat; }
  //: Hash unsigned 64 bit int.
  
#if RAVL_COMPILER_VISUALCPP
#pragma warning ( pop )
#endif

}

#endif

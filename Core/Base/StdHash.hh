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
  inline K StdCopy(const K &dat)
  { return dat.Copy(); }
  //: Copy.
  
  template<class K>
  inline bool HashIsEqual(const K &d1,const K &d2) 
  { return (bool) (d1 == d2); }
  
  inline long double StdCopy(long double x) { return x; }
  //: Copy long double.
  
  inline double StdCopy(double x) { return x; }
  //: Copy double.
  
  inline float StdCopy(float x) { return x; }
  //: Copy float.
  
  bool HashIsEqual(const char *d1,const char *d2);
  //: Compair 'C' style strings.
  
  UIntT StdHash(const char *dat);
  //: Hash 'C' style strings.
  
  inline const char *StdCopy(const char *dat)
  { return dat; } 
  //: Copy constant 'C' style string.
  // No point in copying a constant string.
  // If otherwise you should use StringC intead.
  
  inline UIntT StdHash(bool dat) 
  { return (UIntT) dat; }
  //: Hash a bool.
  // Not alot you can do with this.
  
  inline bool StdCopy(bool x)
  { return x; }
  //: Copy bool.
  
  inline UIntT StdHash(const short dat) 
  { return (UIntT) (dat >> 7) ^ dat; }
  //: Hash short.
  
  inline short StdCopy(short x)
  { return x; }
  //: Copy short.
  
  inline UIntT StdHash(const unsigned short dat) 
  { return (UIntT) (dat >> 7) ^ dat; }
  //: Hash unsigned short.
  
  inline unsigned short StdCopy(unsigned short x)
  { return x; }
  //: Copy short.
  
  inline UIntT StdHash(const int dat) 
  { return (UIntT) (dat >> 11) ^ dat; }
  //: Hash int.

  inline int StdCopy(int x)
  { return x; }
  //: Copy int.
  
  inline UIntT StdHash(const unsigned int dat) 
  { return (UIntT) (dat >> 11) ^ dat; }
  //: Hash unsigned int.
  
  inline unsigned int StdCopy(unsigned int x)
  { return x; }
  //: Copy unsigned int.

  inline UIntT StdHash(const long dat) 
  { return (UIntT) (dat >> 11) ^ dat; }
  //: Hash long value.
  
  inline long StdCopy(long x)
  { return x; }
  //: Copy long
  
  inline UIntT StdHash(const unsigned long dat) 
  { return (UIntT) (dat >> 11) ^ dat; }
  //: Hash unsigned long.

  inline unsigned long StdCopy(unsigned long x)
  { return x; }
  //: Copy unsigned long.
  
  inline UIntT StdHash(const char dat) 
  { return (UIntT) (dat >> 3) ^ dat; }
  //: Hash char.
  
  inline char StdCopy(char x) { return x; }
  //: Copy char.
  
  inline UIntT StdHash(const unsigned char dat) 
  { return (UIntT) (dat >> 3) ^ dat; }
  //: Hash unsigned char.
  
  inline char StdCopy(unsigned char x) { return x; }
  //: Copy unsigned char.
  
  inline UIntT StdHash(const Int64T dat) 
  { return (UIntT) (dat >> 17) ^ (dat >> 32) ^ dat; }
  //: Hash 64 bit int.
  
  inline Int64T StdCopy(Int64T x) { return x; }
  //: Copy 64 bit int.
  
  inline UIntT StdHash(const UInt64T dat) 
  { return (UIntT) (dat >> 17) ^ (dat >> 32) ^ dat; }
  //: Hash unsigned 64 bit int.
  
  inline UInt64T StdCopy(UInt64T x) { return x; }
  //: Copy unsigned 64 bit int.


}

#endif

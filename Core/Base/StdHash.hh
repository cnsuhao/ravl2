// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSTDHASH_HEADER
#define RAVLSTDHASH_HEADER 1
///////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/StdHash.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="1/9/96"
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
  
  // Misc //////////////////////
  
  inline long double StdCopy(long double x) { return x; }
  inline double StdCopy(double x) { return x; }
  inline float StdCopy(float x) { return x; }
  
  /////////////////
  
  bool HashIsEqual(const char *d1,const char *d2);
  UIntT StdHash(const char *dat);
  
  inline const char *StdCopy(const char *dat)
  { return dat; } 
  // No point in copying a constant string.
  // If otherwise you should use StringC intead.

  ///////////////
  
  inline UIntT StdHash(const short dat) 
  { return (UIntT) (dat >> 7) ^ dat; }
  
  inline short StdCopy(short x)
  { return x; }

  ///////////////
  
  inline UIntT StdHash(bool dat) 
  { return (UIntT) dat; }
  
  inline short StdCopy(bool x)
  { return x; }
  
  ///////////////
  
  inline UIntT StdHash(const unsigned short dat) 
  { return (UIntT) (dat >> 7) ^ dat; }
  
  inline unsigned short StdCopy(unsigned short x)
  { return x; }

  ///////////////
  
  inline UIntT StdHash(const int dat) 
  { return (UIntT) (dat >> 11) ^ dat; }

  inline int StdCopy(int x)
  { return x; }

  ///////////////

  inline UIntT StdHash(const unsigned int dat) 
  { return (UIntT) (dat >> 11) ^ dat; }

  inline unsigned int StdCopy(unsigned int x)
  { return x; }

  ///////////////

  inline UIntT StdHash(const long dat) 
  { return (UIntT) (dat >> 11) ^ dat; }

  inline long StdCopy(long x)
  { return x; }

  ///////////////
 
  inline UIntT StdHash(const unsigned long dat) 
  { return (UIntT) (dat >> 11) ^ dat; }

  inline unsigned long StdCopy(unsigned long x)
  { return x; }


}

#endif

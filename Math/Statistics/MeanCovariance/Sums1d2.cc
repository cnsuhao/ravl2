// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/MeanCovariance/Sums1d2.cc"

#include "Ravl/Sums1d2.hh"
#include "Ravl/Stream.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  ostream& operator<<(ostream &s,const Sums1d2C &mv) {
    s << mv.Size() << " " << mv.Sum() << " " << mv.Sum2();
    return s;
  }
  
  istream& operator>>(istream &s, Sums1d2C &mv) {
    UIntT n;
    RealT s1,s2;
    s >> n >> s1 >> s2;
    mv = Sums1d2C(n,s1,s2);
    return s;
  }

  BinOStreamC& operator<<(BinOStreamC &s,const Sums1d2C &mv) {
    s << mv.Size() << mv.Sum() << mv.Sum2();
    return s;
  }
  
  BinIStreamC& operator>>(BinIStreamC &s, Sums1d2C &mv) {
    UIntT n;
    RealT s1,s2;
    s >> n >> s1 >> s2;
    mv = Sums1d2C(n,s1,s2);
    return s;
  }
  
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/RealRange1d.cc"

#include "Ravl/RealRange1d.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/Stream.hh"
#include "Ravl/IndexRange1d.hh"

namespace RavlN {
  
  RealRangeC::RealRangeC(istream & s)
  { s >> min >> max; }
  
  bool RealRangeC::In(const RealRangeC & range) const {
    return IsInside(Min(),range) && IsInside(Max(),range);
  } 
  
  IndexRangeC operator*(const RealRangeC &realRange,const IndexRangeC &indexRange) {
    RealT size = indexRange.Size();
    IndexC max = indexRange.Min() + IndexC(realRange.Max() * size);
    IndexC min = indexRange.Min() + IndexC(realRange.Min() * size);
    return IndexRangeC(min,max);
  }
  
  istream &operator>>(istream & sss, RealRangeC & range) { 
    sss >> range.Min() >> range.Max();
    return  sss;
  }
  
  ostream &operator<<(ostream & s, const RealRangeC & range) { 
    s << range.Min() << ' ' << range.Max();
    return s;
  }

  BinOStreamC &operator<<(BinOStreamC &s,const RealRangeC &range) {
    s << range.Min() << range.Max();
    return  s;
  }
  
  BinIStreamC &operator>>(BinIStreamC &s,RealRangeC &range) {
    s >> range.Min() >> range.Max();
    return s;
  }
  
}




// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/IndexRange3d.cc"

#include "Ravl/IndexRange3d.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  IndexRange3dC::IndexRange3dC(const IndexRangeC & iRange,
			       const IndexRangeC & jRange,
			       const IndexRangeC & kRange)
    : is(iRange), 
      js(jRange),
      ks(kRange)
  {}

  ostream &operator<<(ostream &s,const IndexRange3dC &ir) {
    s << ir.Range1() << ' ' << ir.Range2() << ' ' << ir.Range3();
    return s;
  }
  
  istream &operator>>(istream &s,IndexRange3dC &ir) {
    s >> ir.Range1() >> ir.Range2() >> ir.Range3();
    return s;
  }
  
  BinOStreamC &operator<<(BinOStreamC &s,const IndexRange3dC &ir) {
    s << ir.Range1() << ir.Range2() << ir.Range3();
    return s;
  }
  
  BinIStreamC &operator>>(BinIStreamC &s,IndexRange3dC &ir) {
    s >> ir.Range1() >> ir.Range2() >> ir.Range3();
    return s;
  }
  
}

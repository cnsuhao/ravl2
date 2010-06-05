// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id: IntC.cc 1294 2002-06-25 15:17:27Z craftit $"
//! lib=RavlCore
//! file="Ravl/Core/Base/IntC.cc"

#include "Ravl/IntC.hh"
#include "Ravl/Stream.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  ostream &operator<<(ostream &out,const IntC &x) {
    out << ((int) x.v);
    return out;
  }
  
  istream &operator>>(istream &in,IntC &x) {
    in >> ((int &) x.v);
    return in;
  }

  BinOStreamC &operator<<(BinOStreamC &strm,const IntC &x) {
    strm << x.v;
    return strm;
  }
  
  BinIStreamC &operator>>(BinIStreamC &strm,IntC &x) {
    strm >> x.v;
    return strm;
  }

  ostream &operator<<(ostream &out,const UIntC &x) {
    out << ((unsigned int) x.v);
    return out;
  }
  
  istream &operator>>(istream &in,UIntC &x) {
    in >> ((unsigned int &) x.v);
    return in;
  }

  BinOStreamC &operator<<(BinOStreamC &strm,const UIntC &x) {
    strm << x.v;
    return strm;
  }
  
  BinIStreamC &operator>>(BinIStreamC &strm,UIntC &x) {
    strm >> x.v;
    return strm;
  }

}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/IndexRange2d.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  IndexRange2dC::IndexRange2dC(const IndexRangeC & rowRange,
			       const IndexRangeC & colRange)
    : rows(rowRange), cols(colRange)
  {}
  
  IndexRange2dC::IndexRange2dC(const IndexRange2dC & range)
    : rows(range.RowRange()), cols(range.ColRange())
  {}
  
  BinOStreamC &operator<<(BinOStreamC &s,const IndexRange2dC &ir) {
    s << ir.Range1() << ir.Range2();
    return s;
  }
  
  BinIStreamC &operator>>(BinIStreamC &s,IndexRange2dC &ir) {
    s >> ir.Range1() >> ir.Range2();
    return s;
  }
  
}

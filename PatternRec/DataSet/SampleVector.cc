// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/SArr1Iter.hh"

namespace RavlN {

  //: Find the mean vector.
  
  VectorC SampleVectorC::Mean() {
    SArray1dIterC<VectorC> it(Array());
    if(!it)
      return VectorC();
    VectorC total = *it;
    for(;it;it++)
      total += *it;
    return total/ ((RealT) Size());
  }
  
}


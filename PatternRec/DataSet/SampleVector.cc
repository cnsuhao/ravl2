// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/SampleVector.cc"

#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/DArray1dIter.hh"

namespace RavlN {

  //: Find the mean vector.
  
  VectorC SampleVectorC::Mean() {
    DArray1dIterC<VectorC> it(*this);
    if(!it)
      return VectorC();
    VectorC total = *it;
    for(;it;it++)
      total += *it;
    return total/ ((RealT) Size());
  }
  
}


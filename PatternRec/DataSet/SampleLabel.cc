// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/SampleLabel.cc"
//! rcsid="$Id$"

#include "Ravl/PatternRec/SampleLabel.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/Vector.hh"

namespace RavlN {

  //: Find the value of the largest label.
  
  UIntT SampleLabelC::MaxValue() const {
    UIntT lv = 0;
    for(DArray1dIterC<UIntT> it(*this);it;it++) 
      if(*it > lv)
	lv = *it;
    return lv;
  }

  //: Convert a sample of labels to vectors
  // Where the label index is set to 'inClass' and the rest to 'outClass'.
  
  SampleC<VectorC> SampleLabelC::SampleVector(RealT inClass,RealT outClass,IntT maxLabel) const {
    if(maxLabel < 0) {
      for(SampleIterC<UIntT> it(*this);it;it++)
	if(*it > (UIntT) maxLabel)
	  maxLabel = (UIntT) *it;
    }
    SampleC<VectorC> ret(Size());
    for(SampleIterC<UIntT> it(*this);it;it++) {
      VectorC vec(maxLabel);
      vec.Fill(outClass);
      vec[*it] = inClass;
      ret.Append(vec);
    }
    return ret;

  }

  
}

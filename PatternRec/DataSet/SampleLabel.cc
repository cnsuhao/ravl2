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
#include "Ravl/DArray1dIter.hh"

namespace RavlN {

  //: Find the value of the largest label.
  
  UIntT SampleLabelC::MaxValue() const {
    UIntT lv = 0;
    for(DArray1dIterC<UIntT> it(*this);it;it++) 
      if(*it > lv)
	lv = *it;
    return lv;
  }

  
}

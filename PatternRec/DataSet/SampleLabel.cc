// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlPatternRec

//! rcsid="$Id$"

#include "Ravl/PatternRec/SampleLabel.hh"
#include "Ravl/CollectionIter.hh"

namespace RavlN {

  //: List all the instances (by sample no) of each Label in the sample.
  // If index is set, only search the sample no's given there.
  
  RCHashC<UIntT,CollectionC<UIntT> > SampleLabelC::ListInstancesOfLabels() const {
    RCHashC<UIntT,CollectionC<UIntT> > ret;
    for(CollectionConstIterC<UIntT> it(*this);it;it++)
      ret[(UIntT) it.Index().V()].Insert(*it);
    return ret;
  }

  //: List all the instances (by sample no) of each Label in the sample.
  // If index is set, only search the sample no's given there.
  
  RCHashC<UIntT,CollectionC<UIntT> > SampleLabelC::ListInstancesOfLabels(const CollectionC<UIntT> &index) const {
    RCHashC<UIntT,CollectionC<UIntT> > ret;
    for(CollectionConstIterC<UIntT> it(index);it;it++)
      ret[(*this)[*it]].Insert(*it);
    return ret;
  }
  
}

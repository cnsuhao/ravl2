// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DataSetVectorLabel.hh"
#include "Ravl/PatternRec/DataSet2Iter.hh"

namespace RavlN {

  //: Create a seperate sample for each label.
  
  SArray1dC<SampleVectorC> DataSetVectorLabelBodyC::SeperateLabels() {
    SArray1dC<SampleVectorC> ret(Sample2().MaxValue()+1);
    for(DataSet2IterC<SampleVectorC,SampleLabelC> it(Sample1(),Sample2());it;it++)
      ret[it.Data2()].Append(it.Data1());
    return ret;
  }

}

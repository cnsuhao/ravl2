// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDATASET1ITER_HEADER
#define RAVLDATASET1ITER_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DataSet1.hh"
#include "Ravl/DArray1dIter.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Iterate through a data set.
  
  template<class SampleT>
  class DataSet1IterC 
    : public DArray1dIterC<typename SampleT::ElementT>
  {
  public:
    DataSet1IterC()
    {}
    //: Default construtor.
    
    DataSet1IterC(DataSet1C<SampleT> &nds)
      : DArray1dIterC<typename SampleT::ElementT>(nds.Sample())
    {}
    //: Construct from a data set.
    
  };
  
}



#endif

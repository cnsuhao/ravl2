// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASET2ITER_HEADER
#define RAVL_DATASET2ITER_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DataSet3.hh"
#include "Ravl/DArray1dIter3.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Iterate through a data set.
  
  template<class Sample1T,class Sample2T,class Sample3T>
  class DataSet3IterC 
    : public DArray1dIter3C<Sample1T::ElementT,Sample2T::ElementT,Sample3T::ElementT>
  {
  public:
    DataSet3IterC()
    {}
    //: Default construtor.
    
    DataSet3IterC(DataSet3C<Sample1T,Sample2T,Sample3T> &nds)
      : DArray1dIter3C<Sample1T::ElementT,Sample2T::ElementT,Sample3T::ElementT>(nds.Sample1(),nds.Sample2(),nds.Sample3())
    {}
    //: Construct from a data set.
    
    
  };
  
}



#endif

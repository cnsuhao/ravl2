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
//! file="Ravl/PatternRec/DataSet/DataSet2Iter.hh"

#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/DArray1dIter2.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Iterate through a data set.
  
  template<class Sample1T,class Sample2T>
  class DataSet2IterC
    : public DArray1dIter2C<typename Sample1T::ElementT,typename Sample2T::ElementT>
  {
  public:
    DataSet2IterC()
    {}
    //: Default construtor.
    
    DataSet2IterC(const DataSet2C<Sample1T,Sample2T> &nds)
      : DArray1dIter2C<typename Sample1T::ElementT,typename Sample2T::ElementT>(nds.Sample1().DArray(),nds.Sample2().DArray())
    {}
    //: Construct from a data set.
    
  };
  
}



#endif

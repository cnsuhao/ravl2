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

#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/DArray1dIter2.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Iterate through a data set.
  
  template<class Sample1T,class Sample2T>
  class DataSet2IterC 
    : public DArray1dIter2C<Sample1T::ElementT,Sample2T::ElementT>
  {
  public:
    DataSet2IterC()
    {}
    //: Default construtor.
    
    DataSet2IterC(DataSet2C<Sample1T,Sample2T> &nds)
      : it(nds.Sample1(),nds.Sample2())
    {}
    //: Construct from a data set.
    
  };
  
}



#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DataSetBase.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Default constructor.
  
  DataSetBaseBodyC::DataSetBaseBodyC(SizeT size) 
    : index(size)
  {
    ONDEBUG(cerr << "DataSetBaseBodyC::DataSetBaseBodyC(SizeT), Index of " << size << " elements. \n");
    // Initialise index.
    for(UIntT i=0;i<size;i++)
      index.Insert(i);
  }
  
  //: In Place shuffle.
  // Randomise the order of this dataset.
  
  void DataSetBaseBodyC::ShuffleIP() {
    index.ShuffleIP();
  }
  
}

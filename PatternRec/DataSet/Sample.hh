// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSAMPLE_HEADER
#define RAVLSAMPLE_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include"Ravl/Collection.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Sample of DataT's
  
  template <class DataT> 
  class SampleC 
    : protected CollectionC<DataT>
    {
      
    public:
      SampleC(SizeT maxSize=10)
	: CollectionC<DataT>(maxSize)
	{}
      //: Create a sample of data with a maximum size
      
      SampleC(const SArray1dC<DataT> & dat)
	: CollectionC<DataT>(dat)
	{}
      //: Create a sample of data from an array

      void Insert(const DataT & dat)
	{ CollectionC<DataT>::Insert(dat); }
      //: Insert a single sample into sample
      
      DataT Pick()
	{ return CollectionC<DataT>::Pick(); }
      //: Pick a random item from the collection
      
      SizeT Size() const
	{ return CollectionC<DataT>::Size(); }
      //: Return the number of valid samples in the collection
      
      
    }; // end of class SampleC 

}

#endif

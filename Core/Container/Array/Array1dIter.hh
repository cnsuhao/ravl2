// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLARR1ITER_HEADER
#define RAVLARR1ITER_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Arrays.1D"
//! file="Ravl/Core/Container/Array/Array1dIter.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="//"
//! userlevel=Default

#include "Ravl/Array1d.hh"
#include "Ravl/BfAccIter.hh"

namespace RavlN {
  //! userlevel=Normal
  //: Array1dC iterator.
  
  template<class DataT>
  class Array1dIterC 
    : public BufferAccessIterC<DataT>
  {
  public:
    Array1dIterC()
      {}
    //: Default constructor.
    
    Array1dIterC(const Array1dC<DataT> &arr)
      : BufferAccessIterC<DataT>(arr),
        dat(arr)
      {}
    //: Constructor.
    
    Array1dIterC(const Array1dC<DataT> &arr,const IndexRangeC & range)
      : dat(arr,range)
      { BufferAccessIterC<DataT>::operator=(dat); }
    //: Iterate through a sub-range.
    
    inline void First() 
      { BufferAccessIterC<DataT>::First(dat); }
    //: Goto first element in the array.
    
    inline void First(Array1dC<DataT> &arr) { 
      dat = arr;
      BufferAccessIterC<DataT>::First(dat); 
    }
    //: Goto first element in the array.
    
    const Array1dIterC<DataT> &operator=(const Array1dC<DataT> &arr) {
      dat = arr;
      First();
      return *this;
    }
    //: Assignment.
    
    IndexC Index() const
      { return IndexC((IntT)( at - dat.ReferenceElm())); }
    //: Calculate the index we're at.
    
  protected:
    Array1dC<DataT> dat;
  };
  
}
#endif

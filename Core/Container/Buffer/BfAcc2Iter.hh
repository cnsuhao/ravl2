// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLRBFACC2ITER_HEADER
#define RAVLRBFACC2ITER_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BfAcc2Iter.hh"
//! docentry="Ravl.Core.Arrays.Buffer"
//! lib=RavlCore
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/BfAccIter.hh"
#include "Ravl/IndexRange1d.hh"

namespace RavlN {
  //! userlevel=Advanced
  //: 2d buffer iterator.
  
  template <class DataC>
  class BufferAccess2dIterC {
  public:
    BufferAccess2dIterC()
      {}
    //: Default constructor.
    
    BufferAccess2dIterC(const SizeBufferAccessC<BufferAccessC<DataC> > &pbuf,SizeT size)
      { First(pbuf,size); }
    //: Constructor.
    
    BufferAccess2dIterC(const RangeBufferAccessC<BufferAccessC<DataC> > &pbuf,const IndexRangeC &nrng2)
      { First(pbuf,nrng2); }
    //: Constructor.
    
    bool First(const SizeBufferAccessC<BufferAccessC<DataC> > &pbuf,SizeT size) {
      rit = pbuf;
      rng = IndexRangeC(0,size-1);
      if(rng.Size() > 0 && rit.IsElm()) {
	cit.First(*rit,rng);
	return true;
      }
      cit.Invalidate();
      return false;
    }
    //: Goto first element in the array.
    
    bool First(const RangeBufferAccessC<BufferAccessC<DataC> > &pbuf,const IndexRangeC &nrng) {
      rit = pbuf;
      rng = nrng;
      if(rng.Size() > 0 && rit.IsElm()) {
	cit.First(*rit,rng);
	return true;
      }
      cit.Invalidate();
      return false;
    }
    //: Goto first element in the array
    
    void RowStart() {
      cit.First(*rit,rng);
    }
    //: Go back to the begining of this row.

    bool NextRow() {
      rit.Next();
      if(!rit.IsElm())
	return false;
      cit.First(rit.Data(),rng);
      return true;      
    }
    //: Go to the begining of the next row.
    // returns true if iterator is left at the begining of a valid row or
    // false if the end of the array has been reached.
    
    void NextCol()
      { cit.Next(); }
    //: Goto next column, without checking for row change.
    // Use with care.
    
    bool Next() { 
      cit.Next();
      if(cit.IsElm())
	return true;
      rit.Next();
      if(!rit.IsElm())
	return false;
      cit.First(rit.Data(),rng);
      return false;
    }
    //: Goto next element.
    // Goto next element in the array. Returns true if the element
    // is on the same row of the array. It returns false if the element is on
    // the next row or at the end of the array.
    
    bool IsElm() const
      { return cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
      { return cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() 
      { Next(); }
    //: Goto next element.

    void operator++(int) 
      { Next(); }
    //: Goto next element.
    
    DataC &operator*() 
      { return *cit; }
    //: Access data of current element
    
    const DataC &operator*() const
      { return *cit; }
    //: Access data of current element

    DataC &Data() 
      { return *cit; }
    //: Access data of current element

    const DataC &Data() const
      { return *cit; }
    //: Access data of current element

    DataC &Data1() 
      { return *cit; }
    //: Access data of current element
    
    const DataC &Data1() const
      { return *cit; }
    //: Access data of current element
    
    RangeBufferAccessC<DataC> &Row()
      { return RangeBufferAccessC<DataC>(rng,*rit); }
    //: Access row we're currently iterating.
    
    const RangeBufferAccessC<DataC> &Row() const
      { return RangeBufferAccessC<DataC>(rng,*rit); }
    //: Access row we're currently iterating.
    
  protected:
    BufferAccessIterC<BufferAccessC<DataC> > rit;
    BufferAccessIterC<DataC> cit;
    IndexRangeC rng;
  };
}


#endif

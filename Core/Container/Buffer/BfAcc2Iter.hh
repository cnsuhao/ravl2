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
//! userlevel=Advanced
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/BfAccIter.hh"
#include "Ravl/IndexRange1d.hh"
#include "Ravl/Index2d.hh"

namespace RavlN {
  //! userlevel=Advanced
  //: 2d buffer iterator.
  
  template <class DataT>
  class BufferAccess2dIterC {
  public:
    BufferAccess2dIterC()
      {}
    //: Default constructor.

    BufferAccess2dIterC(const BufferAccessC<BufferAccessC<DataT> > &pbuf,SizeT size1,SizeT size2)
      { First(pbuf,size1,size2); }
    //: Constructor.    
    
    BufferAccess2dIterC(const SizeBufferAccessC<BufferAccessC<DataT> > &pbuf,SizeT size)
      { First(pbuf,size); }
    //: Constructor.
    
    BufferAccess2dIterC(const RangeBufferAccessC<BufferAccessC<DataT> > &pbuf,const IndexRangeC &nrng2)
      { First(pbuf,nrng2); }
    //: Constructor.

    BufferAccess2dIterC(const BufferAccessC<BufferAccessC<DataT> > &pbuf,const IndexRangeC &nrng1,const IndexRangeC &nrng2)
      { First(pbuf,nrng1,nrng2); }
    //: Constructor.

    bool First(const BufferAccessC<BufferAccessC<DataT> > &pbuf,SizeT size1,SizeT size2) {
      rit.First(pbuf,size1);
      rng = IndexRangeC(0,size2-1);
      if(size2 > 0 && rit.IsElm()) {
	cit.First(*rit,rng);
	return true;
      }
      cit.Invalidate();
      return false;
    }
    //: Goto first element in the array.
    
    bool First(const SizeBufferAccessC<BufferAccessC<DataT> > &pbuf,SizeT size) {
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

    bool First(const BufferAccessC<BufferAccessC<DataT> > &pbuf,const IndexRangeC &nrng1,const IndexRangeC &nrng2) 
      { return First(RangeBufferAccessC<BufferAccessC<DataT> >(nrng1,pbuf),nrng2); }
    //: Goto first element in the array.
    
    bool First(const RangeBufferAccessC<BufferAccessC<DataT> > &pbuf,const IndexRangeC &nrng) {
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
    
    DataT &operator*() 
      { return *cit; }
    //: Access data of current element
    
    const DataT &operator*() const
      { return *cit; }
    //: Access data of current element

    DataT &Data() 
      { return *cit; }
    //: Access data of current element

    const DataT &Data() const
      { return *cit; }
    //: Access data of current element

    DataT &Data1() 
      { return *cit; }
    //: Access data of current element
    
    const DataT &Data1() const
      { return *cit; }
    //: Access data of current element
    
    RangeBufferAccessC<DataT> &Row()
      { return RangeBufferAccessC<DataT>(rng,*rit); }
    //: Access row we're currently iterating.
    
    const RangeBufferAccessC<DataT> &Row() const
      { return RangeBufferAccessC<DataT>(rng,*rit); }
    //: Access row we're currently iterating.
    
    Index2dC Index(const BufferAccessC<DataT> *rowBegin) const { 
      return Index2dC((IntT) (&(*rit) - rowBegin),
		      (IntT) (&(*cit) - rit->ReferenceElm()));
    }
    //: Get index of current location.
    // Has to be calculate, and so is slightly slow.
		  
    void Invalidate()
      { cit.Invalidate(); }
    //: Invalidate this iterator.
    
  protected:
    BufferAccessIterC<BufferAccessC<DataT> > rit;
    BufferAccessIterC<DataT> cit;
    IndexRangeC rng;
  };
}


#endif

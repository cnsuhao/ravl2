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
    //: Goto first element.

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
    //: Goto first element.

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
    // returns true if there is one.
    
    void NextCol()
      { cit.Next(); }
    //: Goto next columb, without checking for row change.
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
    
    bool IsElm() const
      { return cit.IsElm(); }
    //: At a valid element ?
    
    operator bool() const
      { return cit.IsElm(); }
    //: At a valid element ?
    
    void operator++() 
      { Next(); }
    // Goto next element.

    void operator++(int) 
      { Next(); }
    // Goto next element.
    
    DataC &operator*() 
      { return *cit; }
    // Access data.
    
    const DataC &operator*() const
      { return *cit; }
    // Access data.

    DataC &Data() 
      { return *cit; }
    // Access data.

    const DataC &Data() const
      { return *cit; }
    // Access data.

    DataC &Data1() 
      { return *cit; }
    // Access data.
    
    const DataC &Data1() const
      { return *cit; }
    // Access data.
        
  protected:
    BufferAccessIterC<BufferAccessC<DataC> > rit;
    BufferAccessIterC<DataC> cit;
    IndexRangeC rng;
  };
}


#endif

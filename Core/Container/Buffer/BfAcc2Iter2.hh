// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLRBFACC2ITER2_HEADER
#define RAVLRBFACC2ITER2_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BfAcc2Iter2.hh"
//! lib=RavlCore
//! userlevel=Default
//! docentry="Ravl.Core.Arrays.Buffer"
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/BfAccIter2.hh"

namespace RavlN {
  
  //! userlevel=Advanced
  //: Iterate through a 2d buffer.
  
  template <class Data1C,class Data2C>
  class BufferAccess2dIter2C {
  public:
    BufferAccess2dIter2C()
      {}
    //: Default constructor.
    
    BufferAccess2dIter2C(const SizeBufferAccessC<BufferAccessC<Data1C> > &pbuf1,SizeT size1,
			 const SizeBufferAccessC<BufferAccessC<Data2C> > &pbuf2,SizeT size2)
      { First(pbuf1,size1,pbuf2,size2); }
    //: Constructor.
    
    BufferAccess2dIter2C(const RangeBufferAccessC<BufferAccessC<Data1C> > &pbuf1,const IndexRangeC &nrng1,
			 const RangeBufferAccessC<BufferAccessC<Data2C> > &pbuf2,const IndexRangeC &nrng2)
      { First(pbuf1,nrng1,pbuf2,nrng2); }
    //: Constructor.
    
    bool First(const RangeBufferAccessC<BufferAccessC<Data1C> > &pbuf1,const IndexRangeC &nrng1,
	       const RangeBufferAccessC<BufferAccessC<Data2C> > &pbuf2,const IndexRangeC &nrng2) {
      rit.First(pbuf1,pbuf2);
      rng1 = nrng1;
      rng2 = nrng2;
      if(rng1.Size() > 0 && rit.IsElm())
	return cit.First(rit.Data1(),rng1,rit.Data2(),rng2);      
      cit.Invalidate();
      return false;
    }
    // Goto first element.
    // returns true if there is one.
    
    bool First(const SizeBufferAccessC<BufferAccessC<Data1C> > &pbuf1,SizeT size1,
	       const SizeBufferAccessC<BufferAccessC<Data2C> > &pbuf2,SizeT size2) {
      rit.First(pbuf1,pbuf2);
      rng1 = IndexRangeC(0,size1-1);
      rng2 = IndexRangeC(0,size2-1);
      if(rng1.Size() > 0 && rit.IsElm())
	return cit.First(rit.Data1(),rng1,rit.Data2(),rng2);
      cit.Invalidate();
      return false;
    }
    // Goto first element.
    // returns true if there is one.
    
    bool Next() { 
      cit.Next();
      if(cit.IsElm())
	return true;
      rit.Next();
      if(!rit.IsElm())
	return false;
      cit.First(rit.Data1(),rng1,rit.Data2(),rng2);
      return false;
    }
    //: Goto next element.
    // returns true if on the same row.
    
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
    
    Data1C &Data1() 
      { return cit.Data1(); }
    // Access data.

    const Data1C &Data1() const
      { return cit.Data1(); }
    // Access data.

    Data2C &Data2() 
      { return cit.Data2(); }
    // Access data.
    
    const Data2C &Data2() const
      { return cit.Data2(); }
    // Access data.
        
  protected:
    BufferAccessIter2C<BufferAccessC<Data1C>,BufferAccessC<Data2C> > rit;
    BufferAccessIter2C<Data1C,Data2C> cit;
    IndexRangeC rng1;
    IndexRangeC rng2;
  };
}

#endif


// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLRBFACC2ITER3_HEADER
#define RAVLRBFACC2ITER3_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BfAcc2Iter3.hh"
//! lib=RavlCore
//! docentry="Ravl.Core.Arrays.Buffer"
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/BfAccIter3.hh"

namespace RavlN {
  
  //! userlevel=Advanced
  //: Iterate through a 2d buffer.
  
  template <class Data1T,class Data2T,class Data3T>
  class BufferAccess2dIter3C {
  public:
    BufferAccess2dIter3C()
      {}
    //: Default constructor.
    
    BufferAccess2dIter3C(const SizeBufferAccessC<BufferAccessC<Data1T> > &pbuf1,SizeT size1,
			 const SizeBufferAccessC<BufferAccessC<Data2T> > &pbuf2,SizeT size2,
			 const SizeBufferAccessC<BufferAccessC<Data3T> > &pbuf3,SizeT size3)
      { First(pbuf1,size1,pbuf2,size2,pbuf3,size3); }
    //: Constructor.
    
    BufferAccess2dIter3C(const RangeBufferAccessC<BufferAccessC<Data1T> > &pbuf1,const IndexRangeC &nrng1,
			 const RangeBufferAccessC<BufferAccessC<Data2T> > &pbuf2,const IndexRangeC &nrng2,
			 const RangeBufferAccessC<BufferAccessC<Data3T> > &pbuf3,const IndexRangeC &nrng3)
      { First(pbuf1,nrng1,pbuf2,nrng2,pbuf3,nrng3); }
    //: Constructor.


    BufferAccess2dIter3C(const BufferAccessC<BufferAccessC<Data1T> > &pbufa,const IndexRangeC &nrng1a,const IndexRangeC &nrng2a,
			 const BufferAccessC<BufferAccessC<Data2T> > &pbufb,const IndexRangeC &nrng1b,const IndexRangeC &nrng2b,
			 const BufferAccessC<BufferAccessC<Data3T> > &pbufc,const IndexRangeC &nrng1c,const IndexRangeC &nrng2c)
      { First(pbufa,nrng1a,nrng2a,
	      pbufb,nrng1b,nrng2b,
	      pbufc,nrng1c,nrng2c); 
      }
    //: Constructor.

    bool First(const BufferAccessC<BufferAccessC<Data1T> > &pbufa,const IndexRangeC &nrng1a,const IndexRangeC &nrng2a,
	       const BufferAccessC<BufferAccessC<Data2T> > &pbufb,const IndexRangeC &nrng1b,const IndexRangeC &nrng2b,
	       const BufferAccessC<BufferAccessC<Data3T> > &pbufc,const IndexRangeC &nrng1c,const IndexRangeC &nrng2c) {
      rit.First(pbufa,nrng1a,pbufb,nrng1c,pbufc,nrng1c);
      rng1 = nrng2a;
      rng2 = nrng2b;
      rng3 = nrng2c;
      if(rng1.Size() > 0 && rit.IsElm())
	return cit.First(rit.Data1(),rng1,
			 rit.Data2(),rng2,
			 rit.Data3(),rng3); 
      cit.Invalidate();
      return false;
    }
    //: Goto first element.
    // returns true if there is one.
    
    bool First(const RangeBufferAccessC<BufferAccessC<Data1T> > &pbuf1,const IndexRangeC &nrng1,
	       const RangeBufferAccessC<BufferAccessC<Data2T> > &pbuf2,const IndexRangeC &nrng2,
	       const RangeBufferAccessC<BufferAccessC<Data3T> > &pbuf3,const IndexRangeC &nrng3) {
      rit.First(pbuf1,pbuf2,pbuf3);
      rng1 = nrng1;
      rng2 = nrng2;
      rng3 = nrng3;
      if(rng1.Size() > 0 && rit.IsElm())
	return cit.First(rit.Data1(),rng1,rit.Data2(),rng2,rit.Data3(),rng3); 
      cit.Invalidate();
      return false;
    }
    //: Goto first element.
    // returns true if there is one.
    
    bool First(const SizeBufferAccessC<BufferAccessC<Data1T> > &pbuf1,SizeT size1,
	       const SizeBufferAccessC<BufferAccessC<Data2T> > &pbuf2,SizeT size2,
	       const SizeBufferAccessC<BufferAccessC<Data3T> > &pbuf3,SizeT size3) {
      rit.First(pbuf1,pbuf2,pbuf3);
      rng1 = IndexRangeC(0,size1-1);
      rng2 = IndexRangeC(0,size2-1);
      rng3 = IndexRangeC(0,size3-1);
      if(rng1.Size() > 0 && rit.IsElm())
	return cit.First(rit.Data1(),rng1,rit.Data2(),rng2,rit.Data3(),rng3); 
      cit.Invalidate();
      return false;
    }
    //: Goto first element.
    // returns true if there is one.
    
    bool Next() { 
      cit.Next();
      if(cit.IsElm())
	return true;
      rit.Next();
      if(!rit.IsElm())
	return false;
      cit.First(rit.Data1(),rng1,rit.Data2(),rng2,rit.Data3(),rng3);
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
    //: Goto next element.

    void operator++(int) 
      { Next(); }
    //: Goto next element.
    
    Data1T &Data1() 
      { return cit.Data1(); }
    //: Access data.

    const Data1T &Data1() const
      { return cit.Data1(); }
    //: Access data.

    Data2T &Data2() 
      { return cit.Data2(); }
    //: Access data.

    const Data2T &Data2() const
      { return cit.Data2(); }
    //: Access data.
    
    Data3T &Data3()
      { return cit.Data3(); }
    //: Access data.

    const Data3T &Data3() const
      { return cit.Data3(); }
    //: Access data.

    Index2dC Index(const BufferAccessC<Data1T> *row1Begin) const { 
      return Index2dC((IntT) (&(rit.Data1()) - row1Begin),
		      (IntT) (&(cit.Data1()) - rit.Data1().ReferenceElm()));
    }
    //: Get index of current location.
    // Has to be calculate, and so is slightly slow.
    
    void Invalidate()
      { cit.Invalidate(); }
    //: Invalidate this iterator.
    
  protected:
    BufferAccessIter3C<BufferAccessC<Data1T>,BufferAccessC<Data2T>,BufferAccessC<Data3T> > rit;
    BufferAccessIter3C<Data1T,Data2T,Data3T> cit;
    IndexRangeC rng1;
    IndexRangeC rng2;
    IndexRangeC rng3;
  };
}

#endif


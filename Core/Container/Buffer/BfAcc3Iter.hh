// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBFACC3ITER_HEADER
#define RAVLBFACC3ITER_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BfAcc3Iter.hh"
//! docentry="Ravl.Core.Arrays.Buffer"
//! lib=RavlCore
//! userlevel=Advanced
//! author="Charles Galambos"

#include "Ravl/BfAccIter.hh"
#include "Ravl/BfAcc2Iter.hh"
#include "Ravl/IndexRange1d.hh"

namespace RavlN {
  //! userlevel=Advanced
  //: 3D buffer iterator.
  
  template <class DataC>
  class BufferAccess3dIterC {
  public:
    BufferAccess3dIterC()
      {}
    //: Default constructor.
    
    BufferAccess3dIterC(const BufferAccessC<BufferAccessC<BufferAccessC<DataC> > > &pbuf,SizeT size1,SizeT size2,SizeT size3)
      { First(pbuf,size1,size2,size3); }
    //: Constructor.

    BufferAccess3dIterC(const BufferAccessC<BufferAccessC<BufferAccessC<DataC> > > &pbuf,const IndexRangeC &nrng1,const IndexRangeC &nrng2,const IndexRangeC &nrng3)
      { First(pbuf,nrng1,nrng2,nrng3); }
    //: Constructor.
    
    BufferAccess3dIterC(const SizeBufferAccessC<BufferAccessC<BufferAccessC<DataC> > > &pbuf,SizeT size2,SizeT size3)
      { First(pbuf,size2,size3); }
    //: Constructor.

    BufferAccess3dIterC(const RangeBufferAccessC<BufferAccessC<BufferAccessC<DataC> > > &pbuf,const IndexRangeC &nrng2,const IndexRangeC &nrng3)
      { First(pbuf,nrng2,nrng3); }
    //: Constructor.
    
    bool First(const BufferAccessC<BufferAccessC<BufferAccessC<DataC> > > &pbuf,const IndexRangeC &nrng1,const IndexRangeC &nrng2,const IndexRangeC &nrng3) {
      rng2 = nrng2;
      rng3 = nrng3;
      rit.First(pbuf,nrng1);
      if(rit.IsElm())
	return sit.First(*rit,rng2,rng3);
      sit.Invalidate();
      return false;
    }
    //: Goto first element in the array

    bool First(const RangeBufferAccessC<BufferAccessC<BufferAccessC<DataC> > > &pbuf,const IndexRangeC &nrng2,const IndexRangeC &nrng3) {
      rng2 = nrng2;
      rng3 = nrng3;
      rit.First(pbuf,pbuf.Range());
      if(rit.IsElm())
	return sit.First(*rit,rng2,rng3);
      sit.Invalidate();
      return false;
    }
    //: Goto first element in the array
    
    bool First(const BufferAccessC<BufferAccessC<BufferAccessC<DataC> > > &pbuf,SizeT size1,SizeT size2,SizeT size3) {
      rng2 = IndexRangeC(0,size2-1);
      rng3 = IndexRangeC(0,size3-1);
      rit.First(pbuf,size1);
      if(rit.IsElm())
	return sit.First(*rit,size2,size3);
      sit.Invalidate();
      return false;
    }
    //: Goto first element in the array

    bool First(const SizeBufferAccessC<BufferAccessC<BufferAccessC<DataC> > > &pbuf,SizeT size2,SizeT size3) {
      rng2 = IndexRangeC(0,size2-1);
      rng3 = IndexRangeC(0,size3-1);
      rit.First(pbuf,pbuf.Size());
      if(rit.IsElm())
	return sit.First(*rit,size2,size3);
      sit.Invalidate();
      return false;
    }
    //: Goto first element in the array
    
    void SliceStart() 
      { sit.First(*rit,rng2,rng3); }
    //: Go back to the begining of this row.
    
    bool NextSlice() {
      rit.Next();
      if(!rit.IsElm())
	return false;
      sit.First(*rit,rng2,rng3);;
      return true;      
    }
    //: Go to the begining of the next row.
    // returns true if iterator is left at the begining of a valid row or
    // false if the end of the array has been reached.
    
    bool Next() { 
      sit.Next();
      if(sit.IsElm())
	return true;
      rit.Next();
      if(!rit.IsElm())
	return false;
      sit.First(*rit,rng2,rng3);;
      return false;
    }
    //: Goto next element.
    // Goto next element in the array. Returns true if the element
    // is on the same row of the array. It returns false if the element is on
    // the next row or at the end of the array.
    
    bool IsElm() const
      { return sit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
      { return sit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() 
      { Next(); }
    //: Goto next element.

    void operator++(int) 
      { Next(); }
    //: Goto next element.
    
    DataC &operator*() 
      { return *sit; }
    //: Access data of current element
    
    const DataC &operator*() const
      { return *sit; }
    //: Access data of current element

    DataC &Data() 
      { return *sit; }
    //: Access data of current element

    const DataC &Data() const
      { return *sit; }
    //: Access data of current element

    DataC &Data1() 
      { return *sit; }
    //: Access data of current element
    
    const DataC &Data1() const
      { return *sit; }
    //: Access data of current element
    
  protected:
    BufferAccessIterC<BufferAccessC<BufferAccessC<DataC> > > rit;
    BufferAccess2dIterC<DataC> sit;
    IndexRangeC rng2;
    IndexRangeC rng3;
  };
}


#endif

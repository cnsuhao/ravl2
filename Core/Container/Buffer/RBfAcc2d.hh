// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RBFACC2D_HEADER
#define RAVL_RBFACC2D_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/RBfAcc2d.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Core.Arrays.Buffer"

#include "Ravl/RBfAcc.hh"
#include "Ravl/BfAcc2Iter.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/Assert.hh"

class istream;
class ostream;

namespace RavlN {
  
  class BinOStreamC;
  class BinIStreamC;
  
  //! userlevel=Develop
  //: Basic access to buffer with limited size
  // The class RangeBufferAccessC enables to random indexed access to
  // a sequentially organised continous part of memory called buffer.
  // The access functions check if an accessed element is valid only in
  // debug mode.
  
  template <class DataC>
  class RangeBufferAccess2dC 
    : public RangeBufferAccessC<BufferAccessC<DataC> >
  {
  public:
    RangeBufferAccess2dC(const IndexRangeC &nrng2)
      : rng2(nrng2)
      {}
    //: Constructor.
    
    RangeBufferAccess2dC(const RangeBufferAccessC<BufferAccessC<DataC> > &ab,const IndexRangeC &nrng2)
      : RangeBufferAccessC<BufferAccessC<DataC> >(ab),
      rng2(nrng2)
      {}
    //: Constructor.

    RangeBufferAccess2dC(const RangeBufferAccessC<BufferAccessC<DataC> > &ab,const IndexRange2dC &rect)
      : RangeBufferAccessC<BufferAccessC<DataC> >(ab,rect.Range1()),
      rng2(rect.Range2())
      {}
    //: Construct a access to a rectangle within 'ab' with indexs 'rect'.

    RangeBufferAccess2dC(const RangeBufferAccessC<BufferAccessC<DataC> > &ab,const IndexRangeC &r1,const IndexRangeC &r2)
      : RangeBufferAccessC<BufferAccessC<DataC> >(ab,r1),
      rng2(r2)
      {}
    //: Construct a access to a rectangle within 'ab' with ranges r1 and r2.
    
    RangeBufferAccess2dC(const BufferAccessC<BufferAccessC<DataC> > &ab,const IndexRangeC &r1,const IndexRangeC &r2)
      : RangeBufferAccessC<BufferAccessC<DataC> >(r1,ab),
      rng2(r2)
      {}
    //: Construct a access to a rectangle within 'ab' with ranges r1 and r2.
    // All the offsets for the buffers should already be setup.
    
    RangeBufferAccess2dC()
      : rng2(0,-1)
      {}
    //: Default constructor.
    
    inline DataC & operator[](const Index2dC & i) { 
      RavlAssert(rng2.Contains(i.Col()));
      return RangeBufferAccessC<BufferAccessC<DataC> >::operator[](i.Row())[i.Col()]; 
    }
    //: access to the item array[(i)]
    
    inline const DataC & operator[](const Index2dC & i) const { 
      RavlAssert(rng2.Contains(i.Col()));
      return RangeBufferAccessC<BufferAccessC<DataC> >::operator[](i.Row())[i.Col()]; 
    }
    //: return the item array[(i)]
    
    inline RangeBufferAccessC<DataC> operator[](IndexC i)
      { return RangeBufferAccessC<DataC>(rng2,RangeBufferAccessC<BufferAccessC<DataC> >::operator[](i)); }
    //: access to the item array[(i)]
    
    inline const RangeBufferAccessC<DataC> operator[](IndexC i) const
      { return RangeBufferAccessC<DataC>(rng2,RangeBufferAccessC<BufferAccessC<DataC> >::operator[](i)); }
    //: return the item array[(i)]
    
    inline const IndexRangeC &Range1() const
      { return Range(); }
    //: Range of first index.
    
    inline const IndexRangeC &Range2() const
      { return rng2; }
    //: Range of second index.

    UIntT Size() const 
    { return Range1().Size() * Range2().Size(); }
    //: Get the total number of elements in the array.
    
    void Fill(const DataC &d);
    //: Fill array with value.
    
    IndexRange2dC Rectangle() const
      { return IndexRange2dC(Range1(),Range2()); }
    //: Return ranges of indexes
    
    IndexRange2dC Frame() const
      { return IndexRange2dC(Range1(),Range2()); }
    //: Return ranges of indexes

    inline bool Contains(const Index2dC & i) const
      { return Range1().Contains(i.Row()) && Range2().Contains(i.Col()); }
    //: Returns TRUE if there is an item of the 2D array
    
    IntT Stride() const {
      if(Range1().Size() < 1)
	return (IntT) rng2.Size();
      return (IntT) (RangeBufferAccessC<BufferAccessC<DataC> >::operator[](1).ReferenceElm() -  
		     RangeBufferAccessC<BufferAccessC<DataC> >::operator[](0).ReferenceElm());
    }
    //: Get the stide of the 2d array. 
    
    bool IsContinuous() const 
      { return Stride() == (IntT) rn2.Size(); }
    //: Test if the array is allocated in a continous area of memory.
    // Note: this only checks the first two rows follow each other in
    // memory, this may miss other discontunities.

    bool IsEmpty() const
      { return (Range1().Size() <= 0) || (Range2().Size() <= 0); }
    //: Is rectangle empty ?
    
    BufferAccess2dIterC<DataC> Iter()
      { return BufferAccess2dIterC<DataC>(*this,rng2); }
    //: Creat an iterator for this buffer.
    
  protected:
    IndexRangeC rng2;
  };
  
  template<class DataC>
  void RangeBufferAccess2dC<DataC>::Fill(const DataC &d) {
    for(BufferAccess2dIterC<DataC> it(*this,rng2);it;it++)
      *it = d;
  }
  
  template <class DataC>
  ostream & operator<<(ostream & s, const RangeBufferAccess2dC<DataC> & arr) {
    for(BufferAccess2dIterC<DataC> it(arr,arr.Range2());it;) {
      s << *it;
      for(;it.Next();) 
	s << ' ' << *it;
      s << '\n';
    }    
    return s;
  }
  
  template <class DataC>
  istream & operator>>(istream & s, RangeBufferAccess2dC<DataC> & arr) {
    for(BufferAccess2dIterC<DataC> it(arr,arr.Range2());it;it++) 
      s >> *it;
    return s;
  }

  template<class DataC>
  BinOStreamC &operator<<(BinOStreamC & s, const RangeBufferAccess2dC<DataC> & arr) {
    for(BufferAccess2dIterC<DataC> it(arr,arr.Range2());it;it++)
      s << *it;
    return s;
  }
  
  template<class DataC>
  BinIStreamC &operator>>(BinIStreamC & s, RangeBufferAccess2dC<DataC> & arr) {
    for(BufferAccess2dIterC<DataC> it(arr,arr.Range2());it;it++)
      s >> *it;
    return s;
  }
}

#endif

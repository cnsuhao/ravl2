// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SBFACC2D_HEADER
#define RAVL_SBFACC2D_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/SBfAcc2d.hh"
//! lib=RavlCore
//! userlevel=Develop
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Core.Arrays.Buffer"

#include "Ravl/SBfAcc.hh"
#include "Ravl/BfAcc2Iter.hh"
#include "Ravl/Index2d.hh"
#include <assert.h>

class istream;
class ostream;

namespace RavlN {
  
  class BinOStreamC;
  class BinIStreamC;
  
  //: Basic access to buffer with limited size
  // The class SizeBufferAccessC enables to random indexed access to
  // a sequentially organised continous part of memory called buffer.
  // The access functions check if an accessed element is valid only in
  // debug mode.
  
  template <class DataC>
  class SizeBufferAccess2dC 
    : public SizeBufferAccessC<BufferAccessC<DataC> >
  {
  public:
    SizeBufferAccess2dC(SizeT nsize2)
      : size2(nsize2)
      {}
    //: Constructor.
    
    SizeBufferAccess2dC(const SizeBufferAccessC<BufferAccessC<DataC> > &ab,SizeT nsize2)
      : SizeBufferAccessC<BufferAccessC<DataC> >(ab),
      size2(nsize2)
      {}
    //: Constructor.

    SizeBufferAccess2dC(const BufferAccessC<BufferAccessC<DataC> > &ab,SizeT nsize1,SizeT nsize2)
      : SizeBufferAccessC<BufferAccessC<DataC> >(ab,nsize1),
      size2(nsize2)
      {}
    //: Constructor.
    
    SizeBufferAccess2dC()
      : size2(0)
      {}
    //: Default constructor.
    
    inline Contains(const Index2dC &i)  { 
      return (((UIntT) i.Col().V()) < size2) && 
	(((UIntT) i.Row().V()) < Size1()); 
      }
    //: Does this buffer contain the index i ?
    // Returns true if yes.
    
    inline DataC & operator[](const Index2dC & i) { 
      RavlAssert(((UIntT) i.Col()) < size2);
      return SizeBufferAccessC<BufferAccessC<DataC> >::operator[](i.Row())[i.Col()]; 
    }
    //: access to the item array[(i)]
    
    inline const DataC & operator[](const Index2dC & i) const { 
      RavlAssert(((UIntT) i.Col().V()) < size2);
      return SizeBufferAccessC<BufferAccessC<DataC> >::operator[](i.Row())[i.Col()]; 
    }
    //: return the item array[(i)]
    
    inline SizeBufferAccessC<DataC> operator[](IndexC i)
      { return SizeBufferAccessC<DataC>(SizeBufferAccessC<BufferAccessC<DataC> >::operator[](i),size2); }
    //: access to the item array[(i)]
    
    inline const SizeBufferAccessC<DataC> operator[](IndexC i) const
      { return SizeBufferAccessC<DataC>(SizeBufferAccessC<BufferAccessC<DataC> >::operator[](i),size2); }
    //: return the item array[(i)]
    
    inline SizeT Size1() const
      { return Size(); }
    //: Size.
    
    inline SizeT Size2() const
      { return size2; }
    //: Size.
    
    void Fill(const DataC &d);
    //: Fill array with value.
    
    IntT Stride() const {
      if(Size1() < 1)
	return size2;
      return (IntT) (SizeBufferAccessC<BufferAccessC<DataC> >::operator[](1).ReferenceElm() -  
		     SizeBufferAccessC<BufferAccessC<DataC> >::operator[](0).ReferenceElm());
    }
    //: Get the stide of the 2d array. 
    
    bool IsContinuous() const 
      { return Stride() == (IntT) size2; }
    //: Test if the array is allocated in a continous area of memory.
    // Note: this only checks the first two rows follow each other in
    // memory, this may miss other discontunities.
    
  protected:
    SizeT size2;
  };

  
  template<class DataC>
  void SizeBufferAccess2dC<DataC>::Fill(const DataC &d) {
    for(BufferAccess2dIterC<DataC> it(*this,size2);it;it++)
      *it = d;
  }
  
  template <class DataC>
  ostream & operator<<(ostream & s, const SizeBufferAccess2dC<DataC> & arr) {
    for(BufferAccess2dIterC<DataC> it(arr,arr.Size2());it;) {
      s << *it;
      for(;it.Next();) 
	s << ' ' << *it;
      s << '\n';
    }    
    return s;
  }
  
  template <class DataC>
  istream & operator>>(istream & s, SizeBufferAccess2dC<DataC> & arr) {
    for(BufferAccess2dIterC<DataC> it(arr,arr.Size2());it;it++) 
      s >> *it;
    return s;
  }
  
  template<class DataC>
  BinOStreamC &operator<<(BinOStreamC & s, const SizeBufferAccess2dC<DataC> & arr) {
    for(BufferAccess2dIterC<DataC> it(arr,arr.Size2());it;it++)
      s << *it;
    return s;
  }
  
  template<class DataC>
  BinIStreamC &operator>>(BinIStreamC & s, SizeBufferAccess2dC<DataC> & arr) {
    for(BufferAccess2dIterC<DataC> it(arr,arr.Size2());it;it++)
      s >> *it;
    return s;
  }

  
}
#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLRBFACCITER_HEADER
#define RAVLRBFACCITER_HEADER 1
///////////////////////////////////////////////////
//! userlevel=Normal
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BfAccIter.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Core.Arrays.Buffer"

#include "Ravl/BufferAccess.hh"
#include "Ravl/Assert.hh"

namespace RavlN {

  template <class DataC> class RangeBufferAccessC ;
  template <class DataC> class SizeBufferAccessC ;

  class IndexRangeC;
  
  //! userlevel=Advanced
  //: Iterator for access buffer.
  
  template <class DataC>
  class BufferAccessIterC {
  public:
    inline BufferAccessIterC();
    //: Default constructor.
    
    inline BufferAccessIterC(const BufferAccessC<DataC> &buff,const IndexRangeC &rng)
      { First(buff,rng); }
    //: Constructor.
    
    inline BufferAccessIterC(const BufferAccessC<DataC> &buff,UIntT size)
      { First(buff,size); }
    //: Constructor.
    
    inline BufferAccessIterC(const RangeBufferAccessC<DataC> &buff)
      { First(buff); }
    //: Constructor.

    inline BufferAccessIterC(const SizeBufferAccessC<DataC> &buff)
      { First(buff); }
    //: Constructor.
    
    inline BufferAccessIterC<DataC> &operator=(const RangeBufferAccessC<DataC> &buff);
    //: Assignment to a buffer.

    inline BufferAccessIterC<DataC> &operator=(const SizeBufferAccessC<DataC> &buff);
    //: Assignment to a buffer.
    
    inline bool First(const BufferAccessC<DataC> &buff,const IndexRangeC &rng);
    //: Goto fist element.
    
    inline bool First(const BufferAccessC<DataC> &buff,UIntT size);
    //: Goto fist element.
    
    inline bool First(const RangeBufferAccessC<DataC> &buff);
    //: Goto fist element.
    
    inline bool First(const SizeBufferAccessC<DataC> &buff);
    //: Goto fist element.
    
    inline bool IsElm() const
    { return at != endOfRow; }
    //: At valid element ?
    
    inline bool IsLast() const
    { return (at+1) == endOfRow; }
    //: Test if we're at the last valid element in the range.
    // Note: This is slightly slower than IsElm().
    
    inline operator bool() const
      { return at != endOfRow; }
    //: At valid element ?
    
    inline bool operator!() const
      { return at == endOfRow; }
    //: At valid element ?
    
    inline void Next()
      { RavlAssert(at != endOfRow); at++; }
    //: Goto next element.
    // Call ONLY if IsElm() is valid.
    
    inline void operator++(int) 
      { RavlAssert(at != endOfRow); at++; }
    //: Goto next element.
    // Call ONLY if IsElm() is valid.
    
    inline void operator++() 
      { RavlAssert(at != endOfRow); at++; }
    //: Goto next element.
    // Call ONLY if IsElm() is valid.
    
    DataC &operator*() 
      { return *at; }
    //: Access data.
    
    const DataC &operator*() const
      { return *at; }
    //: Access data.
    
    DataC *operator->() 
      { return at; }
    //: Access data.
    
    const DataC *operator->() const
      { return at; }
    //: Access data.
    
    inline DataC &Data()
      { return *at; }
    //: Access data.
    
    inline const DataC &Data() const
      { return *at; }
    //: Access data.
    
    inline DataC &Data1()
      { return *at; }  
    //: Access data.
    // Equivelent to .Data(), for compatability with other iterators.
    
    inline const DataC &Data1() const
      { return *at; }
    //: Const access data.
    // Equivelent to .Data(), for compatability with other iterators.
    
    inline void Invalidate();
    //: Make IsElm() return false.
    
  protected:
    DataC *at;
    const DataC *endOfRow;
  };
  
  //////////////////////////////////////////////////////
  
  template <class DataC>
  inline 
  BufferAccessIterC<DataC>::BufferAccessIterC()
    : at(0), 
      endOfRow(0)
  {}
  
  template <class DataC>
  inline 
  bool BufferAccessIterC<DataC>::First(const BufferAccessC<DataC> &buff,const IndexRangeC &rng) {
    if(rng.Size() <= 0) {
      at = 0;
      endOfRow = 0;
      return false;
    }
    at = const_cast<DataC *>(&buff[rng.Min()]);
    endOfRow = &(at[rng.Size()]);
    return true;
  }
  
  template <class DataC>
  inline 
  bool BufferAccessIterC<DataC>::First(const BufferAccessC<DataC> &buff,UIntT size) {
    if(size <= 0) {
      at = 0;
      endOfRow = 0;
      return false;
    }
    at = const_cast<DataC *>(buff.ReferenceElm());
    endOfRow = &(at[size]);
    return true;
  }
  
  template <class DataC>
  inline 
  bool BufferAccessIterC<DataC>::First(const RangeBufferAccessC<DataC> &buff) {
    if(buff.Size() <= 0) {
      at = 0;
      endOfRow = 0;
      return false;
    }
    at = const_cast<DataC *>(&buff[buff.IMin()]);
    endOfRow = &(at[buff.Size()]);
    return true;
  }
  
  template <class DataC>
  inline 
  bool BufferAccessIterC<DataC>::First(const SizeBufferAccessC<DataC> &buff) {
    if(buff.Size() <= 0) {
      at = 0;
      endOfRow = 0;
      return false;
    }
    at = const_cast<DataC *>(buff.ReferenceElm());
    endOfRow = &(at[buff.Size()]);
    return true;
  }
  
  template <class DataC>
  inline 
  BufferAccessIterC<DataC> &
  BufferAccessIterC<DataC>::operator=(const RangeBufferAccessC<DataC> &buff) { 
    First(buff); 
    return *this; 
  }
  
  template <class DataC>
  inline 
  BufferAccessIterC<DataC> &
  BufferAccessIterC<DataC>::operator=(const SizeBufferAccessC<DataC> &buff) { 
    First(buff); 
    return *this; 
  }
  
  template <class DataC>
  inline 
  void 
  BufferAccessIterC<DataC>::Invalidate() { 
    at = 0;
    endOfRow = 0; 
  }
  
}

#endif

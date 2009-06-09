// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SLICE1DITER2_HEADER
#define RAVL_SLICE1DITER2_HEADER 1
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Advanced
//! file="Ravl/Core/Container/Buffer/Slice1dIter2.hh"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Arrays"
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/Slice1dIter.hh"

// Ravl namespace.

namespace RavlN {
  
  //: Slice iterator.
  // Iterates through the elements in a slice
  // Note: this does NOT hold a reference to slices.

  template<class Data1T,class Data2T>
  class Slice1dIter2C {
  public:
    Slice1dIter2C()
      : m_at1(0),
        m_end(0)
    {}
    //: Creates an invalid iterator.
    
    Slice1dIter2C(const Slice1dC<Data1T> &vec1,const Slice1dC<Data2T> &vec2)
    { First(vec1,vec2); }
    //: Creates an iterator of 'nvec'
    
    Slice1dIter2C(const Slice1dC<Data1T> &vec1,
                  const Slice1dC<Data2T> &vec2,
                  const IndexRangeC &rng)
    { First(vec1,vec2,rng); }
    //: Creates an iterator of 'nvec1' and 'nvec2' over range 'rng'.
    
    void First(const Slice1dC<Data1T> &nvec1,const Slice1dC<Data2T> &nvec2);
    //: Goto first element.

    void First(const Slice1dC<Data1T> &nvec1,const Slice1dC<Data2T> &nvec2,const IndexRangeC &rng);
    //: Goto first element.

    void First() {
      m_at1 = m_start1;
      m_at2 = m_start2;
    }
    //: Goto first element.
    
    operator bool() const
    { return m_at1 != m_end; }
    //: Test if we're at a valid element.

    bool IsElm() const
    { return m_at1 != m_end; }
    //: Test if we're at a valid element.

    inline bool IsLast() const
    { return (m_at1+m_stride1) == m_end; }
    //: Test if we're at the last valid element in the slice.
    // This is slower than IsElm().
    
    inline bool IsFirst() const
    { return m_at1 == m_start1; }
    //: Test if we're at the first element in the slice.
    // This is slower than IsElm().
    
    void Next() { 
      m_at1 += m_stride1;
      m_at2 += m_stride2;
    }
    //: Goto next element.
    // Call ONLY if IsElm() is valid.
    
    void operator++(int) 
    { Next(); }
    //: Goto next element.
    // Call ONLY if IsElm() is valid.
    
    Data1T &Data1()
    { return *reinterpret_cast<Data1T *>(m_at1); }
    //: Access data at current element.

    const Data1T &Data1() const
    { return *reinterpret_cast<const Data1T *>(m_at1); }
    //: Access data at current element.

    Data2T &Data2()
    { return *reinterpret_cast<Data2T *>(m_at2); }
    //: Access data at current element.
    
    const Data2T &Data2() const
    { return *reinterpret_cast<const Data2T *>(m_at2); }
    //: Access data at current element.
    
    IntT Index() const
    { return (m_at1 - m_start1)/m_stride1; }
    //: Calculate current index.
    
  protected:
    char *m_start1;
    char *m_start2;
    char *m_at1;
    char *m_at2;
    char *m_end; // End index of 1.
    IntT m_stride1;
    IntT m_stride2;
  };
  
  /// Slice1dIterC /////////////////////////////////////////////////////////////
  
  template<class Data1T,class Data2T>
  void Slice1dIter2C<Data1T,Data2T>::First(const Slice1dC<Data1T> &vec1,
                                           const Slice1dC<Data2T> &vec2)
  { 
    RavlAssert(vec2.Size() <= vec1.Size());
    if(vec1.Size() <= 0) {
      m_start1 = 0;
      m_at1 = 0;
      m_end = 0;
      return;
    }
    m_start1 = const_cast<char *>(reinterpret_cast<const char *>(&vec1.First()));
    m_start2 = const_cast<char *>(reinterpret_cast<const char *>(&vec2.First()));
    m_at1 = m_start1;
    m_at2 = m_start2;
    m_stride1 = vec1.ByteStride();
    m_stride2 = vec2.ByteStride();
    m_end = &m_start1[vec1.Size() * vec1.ByteStride()];
  }
  
  template<class Data1T,class Data2T>
  void Slice1dIter2C<Data1T,Data2T>::First(const Slice1dC<Data1T> &vec1,
                                           const Slice1dC<Data2T> &vec2,
                                           const IndexRangeC &rng)
  {
    RavlAssert(vec1.Range().Contains(rng.Max()));
    RavlAssert(vec2.Range().Contains(rng.Max()));
    if(rng.Size() <= 0) {
      m_at1 = 0;
      m_end = 0;
      return;
    }  
    m_start1 = const_cast<char *>(reinterpret_cast<const char *>(&(vec1[rng.Min()])));
    m_start2 = const_cast<char *>(reinterpret_cast<const char *>(&(vec2[rng.Min()])));
    m_at1 = m_start1;
    m_at2 = m_start2;
    m_stride1 = vec1.ByteStride();
    m_stride2 = vec2.ByteStride();
    m_end = &(m_start1[rng.Size() * vec1.ByteStride()]);
  }
  
  
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SLICEITER_HEADER
#define RAVL_SLICEITER_HEADER 1
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Advanced
//! file="Ravl/Core/Container/Buffer/Slice1dIter.hh"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Arrays"
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/Slice1d.hh"

// Ravl namespace.

namespace RavlN {
  
  
  //: Slice iterator.
  // Iterates through the elements in a slice
  // Note: this does NOT hold a reference to slices.

  template<class DataT>
  class Slice1dIterC {
  public:
    Slice1dIterC()
      : m_start(0),
        m_place(0),
        m_end(0),
        m_stride(0)
    {}
    //: Creates an invalid iterator.
    
    Slice1dIterC(const Slice1dC<DataT> &slice)
    { First(slice); }
    //: Creates an iterator of 'nvec'
    
    Slice1dIterC(const Slice1dC<DataT> &slice,const IndexRangeC &rng)
    { First(slice,rng); }
    //: Creates an iterator for sub range of 'nvec'
    
    void First()
    { m_place = m_start; }
    //: Goto first element in current slice.
    
    void First(const Slice1dC<DataT> &vec);
    //: Goto first element in a slice.

    void First(const Slice1dC<DataT> &vec,const IndexRangeC &rng);
    //: Goto first element in a slice.
    
    operator bool() const
    { return m_place != m_end; }
    //: Test if we're at a valid element.
    
    bool IsElm() const
    { return m_place != m_end; }
    //: Test if we're at a valid element.
    
    inline bool IsLast() const
    { return (m_place+m_stride) == m_end; }
    //: Test if we're at the last valid element in the slice.
    // This is slower than IsElm().
    
    inline bool IsFirst() const
    { return m_place == m_start; }
    //: Test if we're at the first element in the slice.
    // This is slower than IsElm().
    
    void Next() 
    { m_place += m_stride; }
    //: Goto next element.
    // Call ONLY if IsElm() is valid.
    
    void operator++(int) 
    { m_place += m_stride; }
    //: Goto next element.
    // Call ONLY if IsElm() is valid.

    void operator++()
    { m_place += m_stride; }
    //: Goto next element.
    // Call ONLY if IsElm() is valid.
    
    DataT &Data()
    { return *reinterpret_cast<DataT *>(m_place); }
    //: Access data at current element.
    
    const DataT &Data() const
    { return *reinterpret_cast<const DataT *>(m_place); }
    //: Access data at current element.

    DataT &operator*() 
    { return *reinterpret_cast<DataT *>(m_place); }
    //: Access data.
    
    const DataT &operator*() const
    { return *reinterpret_cast<const DataT *>(m_place); }
    //: Access data.
    
    DataT *operator->() 
    { return reinterpret_cast<DataT *>(m_place); }
    //: Access data.
    
    const DataT *operator->() const
    { return reinterpret_cast<DataT *>(m_place); }
    //: Access data.
    
    IntT Index() const
    { return (m_place - m_start)/m_stride; }
    //: Calculate offset from first element iterated.
    
  protected:
    char *m_start;
    char *m_place;
    char *m_end;
    IntT m_stride;
  };
  
  /// Slice1dIterC ///////////////////////////////////////////////////////////////////
  
  template<class DataT>
  void Slice1dIterC<DataT>::First(const Slice1dC<DataT> &vec,const IndexRangeC &rng) {
    RavlAssert(vec.Range().Contains(rng));
    if(rng.Size() <= 0) {
      m_place = 0;
      m_end = 0;
      return ;
    }
    m_stride = vec.ByteStride();
    m_start= const_cast<char *>(reinterpret_cast<const char *>(&(vec[rng.Min()])));
    m_place= m_start;
    m_end = &(m_place[rng.Size() * vec.ByteStride()]);
  }


  template<class DataT>
  void Slice1dIterC<DataT>::First(const Slice1dC<DataT> &vec) {
    if(vec.Size() <= 0) {
      m_start = 0;
      m_place = 0;
      m_end = 0;
      return;
    }
    m_stride = vec.ByteStride();
    m_start = const_cast<char *>(reinterpret_cast<const char *>(&vec.First()));
    m_place = m_start;
    m_end = &(m_place[(IntT) vec.Size() * m_stride]);
  }
  
}

#endif

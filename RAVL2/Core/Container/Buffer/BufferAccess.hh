// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BUFFERACCESS_HEADER
#define RAVL_BUFFERACCESS_HEADER
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BufferAccess.hh"
//! lib=RavlCore
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.API.Core.Arrays.Buffer"

#include "Ravl/Index.hh"
#if RAVL_HAVE_TEMPLATEREQUIREALLDEFINITIONS
#include "Ravl/Stream.hh"
#include "Ravl/BinStream.hh"
#endif

namespace RavlN {

  //! userlevel=Advanced
  //: Basic unsized m_buffer.
  
  template <class DataT>
  class BufferAccessC {
  public:
    BufferAccessC()
      : m_buff(0)
    {}
    //: Default constructor.

    BufferAccessC(const BufferAccessC<DataT> &b)
      : m_buff(b.m_buff)
    {}
    //: Default constructor.
    
    BufferAccessC(DataT *dat)
      : m_buff(dat)
    {}
    //: Constructor.
    
    inline DataT * ReferenceElm() const
    { return m_buff; }
    // Returns the pointer to the reference element of the attached buffer.
    // The reference element need not to be the valid element of the buffer.
    
    inline void * ReferenceVoid() const
    { return (void *) m_buff; }
    // Returns the pointer to the reference element of the attached buffer.
    // The reference element need not to be the valid element of the buffer.
    // The function is intended to be used in printing.
    
    inline bool IsValid() const
    { return m_buff != 0; }
    // Returns TRUE if this buffer access is not a default access object.
    
    inline const DataT  & operator[](IntT i) const
    { return m_buff[i]; }
    // Read-only access to the 'i'-th element of the buffer.     
    
    inline DataT & operator[](IntT i)
    { return m_buff[i]; }
    // Read-write access  to the 'i'-th element of the buffer. 

    inline const DataT  & operator[](const IndexC &i) const
    { return m_buff[i.V()]; }
    // Read-only access to the 'i'-th element of the buffer.     
    
    inline DataT & operator[](const IndexC &i)
    { return m_buff[i.V()]; }
    // Read-write access  to the 'i'-th element of the buffer. 

    inline const DataT  & operator[](const SizeC &i) const
    { return m_buff[i.V()]; }
    // Read-only access to the 'i'-th element of the buffer.

    inline DataT & operator[](const SizeC &i)
    { return m_buff[i.V()]; }
    // Read-write access  to the 'i'-th element of the buffer.

    const BufferAccessC<DataT> &operator+=(IndexC ind) { 
      m_buff += ind.V();
      return *this;
    }
    //: Inplace Add index to start position.

    const BufferAccessC<DataT> &operator-=(IndexC ind) { 
      m_buff -= ind.V();
      return *this;
    }
    //: Inplace Subtract index from start position.
    
    BufferAccessC<DataT> operator-(IndexC ind) const 
    { return BufferAccessC<DataT>(m_buff - ind.V()); }
    //: Substract value from position, and return it as a new value.

    BufferAccessC<DataT> operator+(IndexC ind) const 
    { return BufferAccessC<DataT>(m_buff + ind.V()); }
    //: Substract value from position, and return it as a new value.

    bool operator==(const BufferAccessC<DataT> &ba) const
    { return m_buff == ba.m_buff; }
    //: Are two accesses the same ?
    
    bool operator!=(const BufferAccessC<DataT> &ba) const
    { return m_buff != ba.m_buff; }
    //: Are two accesses the same ?
        
  protected:
    DataT *m_buff;
  };

}

#endif

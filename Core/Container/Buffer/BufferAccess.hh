// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBUFFERACCESS_HEADER
#define RAVLBUFFERACCESS_HEADER
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BufferAccess.hh"
//! lib=RavlCore
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Core.Arrays.Buffer"

#include "Ravl/Index.hh"

namespace RavlN {

  //! userlevel=Advanced
  //: Basic unsized buffer.
  
  template <class DataC>
  class BufferAccessC {
  public:
    BufferAccessC()
      : buff(0)
      {}
    //: Default constructor.

    BufferAccessC(const BufferAccessC<DataC> &b)
      : buff(b.buff)
      {}
    //: Default constructor.
    
    BufferAccessC(DataC *dat)
      : buff(dat)
      {}
    //: Constructor.
    
    inline DataC * ReferenceElm() const
      { return buff; }
    // Returns the pointer to the reference element of the attached buffer.
    // The reference element need not to be the valid element of the buffer.
    
    inline void * ReferenceVoid() const
      { return (void *) buff; }
    // Returns the pointer to the reference element of the attached buffer.
    // The reference element need not to be the valid element of the buffer.
    // The function is intended to be used in printing.
    
    inline bool IsValid() const
      { return buff != 0; }
    // Returns TRUE if this buffer access is not a default access object.
    
    inline const DataC  & operator[](const IndexC i) const
      { return buff[i.V()]; }
    // Read-only access to the ('i'+1)-th element of the buffer.     
    
    inline DataC & operator[](const IndexC i)
      { return buff[i.V()]; }
    // Read-write access  to the ('i'+1)-th element of the buffer. 

    const BufferAccessC<DataC> &operator+=(IndexC ind) { 
      buff += ind.V();
      return *this;
    }
    //: Inplace Add index to start position.

    const BufferAccessC<DataC> &operator-=(IndexC ind) { 
      buff -= ind.V();
      return *this;
    }
    //: Inplace Subtract index from start position.
    
    BufferAccessC<DataC> operator-(IndexC ind) const {
      return BufferAccessC<DataC>(buff - ind.V());
    }
    //: Substract value from position, and return it as a new value.

    BufferAccessC<DataC> operator+(IndexC ind) const {
      return BufferAccessC<DataC>(buff + ind.V());
    }
    //: Substract value from position, and return it as a new value.
    
  protected:
    DataC *buff;
  };

}

#endif

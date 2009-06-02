// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BUFFERACCESS2DITERBASE_HH
#define	RAVL_BUFFERACCESS2DITERBASE_HH
///////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Buffer/BufferAccess2dIter2.hh"
//! lib=RavlCore
//! userlevel=Default
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/Types.hh"

namespace RavlN {

  //: Base class for 2d iterators.

  class BufferAccess2dIterBaseC {
  public:
    BufferAccess2dIterBaseC()
      : m_rit1(0),
        m_endRow(0),
        m_stride1(0)
    {}
    //: Constructor.
    
  protected:
    char  *m_rit1; // Start of current row for array 1
    const char *m_endRow;
    IntT m_stride1;
  };
}


#endif


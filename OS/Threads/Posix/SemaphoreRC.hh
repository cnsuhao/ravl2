// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SEMAPHORERC_HEADER
#define RAVL_SEMAPHORERC_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Posix/SemaphoreRC.hh"
//! lib=RavlThreads
//! userlevel=Normal
//! docentry="Ravl.OS.Threads"
//! author="Charles Galambos"
//! date="22/11/1999"

#include "Ravl/Threads/Semaphore.hh"
#include "Ravl/RCWrap.hh"

namespace RavlN
{
  //! userlevel=Normal
  //: Reference counted semaphore.
  
  class SemaphoreRC
    : public RCWrapC<SemaphoreC>
  {
  public:
    SemaphoreRC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SemaphoreRC(IntT count)
      : RCWrapC<SemaphoreC>(SemaphoreC(count))
    {}
    //: Default constructor.
    // Creates an invalid handle.

    bool Wait()
    { return Data().Wait(); }
    //: Wait for semaphore.
    
    bool TryWait() 
    { return Data().TryWait(); }
    //: Try and wait for semaphore
    
    bool Post() 
    { return Data().Post(); }
    //: Post a semaphore.
    
    int Count(void) const 
    { return Data().Count(); }
    //: Read semaphore count.
    
  private:
    void Dummy(void);
    //: Just to give it a file.
  };
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSIGCONNECTIONSET_HEADER
#define RAVLSIGCONNECTIONSET_HEADER 1
/////////////////////////////////////////////////////
//! docentry="Ravl.OS.Signals"
//! lib=RavlThreads
//! author="Charles Galambos"
//! date="13/12/2000"
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Tools/SignalConnectionSet.hh"

#include "Ravl/Threads/Signal.hh"
#include "Ravl/HSet.hh"

namespace RavlN 
{

  //! userlevel=Develop
  //: Signal connection set body.
  
  class SignalConnectionSetBodyC 
    : public RCBodyC
  {
  public:
    SignalConnectionSetBodyC()
      {}
    //: Constructor.
    
    ~SignalConnectionSetBodyC()
      { DisconnectAll(); }
    //: Destructor.
    
    void DisconnectAll();
    //: Disconnect everything.
    
    void operator+=(const SignalConnectorC &c)
      { cons += c; }
    //: Add a connection.
    
    void operator-=(const SignalConnectorC &c)
      { cons -= c; }
    //: Remove a connection.
    
  protected:
    HSetC<SignalConnectorC> cons;
  };
  
  //! userlevel=Normal
  //: Signal connection set body.
  // This class is used to construct a list of
  // connections that should be disconnected when the class
  // is destroyed or at some other point in processing.
  
  class SignalConnectionSetC 
    : public RCHandleC<SignalConnectionSetBodyC>
  {
  public:
    //SignalConnectionSetC()
    //{}
    //: Default constructor.
    // creates an invalid handle.
    
    SignalConnectionSetC()
      : RCHandleC<SignalConnectionSetBodyC>(*new SignalConnectionSetBodyC())
      {}
    //: Constructor.
    
    void DisconnectAll()
     { Body().DisconnectAll(); }
    //: Disconnect everything.
    
    void operator+=(const SignalConnectorC &c)
      { Body().operator+=(c); }
    //: Add a connection.
   
    void operator-=(const SignalConnectorC &c)
      { Body().operator-=(c); }
    //: Remove a connection.
    
  };
}

#endif

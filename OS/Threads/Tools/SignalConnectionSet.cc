// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/SignalConnectionSet.cc"

#include "Ravl/Threads/SignalConnectionSet.hh"

namespace RavlN {

  //: Disconnect everything.
  
  void SignalConnectionSetBodyC::DisconnectAll() {
    for(HSetIterC<SignalConnectorC> it(cons);it;it++)
      const_cast<SignalConnectorC &>(*it).Disconnect();
    cons.Empty();
  }
}




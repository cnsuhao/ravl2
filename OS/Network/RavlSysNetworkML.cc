// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
// $Id$
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/Network/RavlSysNetworkML.cc"

#include "Ravl/OS/NetStream.hh"

namespace RavlN {
  
  extern void StreamType_NetStream_MustLink();
  
  void RavlSysNetworkMustLink() {
    StreamType_NetStream_MustLink();
  }
}

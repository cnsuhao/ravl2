// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETPORT_HEADER
#define RAVL_NETPORT_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.OS.Network.NetPort"
//! example=exNetPort.cc
//! lib=RavlNet
//! rcsid="$Id$"
//! file="Ravl/OS/Network/NetPort.hh"

#include "Ravl/Types.hh"

namespace RavlN {
  
  enum NPMsgT {
    NPMsg_ReqConnection = 10, // Port,Datatype,input flag : 
    NPMsg_ReqInfo       = 11, //               : Request stream info
    NPMsg_ReqFailed     = 12, // Error         :    1=End of stream. 2=Get failed.
    NPMsg_ReqData       = 13, // Position      :
    NPMsg_StreamInfo    = 20, // At,Start,Size :
    NPMsg_Data          = 21, // Position,Data :
    NPMsg_Close         = 22  //               : Close stream.
  };
  //: Messages used in NetPorts.
  
}

#endif

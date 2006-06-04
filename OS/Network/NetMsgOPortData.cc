// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlNet

#include "Ravl/OS/NetMsgOPortData.hh"
#include "Ravl/OS/NetPort.hh"

namespace RavlN {
  
  //: Constructor.
  
  NetMsgOPortDataBodyC::NetMsgOPortDataBodyC(UIntT nid,
                                             const StringC &nname,
                                             const DPOPortBaseC &portBase,
                                             const DPSeekCtrlC &nSeekCtrl
                                             )
    : NetMsgRegisterBodyC(nid,nname),
      at(-1),
      oportBase(portBase),
      seekCtrl(nSeekCtrl),
      dataType(TypeInfo(portBase.OutputType()))
  {
    RavlAssert(dataType.IsValid());
  }
  

  //: Decode and execute a packet.
  
  bool NetMsgOPortDataBodyC::Decode(NetEndPointC &ep,BinIStreamC &pkt) {
    if(!oportBase.IsValid()) {
      //cerr << "NetOSPortServerBodyC<DataT>::ReqData(), Invalid output port.\n";      
      ep.Send(NPMsg_ReqFailed,1); // Report end of stream.
      return true;
    }
    
    // Decode position info.
    Int64T pos;
    pkt >> pos;
    
    //cerr << "NetOSPortServerBodyC<DataT>::ReqData(), Pos=" << pos << " at=" << at << " Tell=" << oport.Tell() <<"\n";
    if(at != pos && pos != (UIntT)(-1) && seekCtrl.IsValid()) {
      seekCtrl.Seek64(pos);
      at = pos;
    }
    
    if(dataType.ReadAndPut(pkt,oportBase)) {
      at++;
    } else { // Failed to get data.
      //cerr << "NetOSPortServerBodyC<DataT>::ReqData(), Put failed. \n";
      if(!oportBase.IsPutReady())
	ep.Send(NPMsg_ReqFailed,1); // Ug
      else
	ep.Send(NPMsg_ReqFailed,2); // Just get failed.
    }
    return true;
  }

}

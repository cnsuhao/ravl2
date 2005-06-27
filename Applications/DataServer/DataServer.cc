// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/DataServer/DataServer.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/TypeName.hh"

namespace RavlN {

  //: Constructor.
  
  DataServerBodyC::DataServerBodyC(const StringC &name)
    : NetPortManagerBodyC(name),
      verbose(false)
  {}
  
  //: Open server connection.
  
  bool DataServerBodyC::Open(const StringC &addr) {
    StringC empty;
    
    RegisterIPortRequestManager(TriggerR(*this,&DataServerBodyC::HandleRequestIPort,empty,empty,NetISPortServerBaseC()));
    RegisterOPortRequestManager(TriggerR(*this,&DataServerBodyC::HandleRequestOPort,empty,empty,NetOSPortServerBaseC()));
    
    return NetPortManagerBodyC::Open(addr);
  }

  //: Handle a request for an input port.
  
  bool DataServerBodyC::HandleRequestIPort(StringC name,StringC dataType,NetISPortServerBaseC &port) {
    cerr << "DataServerBodyC::HandleRequestIPort, Name=" << name << " Type=" << dataType << "\n";
    
    DPTypeInfoC typeInfo = TypeInfo(RTypeInfo(dataType));
    if(!typeInfo.IsValid()) {
      cerr << "DataServerBodyC::HandleRequestIPort, type '" << dataType << "' unknown. \n";
      return false; 
    }
    DPIPortBaseC ip;
    DPSeekCtrlC sc;
    if(!OpenISequenceBase(ip,sc,name,"",typeInfo.TypeInfo(),verbose)) {
      cerr << "DataServerBodyC::HandleRequestIPort, Failed to open stream '" << name << "' of type '" << dataType << "' \n";
      return false;
    }
    RavlAssert(ip.IsValid());
    port = NetISPortServerBaseC(AttributeCtrlC(ip),
                                ip,
                                sc,
                                name);
    return true;
  }
  
  //: Handle a request for an output port.
  
  bool DataServerBodyC::HandleRequestOPort(StringC name,StringC dataType,NetOSPortServerBaseC &port) {
    cerr << "DataServerBodyC::HandleRequestOPort, Name=" << name << " Type=" << dataType << "\n";
    
    DPTypeInfoC typeInfo = TypeInfo(RTypeInfo(dataType));
    if(!typeInfo.IsValid()) {
      cerr << "DataServerBodyC::HandleRequestIPort, type '" << dataType << "' unknown. \n";
      return false; 
    }
    DPOPortBaseC op;
    DPSeekCtrlC sc;
    if(!OpenOSequenceBase(op,sc,name,"",typeInfo.TypeInfo(),verbose)) {
      cerr << "DataServerBodyC::HandleRequestIPort, Failed to open stream '" << name << "' of type '" << dataType << "' \n";
      return false;
    }
    RavlAssert(op.IsValid());
    
    port = NetOSPortServerBaseC(AttributeCtrlC(op),
                                op,
                                sc,
                                name);
    
    return true;
  }
  
}

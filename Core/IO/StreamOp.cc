// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/StreamOp.cc"

#include "Ravl/DP/StreamOp.hh"

namespace RavlN {
  
  //: Input plugs.
  
  DListC<DPIPlugBaseC> DPStreamOpBodyC::IPlugs() const {
    return DListC<DPIPlugBaseC>();
  }
  
  //: Output plugs
  
  DListC<DPOPlugBaseC> DPStreamOpBodyC::OPlugs() const {
    return DListC<DPOPlugBaseC>();
  }
  
  //: Input ports.
  
  DListC<DPIPortBaseC> DPStreamOpBodyC::IPorts() const {
    return DListC<DPIPortBaseC>();
  }
    
  //: Output ports
  
  DListC<DPOPortBaseC> DPStreamOpBodyC::OPorts() const {
    return DListC<DPOPortBaseC>();
  }

  
}

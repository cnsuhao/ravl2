// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! userlevel=Advanced
//! docentry="Algorithms.Data Processing" 
//! example=exDataProc.cc
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/Entity.cc"

#include "Ravl/DP/Entity.hh"
#include "Ravl/RCAbstract.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/VirtualConstructor.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <typeinfo>
#include <iostream>
#else
#include <iostream.h>
#include <typeinfo.h>
#endif

namespace RavlN {
  
  ///// DPEntityBC /////////////////////////////////////////////////////////
  
  
  bool DPEntityBodyC::Save(ostream &out) const  { 
    return RCBodyVC::Save(out);
  }

  //: Save to binary stream.  
  
  bool DPEntityBodyC::Save(BinOStreamC &out) const {
    return RCBodyVC::Save(out);    
  }
  
  //: Creat a copy of this object.
  
  RCBodyVC &DPEntityBodyC::Copy() const {
    cerr << "DPEntityBodyC::Copy(). WARNING:Copy not implemented for " << typeid(*this).name() << "\n";
    return * new DPEntityBodyC();
  }
  
  
  ///// DPEntityC /////////////////////////////////////////////////////////

  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DPEntityBodyC,DPEntityC,RCHandleVC<DPEntityBodyC>);
  
#if 0
  // Constructor from stream.
  
  DPEntityC::DPEntityC(istream &strm)
    : RCHandleVC<DPEntityBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,DPEntityBodyC))
  {}
  
  //: Load from stream using virtual constructor.
  
  DPEntityC::DPEntityC(BinIStreamC &strm)
    : RCHandleVC<DPEntityBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,DPEntityBodyC))
  {}

  // This isn't really nessary, but is here as an example for making a class
  // with a virtual constructor.
  
  RAVL_INITVIRTUALCONSTRUCTOR(DPEntityBodyC);
#endif
  
  // Construct from abstract handle.
  
  DPEntityC::DPEntityC(const RCAbstractC &abst)
    : RCHandleVC<DPEntityBodyC>(abst) 
  { CheckHandleType(Body()); }
  
  
}

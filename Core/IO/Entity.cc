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
#include <iostream.h>

#if RAVL_HAVE_ANSICPPHEADERS
#include <typeinfo>
#else
#include <typeinfo.h>
#endif

namespace RavlN {
  
  ///// DPEntityBC /////////////////////////////////////////////////////////
  
  
  bool DPEntityBodyC::Save(ostream &out) const  { 
    // BodyRefCounterVC::Save(out) is made before TypeName code.
    // and so can't use the standard typenames. Hence we have
    // to write the class name for the virtual constructor here.
    out << TypeName(typeid(*this).name()) << "\n";
    return out.good();
  }
  
  //: Creat a copy of this object.
  
  RCBodyVC &DPEntityBodyC::Copy() const {
    cerr << "DPEntityBodyC::Copy(). WARNING:Copy not implemented for " << typeid(*this).name() << "\n";
    return * new DPEntityBodyC();
  }
  
  
  ///// DPEntityC /////////////////////////////////////////////////////////

  // Constructor from stream.

  
  DPEntityC::DPEntityC(istream &in)
#if 0
    : RCHandleC<DPEntityBodyC> (VirtualConstructorC::DynLoad(in))
  { CheckHandleType(Body()); } 
#else
  {}
#endif
  
  // Construct from abstract handle.
  
  DPEntityC::DPEntityC(const RCAbstractC &abst)
    : RCHandleC<DPEntityBodyC>(abst) 
  { CheckHandleType(Body()); }
  

}

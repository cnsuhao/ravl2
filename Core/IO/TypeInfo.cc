// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/TypeInfo.cc"

#include "Ravl/DP/TypeInfo.hh"
#include "Ravl/DList.hh"
#include "Ravl/MTLocks.hh"

namespace RavlN {
  ////////////////////////////
  //: Default constructor.
  
  DPTypeInfoBodyC::DPTypeInfoBodyC(const type_info &typeInfo)
    : typeInfo(typeInfo)
  { 
    MTWriteLockC writeLock;
    Types()[typeInfo.name()] = DPTypeInfoC(*this); 
  }
  
  /////////////////////////////
  //: Create instance of the type with the default constructor.
  
  RCWrapAbstractC DPTypeInfoBodyC::Create() const  {
    RavlAssert(0); // Should never be called.
    return RCWrapAbstractC();
  }
  
  //: Create instance of the type from stream constructor.
  
  RCWrapAbstractC DPTypeInfoBodyC::Create(istream &) const {
    RavlAssert(0); // Should never be called.
    return RCWrapAbstractC();
  }
  
  /////////////////////////////
  //: Attempt to load object from a file.
  
  RCWrapAbstractC DPTypeInfoBodyC::Load(const StringC &,const StringC &fmtName,bool) const {
    RavlAssert(0); // Should never be called.
    return RCWrapAbstractC();
  }
  
  //: Put generic object to port.
  // Will throw ExceptionErrorCastC if types aren't correct, or in debug mode
  // an assert may fail.
  
  bool 
  DPTypeInfoBodyC::Put(DPOPortBaseC &,const RCWrapAbstractC &) throw(ExceptionErrorCastC) {
    RavlAssert(0); // Abstract function called.
    return false;
  }
  
  //: Get generic object from port.
  // Will throw ExceptionErrorCastC if types aren't correct, or in debug mode
  // an assert may fail.
  
  RCWrapAbstractC 
  DPTypeInfoBodyC::Get(DPIPortBaseC &) throw(ExceptionErrorCastC) {
    RavlAssert(0); // Abstract function called.
    return RCWrapAbstractC();
  }
  
  //: Create an input pipe
  
  DPIPipeBaseC DPTypeInfoBodyC::CreateIPipe(const DPEntityC &) const {
    RavlAssert(0); // Abstract function called.
    return DPIPipeBaseC();
  }
  
  //: Create an output pipe
  
  DPOPipeBaseC DPTypeInfoBodyC::CreateOPipe(const DPEntityC &) const {
    RavlAssert(0); // Abstract function called.
    return DPOPipeBaseC();
  }
  
  /////////////////////////////
  //: Access type list.
  
  HashC<const char *,DPTypeInfoC> &DPTypeInfoBodyC::Types() {
    static HashC<const char *,DPTypeInfoC> typelist;
    return typelist;
  }
  
  //////// DPTypeInfoC /////////////////////////////////////////////////
  
  //: Lookup type. 
  // Creates an invalid handle if failed.
  
  DPTypeInfoC::DPTypeInfoC(const type_info &ti) 
    : DPEntityC(true)
  {
    MTReadLockC readLock;
    DPTypeInfoC *tip = DPTypeInfoBodyC::Types().Lookup(ti.name());
    if(tip != 0)
      (*this) = *tip;
  }
  
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"

#include "Ravl/DF/DFSystem.hh"
#include "Ravl/DF/DFData.hh"
#include "Ravl/DF/DFPort.hh"
#include "Ravl/IO.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  
  //: Constructor.
  
  DFSystemBodyC::DFSystemBodyC(const StringC &nname)
    : name(nname),
      sigChange(DFOU_CHANGED)
  {}
  
  //: Add an object to the system.
  
  bool DFSystemBodyC::AddObject(DFObjectC &obj) {
    objects += obj;
    sigChange(DFOU_ADDED,obj);
    return true;
  }

  //: Remove an object from the system.
  
  bool DFSystemBodyC::DelObject(DFObjectC &obj) {
    if(objects.Del(obj)) {
      sigChange(DFOU_DELETED,obj);
      return true;
    }
    return false;
  }
  
  //: Create an input port.
  
  DFObjectC DFSystemBodyC::CreateIPort(const StringC &name) {
    DFIPortC ip(name);
    AddObject(ip);
    return ip;
  }
  
  //: Create an output port.
  
  DFObjectC DFSystemBodyC::CreateOPort(const StringC &name) {
    DFIPortC op(name);
    AddObject(op);
    return op;
  }
  
  //: Attempt to link two objects.
  // Will return an invalid handle if operation fails.
  
  DFObjectC DFSystemBodyC::CreateLink(const DFObjectC &obj1,const DFObjectC &obj2,bool autoConvert) {
    ONDEBUG(cerr << "DFSystemBodyC::CreateLink(), Called. \n");
    DFObjectC ret;
    if(!obj1.IsValid() || ! obj2.IsValid())
      return ret;
    if(obj1 == obj2)
      return ret; // Can't link to itself.
    ret = DFObjectC(obj1).LinkTo(DFObjectC(obj2),autoConvert);
    if(ret.IsValid())
      AddObject(ret);
    return ret;
  }

  //: Load object from file and add it the system.
  
  DFObjectC DFSystemBodyC::LoadObject(const StringC &fn) {
    DFObjectC ret;
    ONDEBUG(cerr << "DFSystemBodyC::LoadObject(" << fn << ") Called. \n");
    if(!Load(fn,ret))
      return DFObjectC();
    AddObject(ret);
    return ret;
  }

}

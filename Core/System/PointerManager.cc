// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/PointerManager.cc"

#include "Ravl/PointerManager.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlN {
  //:----------------------------------------------------
  
  //: Destructor.
  
  StoredPointerC::~StoredPointerC() {
    ONDEBUG(cerr << "StoredPointerC::~StoredPointerC(), Called. " << (void *) actions << " " << (void *) obj << "\n");
    if(actions != 0 && obj != 0)
      actions->Free(obj);
  }
  
  //:----------------------------------------------------
  
  //: Default constructor.
  
  PointerManagerBodyC::PointerManagerBodyC(bool forSave) 
    : idAlloc(0)
  {}
  
  //: Destructor.
  
  PointerManagerBodyC::~PointerManagerBodyC() 
  { ONDEBUG(cerr << "PointerManagerBodyC::~PointerManagerBodyC(), Called. \n"); }
  
  //:----------------------------------------------------
  
  BinOStreamC &operator<<(BinOStreamC &strm,IOPtrC obj) {
    if(!strm.PointerManager().IsValid())
      strm.PointerManager() = PointerManagerC(true);
    PointerManagerC mgr(strm.PointerManager());
    UIntT id;
    if(mgr.Lookup(obj,id)) { // Seen this object already ?
      ONDEBUG(cerr << "Storing id " << id << " from " << *((void **)obj.Pointer()) << "\n");
      strm << id;
    } else {
      // Not seen before, save id then object.
      id = mgr.Insert(obj);
      ONDEBUG(cerr << "Storing data with id " << id << " \n");
      strm << id;
      obj.Save(strm);
    }
    return strm;
  }
  
  //: Load managed pointer from a stream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,IOPtrC obj) {
    if(!strm.PointerManager().IsValid())
      strm.PointerManager() = PointerManagerC(false);
    PointerManagerC mgr(strm.PointerManager());
    UIntT id;
    strm >> id;
    StoredPointerC *ptr = mgr.Lookup(id);
    if(ptr != 0) { // Seen this object already ?
      ONDEBUG(cerr << "Loading id " << id << " \n");
      obj.Assign(*ptr);
    } else {
      // Not seen before, save id then object.
      ONDEBUG(cerr << "Loading data with id " << id << "\n");
      obj.Load(strm);
      mgr.Insert(id,obj);
    }
    return strm;
  }


}

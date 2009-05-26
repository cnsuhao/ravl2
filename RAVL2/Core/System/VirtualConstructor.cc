// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/VirtualConstructor.cc"

#include "Ravl/VirtualConstructor.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/BinStream.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Access virtual constructor table.
  
  static HashC<const char *,VirtualConstructorC> &Table() {
    static HashC<const char *,VirtualConstructorC> tab;
    return tab;
  }
  
  bool CreateVirtualConstructorAlias(const char *newName,const char *oldName) {
    VirtualConstructorC *oldVC = Table().Lookup(oldName);
    if(oldVC == 0) {
      std::cerr << "Failed to construct virtual construtor alias '" << newName << "' for unknown type '" << oldName << "'\n";
      return false;
    }
    if(Table().Lookup(newName) != 0) {
      std::cerr << "Failed to construct virtual construtor alias '" << newName << "' for '" << oldName << "', name in use. \n";
      return false;
    }
    Table()[newName] = *oldVC;
    return true;
  }

  //: Default constructor.
  
  VirtualConstructorBodyC::VirtualConstructorBodyC(const type_info &info,const char *typesname)
  {
    ONDEBUG(cerr << "VirtualConstructorBodyC::VirtualConstructorBodyC(), Registering '" << info.name() << "' as '" <<typesname << "' \n");
    Table()[typesname] = VirtualConstructorC(*this);
    AddTypeName(info,typesname);
    
  }

  //: Construct from an istream.
  // Dummy method.
  
  VirtualConstructorBodyC::VirtualConstructorBodyC(istream &in)
    : RCBodyVC(in)
  {}
  
  //: Construct from an istream.
  // Dummy method
  
  VirtualConstructorBodyC::VirtualConstructorBodyC(BinIStreamC &in) 
    : RCBodyVC(in)
  {}
  
  //: Load an object of this type from an istream
  
  RCBodyVC *VirtualConstructorBodyC::Load(istream &in) const { 
    RavlAssertMsg(0,"VirtualConstructorBodyC::Load(), Abstract method called. ");
    return 0; 
  }
  
  //: Load an object of this type from a BinIStreamC
  
  RCBodyVC *VirtualConstructorBodyC::Load(BinIStreamC &in) const {
    RavlAssertMsg(0,"VirtualConstructorBodyC::Load(), Abstract method called. ");
    return 0; 
  }

  
  RCBodyVC *VCLoad(istream &s) {
    StringC name;
    s >> name;
    VirtualConstructorC vc;
    if(!Table().Lookup(name.chars(),vc)) {
      cerr << "WARNING: Failed to find virtual constructor for type '" << name.chars() << "' \n";
      return 0; // Type not found.
    }
    return vc.Load(s);
  }
  
  RCBodyVC *VCLoad(BinIStreamC &s) {
    StringC name;
    s >> name;
    VirtualConstructorC vc;
    if(!Table().Lookup(name.chars(),vc)) {
      cerr << "WARNING: Failed to find virtual constructor for type '" << name.chars() << "' \n";
      return 0; // Type not found.
    }
    return vc.Load(s);
  }
  
  // The following is included for debugging only.
  
  RAVL_INITVIRTUALCONSTRUCTOR(VirtualConstructorBodyC)
}

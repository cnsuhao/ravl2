// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/VirtualConstructor.hh"
#include "Ravl/TypeName.hh"

namespace RavlN {

  //: Default constructor.
  
  VirtualConstructorBodyC::VirtualConstructorBodyC(const type_info &info,const char *typesname)
  {
    AddTypeName(info,typesname);
  }
  
  //: Load an object of this type from an istream
  
  RCBodyC *VirtualConstructorBodyC::Load(istream &in) const
  { return 0; }
  
  //: Load an object of this type from a BinIStreamC
  
  RCBodyC *VirtualConstructorBodyC::Load(BinIStreamC &in) const
  { return 0; }

  //: Access virtual constructor table.
  
  static HashC<const char *,VirtualConstructorC> &Table() {
    static HashC<const char *,VirtualConstructorC> tab;
    return tab;
  }
  
  RCBodyC *VCLoad(istream &s) {
    StringC name;
    s >> name;
    VirtualConstructorC vc;
    if(!Table().Lookup(name.chars(),vc))
      return 0; // Type not found.
    return vc.Load(s);
  }
  
  RCBodyC *VCLoad(BinIStreamC &s) {
    StringC name;
    s >> name;
    VirtualConstructorC vc;
    if(!Table().Lookup(name.chars(),vc))
      return 0; // Type not found.
    return vc.Load(s);
  }
  
}

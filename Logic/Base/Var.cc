// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/Var.hh"
#include "Ravl/Logic/BindSet.hh"

namespace RavlLogicN {
 
  //: Unify with another variable.
  
  bool VarBodyC::Unify(const LiteralC &x,BindSetC &bs) const {
    //: Bind value 'oth' to this.
    LiteralC var(const_cast<VarBodyC &>(*this));
    LiteralC val;
    if(bs.Resolve(var,val)) // Is x bound to something ?
      return val.Unify(x,bs);
    if(bs.Resolve(x,val)) 
      return var.Unify(val,bs);
    return bs.Bind(var,x);
  }
  
  //: Unify 

  bool VarBodyC::UnifyLiteral(const LiteralBodyC &oth,BindSetC &bs) const {
    //: Bind this to 'oth'
    LiteralC val(const_cast<LiteralBodyC &>(oth));
    return VarBodyC::Unify(val,bs);
  }

  //: Dump info in human readable format to stream 'out'.
  void VarBodyC::Dump(ostream &out) {
    out << "V:" << ((void *) this);
  }

  //: Get the name of symbol.
  StringC VarBodyC::Name() const { 
    return StringC("V:") + StringC((UIntT) this); 
  }
 
}

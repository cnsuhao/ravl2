// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/StateSet.hh"
#include "Ravl/Logic/LiteralIterWrap.hh"
#include "Ravl/Logic/LiteralFilterIter.hh"
#include "Ravl/DList.hh"

namespace RavlLogicN {
  
  
  //: Make a copy of this state.
  
  RCBodyVC &StateSetBodyC::Copy() const {
    return *new StateSetBodyC(data.Copy());
  }
  
  //: Ask if a literal is set.
  
  bool StateSetBodyC::Ask(const LiteralC &lit) const {
    return data[lit];
  }
  
  //: Ask if a literal is set.
  
  bool StateSetBodyC::Ask(const LiteralC &lit,BindSetC &binds) const {
    if(lit.IsGrounded())
      return data[lit];
    RavlAssertMsg(0,"StateSetBodyC::Ask(LiteralC,BindSetC), Not implemented. ");
    return data[lit];
  }
  
  //: Set a literal.
  
  bool StateSetBodyC::Tell(const LiteralC &lit) {
    data += lit;
    return true;
  }
  
  //: List contents of state.
  
  LiteralIterC StateSetBodyC::List() const {
    return LiteralIterWrapC<HSetIterC<LiteralC> >(data);
  }
  
  //: Search state for matching literals.
  
  LiteralIterC StateSetBodyC::ListFilter(const LiteralC &it,BindSetC &bnds) const {
    return LiteralFilterIterC(LiteralIterWrapC<HSetIterC<LiteralC> >(data,bnds),it);
  }
  
  //: Return the number of literals in the state.
  
  UIntT StateSetBodyC::Size() const {
    return data.Size();
  }
  
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/Not.hh"
#include "Ravl/Logic/BindSet.hh"

namespace RavlLogicN {

  //: Generate hash value for condition.
  
  UIntT NotBodyC::Hash() const {
    UIntT ret = 0;
    if(term.IsValid())
      ret += term.Hash() ^ 0xf0f0f0f0;
    return ret;
  }
  
  //: Is this equal to another condition ?
  
  bool NotBodyC::IsEqual(const LiteralC &oth) const {
    NotC isNot(oth);
    if(!isNot.IsValid())
      return false;
    return term.IsEqual(isNot.Term());
  }

  //: Is this a simple expression with no variables ?
  bool NotBodyC::IsGrounded() const {
    if(!term.IsValid())
      return true;
    return term.IsGrounded();
  }
  
  //: Unify with another variable.
  bool NotBodyC::Unify(const LiteralC &oth,BindSetC &bs) const {
    BindMarkT bm = bs.Mark();
    if(term.Unify(oth,bs)) {
      bs.Undo(bm);
      return false;
    }
    return true;
  }
  
  //: Get the name of symbol.
  
  StringC NotBodyC::Name() const {
    return StringC("!") + term.Name(); 
  }

  //: Test if condition is true in 'state'.
  
  bool NotBodyC::Test(const StateC &state,BindSetC &binds) const {
    return !term.Test(state,binds);
  }
  
  //: Not operator.
  // FIXME :- Do more simplification.

  LiteralC operator!(const LiteralC &lit) {
    NotC xnot(lit);
    if(xnot.IsValid())
      return xnot.Term(); // Double not simplifies.
    return NotC(lit);
  }

  
  
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/Not.cc"

#include "Ravl/Logic/Not.hh"
#include "Ravl/Logic/BindSet.hh"
#include "Ravl/Logic/LiteralFilterIter.hh"
#include "Ravl/Logic/State.hh"

namespace RavlLogicN {
  
  LiteralC literalNot("not");

  //: Default constructor.
  
  NotBodyC::NotBodyC()
    : ConditionBodyC(2)
  { args[0] = literalNot; }
  
  //: Constructor.
  
  NotBodyC::NotBodyC(const LiteralC &nterm)
    : ConditionBodyC(2)
  {
    args[0] = literalNot;
    args[1] = nterm;
  }
  
  //: Is this equal to another condition ?
  
  bool NotBodyC::IsEqual(const LiteralC &oth) const {
    NotC isNot(oth);
    if(!isNot.IsValid())
      return false;
    return Term().IsEqual(isNot.Term());
  }
  
  //: Is this a simple expression with no variables ?
  
  bool NotBodyC::IsGrounded() const {
    if(!Term().IsValid())
      return true;
    return Term().IsGrounded();
  }
  
  //: Unify with another variable.
  
  bool NotBodyC::Unify(const LiteralC &oth,BindSetC &bs) const {
    BindMarkT bm = bs.Mark();
    if(Term().Unify(oth,bs)) {
      bs.Undo(bm);
      return false;
    }
    return true;
  }
  
  //: Get the name of symbol.
  
  StringC NotBodyC::Name() const 
  { return StringC("!") + Term().Name(); }

  //: Test if condition is true in 'state'.
  
  bool NotBodyC::Test(const StateC &state,BindSetC &binds) const {
    RavlAssert(Term().IsValid());
    return !Term().Test(state,binds);
  }
  
  //: Return iterator through possibile matches to this literal in 'state', if any.
  
  LiteralIterC NotBodyC::Solutions(const StateC &state,BindSetC &binds) const {
    NotC me(const_cast<NotBodyC &>(*this));
    return LiteralFilterIterC(state.List(),me);
  }
  
  //: Not operator.
  // FIXME :- Do more simplification.

  LiteralC operator!(const LiteralC &lit) {
    NotC xnot(lit);
    if(xnot.IsValid())
      return xnot.Term(); // Double not simplifies.
    return NotC(true,lit);
  }

  
  
}

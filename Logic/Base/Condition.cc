// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/Condition.cc"

#include "Ravl/Logic/Condition.hh"
#include "Ravl/Logic/BindSet.hh"
#include "Ravl/Logic/LiteralIter.hh"

namespace RavlLogicN {

  //: Generate hash value for condition.
  
  UIntT ConditionBodyC::Hash() const {
    RavlAssert(0); // Abstract method called.
    return 0;
  }
  
  //: Is this equal to another condition ?
  
  bool ConditionBodyC::IsEqual(const ConditionC &oth) const {
    return this == &oth.Body();
  }
  
  
  //: Is this a simple expression with no variables ?
  bool ConditionBodyC::IsGrounded() const { 
    RavlAssertMsg(0,"ConditionBodyC::IsGrounded(), Abstract function called. ");
    return true; 
  }
  
  //: Unify with another variable.
  
  bool ConditionBodyC::Unify(const LiteralC &oth,BindSetC &bs) const {
    RavlAssertMsg(0,"ConditionBodyC::Unify(), Abstract function called. ");
    return false;
  }

  //: Get the name of symbol.
  
  StringC ConditionBodyC::Name() const {
    return StringC("Condition:") + StringC((UIntT) this);
  }

  //: Test if condition is true in 'state'.
  
  bool ConditionBodyC::Test(const StateC &state,BindSetC &binds) const {
    BindMarkT mark = binds.Mark();
    LiteralIterC ret = Solutions(state,binds);
    RavlAssert(ret.IsValid());
    if(!ret.IsElm()) {
      binds.Undo(mark);
      return false;
    }
    return true;
  }
  
  //: Return iterator through possibile matches to this literal in 'state', if any.
  
  LiteralIterC ConditionBodyC::Solutions(const StateC &state,BindSetC &binds) const {
    LiteralIterC ret;
    RavlAssertMsg(0,"ConditionBodyC::Solutions(), Abstract method called. ");
    return ret;
  }

}

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
  
  //: Add some terms.
  
  void ConditionBodyC::AddTerms(const SArray1dC<LiteralC> &terms) {
    SArray1dC<LiteralC> newun(args.Size() + terms.Size());
    for(BufferAccessIter2C<LiteralC,LiteralC> it(args,newun);it;it++)
      it.Data2() = it.Data1();
    for(BufferAccessIter2C<LiteralC,LiteralC> it(args.From(args.Size()),terms);it;it++)
      it.Data2() = it.Data1();
    args = newun;
  }
  
  //: Add a term.
  
  void ConditionBodyC::AddTerm(const LiteralC &term) {
    SArray1dC<LiteralC> newun(args.Size() + 1);
    for(BufferAccessIter2C<LiteralC,LiteralC> it(args,newun);it;it++)
      it.Data2() = it.Data1();
    newun[args.Size()] = term;
    args = newun;
  }

}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/Tuple.hh"
#include "Ravl/SArr1Iter2.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/Logic/BindSet.hh"

namespace RavlLogicN {

  //: Is this a simple expression with no variables ?
  
  bool TupleBodyC::IsGrounded() const {
    for(SArray1dIterC<LiteralC> it(Args());it;it++)
      if(!it->IsGrounded())
	return false;
    return true;
  }
  
  //: Unify with another variable.
  
  bool TupleBodyC::Unify(const LiteralC &oth,BindSetC &bs) const {
    TupleC x(oth);
    if(!x.IsValid())
      return false; // Can only unify expr with expr's.
    if(x.Arity() != Arity())
      return false; // Can only unify if equal sizes.
    BindMarkT bm = bs.Mark();
    for(SArray1dIter2C<LiteralC,LiteralC> it(Args(),x.Args());it;it++) {
      RavlAssert(it.Data1().IsValid());
      RavlAssert(it.Data2().IsValid());
      if(!it.Data1().Unify(it.Data2(),bs)) {
	bs.Undo(bm);
	return false;
      }
    }
    return true;
  }

  //: Unify with simple symb
   
  bool TupleBodyC::UnifyLiteral(const LiteralBodyC &oth,BindSetC &bs) const {
    // Can't unify with a simple Literal.
    return false;
  }

  //: Get the name of symbol.
  
  StringC TupleBodyC::Name() const {
    StringC out;
    SArray1dIterC<LiteralC> it(Args());
    out += '(';
    if(it) {
      if(it->IsValid())
	out += it->Name();
      else
	out += "-NIL-";
      it++;
      for(;it;it++) {
	out += ',';
	if(it->IsValid())
	  out += it->Name();
	else
	  out += "-NIL-";
      }
    }
    out += ')';
    return out;
  }

  //: Dump info in human readable format to stream 'out'.
  void TupleBodyC::Dump(ostream &out) {
    out << Name();
  }

}

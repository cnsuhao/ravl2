// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/And.cc"

#include "Ravl/Logic/And.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/SArr1Iter2.hh"
#include "Ravl/Logic/BindSet.hh"
#include "Ravl/Logic/StateAndIter.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {
  
  LiteralC literalAnd("and");
  
  //: Default constructor.
  
  AndBodyC::AndBodyC()
    : ConditionBodyC(1)
  { args[0] = literalAnd; }
  
  //: Create an and term with 'arity' elements.
  
  AndBodyC::AndBodyC(UIntT arity)
    : ConditionBodyC(arity)
  { args[0] = literalAnd; }
  
  //: Constructor.
  
  AndBodyC::AndBodyC(const SArray1dC<LiteralC> &set)
  {
    if(set.Size() == 0) {
      args = SArray1dC<LiteralC>(1);
      args[0] = literalAnd;
      return ;
    }
    if(set[0] != literalAnd) {
      args =SArray1dC<LiteralC>(set.Size() + 1);
      args[0] = literalAnd;
      for(BufferAccessIter2C<LiteralC,LiteralC> it(set,args.BufferFrom(1,set.Size()));it;it++)
	it.Data2() = it.Data1();
    } else
      args = set;
    ONDEBUG(cerr << "AndBodyC::AndBodyC(), Name=" << Name() << "\n");
  }
  
  //: Is this equal to another condition ?
  
  bool AndBodyC::IsEqual(const LiteralC &oth) const {
    AndC a(oth);
    if(!a.IsValid())
      return false;
    RavlAssertMsg(0,"AndBodyC::IsEqual(), Not implemented. ");
    return false;
  }
  
  
  //: Unify with another variable.
  bool AndBodyC::Unify(const LiteralC &oth,BindSetC &bs) const {
    BindMarkT bm = bs.Mark();
    for(SArray1dIterC<LiteralC> it(args);it;it++) {
      if(!it->Unify(oth,bs)) {
	bs.Undo(bm);
	return false;
      }
    }
    return true;
  }
  
  //: Add literal.
  
  void AndBodyC::AndAdd(const LiteralC &lit) {
    // FIXME :- Try and minimize
    AndC an(lit);
    if(an.IsValid()) 
      AndAdd(an.Terms());
    else
      AddTerm(lit);
  }
  
  //: Add literals.
  
  void AndBodyC::AndAdd(const SArray1dC<LiteralC> &lits) {
    // FIXME :- Try and minimize
    AddTerms(lits);
  }
  
  //: Return iterator through possibile matches to this literal in 'state', if any.
  
  LiteralIterC AndBodyC::Solutions(const StateC &state,BindSetC &binds) const {
    return StateAndIterC(state,AndC(const_cast<AndBodyC &>(*this)),binds);    
  }

  
  //: And two terms.
  // FIXME :- Do more simplification.
  
  TupleC operator*(const LiteralC &l1,const LiteralC &l2) {
    SizeT size = 0;
    ONDEBUG(cerr << "operator*(LiteralC,LiteralC) Called for " << l1 << " and " << l2 << "\n");
    AndC a1(l1);
    if(a1.IsValid())
      size += a1.Size();
    else
      size++;
    AndC a2(l2);
    if(a2.IsValid())
      size += a2.Size();
    else
      size++;
    SArray1dC<LiteralC> arr(size+1);
    arr[0] = literalAnd;
    UIntT at = 1;
    if(a1.IsValid()) {
      for(SArray1dIter2C<LiteralC,LiteralC> it(a1.Terms().After(0),arr.From(at));it;it++)
	it.Data2() = it.Data1();
      at += a1.Size();
    } else
      arr[at++] = l1;
    if(a2.IsValid()) {
      for(SArray1dIter2C<LiteralC,LiteralC> it(a2.Terms().After(0),arr.From(at));it;it++)
	it.Data2() = it.Data1();
    } else
      arr[at] = l2;
    ONDEBUG(cerr << "operator*(LiteralC,LiteralC) Result=" << arr << "\n");
    return AndC(arr); 
  }
  //: And operator.

}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/Or.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/SArr1Iter2.hh"
#include "Ravl/Logic/BindSet.hh"
#include "Ravl/Logic/StateOrIter.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {
  
  //: Generate hash value for condition.
  
  UIntT OrBodyC::Hash() const {
    UIntT ret = 1;
    for(SArray1dIterC<LiteralC> it(terms);it;it++)
      ret += it->Hash();
    return ret;
  }
    
  //: Is this equal to another condition ?
  
  bool OrBodyC::IsEqual(const LiteralC &oth) const {    
    OrC a(oth);
    if(!a.IsValid())
      return false;
    RavlAssertMsg(0,"OrBodyC::IsEqual(), Not implemented. ");
    return false;

  }
  
  //: Is this a simple expression with no variables ?
  
  bool OrBodyC::IsGrounded() const {
    for(SArray1dIterC<LiteralC> it(terms);it;it++)
      if(!it->IsGrounded())
	return false;
    return true; 
  }

  //: Unify with another variable.
  
  bool OrBodyC::Unify(const LiteralC &oth,BindSetC &bs) const {
    BindMarkT bm = bs.Mark();
    for(SArray1dIterC<LiteralC> it(terms);it;it++) {
      if(it->Unify(oth,bs))
	return true;
      bs.Undo(bm);
    }
    return false;
  }
  
  //: Get the name of symbol.
  
  StringC OrBodyC::Name() const {
    StringC ret("or(");
    SArray1dIterC<LiteralC> it(terms);
    if(it) {
      ret += it->Name();
      it++;
      for(;it;it++) {
	ret += ',';
	ret += it->Name();
      }
    }
    ret +=')';
    return ret;
  }

  //: Return iterator through possibile matches to this literal in 'state', if any.
  
  LiteralIterC OrBodyC::Solutions(const StateC &state,BindSetC &binds) const {
    return StateOrIterC(state,OrC(const_cast<OrBodyC &>(*this)),binds);
  }
  
  //////////////////////////////////////////////////////////////////////
  
  //: Or two literals.
  // FIXME :- Do more simplification.
  
  ConditionC operator+(const LiteralC &l1,const LiteralC &l2) {
    SizeT size = 0;
    OrC a1(l1);
    if(a1.IsValid())
      size += a1.Size();
    else
      size++;
    OrC a2(l2);
    if(a2.IsValid())
      size += a2.Size();
    else
      size++;
    SArray1dC<LiteralC> arr(size);
    UIntT at = 0;
    if(a1.IsValid()) {
      for(SArray1dIter2C<LiteralC,LiteralC> it(a1.Terms(),arr);it;it++)
	it.Data2() = it.Data1();
      at += a1.Size();
    } else
      arr[at++] = l1;
    if(a1.IsValid()) {
      for(SArray1dIter2C<LiteralC,LiteralC> it(a1.Terms().From(at),arr);it;it++)
	it.Data2() = it.Data1();
    } else
      arr[at] = l2;    
    return OrC(arr); 
  }
 
}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/MinTerm.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/Logic/BindSet.hh"

namespace RavlLogicN {
  
  //: Generate hash value for condition.
  
  UIntT MinTermBodyC::Hash() const {
    UIntT ret = 2;
    for(SArray1dIterC<LiteralC> it(t);it;it++)
      ret += it->Hash();
    for(SArray1dIterC<LiteralC> it(n);it;it++)
      ret += it->Hash() ^ 0xf0f0f0f0;
    return ret;
  }
  
  //: Is this equal to another condition ?
  
  bool MinTermBodyC::IsEqual(const LiteralC &oth) const {
    MinTermC mt(oth);
    if(mt.IsValid())
      return false;
    // This is hard...
    RavlAssertMsg(0,"MinTermBodyC::IsEqual(), ERROR: Not implemented.");
    return false;
  }
  
  //: Is this a simple expression with no variables ?
  
  bool MinTermBodyC::IsGrounded() const {
    for(SArray1dIterC<LiteralC> it(t);it;it++)
      if(!it->IsGrounded())
	return false;
    for(SArray1dIterC<LiteralC> it(n);it;it++)
      if(!it->IsGrounded())
	return false;
    return true;
  }
  
  //: Unify with another variable.
  
  bool MinTermBodyC::Unify(const LiteralC &oth,BindSetC &bs) const {
    BindMarkT bm = bs.Mark();
    for(SArray1dIterC<LiteralC> it(t);it;it++) {
      if(!it->Unify(oth,bs)) {
	bs.Undo(bm);
	return false;
      }
    }
    for(SArray1dIterC<LiteralC> it(n);it;it++) {
      if(it->Unify(oth,bs)) {
	bs.Undo(bm);
	return false;
      }
    }
    return true;
  }
  
  //: Get the name of symbol.
  
  StringC MinTermBodyC::Name() const {
    StringC ret("and(and(");
    SArray1dIterC<LiteralC> it(t);
    if(it) {
      ret += it->Name();
      it++;
      for(;it;it++) {
	ret += ',';
	ret += it->Name();
      }
    }
    ret +="),!and(";
    it = n;
    if(it) {
      ret += it->Name();
      it++;
      for(;it;it++) {
	ret += ',';
	ret += it->Name();
      }
    }    
    ret += ")";
    return ret;
  }
  
}

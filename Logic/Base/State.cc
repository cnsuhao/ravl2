// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/State.hh"
#include "Ravl/Collection.hh"
#include "Ravl/Logic/BindSet.hh"

namespace RavlLogicN {

  //: Make a copy of this state.
  RCBodyVC &StateBodyC::Copy() const {
    RavlAssertMsg(0,"StateBodyC::Copy(), Abstract method called. ");
    return const_cast<RCBodyVC &>((RCBodyVC&)*this);
  }

  //: Ask if a literal is set.
  
  bool StateBodyC::Ask(const LiteralC &lit) const {
    BindSetC binds;
    return Ask(lit,binds);
  }
  
  //: Ask if a literal is set.
  
  bool StateBodyC::Ask(const LiteralC &lit,BindSetC &binds) const {
    RavlAssertMsg(0,"StateBodyC::Ask(), Abstract method called. ");
    return false;
  }
  
  //: Set a literal.
  
  bool StateBodyC::Tell(const LiteralC &lit) {
    RavlAssertMsg(0,"StateBodyC::Tell(), Abstract method called. ");
    return false;
  }

  //: List contents of state.
  
  LiteralIterC StateBodyC::List() const {
    RavlAssertMsg(0,"StateBodyC::List(), Abstract method called. ");
    return LiteralIterC();
  }

  //: Return the number of literals in the state.
  
  UIntT StateBodyC::Size() const {
    RavlAssertMsg(0,"StateBodyC::List(), Abstract method called. ");
    return 0;
  }
  
  //: Search state for matching literals.
  
  LiteralIterC StateBodyC::ListFilter(const LiteralC &it,BindSetC &bnds) const {
    RavlAssertMsg(0,"StateBodyC::ListFilter(), Abstract method called. ");
    return LiteralIterC();
  }
  

  //: List the differences between this and another state.
  // Positive terms are ones in this state, but not in 'oth'. <p>
  // Negative terms are those in the 'oth' state but not in this one.
  
  MinTermC StateBodyC::Difference(const StateC &oth) const {
    LiteralIterC it;
    UIntT size = Size()/2;
    if(size < 8)
      size = 8;
    CollectionC<LiteralC> pos(size);
    for(it = List();it;it++) {
      if(oth.Ask(*it)) 
	continue;
      pos += *it;
    }
    size = oth.Size()/2;
    if(size < 8)
      size = 8;
    CollectionC<LiteralC> neg(size);
    for(it = oth.List();it;it++) {
      if(Ask(*it)) 
	continue;
      neg += *it;
    }
    return MinTermC(pos.Array(),neg.Array());;
  }

  //: Generate a hash number for this state.
  
  UIntT StateBodyC::Hash() const {
    UIntT hash = 0;
    for(LiteralIterC it(List());it;it++)
      hash += (*it).Hash();
    return hash;
  }

  //: Test if this state is equal to another.
  
  bool StateBodyC::operator==(const StateC &oth) const {
    if(Size() != oth.Size()) return false;
    for(LiteralIterC it(oth.List());it;it++)
      if(!Ask(*it)) return false;
    return true;
  }

  ostream &operator<<(ostream &s,const StateC &state) {
    RavlAssert(state.IsValid());
    for(LiteralIterC it(state.List());it;it++)
      s << it.Data() << "\n";
    return s;
  }
  //: Write out to stream.
  
  istream &operator>>(istream &s,StateC &state) {
    RavlAssertMsg(0,"operator>>(istream &s,StateC &state), Not implemented. ");
    return s;
  }
  //: Read in from stream.

}

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/MinTerm.cc"

#include "Ravl/Logic/MinTerm.hh"
#include "Ravl/Logic/Not.hh"
#include "Ravl/Logic/Or.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/Logic/BindSet.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {

  //: Default constructor.
  
  MinTermBodyC::MinTermBodyC() 
    : AndBodyC(3)
  {}
  
  //: Construct from a single literal.
  // Effectively add NotC(lit) if negate is true.
  
  MinTermBodyC::MinTermBodyC(const LiteralC &lit,bool negate) 
    : AndBodyC(3)
  {
    if(negate) {
      NotC nt(lit);
      // args[1] = ; 
      args[2] = nt;
      n = nt.Args().From(1,1);
    } else {
      args[1] = lit;
      // args[2] = ; 
      t = args.From(1,1);
    }
  }
  
  //: Constructor
  
  MinTermBodyC::MinTermBodyC(const SArray1dC<LiteralC> &ts,const SArray1dC<LiteralC> &ns) 
  { SetTerms(ts,ns); }
  
  //: Setup terms.
  
  void MinTermBodyC::SetTerms(const SArray1dC<LiteralC> &ts,const SArray1dC<LiteralC> &ns) {
    OrC orv(ns);
    n = orv.Args().From(1,orv.Args().Size()-1);
    args[2] = NotC(orv);
    AndC xa(ts);
    args[1] = xa; 
    t = xa.Terms().From(1);
    n = orv.Terms().From(1);
  }
  
  //: Copy minterm.
  
  RCBodyVC &MinTermBodyC::Copy() const {
    return *new MinTermBodyC(Pos(),Neg()); 
  }
  
  
  //: Add another term to the minterm.
  
  bool MinTermBodyC::AndAdd(const LiteralC &lit) {
    NotC nt(lit);
    ONDEBUG(cerr << "MinTermBodyC::AndAdd(), Add '" << lit.Name() << "'\n");
    if(nt.IsValid()) {
      NotC tn(args[2]);
      if(tn.IsValid()) {
	RavlAssert(tn.Term().IsValid())
	OrC on(true);
	on.OrAdd(nt.Term());
	n = on.Terms().From(1);
      } else {
	OrC on(true);
	on += nt.Term();
	args[2] = NotC(true,on);
	n = on.Terms().From(1);	
      }
    } else {
      AndC an(args[2]);
      an.AndAdd(nt.Term());
      t = an.Terms().From(1);
    }
    return true;
  }
  
}

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

namespace RavlLogicN {

  //: Default constructor.
  
  MinTermBodyC::MinTermBodyC() 
    : AndBodyC(1)
  {}
  
  //: Construct from a single literal.
  // Effectively add NotC(lit) if negate is true.
  
  MinTermBodyC::MinTermBodyC(const LiteralC &lit,bool negate) {
    args = SArray1dC<LiteralC>(2);
    args[0] = literalAnd;
    if(negate) {
      NotC nt(lit);
      args[1] = nt;
      n = nt.Args().From(1,1);
    } else {
      args[1] = lit;
      t = args.From(1,1);
    }
  }
  
  //: Constructor
  
  MinTermBodyC::MinTermBodyC(const SArray1dC<LiteralC> &ts,const SArray1dC<LiteralC> &ns) 
  {
    if(ns.Size() > 0) 
      args = SArray1dC<LiteralC>(ts.Size() + 2);
    else
      args = SArray1dC<LiteralC>(ts.Size() + 1);
    args[0] = literalAnd;
    for(BufferAccessIter2C<LiteralC,LiteralC> it(ts,args.BufferFrom(1,ts.Size()));it;it++)
      it.Data2() = it.Data1();
    t = args.From(1,ts.Size());
    if(ns.Size() > 0) {
      OrC orv(ns);
      n = orv.Args().From(1,orv.Args().Size()-1);
      args[ts.Size() + 1] = NotC(orv);
    }
  }
  
}

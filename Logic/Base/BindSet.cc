// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/BindSet.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlLogicN {
  
  
  //: Copy constructor.
  
  BindSetC::BindSetC(const BindSetC &oth) 
    : HashC<LiteralC,BindC>(NextPrime(oth.Size()+1))
  {
    BindMarkT place = oth.Mark();
    if(place == 0)
      return ;
    // Take care of the top element.
    UIntT hashVal = place->GetKey().Hash();
    BindMarkT elem = new HashElem(place->GetKey(),hashVal,BindC(place->Data().Value(),0));
    table[hashVal % table.Size()].InsFirst(*elem);
    top = elem;
    BindMarkT lastelem = elem;
    place = place->Data().Next();
    // Take care of the rest.
    for(;place != 0;place = place->Data().Next()) {
      hashVal = place->GetKey().Hash();
      elem = new HashElem(place->GetKey(),hashVal,BindC(place->Data().Value(),0));
      table[hashVal % table.Size()].InsFirst(*elem);
      lastelem->Data().Next() = elem;
      lastelem = elem;
    }
    elements = oth.Size();
  }
  
  //: Attempty to bind a value to var.
  
  bool BindSetC::Bind(const LiteralC &var,const LiteralC &val) {
    RavlAssert(var.IsValid());
    RavlAssert(var.IsVariable());

    UIntT hashVal;
    BindMarkT elem = LookupHV(var,hashVal);
    if(elem != 0)
      return false; // Already bound.
    CheckAdd();
    elem = new HashElem(var,hashVal,BindC(val,top));
    table[hashVal % table.Size()].InsFirst(*elem);
    top = elem;
    return true;
  }

  //: Undo bindings to marked place.
  
  void BindSetC::Undo(BindMarkT bm) {
    ONDEBUG(cerr << "Undo to :" << ((void *) bm) << "\n");
    while(top != bm) {
      ONDEBUG(cerr << "top :" << ((void *) top) << "\n");
      RavlAssert(top != 0);
      BindMarkT nxt = top->Data().Next();
      Del(top,true);
      top = nxt;
    }
  }
  
  
  //: Undo bindings done after and including var.
  
  void BindSetC::Undo(LiteralC var) {
    ONDEBUG(cerr << "Undo to :" << ((void *) bm) << "\n");
    while(top->GetKey() != var) {
      ONDEBUG(cerr << "top :" << ((void *) top) << "\n");
      RavlAssert(top != 0);
      BindMarkT nxt = top->Data().Next();
      Del(top,true);
      top = nxt;
    }
    RavlAssert(top != 0);    
    // Do var as well.
    BindMarkT nxt = top->Data().Next();
    Del(top,true);
    top = nxt;
  }

  //: Remove all bindings from set.
  
  void BindSetC::Empty() {
    HashC<LiteralC,BindC>::Empty();
    top = 0;
  }
  
}

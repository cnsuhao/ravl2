// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBINDSET_HEADER
#define RAVLBINDSET_HEADER 1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic"
//! lib=RavlLogic

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Hash.hh"
#include "Ravl/HSet.hh"

namespace RavlLogicN {

  class BindC;
  
  typedef HashElemC<LiteralC,BindC>* BindMarkT;
  
  //! userlevel=Advanced
  //: Information about a single binding.
  
  class BindC {
  public:
    BindC()
      {}

    BindC(const LiteralC &val,BindMarkT nnext)
      : value(val),
	next(nnext)
      {}
    
    LiteralC &Value()
    { return value; }
    //: Access value.
    
    BindMarkT &Next()
    { return next; }
    //: access next ptr.
    
  protected:
    LiteralC value;
    BindMarkT next;
  };
  
  typedef HashElemC<LiteralC,BindC>* BindMarkT;
  
  //! userlevel=Normal
  //: Set of bindings.
  // Note: This is a small object.
  
  class BindSetC 
    : protected HashC<LiteralC,BindC> 
  {
  public:
    BindSetC()
      : top(0)
      {}
    //: Default constructor.
    
    BindSetC(const BindSetC &oth);
    //: Copy constructor.
    // Any bind marks in oth will NOT be valid for
    // the new BindSetC.

    bool IsBound(const LiteralC &var) const {
      return Lookup(var) != 0;
    }
    //: Is variable bound ?

    bool Resolve(const LiteralC &var,LiteralC &x) {
      BindC *lu = Lookup(var);
      if(lu == 0)
	return false;
      x = lu->Value();
      return true;
    }
    //: Resolve value 

    LiteralC Resolve(const LiteralC &var) {
      BindC *lu = Lookup(var);
      if(lu != 0)
	return lu->Value();
      return var;
    }
    //: Resolve a binding.
    // return the value 'var' is bound to, or
    // if its a free variable 'var' itself.
    
    LiteralC operator[](const LiteralC &var) {
      return Resolve(var);
    }
    //: Resolve a binding.
    
    bool Bind(const LiteralC &var,const LiteralC &val);
    //: Attempty to bind a value to var.
    // Will fail if var is already bound.
  
    BindMarkT Mark() const
    { return top; }
    //: Mark the current set of bindings.
    
    void Undo(BindMarkT bm);
    //: Undo bindings to marked place.
    
    void Undo(LiteralC var);
    //: Undo bindings done after and including var.
    
    UIntT Size() const
    { return HashC<LiteralC,BindC>::Size(); }
    //: Get the number of binds in set.
    
    void Empty();
    //: Remove all bindings from set.
  protected:
    BindMarkT top;

  private:
  };
  
}

#endif

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
  class BindSetC;
  
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

    const LiteralC &Value() const
    { return value; }
    //: Access value.
    
    BindMarkT &Next()
    { return next; }
    //: access next ptr.

    const BindMarkT &Next() const
    { return next; }
    //: access next ptr.
    
  protected:
    LiteralC value;
    BindMarkT next;
  };

  inline ostream &operator<<(ostream &s,const BindC &bind) { 
    s << bind.Value();
    return s;
  }
  //! userlevel=Advanced
  //: output stream 
  
  inline istream &operator<<(istream &s,BindC &bind) {
    RavlAssertMsg(0,"operator<<(istream &s,BindC &binds), Not implemented. ");
    return s;
  }
  //! userlevel=Advanced
  //: input stream 
  
  typedef HashElemC<LiteralC,BindC>* BindMarkT;
  
  //! userlevel=Normal
  //: Set of bindings.
  // Note: This is a small object.
  
  class BindSetBodyC 
    : public RCBodyC,
      protected HashC<LiteralC,BindC> 
  {
  public:
    BindSetBodyC()
      : top(0)
      {}
    //: Default constructor.
    
    BindSetBodyC(const BindSetC &oth);
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
    
    friend class BindSetC;
  };

  //! userlevel=Normal
  //: Set of bindings.
  // Note: This is a small object.
  
  class BindSetC 
    : public RCHandleC<BindSetBodyC>
  {
  public:
    BindSetC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    BindSetC(bool)
      : RCHandleC<BindSetBodyC>(*new BindSetBodyC())
      {}
    //: Constructor.
    
  protected:    
    BindSetBodyC &Body()
      { return RCHandleC<BindSetBodyC>::Body(); }
    //: Access body.

    const BindSetBodyC &Body() const
      { return RCHandleC<BindSetBodyC>::Body(); }
    //: Access body.
    
  public:
    bool IsBound(const LiteralC &var) const 
      { return Body().IsBound(var); }
    //: Is variable bound ?

    bool Resolve(const LiteralC &var,LiteralC &x)
      { return Body().Resolve(var,x); }
    //: Resolve value 

    LiteralC Resolve(const LiteralC &var) 
      { return Body().Resolve(var); }
    //: Resolve a binding.
    // return the value 'var' is bound to, or
    // if its a free variable 'var' itself.
    
    LiteralC operator[](const LiteralC &var) 
      { return Resolve(var); }
    //: Resolve a binding.
    
    bool Bind(const LiteralC &var,const LiteralC &val)
      { return Body().Bind(var,val); }
    //: Attempty to bind a value to var.
    // Will fail if var is already bound.

    BindMarkT Mark() const
      { return Body().Mark(); }
    //: Mark the current set of bindings.
    
    void Undo(BindMarkT bm)
      { Body().Undo(bm); }
    //: Undo bindings to marked place.
    
    void Undo(LiteralC var)
      { Body().Undo(var); }
    //: Undo bindings done after and including var.
    
    UIntT Size() const
      { return Body().Size(); }
    //: Get the number of binds in set.
    
    void Empty()
      { Body().Empty(); }
    //: Remove all bindings from set.
    
    HashIterC<LiteralC,BindC> Iter()
      { return HashC<LiteralC,BindC>(Body()); }
    //: Iterate through binds.
  };
  
  ostream &operator<<(ostream &s,const BindSetC &binds);
  //: output stream 
  
  istream &operator<<(istream &s,BindSetC &binds);
  //: input stream 
  
}

#endif

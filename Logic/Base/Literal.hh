// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_LITERAL_HEADER
#define RAVLLOGIC_LITERAL_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic"
//! userlevel=Normal
//! lib=RavlLogic
//! file="Ravl/Logic/Base/Literal.hh"
//! author="Charles Galambos"

#include "Ravl/RefCounter.hh"
#include "Ravl/String.hh"
#include "Ravl/HSet.hh"

namespace RavlLogicN {
  using namespace RavlN;
  class StateC;
  StringC Indent(int level);
  //: Helper function for producing debug output.
  // create a string with 'level' spaces.
  
  class VarC;
  class VarBodyC;
  class BindSetC;
  class LiteralC;
  class ExprC;
  class LiteralIterC;
  class XMLIStreamC;
  class XMLOStreamC;
  
  //! userlevel=Develop
  //: Literal body

  class LiteralBodyC 
    : public RCBodyVC
  {
  public:
    LiteralBodyC()
    {}
    //: Default constructor.
    
    virtual bool IsVariable() const
    { return false; }
    //: Is this a variable ?

    virtual bool IsGrounded() const
    { return true; }
    //: Is this a simple expression with no variables ?
    
    virtual bool Unify(const LiteralC &oth,BindSetC &bs) const;
    //: Unify with another variable.

    virtual void Dump(ostream &out);
    //: Dump info in human readable format to stream 'out'.

    virtual StringC Name() const;
    //: Get the name of symbol.
    
    virtual UIntT Hash() const 
    { return ((UIntT) this) >> 2; }
    //: Get hash value for symbol.
    
    virtual bool IsEqual(const LiteralC &oth) const;
    //: Is this equial to another LiteralC ?
    
    virtual bool Test(const StateC &state,BindSetC &binds) const;
    //: Test if condition is true in 'state'.
    
    virtual LiteralIterC Solutions(const StateC &state,BindSetC &binds) const;
    //: Return iterator through possibile matches to this literal in 'state', if any.
    
    virtual void SubLiterals(HSetC<LiteralC> &lits) const;
    //: Get a set of all sub literals.
  protected:
    virtual bool UnifyLiteral(const LiteralBodyC &oth,BindSetC &bs) const;
    //: Unify with simple symb.

    friend class LiteralC;
  };

  //! userlevel=Normal
  //: Literalol
  
  class LiteralC 
    : public RCHandleC<LiteralBodyC>
  {
  public:
    LiteralC()
      {}
    //: Default constructor.

    LiteralC(bool)
      : RCHandleC<LiteralBodyC>(*new LiteralBodyC())
      {}
    //: Constructor.

  protected:
    LiteralC(LiteralBodyC &bod)
      : RCHandleC<LiteralBodyC>(bod)
    {}
    //: Body constructor.
    
    LiteralBodyC &Body()
      { return RCHandleC<LiteralBodyC>::Body(); }
    //: Access body.

    const LiteralBodyC &Body() const
      { return RCHandleC<LiteralBodyC>::Body(); }
    //: Access body.
    
  public:
    
    StringC Name() const { 
      if(!IsValid())
	return StringC("-NIL-");
      return Body().Name(); 
    }
    //: Get the name of symbol.
    
    bool IsVariable() const
    { return Body().IsVariable(); }
    //: Is this a variable ?

    bool IsGrounded() const
    { return Body().IsGrounded(); }
    //: Is this a simple expression with no variables ?

    bool Unify(const LiteralC &val,BindSetC &bs) const
    { return Body().Unify(val,bs); }
    //: Unify this and 'val'.
    
    UIntT Hash() const 
    { return Body().Hash(); }
    //: Get hash value.
    
    bool IsEqual(const LiteralC &oth) const
    { return Body().IsEqual(oth); }
    //: Is this equial to another LiteralC ?
    
    bool operator==(const LiteralC &oth) const 
    { return Body().IsEqual(oth); }
    //: Equality test.
    
    void Dump(ostream &out)
      { Body().Dump(out); }
    //: Dump info in human readable format to stream 'out'.

    bool Test(const StateC &state,BindSetC &binds) const
    { return Body().Test(state,binds); }
    //: Test if condition is true in 'state'.
    
    LiteralIterC Solutions(const StateC &state,BindSetC &binds) const;
    //: Return iterator through possibile matches to this literal in 'state', if any.
    
    void SubLiterals(HSetC<LiteralC> &lits) const
    {  Body().SubLiterals(lits); }
    //: Get a set of all sub literals.
    
    friend class LiteralBodyC;
    friend class VarBodyC;
  };

  inline LiteralC Literal()
  { return LiteralC(true); }
  //: Create an anonymous symbol.
  
  inline
  ostream &operator<<(ostream &s,const LiteralC  &l) {
    s << l.Name();
    return s;
  }
}

#endif

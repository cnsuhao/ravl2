// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_TUPLE_HEADER
#define RAVLLOGIC_TUPLE_HEADER 1
//////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.API.Logic"
//! author="Charles Galambos"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/Tuple.hh"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/SArray1d.hh"

namespace RavlLogicN {
  using namespace RavlN;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::UIntT;
  using RavlN::SArray1dC;
  using RavlN::StringC;
  using RavlN::HSetC;
#endif
  
  //! userlevel=Develop
  //: Tuple of literals.
  
  class TupleBodyC
    : public LiteralBodyC
  {
  public:
    TupleBodyC(UIntT arity = 1)
      : args(arity)
    {}
    //: Create expression with given arity.
    
    TupleBodyC(const SArray1dC<LiteralC> &arr)
      : args(arr)
    {}
    //: Create a tuple from an array of literals.
    
    TupleBodyC(istream &strm);
    //: Construct from a binary stream.
    
    TupleBodyC(BinIStreamC &strm);
    //: Construct from a binary stream.
    
    virtual bool Save(ostream &out) const;
    //: Save to binary stream 'out'.

    virtual bool Save(BinOStreamC &out) const;
    //: Save to binary stream 'out'.

    virtual bool Unify(const LiteralC &oth,BindSetC &bs) const;
    //: Unify with another variable.
    
    virtual bool IsEqual(const LiteralC &oth) const;
    //: Is this equial to another LiteralC ?
    
    UIntT Arity() const
    { return args.Size(); }
    //: Get the arity of the expression.
    
    SArray1dC<LiteralC> &Args()
    { return args; }
    //: Access array of args.
    
    const SArray1dC<LiteralC> &Args() const
    { return args; }
    //: Access array of args.
    
    virtual bool IsGrounded() const;
    //: Is this a simple expression with no variables ?
    
    virtual bool IsTuple() const;
    //: Is this literal a tuple ?
    
    void SetArg(UIntT n,const LiteralC &s)
    { args[n] = s; }
    //: Set the value of an arg.

    virtual void Dump(ostream &out);
    //: Dump info in human readable format to stream 'out'.

    virtual StringC Name() const;
    //: Get the name of symbol.
    
    virtual void SubLiterals(HSetC<LiteralC> &lits) const;
    //: Get a set of all sub literals.

    virtual LiteralIterC Solutions(const StateC &state,BindSetC &binds) const;
    //: Return iterator through possibile matches to this literal in 'state', if any.
    
    virtual bool Substitute(const BindSetC &binds,LiteralC &result) const;
    //: Substitute variables in 'binds' for their bound values.
    // This builds a new literal with the substute values (if there
    // are any). The new value is assigned to 'result' <p>
    // Returns true if at least one substitution has been made,
    // false if none.
    
    virtual UIntT Hash() const;
    //: Get hash value for symbol.
    
  protected:
    virtual bool UnifyLiteral(const LiteralBodyC &oth,BindSetC &bs) const;
    //: Unify with simple literal.
    
    SArray1dC<LiteralC> args;
  };
  
  //! userlevel=Normal
  //: Tuple of literals.
  
  class TupleC
    : public LiteralC
  {
  public:
    TupleC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    TupleC(UIntT arity)
      : LiteralC(*new TupleBodyC(arity))
    {}
    //: Creat expression with given arity.

    TupleC(SArray1dC<LiteralC> &literals)
      : LiteralC(*new TupleBodyC(literals))
    {}
    //: Create tuple from an array of literals.
    
    TupleC(const LiteralC &x)
      : LiteralC(dynamic_cast<const TupleBodyC *>(BodyPtr(x)))
    {}
    //: Base class constructor.
    // if x isn't an Tuple an invalid handle is created.

    TupleC(const LiteralC &a1,const LiteralC &a2)
      : LiteralC(*new TupleBodyC(2))
    {
      SetArg(0,a1);
      SetArg(1,a2);
    }
    //: Create a tuple containing two literals.

    TupleC(const LiteralC &a1,const LiteralC &a2,const LiteralC &a3)
      : LiteralC(*new TupleBodyC(3))
    {
      SetArg(0,a1);
      SetArg(1,a2);
      SetArg(2,a3);
    }
    //: Create a tuple containing two literals.

    TupleC(const LiteralC &a1,const LiteralC &a2,const LiteralC &a3,const LiteralC &a4)
      : LiteralC(*new TupleBodyC(4))
    {
      SetArg(0,a1);
      SetArg(1,a2);
      SetArg(2,a3);
      SetArg(3,a4);
    }
    //: Create a tuple containing two literals.

    TupleC(istream &strm);
    //: Load from stream.

    TupleC(BinIStreamC &strm);
    //: Load from binary stream.
    
  protected:
    TupleC(TupleBodyC &bod)
      : LiteralC(bod)
    {}
    //: Body constructor.
    
    TupleC(const TupleBodyC *bod)
      : LiteralC(bod)
    {}
    //: Body constructor.
    
    TupleBodyC &Body()
    { return static_cast<TupleBodyC &>(LiteralC::Body()); }
    //: Access body.
    
    const TupleBodyC &Body() const
    { return static_cast<const TupleBodyC &>(LiteralC::Body()); }
    //: Access body.
    
  public:
    UIntT Arity() const
    { return Body().Arity(); }
    //: Get the arity of the expression.
    
    SArray1dC<LiteralC> &Args()
    { return Body().Args(); }
    //: Access array of args.
    
    const SArray1dC<LiteralC> &Args() const
    { return Body().Args(); }
    //: Access array of args.
    
    void SetArg(UIntT n,const LiteralC &s)
    { Body().SetArg(n,s); }
    //: Set the value of an arg.

    const LiteralC &operator[](UIntT n) const
    { return Body().Args()[n]; }
    //: Access an arg of the tuple.
    
    friend class TupleBodyC;
  };
  
  inline TupleC Tuple(const LiteralC &s1) {
    TupleC e(1);
    e.SetArg(0,s1);
    return e;
  }
  //! userlevel=Normal
  //: Create a tuple with 1 paramiter

  inline TupleC Tuple(const LiteralC &s1,const LiteralC &s2) {
    TupleC e(2);
    e.SetArg(0,s1);
    e.SetArg(1,s2);
    return e;
  }
  //! userlevel=Normal
  //: Create a tuple with 2 paramiters
  
  inline TupleC Tuple(const LiteralC &s1,const LiteralC &s2,const LiteralC &s3) {
    TupleC e(3);
    e.SetArg(0,s1);
    e.SetArg(1,s2);
    e.SetArg(2,s3);
    return e;
  }
  //! userlevel=Normal
  //: Create a tuple with 3 paramiters
  
  
  LiteralC TupleArg(const LiteralC &s1,UIntT argno);
  //: Get an the numbered arg of a tuple.
  //: An invalid literal is returned if types don't match.
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICMINTERM_HEADER
#define RAVLLOGICMINTERM_HEADER 1
////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic.Condition"
//! lib=RavlLogic

#include "Ravl/SArray1d.hh"
#include "Ravl/Logic/Condition.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Logical Minterm.
  // This is a set of negative and positive conditions which are anded together.
  
  class MinTermBodyC 
    : public ConditionBodyC
  {
  public:
    MinTermBodyC()
    {}
    //: Default constructor.
    
    MinTermBodyC(const SArray1dC<LiteralC> &ts,const SArray1dC<LiteralC> &ns)
      : t(ts),
	n(ns)
    {}
    //: Constructor
    
    SArray1dC<LiteralC> &Pos()
    { return t; }
    //: Positive terms.
    
    SArray1dC<LiteralC> &Neg()
    { return n; }
    //: Negated terms.
    
    virtual UIntT Hash() const;
    //: Generate hash value for condition.
    
    virtual bool IsEqual(const LiteralC &oth) const;
    //: Is this equal to another condition ?

    virtual bool IsGrounded() const;
    //: Is this a simple expression with no variables ?

    virtual bool Unify(const LiteralC &oth,BindSetC &bs) const;
    //: Unify with another variable.

    virtual StringC Name() const;
    //: Get the name of symbol.
    
  protected:
    SArray1dC<LiteralC> t; // True symbols
    SArray1dC<LiteralC> n; // Negated symbols
  };
  
  //! userlevel=Normal
  //: Logical Minterm.
  // This is a set of negative and positive conditions which are anded together.
  
  class MinTermC 
    : public ConditionC
  {
  public:
    MinTermC()
    {}
    //: Default constructor
    
    MinTermC(const SArray1dC<LiteralC> &ts,const SArray1dC<LiteralC> &ns)
      : ConditionC(*new MinTermBodyC(ts,ns)) 
    {}
    //: Contructor

  protected:
    MinTermC(MinTermBodyC &bod)
      : ConditionC(bod)
    {}
    //: Body constructor.
    
    MinTermBodyC &Body()
    { return static_cast<MinTermBodyC &>(LiteralC::Body()); }
    //: Access body.
    
    const MinTermBodyC &Body() const
    { return static_cast<const MinTermBodyC &>(LiteralC::Body()); }
    //: Access body.
    
  public:    
    MinTermC(const LiteralC &term)
      : ConditionC(term)
    {
      if(dynamic_cast<const MinTermBodyC *>(&LiteralC::Body()) == 0)
	Invalidate();
    }
    //: Construct from base class.
    
    SArray1dC<LiteralC> &Pos()
    { return Body().Pos(); }
    //: Positive terms.
    
    SArray1dC<LiteralC> &Neg()
    { return Body().Neg(); }
    //: Negated terms.
    
  };
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICSUMOFPRODUCTS_HEADER
#define RAVLLOGICSUMOFPRODUCTS_HEADER 1
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic.Condition"
//! lib=RavlLogic

#include "Ravl/Logic/Condition.hh"
#include "Ravl/HSet.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Coniditional Or.
  
  class OrBodyC
    : public ConditionBodyC
  {
  public:
    OrBodyC()
    {}
    //: Default constructor.
    
    OrBodyC(const SArray1dC<LiteralC> &nterms)
      : terms(nterms)
    {}
    //:  constructor.
    
    OrBodyC(const ConditionC &term)
      : terms(1)
    { terms[0] = term; }
    //: Constructor.
    
    SArray1dC<LiteralC> &Terms()
    { return terms; }
    //: Access set of terms.
    
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
    
    SizeT Size() const
    { return terms.Size(); }
    //: Numnber of terms in or.
  protected:
    SArray1dC<LiteralC> terms;
  };
  
  //! userlevel=Normal
  //: Or a set of conditions.
  
  class OrC
    : public ConditionC
  {
  public:
    OrC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    OrC(bool)
      : ConditionC(*new OrBodyC())
    {}
    //: Constructor from a single term.
    
    OrC(const SArray1dC<LiteralC> &nterms)
      : ConditionC(*new OrBodyC(nterms))
    {}
    //: Construct from an array of Literals.
    
  protected:
    OrC(OrBodyC &bod)
      : ConditionC(bod)
    {}
    //: Body constructor.
    
    OrBodyC &Body()
    { return static_cast<OrBodyC &>(LiteralC::Body()); }
    //: Access body.

    const OrBodyC &Body() const
    { return static_cast<const OrBodyC &>(LiteralC::Body()); }
    //: Access body.
    
  public:
    OrC(const ConditionC &term)
      : ConditionC(term)
    {
      if(dynamic_cast<const OrBodyC *>(&LiteralC::Body()) == 0)
	Invalidate();
    }
    //: Construct from base class.
    
    SArray1dC<LiteralC> &Terms()
    { return Body().Terms(); }
    //: Access set of terms.
    
    SizeT Size() const
    { return Body().Size(); }
    //: Numnber of terms in or.
  };

  ConditionC operator+(const LiteralC &l1,const LiteralC &l2);
  //: Or two literals.
  
}

#endif

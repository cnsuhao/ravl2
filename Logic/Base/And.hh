// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICAND_HEADER
#define RAVLLOGICAND_HEADER 1
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic.Condition"
//! lib=RavlLogic

#include "Ravl/Logic/Condition.hh"
#include "Ravl/SArray1d.hh"

namespace RavlLogicN {

  //! userlevel=Develop
  //: And a set of conditions.
  
  class AndBodyC
    : public ConditionBodyC
  {
  public:
    AndBodyC()
    {}
    //: Default constructor.
    
    AndBodyC(const SArray1dC<LiteralC> &set)
      : terms(set)
	{ }
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
    //: Get the number of terms to be anded together.
    
    virtual LiteralIterC Solutions(const StateC &state,BindSetC &binds) const;
    //: Return iterator through possibile matches to this literal in 'state', if any.
    
  protected:
    SArray1dC<LiteralC> terms;
  };
  
  //! userlevel=Normal
  //: And a set of conditions.
  
  class AndC
    : public ConditionC
  {
  public:
    AndC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    AndC(const SArray1dC<LiteralC> &set)
      : ConditionC(*new AndBodyC(set))
    {}
    //: Constructor from a single term.
    
    AndC(bool)
      : ConditionC(*new AndBodyC())
    {}
    //: Constructor.
    
  protected:
    AndC(AndBodyC &bod)
      : ConditionC(bod)
    {}
    //: Body constructor.
    
    AndBodyC &Body()
    { return static_cast<AndBodyC &>(LiteralC::Body()); }
    //: Access body.

    const AndBodyC &Body() const
    { return static_cast<const AndBodyC &>(LiteralC::Body()); }
    //: Access body.
    
  public:
    AndC(const LiteralC &term)
      : ConditionC(term)
    {
      if(dynamic_cast<const AndBodyC *>(&LiteralC::Body()) == 0)
	Invalidate();
    }
    //: Construct from base class.
    
    SArray1dC<LiteralC> &Terms()
    { return Body().Terms(); }
    //: Access set of terms.
    
    SizeT Size() const
    { return Body().Size(); }
    //: Get the number of terms to be anded together.
    
    friend class AndBodyC;
  };
  
  ConditionC operator*(const LiteralC &l1,const LiteralC &l2);
  //: And operator.


}

#endif

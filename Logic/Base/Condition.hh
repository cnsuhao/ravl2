// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_CONDITION_HEADER
#define RAVLLOGIC_CONDITION_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid=$Id$"
//! docentry="Ravl.Logic.Condition"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/Condition.hh"
//! author="Charles Galambos"

#include "Ravl/RefCounter.hh"
#include "Ravl/Logic/Tuple.hh"

namespace RavlLogicN {

  class ConditionC;
  class StateC;
  
  //! userlevel=Develop
  //: Abstract condition
  
  class ConditionBodyC
    : public TupleBodyC
  {
  public:
    ConditionBodyC()
    {}
    //: Default constructor.

    ConditionBodyC(const SArray1dC<LiteralC> &lits)
      : TupleBodyC(lits)
    {}
    //: Default constructor.

    ConditionBodyC(UIntT arity)
      : TupleBodyC(arity)
    {}
    //: Default constructor.
    
    virtual bool Test(const StateC &state,BindSetC &binds) const;
    //: Test if condition is true in 'state'.
    
    virtual bool IsEqual(const LiteralC &oth) const;
    //: Is this equal to another condition ?
    
  protected:
    void AddTerms(const SArray1dC<LiteralC> &terms);
    //: Add some terms.
    
    void AddTerm(const LiteralC &term);
    //: Add a term.
    
    friend class ConditionC;
  };
  
  //! userlevel=Normal
  //: Abstract condition
  
  class ConditionC
    : public TupleC
  {
  public:
    ConditionC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
  protected:
    ConditionC(ConditionBodyC &bod)
      : TupleC(bod)
    {}
    //: Body constructor.
    
    ConditionBodyC &Body()
    { return static_cast<ConditionBodyC &>(LiteralC::Body()); }
    //: Access body.
    
    const ConditionBodyC &Body() const
    { return static_cast<const ConditionBodyC &>(LiteralC::Body()); }
    //: Access body.
    
    void AddTerms(const SArray1dC<LiteralC> &terms)
    { Body().AddTerms(terms); }
    //: Add some terms.
    
    void AddTerm(const LiteralC &term)
    { Body().AddTerm(term); }
    //: Add some terms.

  public:
    ConditionC(const LiteralC &term)
      : TupleC(term)
    {
      if(dynamic_cast<const ConditionBodyC *>(&LiteralC::Body()) == 0)
	Invalidate();
    }
    //: Construct from base class.
    
    UIntT Hash() const
    { return Body().Hash(); }
    //: Generate hash value for condition.
    
    bool IsEqual(const ConditionC &oth) const
    { return Body().IsEqual(oth); }
    //: Is this equal to another condition ?
    
    bool operator==(const ConditionC &oth) const
    { return Body().IsEqual(oth); }
    //: Is this equal to another condition ?
    
    
    friend class ConditionBodyC;
  };

}

#endif

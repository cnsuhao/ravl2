// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICCONDITION_HEADER
#define RAVLLOGICCONDITION_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid=$Id$"
//! docentry="Ravl.Logic.Condition"
//! lib=RavlLogic

#include "Ravl/RefCounter.hh"
#include "Ravl/Logic/Literal.hh"

namespace RavlLogicN {

  class ConditionC;
  
  //! userlevel=Develop
  //: Condition
  
  class ConditionBodyC
    : public LiteralBodyC
  {
  public:
    ConditionBodyC()
    {}
    //: Default constructor.
    
    virtual UIntT Hash() const;
    //: Generate hash value for condition.
    
    virtual bool IsEqual(const ConditionC &oth) const;
    //: Is this equal to another condition ?

    virtual bool IsGrounded() const;
    //: Is this a simple expression with no variables ?

    virtual bool Unify(const LiteralC &oth,BindSetC &bs) const;
    //: Unify with another variable.

    virtual StringC Name() const;
    //: Get the name of symbol.
    
  protected:
  };
  
  //! userlevel=Normal
  //: Condition
  
  class ConditionC
    : public LiteralC
  {
  public:
    ConditionC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
  protected:
    ConditionC(ConditionBodyC &bod)
      : LiteralC(bod)
    {}
    //: Body constructor.
    
    ConditionBodyC &Body()
    { return static_cast<ConditionBodyC &>(LiteralC::Body()); }
    //: Access body.
    
    const ConditionBodyC &Body() const
    { return static_cast<const ConditionBodyC &>(LiteralC::Body()); }
    //: Access body.
    
  public:
    ConditionC(const LiteralC &term)
      : LiteralC(term)
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

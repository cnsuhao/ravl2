// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_OR_HEADER
#define RAVLLOGIC_OR_HEADER 1
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic.Condition"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/Or.hh"

#include "Ravl/Logic/Condition.hh"
#include "Ravl/HSet.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Coniditional Or.
  
  class OrBodyC
    : public ConditionBodyC
  {
  public:
    OrBodyC();
    //: Default constructor.
    
    OrBodyC(const SArray1dC<LiteralC> &nterms);
    //:  constructor.
    
    OrBodyC(const LiteralC &term);
    //: Constructor.
    
    SArray1dC<LiteralC> &Terms()
    { return args; }
    //: Access set of terms.

    const SArray1dC<LiteralC> &Terms() const
    { return args; }
    //: Access set of terms.
    
    virtual bool IsEqual(const LiteralC &oth) const;
    //: Is this equal to another condition ?
    
    virtual bool Unify(const LiteralC &oth,BindSetC &bs) const;
    //: Unify with another variable.
    
    SizeT Size() const
    { return args.Size()-1; }
    //: Numnber of terms in or.

    virtual LiteralIterC Solutions(const StateC &state,BindSetC &binds) const;
    //: Return iterator through possibile matches to this literal in 'state', if any.

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
    OrC(const LiteralC &term)
      : ConditionC(term)
    {
      if(dynamic_cast<const OrBodyC *>(&LiteralC::Body()) == 0)
	Invalidate();
    }
    //: Construct from base class.
    
    SArray1dC<LiteralC> &Terms()
    { return Body().Terms(); }
    //: Access set of terms.
    
    const SArray1dC<LiteralC> &Terms() const
    { return Body().Terms(); }
    //: Access set of terms.
    
    SizeT Size() const
    { return Body().Size(); }
    //: Numnber of terms in or.

    friend class OrBodyC;
  };
  
  TupleC operator+(const LiteralC &l1,const LiteralC &l2);
  //: Or two literals.
  
}

#endif

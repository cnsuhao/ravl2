// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_MINTERM_HEADER
#define RAVLLOGIC_MINTERM_HEADER 1
////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic.Condition"
//! lib=RavlLogic
//! author="Charles Galambos"
//! file="Ravl/Logic/Base/MinTerm.hh"

#include "Ravl/SArray1d.hh"
#include "Ravl/Logic/And.hh"

namespace RavlLogicN {

  class MinTermC;
  
  //! userlevel=Develop
  //: Logical Minterm.
  // This is a set of negative and positive conditions which are anded together.
  
  class MinTermBodyC 
    : public AndBodyC
  {
  public:
    MinTermBodyC();
    //: Default constructor.
    
    MinTermBodyC(const SArray1dC<LiteralC> &ts,const SArray1dC<LiteralC> &ns);
    //: Constructor
    
    MinTermBodyC(const LiteralC &lit,bool negate);
    //: Construct from a single literal.
    // Effectively add NotC(lit) if negate is true.
    
    const SArray1dC<LiteralC> &Pos() const
    { return t; }
    //: Positive terms.
    
    const SArray1dC<LiteralC> &Neg() const
    { return n; }
    //: Negated terms.
    
    RCBodyVC &Copy() const;
    //: Copy minterm.
    
    bool AndAdd(const LiteralC &lit);
    //: Add another term to the minterm.
    
    bool Covers(const MinTermC &mt,BindSetC &bs) const;
    //: Does this minterm cover all terms of mt ?
    
  protected:
    void SetTerms(const SArray1dC<LiteralC> &nt,const SArray1dC<LiteralC> &nn);
    //: Setup terms.
    
    SArray1dC<LiteralC> t;
    SArray1dC<LiteralC> n;
  };
  
  //! userlevel=Normal
  //: Logical Minterm.
  // This is a set of negative and positive conditions which are anded together.
  
  class MinTermC 
    : public AndC
  {
  public:
    MinTermC()
    {}
    //: Default constructor
    
    MinTermC(const SArray1dC<LiteralC> &ts,const SArray1dC<LiteralC> &ns)
      : AndC(*new MinTermBodyC(ts,ns)) 
    {}
    //: Contructor

    MinTermC(const LiteralC &lit,bool negate) 
      : AndC(*new MinTermBodyC(lit,negate))
    {}
    //: Construct from a literal.
    // Effectively add NotC(lit) if negate is true.
    
    MinTermC(const LiteralC &lit) 
      : AndC(lit)
    {
      if(dynamic_cast<const MinTermBodyC *>(&LiteralC::Body()) == 0)
	(*this) = MinTermC(lit,false);
    }
    //: Base constructor
    
  protected:
    MinTermC(MinTermBodyC &bod)
      : AndC(bod)
    {}
    //: Body constructor.
    
    MinTermBodyC &Body()
    { return static_cast<MinTermBodyC &>(LiteralC::Body()); }
    //: Access body.
    
    const MinTermBodyC &Body() const
    { return static_cast<const MinTermBodyC &>(LiteralC::Body()); }
    //: Access body.
    
  public:        
    const SArray1dC<LiteralC> &Pos() const
    { return Body().Pos(); }
    //: Positive terms.
    
    const SArray1dC<LiteralC> &Neg() const
    { return Body().Neg(); }
    //: Negated terms.
    
    MinTermC Copy() const
    { return MinTermC(static_cast<MinTermBodyC &>(Body().Copy())); }
    //: Copy this min term.
    
    const MinTermC &operator*=(const LiteralC &lit) { 
      Body().AndAdd(lit); 
      return *this;
    }
    
    bool Covers(const MinTermC &mt,BindSetC &bs) const
    { return Body().Covers(mt,bs); }
    //: Does this minterm cover all terms of mt ?

  };
}

#endif

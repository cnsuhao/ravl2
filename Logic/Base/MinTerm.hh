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
    
    const SArray1dC<LiteralC> &Pos()
    { return t; }
    //: Positive terms.
    
    const SArray1dC<LiteralC> &Neg()
    { return n; }
    //: Negated terms.
    
  protected:
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
    MinTermC(const LiteralC &term)
      : AndC(term)
    {
      if(dynamic_cast<const MinTermBodyC *>(&LiteralC::Body()) == 0)
	Invalidate();
    }
    //: Construct from base class.
    
    const SArray1dC<LiteralC> &Pos()
    { return Body().Pos(); }
    //: Positive terms.
    
    const SArray1dC<LiteralC> &Neg()
    { return Body().Neg(); }
    //: Negated terms.
    
  };
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICSTATE_HEADER
#define RAVLLOGICSTATE_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! docentry="Ravl.Logic"
//! author="Charles Galambos"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/MinTerm.hh"
#include "Ravl/Logic/LiteralIter.hh"

namespace RavlLogicN {
  
  class BindSetC;
  
  //! userlevel=Develop
  //: Abstract state description.
  
  class StateBodyC
    : public RCBodyVC
  {
  public:
    StateBodyC()
    {}
    //: Default constructor.
    
    virtual RCBodyVC &Copy() const;
    //: Make a copy of this state.
    
    virtual bool Ask(const LiteralC &lit) const;
    //: Ask if a literal is set.

    virtual bool Ask(const LiteralC &lit,BindSetC &binds) const;
    //: Ask if a literal is set.
    
    virtual bool Tell(const LiteralC &lit);
    //: Set a literal.
    
    virtual LiteralIterC List() const;
    //: List contents of state.
    
    virtual LiteralIterC ListFilter(const LiteralC &it,BindSetC &bnds) const;
    //: Search state for matching literals.
    
    virtual MinTermC Difference(const StateC &oth) const;
    //: List the differences between this and another state.
    // Positive terms are ones in this state, but not in 'oth'. <p>
    // Negative terms are those in the 'oth' state but not in this one.
    
    virtual HSetC<LiteralC> Intersection(const StateC &oth) const;
    //: List all common terms between this state and 'oth'.
    
    virtual UIntT Size() const;
    //: Return the number of literals in the state.

    virtual UIntT Hash() const;
    //: Generate a hash number for this state.
    
    virtual bool operator==(const StateC &oth) const;
    //: Test if this state is equal to another.
    
    virtual void Dump(ostream &out) const;
    //: Dump in human readable format to out.
  };
  
  //! userlevel=Normal
  //: Abstract state description.
  
  class StateC 
    : public RCHandleC<StateBodyC>
  {
  public:
    StateC()
      {}
    //: Default constructor
    // creates an invalid handle.
    
    StateC(bool);
    //: Construct a valid state of the default type..
    // This currently creates a StateSet.
    
  protected:
    StateC(StateBodyC &bod)
      : RCHandleC<StateBodyC>(bod)
    {}
    //: Body constructor.
    
    StateBodyC &Body()
    { return RCHandleC<StateBodyC>::Body(); }
    //: Access body.
    
    const StateBodyC &Body() const
    { return RCHandleC<StateBodyC>::Body(); }
    //: Access body.

  public:
    
    StateC Copy() const
      { return StateC(static_cast<StateBodyC &>(Body().Copy())); }
    //: Make a copy of this state.
    
    bool Ask(const LiteralC &lit) const
    { return Body().Ask(lit); }
    //: Ask if a literal is set.

    
    bool Ask(const LiteralC &lit,BindSetC &binds) const
    { return Body().Ask(lit,binds); }
    //: Ask if a literal is set.
    
    bool Tell(const LiteralC &lit)
    { return Body().Tell(lit); }
    //: Set a literal.
    
    bool operator+=(const LiteralC &lit)
    { return Body().Tell(lit); }
    //: Add a literal to the state.
    // This is just an alias for tell.
    
    LiteralIterC List() const
    { return Body().List(); }
    //: List contents of state.
    
    LiteralIterC ListFilter(const LiteralC &it,BindSetC &bnds) const
      { return Body().ListFilter(it,bnds); }
    //: Search state for matching literals.
    
    MinTermC Difference(const StateC &oth) const
    { return Body().Difference(oth); }
    //: List the differences between this and another state.
    // Positive terms are ones in this state, but not in 'oth'. <p>
    // Negative terms are those in the 'oth' state but not in this one.
    
    HSetC<LiteralC> Intersection(const StateC &oth) const
    { return Body().Intersection(oth); }
    //: List all common terms between this state and 'oth'.
    
    UIntT Size() const
    { return Body().Size(); }
    //: Return the number of literals in the state.

    UIntT Hash() const
    { return Body().Hash(); }
    //: Generate a hash number for this state.
    
    bool operator==(const StateC &oth) const
    { return Body() == oth; }
    //: Test if this state is equal to another.
    
    void Dump(ostream &out) const
    { Body().Dump(out); }
    //: Dump in human readable format to out.
    
  };


  ostream &operator<<(ostream &out,const StateC &state);
  //: Write out to stream.
  
  istream &operator>>(istream &out,StateC &stae);
  //: Read in from stream.
}

#endif

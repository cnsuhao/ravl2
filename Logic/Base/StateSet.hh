// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICSTATESET_HEADER
#define RAVLLOGICSTATESET_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! docentry="Ravl.Logic"
//! author="Charles Galambos"

#include "Ravl/Logic/State.hh"
#include "Ravl/HSet.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Set based implementation of a set.
  
  class StateSetBodyC 
    : public StateBodyC
  {
  public:
    StateSetBodyC()
      {}
    //: Default constructor.

    StateSetBodyC(const HSetC<LiteralC> &ndata)
      : data(ndata)
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
    
#if 0
    virtual MinTermC Difference(const StateC &oth) const;
    //: List the differences between this and another state.
    // Positive terms are ones in this state, but not in 'oth'. <p>
    // Negative terms are those in the 'oth' state but not in this one.
#endif
    
    virtual UIntT Size() const;
    //: Return the number of literals in the state.

  protected:
    HSetC<LiteralC> data;
  };

  //! userlevel=Normal
  //: Set based implementation of a set.
  
  class StateSetC 
    : public StateC
  {
  public:
    StateSetC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    StateSetC(bool)
      : StateC(*new StateSetBodyC())
      {}
    //: Constructor.

    StateSetC(const HSetC<LiteralC> &ndata)
      : StateC(*new StateSetBodyC(ndata))
      {}
    //: Constructor.
    
  protected:
  };
  
}

#endif

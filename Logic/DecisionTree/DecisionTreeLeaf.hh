// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_DECISIONTREELEAF_HEADER
#define RAVLLOGIC_DECISIONTREELEAF_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/DecisionTreeElement.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Decision tree body.
  
  class DecisionTreeLeafBodyC 
    : public DecisionTreeElementBodyC
  {
  public:
    DecisionTreeLeafBodyC();
    //: Default constructor.

    DecisionTreeLeafBodyC(const StateC &state,const LiteralC &decision);
    //: Constructor.
    
    LiteralC &Decision()
    { return decision; }
    //: Value of decision of leaf.
    
    virtual bool IsLeaf() const
    { return true; }
    //: Is this a leaf in the decision tree ?

  protected:
    // List of examples.
    LiteralC decision; // Value of decision at the leaf.
  };
  
  //! userlevel=Develop
  //: Decision tree.
  
  class DecisionTreeLeafC 
    : public DecisionTreeElementC
  {
  public:
    DecisionTreeLeafC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    DecisionTreeLeafC(const StateC &state,const LiteralC &decision)
      : DecisionTreeElementC(*new DecisionTreeLeafBodyC(state,decision))
    {}
    //: Constructor.
    
    DecisionTreeLeafC(const DecisionTreeElementC &oth)
      : DecisionTreeElementC(oth)
    {
      if(dynamic_cast<DecisionTreeElementBodyC *>(&Body()) == 0)
	Invalidate();
    }
    //: Base constructor.
    // creates an invalid handle if DecisionTreeElement isn't a leaf.
    
  protected:
    DecisionTreeLeafC(DecisionTreeLeafBodyC &bod)
      : DecisionTreeElementC(bod)
      {}
    //: Body constructor.
    
    DecisionTreeLeafBodyC &Body()
    { return static_cast<DecisionTreeLeafBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.
    
    const DecisionTreeLeafBodyC &Body() const
    { return static_cast<const DecisionTreeLeafBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.
    
  public:
    
    LiteralC &Decision()
    { return Body().Decision(); }
    //: Value of decision of leaf.
   
  };
  
}

#endif

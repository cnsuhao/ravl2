// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_DECISIONTREEBINARY_HEADER
#define RAVLLOGIC_DECISIONTREEBINARY_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/DecisionTreeElement.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Decision tree body.
  
  class DecisionTreeBranchBinaryBodyC 
    : public DecisionTreeElementBodyC
  {
  public:
    DecisionTreeBranchBinaryBodyC();
    //: Default constructor.
    
    virtual DecisionTreeElementC Find(const StateC &state);
    //: Find next level in the decision tree for given 'state'.
    
  protected:
    LiteralC test; // Test for branch.
    DecisionTreeElementC children[2]; // 0-False 1-True.
  };
  
  //! userlevel=Develop
  //: Decision tree.
  
  class DecisionTreeBranchBinaryC 
    : public DecisionTreeElementC
  {
  public:
    DecisionTreeBranchBinaryC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
  protected:
    DecisionTreeBranchBinaryC(DecisionTreeBranchBinaryBodyC &bod)
      : DecisionTreeElementC(bod)
      {}
    //: Body constructor.
    
    DecisionTreeBranchBinaryBodyC &Body()
    { return static_cast<DecisionTreeBranchBinaryBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.
    
    const DecisionTreeBranchBinaryBodyC &Body() const
    { return static_cast<const DecisionTreeBranchBinaryBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}

#endif

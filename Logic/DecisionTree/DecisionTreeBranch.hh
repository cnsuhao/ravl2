// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_DECISIONTREBRANCH_HEADER
#define RAVLLOGIC_DECISIONTREBRANCH_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/DecisionTree/DecisionTreeBranch.hh"
//! author="Charles Galambos"
//! docentry="Ravl.Logic.Decision Tree"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/DecisionTreeElement.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Decision tree body.
  
  class DecisionTreeBranchBodyC 
    : public DecisionTreeElementBodyC
  {
  public:
    DecisionTreeBranchBodyC();
    //: Default constructor.
    
    virtual void Dump(ostream &out,IntT level = 0) const;
    //: Dump node in human readable form,
    
  protected:
    
  };
  
  //! userlevel=Develop
  //: Decision tree.
  
  class DecisionTreeBranchC 
    : public DecisionTreeElementC
  {
  public:
    DecisionTreeBranchC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
  protected:
    DecisionTreeBranchC(DecisionTreeBranchBodyC &bod)
      : DecisionTreeElementC(bod)
    {}
    //: Body constructor.
    
    DecisionTreeBranchBodyC &Body()
    { return static_cast<DecisionTreeBranchBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.

    const DecisionTreeBranchBodyC &Body() const
    { return static_cast<const DecisionTreeBranchBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}

#endif

// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_DECISIONTREEBASE_HEADER
#define RAVLLOGIC_DECISIONTREEBASE_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/DecisionTree/DecisionTreeBase.hh"
//! author="Charles Galambos"
//! docentry="Ravl.Logic.Decision Tree"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/DecisionTreeElement.hh"
#include "Ravl/Logic/DecisionTreeLeaf.hh"
#include "Ravl/Logic/Discriminator.hh"
#include "Ravl/PatternRec/DataSet2.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Decision tree body.
  
  class DecisionTreeBaseBodyC 
    : public RCBodyC
  {
  public:
    DecisionTreeBaseBodyC();
    //: Default constructor.
    // Use the default discriminator.
    
    DecisionTreeBaseBodyC(const DiscriminatorC &desc);
    //: Constructor.
    
    DecisionTreeLeafC Find(const StateC &state);
    //: Find the decision for given 'state'.
    
    bool Add(const StateC &state,const LiteralC &decision);
    //: Add a new example to the tree.
    
    void Train(const DataSet2C<SampleStateC,SampleLiteralC > &data);
    //: Train the decision tree with the new data.
    
    void SetDiscriminator(const DiscriminatorC &desc);
    //: Set the discriminator to use for training.

    void Dump(ostream &out) const;
    //: Dump the tree in a human readable form to stream out.
    
    StateC BuildRuleSet() const;
    //: Build a rule set from the decision tree.
    
  protected:
    DiscriminatorC discriminator; // Used in building the tree.
    DecisionTreeElementC root; // Root of tree.    
  };
  
  //! userlevel=Advanced
  //: Decision tree.
  
  class DecisionTreeBaseC 
    : public RCHandleC<DecisionTreeBaseBodyC>
  {
  public:
    DecisionTreeBaseC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    DecisionTreeBaseC(bool)
      : RCHandleC<DecisionTreeBaseBodyC>(* new DecisionTreeBaseBodyC())
    {}
    //: Constructor.
    // Create a decision tree with the default discriminator.

    DecisionTreeBaseC(const DiscriminatorC &desc)
      : RCHandleC<DecisionTreeBaseBodyC>(* new DecisionTreeBaseBodyC(desc))
    {}
    //: Constructor.
    
  protected:
    DecisionTreeBaseC(DecisionTreeBaseBodyC &bod)
      : RCHandleC<DecisionTreeBaseBodyC>(bod)
      {}
    //: Body constructor.
    
    DecisionTreeBaseBodyC &Body()
    { return RCHandleC<DecisionTreeBaseBodyC>::Body(); }
    //: Access body.

    const DecisionTreeBaseBodyC &Body() const
    { return RCHandleC<DecisionTreeBaseBodyC>::Body(); }
    //: Access body.
    
  public:
    
    DecisionTreeLeafC Find(const StateC &state)
    { return Body().Find(state); }
    //: Find the decision for given 'state'.
    
    bool Add(const StateC &state,const LiteralC &decision)
    { return Body().Add(state,decision); }
    //: Add a new example to the tree.
    
    void Train(const DataSet2C<SampleStateC,SampleLiteralC> &data)
    { Body().Train(data); }
    //: Train the decision tree with the new data.
    
    void SetDiscriminator(const DiscriminatorC &desc)
    { Body().SetDiscriminator(desc); }
    //: Set the discriminator to use for training.
    
    void Dump(ostream &out) const;
    //: Dump the tree in a human readable form to stream out.
    
    StateC BuildRuleSet() const
    { return Body().BuildRuleSet(); }
    //: Build a rule set from the decision tree.

  };
  
}

#endif

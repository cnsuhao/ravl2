// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/DecisionTreeBase.hh"
#include "Ravl/Logic/DecisionTreeLeaf.hh"
#include "Ravl/PatternRec/DataSet2Iter.hh"

#define DODEBUG 1

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {
  
  //: Default constructor.
  // Use the default discriminator.
  
  DecisionTreeBaseBodyC::DecisionTreeBaseBodyC() 
    : discriminator(true)
  {}
  
  //: Constructor.
  DecisionTreeBaseBodyC::DecisionTreeBaseBodyC(const DiscriminatorC &desc)
    : discriminator(desc)
  {}

  //: Find the decision for given 'state'.
  
  DecisionTreeLeafC DecisionTreeBaseBodyC::Find(const StateC &state) {
    DecisionTreeElementC at = root;
    while(at.IsValid()) {
      at = at.Find(state);
      if(at.IsLeaf())
	return DecisionTreeLeafC(at);
    }
    RavlAssert(0); // Should never fail.
    return DecisionTreeLeafC(); // Failed.
  }
  
  //: Add a new example to the tree.
  
  bool DecisionTreeBaseBodyC::Add(const StateC &state,const LiteralC &decision) {
    ONDEBUG(cerr << "DecisionTreeBaseBodyC::Add(state,decision), Called \n");
    DecisionTreeElementC next,at = root;
    while(at.IsValid()) {
      next = at.Find(state);
      if(next.IsLeaf()) {
	DecisionTreeLeafC leaf(next);
	if(leaf.Decision() == decision) {
	  RavlAssert(leaf.Examples().IsValid());
	  leaf.Examples().AddExample(state,decision);
	  return true; // Already 
	}
	// Need to replace the leaf.
	//discriminator.Distinguish( 
      }
      next = at;
    }
    root = DecisionTreeLeafC(state,decision);
    return false;
  }


  //: Train the decision tree with the new data.
  
  void DecisionTreeBaseBodyC::Train(const DataSet2C<SampleStateC,SampleLiteralC> &data) {
    ONDEBUG(cerr << "DecisionTreeBaseBodyC::Train(), Called \n");
    for(DataSet2IterC<SampleStateC,SampleLiteralC> it(data);it;it++)
      Add(it.Data1(),it.Data2());
  }

  //: Dump the tree in a human readable form to stream out.
  
  void DecisionTreeBaseBodyC::Dump(ostream &out) const {
    ONDEBUG(cerr << "DecisionTreeBaseBodyC::Dump(), Called \n");
    out << "Decision tree:\n";
    if(!root.IsValid()) {
      out << " Empty\n";
      return ;
    }
    root.Dump(out,0);
  }


  //------------------------------------------------------------------
  
  void DecisionTreeBaseC::Dump(ostream &out) const { 
    if(!IsValid()) {
      cerr << "(NIL TREE)\n";
      return ;
    }
    Body().Dump(out); 
  }
  //: Dump the tree in a human readable form to stream out.

}

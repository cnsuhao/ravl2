// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/StateAndIter.hh"
#include "Ravl/Logic/LiteralIter1.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {
  
  StateAndIterBodyC::StateAndIterBodyC(const StateC &nstate,const AndC &nand,const BindSetC &bs) 
    : state(nstate),
      lAnd(nand),
      binds(bs)
  {
    initalBm = binds.Mark();
    First();
  }
  
  //: Goto next valid solution.
  // Its not clear we have to worry about the bind marks, the iterator's
  // should deal with this themselves.
  
  bool StateAndIterBodyC::NextValid() {
    ONDEBUG(cerr << "StateAndIterBodyC::NextValid(), Called. MaxTerms:" << lAnd.Size() << "\n");
    RavlAssert(lAnd.Size() != 0); // What to do with zero terms ?
    int maxTerm = lAnd.Size() - 1;
    while(!stack.IsEmpty()) {
      if(!stack.Top().iter.IsElm()) {
	stack.DelTop();
	continue; // Backtrack.
      }
      int nextTerm = stack.Top().termNo + 1;
      if(nextTerm <= maxTerm) {
	BindMarkT mark = binds.Mark();
	ONDEBUG(cerr << "StateAndIterBodyC::NextValid(), Iterating term " << nextTerm <<" " << lAnd.Terms()[nextTerm] << " \n");
	LiteralIterC lit = state.ListFilter(lAnd.Terms()[nextTerm],binds);
	ONDEBUG(cerr << "Binds= " << binds << "\n");
	if(!lit.IsElm()) { // Any solutions ?
	  stack.DelTop(); // Reached a dead-end, backtrack and try again.
	  continue;
	}
	stack.Push(StateAndBackTrackPointC(mark,nextTerm,lit));
	if(nextTerm == maxTerm)
	  return true;
	continue;
      }
      if(stack.Top().iter.Next()) {
	ONDEBUG(cerr << "StateAndIterBodyC::NextValid(), one more solution... \n");
	return true;
      }
    }
    ONDEBUG(cerr << "StateAndIterBodyC::NextValid(), No more solutions. \n");
    binds.Undo(initalBm); // Make sure all binds are cleared.
    return false;
  }
  
  //: Goto next data element.
  // returns true if next element is valid.
  
  bool StateAndIterBodyC::Next() {
    ONDEBUG(cerr << "StateAndIterBodyC::Next(), Called. \n");
    if(stack.Top().iter.Next())
      return true;
    RavlAssert(!stack.Top().iter.IsElm());
    return NextValid();
  }
    
  //: Goto first data element.
  // returns true if next element is valid.
  
  bool StateAndIterBodyC::First() {
    ONDEBUG(cerr << "StateAndIterBodyC::First(), Called. \n");
    stack.Empty();
    binds.Undo(initalBm);
    ONDEBUG(cerr << "StateAndIterBodyC::First(), Iterating term " << 0 <<" " << lAnd.Terms()[0] << " \n");
    stack.Push(StateAndBackTrackPointC(initalBm,0,state.ListFilter(lAnd.Terms()[0],binds)));
    ONDEBUG(cerr << "Binds= " << binds << "\n");
    return NextValid();
  }
  
  //: At a valid element ?
  // returns true if iterator is at a valid
  // element.
  
  bool StateAndIterBodyC::IsElm() const {
    return !stack.IsEmpty();
  }
  
  //: Get current literal.
  
  LiteralC StateAndIterBodyC::Data() {
    RavlAssert(!stack.IsEmpty());
    return stack.Top().iter.Data();
  }
  
  //: Access binds associated with solution.

  BindSetC &StateAndIterBodyC::Binds() {
    return stack.Top().iter.Binds();
  }
  
  //: Access binds associated with solution.
  const BindSetC &StateAndIterBodyC::Binds() const {
    return stack.Top().iter.Binds();
  }

}
